#include <iostream>
#include <fstream>
#include "regex_tokenizer.h"
#include "dfa_builder.h"
#include "dfa.h"
#include <format>
#include <cstdint>

int main() {
    try {
        regex_tokenizer regex{"a{1,3}"};
        dfa obj = dfa_builder::build(regex);
        std::fstream file("dfa.dot", std::ios::out);
        file.setf(std::ios_base::boolalpha);
        file << "digraph {\n";
        for(auto& s: obj.get_states()){
            for(auto& t: s->get_transitions()){
                auto id_from = s.get();
                auto id_to = t.get_to_state().get();
                std::string matching = t.get_transition_matcher()->matching_string();
                std::string str = std::format("{}(accepting:{}) -> {}(accepting:{}) [transition={}]\n",
                                              reinterpret_cast<std::uintptr_t>(id_from),
                                              obj.state_is_accepting(s),
                                              reinterpret_cast<std::uintptr_t>(id_to),
                                              obj.state_is_accepting(t.get_to_state()),
                                              matching);
                file << str;
            }
        }
        file << "}";
        file.close();
    } catch (std::exception &e) {
        std::cout << e.what()<<'\n';
    }
}
