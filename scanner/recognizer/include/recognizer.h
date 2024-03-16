#ifndef VALIDATOR_RECOGNIZER_H
#define VALIDATOR_RECOGNIZER_H
#include <optional>
#include <string>
class recognizer{
public:
    recognizer() = default;
    virtual std::pair<bool, std::optional<std::string>> parse(const std::string& string) = 0;
    virtual ~recognizer() = default;
};

#endif //VALIDATOR_RECOGNIZER_H
