#ifndef REGEX_NFA_H
#define REGEX_NFA_H
#include <vector>
#include <unordered_set>
#include <array>
#include <algorithm>

class nfa{
private:
    std::vector<std::unordered_set<size_t>> follow_pos;

    std::array<std::unordered_set<size_t>, 256> char_to_pos;

    std::unordered_set<size_t> initial_pos;

    std::unordered_set<size_t> curr_pos;

    std::unordered_set<size_t> last_pos;

public:
    nfa() = default;

    nfa(std::vector<std::unordered_set<size_t>>&& follow_pos,
        std::array<std::unordered_set<size_t>, 256>&& char_to_pos,
        std::unordered_set<size_t>&& initial_pos, std::unordered_set<size_t>&& last_pos);

    void consume_input(char c);

    bool is_in_accepting_state() const noexcept;

    void reset() noexcept;
};

#endif //REGEX_NFA_H
