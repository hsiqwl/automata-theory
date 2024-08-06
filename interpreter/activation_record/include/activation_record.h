#ifndef INTERPRETER_ACTIVATION_RECORD_H
#define INTERPRETER_ACTIVATION_RECORD_H
#include "value.h"
#include <unordered_map>
#include <string>

class ActivationRecord {
private:
    std::unordered_map<std::string, Value> records_;

    std::string record_name_;

    size_t nesting_level_;

public:
    ActivationRecord(std::string_view record_name = "Global", size_t nesting_level = 1);

    void PutValue(const std::string& var_name, Value&& value);

    Value& GetValue(const std::string& var_name);

    bool AssociatedValueExists(const std::string& var_name);

    const std::string& GetRecordName() const noexcept;

    size_t GetNestingLevel() const noexcept;
};

#endif //INTERPRETER_ACTIVATION_RECORD_H
