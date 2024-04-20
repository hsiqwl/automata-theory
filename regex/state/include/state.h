#ifndef REGEX_STATE_H
#define REGEX_STATE_H
#include <array>
#include <memory>

class state{
public:
    state();

    bool is_accepting() const noexcept;

    void add_transition(char c, const std::shared_ptr<state>& to_state);

    const state& get_following_state(char c);

    void set_acceptance(bool acceptance);

private:
    std::array<std::shared_ptr<state>, 256> transitions;

    bool accepting;
};

#endif //REGEX_STATE_H
