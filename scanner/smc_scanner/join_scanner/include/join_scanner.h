#ifndef VALIDATOR_JOIN_SCANNER_H
#define VALIDATOR_JOIN_SCANNER_H
#include "join_scanner_sm.h"
#include "../../basic_scanner/basic_scanner.h"
class join_scanner: public basic_scanner{
private:
    join_scannerContext _fsm;

public:
    join_scanner(): basic_scanner(), _fsm(*this){};
    bool validate_string(const std::string& string) override;
};
#endif //VALIDATOR_JOIN_SCANNER_H
