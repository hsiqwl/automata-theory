#ifndef VALIDATOR_GENERATOR_H
#define VALIDATOR_GENERATOR_H
#include <random>
#include <string>
#include <algorithm>
class generator {
private:
    std::random_device engine;
    const static inline std::string forbidden_symbols = "!@#$%^&*'+-|/\?;:<=>[]{}~";
    short max_whitespace_number = 5;
    short max_id_length = 10;
    short max_argument_number = 5;
    float valid_string_probability = 0.5;

    std::string generate_id();
    static std::string generate_create_string();
    static std::string generate_join_string();
    std::string generate_argument_list();
    std::string generate_first_pattern();
    std::string generate_second_pattern();
    void add_whitespaces(std::string& str);
    void make_string_invalid(std::string& str);

public:
    generator() = default;
    generator(short max_id_length, short max_argument_number, short max_whitespace_number, float valid_string_probability);
    std::string generate_string();
    void set_probability_of_valid_string(float& probability);
};

#endif //VALIDATOR_GENERATOR_H
