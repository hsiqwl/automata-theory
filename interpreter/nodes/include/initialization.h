#ifndef INTERPRETER_INITIALIZATION_H
#define INTERPRETER_INITIALIZATION_H
#include "node_interface.h"
#include <any>

class InitializationNode: public INode{


private:
    std::string var_to_init_;

    std::any value_;
};

#endif //INTERPRETER_INITIALIZATION_H
