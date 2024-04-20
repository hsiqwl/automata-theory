#include "dfa_builder.h"

std::vector<token> dfa_builder::infix_to_postfix(std::pair<regex_tokenizer::token_iterator, regex_tokenizer::token_iterator>&& iterators) {
    std::stack<token> operator_stack;
    std::vector<token> postfix_token_sequence;
    for(auto& token_ptr = iterators.first; token_ptr != iterators.second; ++token_ptr) {
        switch (token_ptr->get_type()) {
            case token::token_type::terminal:
                handle_terminal(postfix_token_sequence, *token_ptr);
                break;
            case token::token_type::left_parenthesis:
                handle_left_parenthesis(operator_stack, *token_ptr);
                break;
            case token::token_type::op:
                handle_operator(operator_stack, postfix_token_sequence, *token_ptr);
                break;
            case token::token_type::right_parenthesis:
                handle_right_parenthesis(operator_stack, postfix_token_sequence);
                break;
        }
    }
    while (!operator_stack.empty()) {
        postfix_token_sequence.emplace_back(std::move(operator_stack.top()));
        operator_stack.pop();
    }

    return postfix_token_sequence;
}

void dfa_builder::handle_terminal(std::vector<token>& postfix_token_sequence, const token& terminal_token) {
    postfix_token_sequence.emplace_back(terminal_token);
}

void dfa_builder::handle_left_parenthesis(std::stack<token> &operator_stack, const token& parenthesis_token) {
    operator_stack.push(parenthesis_token);
}

void dfa_builder::handle_operator(std::stack<token> &operator_stack, std::vector<token> &postfix_token_sequence,
                                  const token& op_token) {
    while (!operator_stack.empty() && operator_stack.top().get_type() != token::token_type::left_parenthesis) {
        unsigned short top_op_precedence = operator_stack.top().get_operator_info().get_precedence();
        unsigned short curr_op_precedence = op_token.get_operator_info().get_precedence();
        if (top_op_precedence >= curr_op_precedence) {
            postfix_token_sequence.emplace_back(std::move(operator_stack.top()));
            operator_stack.pop();
        } else {
            break;
        }
    }
    operator_stack.push(op_token);
}

void dfa_builder::handle_right_parenthesis(std::stack<token> &operator_stack, std::vector<token> &postfix_token_sequence) {
    while (operator_stack.top().get_type() != token::token_type::left_parenthesis) {
        postfix_token_sequence.emplace_back(std::move(operator_stack.top()));
        operator_stack.pop();
    }
    operator_stack.pop();
}

void dfa_builder::calculate_nullability_and_positions(std::vector<token> &postfix_token_sequence) {
    pos_counter = 1;
    for (auto iter = postfix_token_sequence.begin(); iter != postfix_token_sequence.end(); ++iter) {
        if (iter->get_type() == token::token_type::terminal) {
            iter->set_nullability(false);
            set_positions_for_terminal(*iter);
        } else {
            switch (iter->get_operator_info().get_op_type()) {
                case operator_info::operator_type::alternation: {
                    set_nullability_for_alternation(*iter, *(iter - 2), *(iter - 1));
                    set_positions_for_alternation(*iter, *(iter - 2), *(iter - 1));
                    break;
                }
                case operator_info::operator_type::concatenation: {
                    set_nullability_for_concatenation(*iter, *(iter - 2), *(iter - 1));
                    set_positions_for_concatenation(*iter, *(iter - 2), *(iter - 1));
                    break;
                }
                case operator_info::operator_type::repetition: {
                    set_nullability_for_repetition(*iter, *(iter - 1));
                    set_positions_for_repetition(*iter, *(iter - 1));
                    break;
                }
            }
        }
    }
}

void dfa_builder::set_nullability_for_alternation(token &operation_token, const token &left_child,
                                                 const token &right_child) {
    operation_token.set_nullability(left_child.is_nullable() || right_child.is_nullable());
}

void dfa_builder::set_nullability_for_concatenation(token &operation_token, const token &left_child,
                                                   const token &right_child) {
    operation_token.set_nullability(left_child.is_nullable() || right_child.is_nullable());
}

void dfa_builder::set_nullability_for_repetition(token &operation_token, const token &child) {
    operation_token.set_nullability(operation_token.get_operator_info().get_min_num_of_repetitions() == 0);
}

void dfa_builder::set_positions_for_terminal(token &terminal) {
    if(!terminal.get_terminal_info().is_character_class()){
        terminal.add_to_first_pos(pos_counter);
        terminal.add_to_last_pos(pos_counter);
        ++pos_counter;
    }
    else{
        auto start = static_cast<size_t>(terminal.get_terminal_info().get_range_min());
        auto end = static_cast<size_t>(terminal.get_terminal_info().get_range_max())
                + terminal.get_terminal_info().get_singles().size();
        for(size_t i = start; i <= end; ++i){
            terminal.add_to_first_pos(pos_counter);
            terminal.add_to_last_pos(pos_counter);
            ++pos_counter;
        }
    }
}

