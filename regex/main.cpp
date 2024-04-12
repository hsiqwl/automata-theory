#include <iostream>
#include <fstream>
#include "regex_tokenizer.h"
#include "dfa_builder.h"
#include "dfa.h"

int main() {
    try {
        regex_tokenizer regex{"a{2,3}"};
        dfa obj = dfa_builder::build(regex);
        std::fstream file("dfa.dot", std::ios::out);
        file.setf(std::ios_base::boolalpha);
        file << "digraph {\n";
        for(auto& s: obj.get_states()){
            for(auto& t: s->get_transitions()){
                auto id_from = s.get();
                auto id_to = t.get_to_state().get();
                std::string matching = t.get_transition_matcher()->matching_string();
                file << id_from << "->" << id_to << "[label = " << matching<<", accepting = "<<obj.state_is_accepting(t.get_to_state())<<"]\n";
            }
        }
        file << "}";
        file.close();
    } catch (std::exception &e) {
        std::cout << e.what()<<'\n';
    }
}
