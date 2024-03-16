#ifndef VALIDATOR_CREATE_SCANNER_H
#define VALIDATOR_CREATE_SCANNER_H
#include "create_scanner_sm.h"
#include "../../basic_scanner/basic_scanner.h"

class create_scanner: public basic_scanner{
private:
    create_scannerContext _fsm;
public:
    create_scanner(): basic_scanner(), _fsm(*this){};
    bool validate_string(const std::string& string) override;
};

#endif //VALIDATOR_CREATE_SCANNER_H
