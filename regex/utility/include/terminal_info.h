#ifndef REGEX_TERMINAL_INFO_H
#define REGEX_TERMINAL_INFO_H
#include <string>

class terminal_info{
private:
    char range_min;

    char range_max;

    std::string singles;

public:
    terminal_info(char c);

    terminal_info(char min, char max, const std::string& singles);

    char get_range_min() const noexcept;

    char get_range_max() const noexcept;

    std::string get_singles() const noexcept;
};

#endif //REGEX_TERMINAL_INFO_H
