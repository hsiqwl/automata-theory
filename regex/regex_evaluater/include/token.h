#ifndef REGEX_TOKEN_H
#define REGEX_TOKEN_H
#include <vector>
#include <variant>
#include <algorithm>
#include "terminal_info.h"
#include "operator_info.h"

class token{
public:
    enum class token_type{
        op,
        left_parenthesis,
        right_parenthesis,
        terminal
    };

    explicit token(token_type type);

    [[nodiscard]] token_type get_type() const noexcept;

    void set_nullability(bool token_nullability);

    [[nodiscard]] bool is_nullable() const noexcept;

    void add_to_first_pos(size_t pos);

    void add_to_last_pos(size_t pos);

    [[nodiscard]] const std::vector<size_t>& get_first_pos() const noexcept;

    [[nodiscard]] const std::vector<size_t>& get_last_pos() const noexcept;

    void set_operator_info(const operator_info& info);

    void set_terminal_info(const terminal_info& info);

    const terminal_info& get_terminal_info() const;

    const operator_info& get_operator_info() const;

    size_t get_sub_expression_length() const noexcept;

private:
    token_type type;

    bool nullability;

    std::vector<size_t> first_pos;

    std::vector<size_t> last_pos;

    std::variant<terminal_info, operator_info> token_info;
};

#endif //REGEX_TOKEN_H
