#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H
#include "var.h"
#include <vector>

class function: public symbol{
private:
    std::vector<var> params;

    std::string return_type;

public:
    function(std::string_view name, std::string_view return_type);

    function(std::string_view name, std::string_view return_type, std::vector<var>&& params);

    size_t get_param_number() const;

    const std::string& get_return_type() const;

    const var& operator [] (int index) const;

    void print(std::ostream& stream) const override;
};

#endif //INTERPRETER_FUNCTION_H
