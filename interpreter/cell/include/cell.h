#ifndef INTERPRETER_CELL_H
#define INTERPRETER_CELL_H

enum class direction{
    top,
    down,
    right,
    left
};

class cell{
private:
    bool top_exists;

    bool down_exists;

    bool right_exists;

    bool left_exists;

    bool top_changeable;

    bool down_changeable;

    bool right_changeable;

    bool left_changeable;

public:
    cell();

    cell(bool top, bool down, bool right, bool left);

    void set_changeability(direction dir, bool changeable);

    [[nodiscard]] bool get_changeability(direction dir) const;

    [[nodiscard]] bool wall_exists(direction dir) const;

    cell operator - (const cell& other) const;

    cell operator / (const cell& other) const;

    cell operator % (const cell& other) const;

    bool operator == (const cell& other) const;
};

#endif //INTERPRETER_CELL_H
