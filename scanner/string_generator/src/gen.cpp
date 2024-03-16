#include "generator.h"
#include <iostream>
int main(int argc, char* argv[]){
    generator _gen;
    if(argc > 1) {
        size_t number_of_string = std::stoi(argv[1]);
        for(size_t i = 0; i < number_of_string; ++i){
            std::cout << _gen.generate_string() <<'\n';
        }
    }else{
        throw std::invalid_argument("invalid parameter\n");
    }
    return 0;
}