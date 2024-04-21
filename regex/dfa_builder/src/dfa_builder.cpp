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
    operation_token.set_nullability(left_child.is_nullable() && right_child.is_nullable());
}

void dfa_builder::set_nullability_for_repetition(token &operation_token, const token &child) {
    operation_token.set_nullability(operation_token.get_operator_info().get_min_num_of_repetitions() == 0);
}

void dfa_builder::set_positions_for_terminal(token &terminal) {
    if (!terminal.get_terminal_info().is_character_class())
        set_positions_for_single_character(terminal);
    else
        set_positions_for_character_class(terminal);
}

void dfa_builder::set_positions_for_single_character(token &single_character) {
    single_character.add_to_first_pos(pos_counter);
    single_character.add_to_last_pos(pos_counter);
    auto index_in_table = static_cast<size_t>(single_character.get_terminal_info().get_range_min());
    add_character_to_alphabet(single_character.get_terminal_info().get_range_min());
    char_to_pos_table[index_in_table].emplace_back(pos_counter);
    ++pos_counter;
}

void dfa_builder::set_positions_for_character_class(token &character_class) {
    auto start = static_cast<size_t>(character_class.get_terminal_info().get_range_min());
    auto end = static_cast<size_t>(character_class.get_terminal_info().get_range_max());
    for (size_t i = start; i <= end; ++i) {
        character_class.add_to_first_pos(pos_counter);
        character_class.add_to_last_pos(pos_counter);
        char_to_pos_table[i].emplace_back(pos_counter);
        add_character_to_alphabet(static_cast<char>(i));
        ++pos_counter;
    }
    for (auto s: character_class.get_terminal_info().get_singles()) {
        character_class.add_to_first_pos(pos_counter);
        character_class.add_to_last_pos(pos_counter);
        auto index_in_table = static_cast<size_t>(s);
        char_to_pos_table[index_in_table].emplace_back(pos_counter);
        add_character_to_alphabet(s);
        ++pos_counter;
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
    } else if (min_rep == 0 && max_rep == operator_info::get_max_possible_num_of_repetitions()) {
        set_positions_for_open_range(operation_token, child);
    } else if (min_rep == 0 && max_rep != operator_info::get_max_possible_num_of_repetitions()) {
        set_positions_for_left_open_range(operation_token, child);
    } else {
        set_positions_for_right_open_range(operation_token, child);
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
            pos_counter = pos + first_pos_offset + 1;
            char_to_pos_table[get_index_by_position(pos)].emplace_back(pos + first_pos_offset);
        }
        for (auto pos: child.get_last_pos()) {
            operation_token.add_to_last_pos(pos + last_pos_offset);
            char_to_pos_table[get_index_by_position(pos)].emplace_back(pos + last_pos_offset);
            pos_counter = pos + last_pos_offset + 1;
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

void dfa_builder::set_positions_for_right_open_range(token &operation_token, const token &child) {
    operator_info augmented_info(operator_info::operator_type::repetition);
    augmented_info.set_min_num_of_repetitions(operation_token.get_operator_info().get_max_num_of_repetitions());
    augmented_info.set_max_num_of_repetitions(operation_token.get_operator_info().get_max_num_of_repetitions());
    operation_token.set_operator_info(augmented_info);
    set_positions_for_closed_range(operation_token, child);

    size_t sub_expression_length = child.get_sub_expression_length();
    size_t last_pos_size = operation_token.get_last_pos().size();
    for (int i = 0; i < last_pos_size; ++i) {
        size_t pos = operation_token.get_last_pos()[i];
        operation_token.add_to_last_pos(sub_expression_length + pos);
        pos_counter = sub_expression_length + pos + 1;
        char_to_pos_table[get_index_by_position(pos)].emplace_back(sub_expression_length + pos);
    }
}

void dfa_builder::set_positions_for_left_open_range(token &operation_token, const token &child) {
    operator_info augmented_info(operator_info::operator_type::repetition);
    augmented_info.set_min_num_of_repetitions(1);
    augmented_info.set_max_num_of_repetitions(operation_token.get_operator_info().get_max_num_of_repetitions());
    operation_token.set_operator_info(augmented_info);
    set_positions_for_closed_range(operation_token, child);
    augmented_info.set_min_num_of_repetitions();
    operation_token.set_operator_info(augmented_info);
}


std::vector<std::vector<size_t>> dfa_builder::calculate_follow_pos(const std::vector<token> &postfix_token_sequence) {
    std::vector<std::vector<size_t>> follow_pos(pos_counter - 1);
    for (auto iter = postfix_token_sequence.begin(); iter != postfix_token_sequence.end(); ++iter) {
        if (iter->get_type() == token::token_type::op) {
            auto op_type = iter->get_operator_info().get_op_type();
            if (op_type == operator_info::operator_type::concatenation) {
                calculate_follow_pos_for_cat_node(*(iter - 2), *(iter - 1), follow_pos);
            }
            if (op_type == operator_info::operator_type::repetition) {
                calculate_follow_pos_for_star_node(*iter, follow_pos);
            }
        }
    }
    return follow_pos;
}

void dfa_builder::calculate_follow_pos_for_cat_node(const token &left_child, const token &right_child,
                                                    std::vector<std::vector<size_t>> &follow_pos) {
    for(auto pos: left_child.get_last_pos()){
        follow_pos[pos - 1].insert(follow_pos[pos - 1].end(), right_child.get_first_pos().begin(), right_child.get_first_pos().end());
    }
}

void dfa_builder::calculate_follow_pos_for_star_node(const token &star_node,
                                                     std::vector<std::vector<size_t>> &follow_pos) {
    for(auto pos: star_node.get_last_pos()){
        follow_pos[pos - 1].insert(follow_pos[pos - 1].end(), star_node.get_first_pos().begin(), star_node.get_first_pos().end());
    }
}


std::vector<std::vector<size_t>> dfa_builder::get_pre_build_info(std::string_view expression) {
    regex_tokenizer tokenizer(static_cast<std::string>(expression));
    std::vector<token> postfix_token_sequence = infix_to_postfix(tokenizer.get_token_sequence());
    calculate_nullability_and_positions(postfix_token_sequence);
    std::vector<std::vector<size_t>> follow_pos = calculate_follow_pos(postfix_token_sequence);
    return follow_pos;
}

void dfa_builder::add_character_to_alphabet(char c) {
    if (!correct_alphabet.contains(c)) {
        correct_alphabet.push_back(c);
    }
}

size_t dfa_builder::get_index_by_position(size_t pos) {
    for (auto iter = char_to_pos_table.begin(); iter != char_to_pos_table.end(); ++iter) {
        for (auto position: *iter) {
            if (pos == position)
                return std::distance(char_to_pos_table.begin(), iter);
        }
    }
}

