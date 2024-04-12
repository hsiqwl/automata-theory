#include <iostream>
#include <fstream>
#include "regex_tokenizer.h"
#include "dfa_builder.h"
#include "dfa.h"
#include <format>

int main() {
    try {
        regex_tokenizer regex{"a?"};
        dfa obj = dfa_builder::build(regex);
        std::fstream file("dfa.dot", std::ios::out);
        file << "digraph {\n";
        for(auto& s: obj.get_states()){
            for(auto& t: s->get_transitions()){
                size_t id_from = s->get_state_id();
                size_t id_to = t.get_to_state()->get_state_id();
                std::string matching = t.get_transition_matcher()->matching_string();
                std::string str = std::format("{} -> {} [label=\"{}\"]\n", id_from, id_to, matching);
                file << str;
            }
        }
        file << "}";
        file.close();
    } catch (std::exception &e) {
        std::cout << e.what()<<'\n';
    }
}
