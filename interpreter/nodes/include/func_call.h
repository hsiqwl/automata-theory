#ifndef INTERPRETER_FUNC_CALL_H
#define INTERPRETER_FUNC_CALL_H
#include "node_interface.h"
#include "printable_interface.h"
#include <vector>

class FuncCall: public INode, public IPrintable {

private:
    std::string func_name_;

    std::vector<std::unique_ptr<INode>> args_;

};

#endif //INTERPRETER_FUNC_CALL_H
