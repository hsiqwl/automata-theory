#include "../include/info_collector.h"

void info_collector::put_accumulated_info_into_table() {
    if(!accumulated_info.first.empty()) {
        attribute_table.insert_or_assign(accumulated_info.first, accumulated_info.second);
        clear_accumulated_info();
    }
}

void info_collector::accumulate_arg_info(std::string string) {
    accumulated_info.second.emplace_back(std::move(string));
}

void info_collector::accumulate_key_info(std::string string) {
    accumulated_info.first = std::move(string);
}

void info_collector::remember_argument(std::string string) {
    if(info_args.first.empty())
        info_args.first = std::move(string);
    else
        info_args.second = std::move(string);
}

std::optional<std::string> info_collector::get_resulting_info_string() {
    auto first_note = attribute_table.find(info_args.first);
    auto second_note = attribute_table.find(info_args.second);
    if(first_note != attribute_table.end() && second_note != attribute_table.end()){
        add_prefix_to_same_strings(first_note->second, second_note->second, first_note->first, second_note->first);
        std::string res{convert_vector_to_string(first_note->second) + "\n" + convert_vector_to_string(second_note->second)};
        return {std::move(res)};
    }else if(first_note != attribute_table.end()){
        return {convert_vector_to_string(first_note->second)};
    }else if(second_note != attribute_table.end()){
        return {convert_vector_to_string(second_note->second)};
    }else{
        return std::nullopt;
    }
}

void info_collector::clear_accumulated_info() {
    accumulated_info.first.clear();
    accumulated_info.second.clear();
}

void info_collector::clear_info_args() {
    info_args.first.clear();
    info_args.second.clear();
}