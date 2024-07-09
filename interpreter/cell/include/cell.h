#ifndef INTERPRETER_CELL_H
#define INTERPRETER_CELL_H

enum class Direction{
    top,
    down,
    right,
    left
};

class Cell{
private:
    bool top_;

    bool down_;

    bool right_;

    bool left_;

    bool top_changeable;

    bool down_changeable;

    bool right_changeable;

    bool left_changeable;

public:
    Cell();

    Cell(bool top, bool down, bool right, bool left);

    void SetChangeability(Direction dir, bool changeable);

    [[nodiscard]] bool GetChangeability(Direction dir) const;

    [[nodiscard]] bool WallExists(Direction dir) const;

    Cell operator - (const Cell& other) const;

    Cell operator / (const Cell& other) const;

    Cell operator % (const Cell& other) const;

    bool operator == (const Cell& other) const;
};

#endif //INTERPRETER_CELL_H
