#include "../include/generator.h"

std::string generator::generate_id() {
    std::string id;
    short length = engine() % max_id_length + 1;
    char first_char =
            engine() % 2 ? 'a' + engine() % 26 : 'A' + engine() % 26;
    id += first_char;
    for (int i = 1; i < length; ++i) {
        char next_char =
                engine() % 3 ? 'a' + engine() % 26 : '0' + engine() % 10;
        if (next_char == ' ') {
            next_char = '.';
        }
        id += next_char;
    }
    return id;
}

std::string generator::generate_create_string() {
    std::string create_string = "create";
    std::transform(create_string.cbegin(), create_string.cend(), create_string.begin(),
                   [](char c) {
                       if (std::random_device{}() % 2) {
                           return std::tolower(c);
                       }
                       return std::toupper(c);
                   });
    return create_string;
}

std::string generator::generate_join_string() {
    std::string join_string = "join";
    std::transform(join_string.cbegin(), join_string.cend(), join_string.begin(),
                   [](char c) {
                       if (std::random_device{}() % 2) {
                           return std::tolower(c);
                       }
                       return std::toupper(c);
                   });
    return join_string;
}

std::string generator::generate_argument_list() {
    std::string argument_list = "(";
    short num_of_arguments = engine() % max_argument_number + 1;
    for (int i = 0; i < num_of_arguments; ++i) {
        argument_list += generate_id();
        if (i < num_of_arguments - 1) {
            argument_list += ", ";
        }
    }
    argument_list += ")";
    return argument_list;
}

std::string generator::generate_first_pattern(){
    std::string result{generate_create_string()};
    add_whitespaces(result);
    result += generate_id();
    result += generate_argument_list();
    return result;
}

std::string generator::generate_second_pattern(){
    std::string result;
    result += generate_id();
    if(engine()%2){
        add_whitespaces(result);
        result += generate_join_string();
        add_whitespaces(result);
        result += generate_id();
        add_whitespaces(result);
    }else{
        add_whitespaces(result);
    }
    return result;
}

void generator::add_whitespaces(std::string& str) {
    short num_of_whitespaces = engine() % max_whitespace_number + 1;
    str += std::string(num_of_whitespaces, ' ');
}

std::string generator::generate_string() {
    std::string result;
    if(engine() % 2)
        result = generate_first_pattern();
    else
        result =  generate_second_pattern();
    std::bernoulli_distribution distribution{valid_string_probability};
    if(!distribution(engine))
        make_string_invalid(result);
    return result;
}

generator::generator(short max_id_length, short max_argument_number, short max_whitespace_number, float valid_string_probability):
        max_id_length(max_id_length), max_argument_number(max_argument_number),
        max_whitespace_number(max_whitespace_number), valid_string_probability(valid_string_probability), engine(){}

void generator::set_probability_of_valid_string(float &probability) {valid_string_probability = probability;}

void generator::make_string_invalid(std::string &str) {
    for(short i = 0; i < engine() % 10; ++i)
        str.insert(str.begin() + engine() % str.size(), forbidden_symbols[engine() % forbidden_symbols.size()]);
}