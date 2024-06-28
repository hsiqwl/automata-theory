#ifndef INTERPRETER_SYMBOL_H
#define INTERPRETER_SYMBOL_H
#include <string>
#include <string_view>
#include <fstream>

class symbol{
protected:
    std::string name;

public:
    symbol(std::string_view name);

    const std::string& get_name() const;

    virtual ~symbol() = default;

    virtual void print(std::ostream& stream) const = 0;
};


#endif //INTERPRETER_SYMBOL_H
