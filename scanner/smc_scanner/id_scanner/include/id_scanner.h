#ifndef VALIDATOR_ID_SCANNER_H
#define VALIDATOR_ID_SCANNER_H
#include "../../basic_scanner/basic_scanner.h"
#include "id_scanner_sm.h"
class id_scanner: public basic_scanner{
private:
    id_scannerContext _fsm;

public:
    id_scanner(): basic_scanner(), _fsm(*this) {}
    bool validate_string(const std::string& string) override;
};

#endif //VALIDATOR_ID_SCANNER_H
