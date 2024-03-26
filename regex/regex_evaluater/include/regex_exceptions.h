#ifndef REGEX_REGEX_EXCEPTIONS_H
#define REGEX_REGEX_EXCEPTIONS_H

#include <exception>
#include <string_view>


class regex_exception: public std::exception{
protected:
    inline const static std::string_view bad_alternation = "bad '|' (alternation) operation, check arguments";

    inline const static std::string_view bad_concatenation = "bad '.' (concatenation) operation, check arguments";

    inline const static std::string_view bad_star = "bad '*' (kleene closure) operation, check arguments";

    inline const static std::string_view bad_repetition = "bad '{}' (repetition) operation, check arguments";

    inline const static std::string_view bad_optional = "bad '?' (optional) operation, check arguments";

    inline const static std::string_view unknown_escape_seq = "unknown escape sequence";
};

#endif //REGEX_REGEX_EXCEPTIONS_H
