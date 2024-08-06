#include "activation_record.h"

ActivationRecord::ActivationRecord(std::string_view record_name, size_t nesting_level)
    :record_name_(record_name), nesting_level_(nesting_level) {}

Value &ActivationRecord::GetValue(const std::string &var_name) {
    return records_.at(var_name);
}

bool ActivationRecord::AssociatedValueExists(const std::string &var_name) {
    return records_.contains(var_name);
}

size_t ActivationRecord::GetNestingLevel() const noexcept {
    return nesting_level_;
}

const std::string &ActivationRecord::GetRecordName() const noexcept {
    return record_name_;
}

void ActivationRecord::PutValue(const std::string &var_name, Value &&value) {
    records_.emplace(var_name, std::move(value));
}