void dfa_builder::set_positions_for_concatenation(token &operation_token, const token &left_child,
                                                  const token &right_child) {
    if(left_child.is_nullable()){
        for(auto pos: right_child.get_first_pos())
            operation_token.add_to_first_pos(pos);
    }
    for(auto pos: left_child.get_first_pos())
        operation_token.add_to_first_pos(pos);

    if(right_child.is_nullable()){
        for(auto pos: left_child.get_last_pos())
            operation_token.add_to_last_pos(pos);
    }
    for(auto pos: right_child.get_last_pos()){
        operation_token.add_to_last_pos(pos);
    }
}

void dfa_builder::set_positions_for_alternation(token &operation_token, const token &left_child,
                                                const token &right_child) {
    for(auto pos: left_child.get_first_pos()){
        operation_token.add_to_first_pos(pos);
    }
    for(auto pos: right_child.get_first_pos()){
        operation_token.add_to_first_pos(pos);
    }
    for(auto pos: left_child.get_last_pos()){
        operation_token.add_to_last_pos(pos);
    }
    for(auto pos: right_child.get_last_pos()){
        operation_token.add_to_last_pos(pos);
    }
}

void dfa_builder::set_positions_for_repetition(token &operation_token, const token &child) {
    size_t min_rep = operation_token.get_operator_info().get_min_num_of_repetitions();
    size_t max_rep = operation_token.get_operator_info().get_max_num_of_repetitions();
    if (min_rep != 0 && max_rep != operator_info::get_max_possible_num_of_repetitions()) {
        set_positions_for_closed_range(operation_token, child);
    } else if (min_rep == 0 && max_rep == 0) {
        set_positions_for_open_range(operation_token, child);
    } else if (min_rep == 0 && max_rep != operator_info::get_max_possible_num_of_repetitions()) {
        set_positions_for_right_open_range(operation_token, child);
    } else {
        set_positions_for_left_open_range(operation_token, child);
    }
}

void dfa_builder::set_positions_for_closed_range(token &operation_token, const token &child) {
    size_t min_rep = operation_token.get_operator_info().get_min_num_of_repetitions();
    size_t max_rep = operation_token.get_operator_info().get_max_num_of_repetitions();
    size_t sub_expression_length = child.get_sub_expression_length();

    size_t first_pos_offset = 0;
    size_t last_pos_offset = (min_rep - 1) * sub_expression_length;

    for (size_t i = 0; i <= max_rep - min_rep; ++i) {
        for (auto pos: child.get_first_pos()) {
            operation_token.add_to_first_pos(pos + first_pos_offset);
            pos_counter = pos + first_pos_offset;
        }
        for (auto pos: child.get_last_pos()) {
            operation_token.add_to_last_pos(pos + last_pos_offset);
        }
        first_pos_offset += (min_rep + i) * sub_expression_length;
        last_pos_offset += (min_rep + i + 1) * sub_expression_length;
    }
}

void dfa_builder::set_positions_for_open_range(token &operation_token, const token &child) {
    for(auto pos: child.get_first_pos()){
        operation_token.add_to_first_pos(pos);
    }
    for(auto pos: child.get_last_pos()){
        operation_token.add_to_last_pos(pos);
    }
}

void dfa_builder::set_positions_for_left_open_range(token &operation_token, const token &child) {
    operator_info augmented_info(operator_info::operator_type::repetition);
    augmented_info.set_min_num_of_repetitions(operation_token.get_operator_info().get_max_num_of_repetitions());
    augmented_info.set_max_num_of_repetitions(operation_token.get_operator_info().get_max_num_of_repetitions());
    operation_token.set_operator_info(augmented_info);
    set_positions_for_closed_range(operation_token, child);

    size_t sub_expression_length = child.get_sub_expression_length();
    size_t last_pos_size = operation_token.get_last_pos().size();
    for (int i = 0; i < last_pos_size; ++i) {
        operation_token.add_to_last_pos(sub_expression_length + operation_token.get_last_pos()[i]);
    }
}

void dfa_builder::set_positions_for_right_open_range(token &operation_token, const token &child) {
    operator_info augmented_info(operator_info::operator_type::repetition);
    augmented_info.set_min_num_of_repetitions(1);
    augmented_info.set_max_num_of_repetitions(operation_token.get_operator_info().get_max_num_of_repetitions());
    operation_token.set_operator_info(augmented_info);
    set_positions_for_closed_range(operation_token, child);
}