#include "cell.h"

Cell::Cell(bool top, bool down, bool right, bool left) {
    top_ = top;
    down_ = down;
    right_ = right;
    left_ = left;
    top_changeable = true;
    down_changeable = true;
    left_changeable = true;
    right_changeable = true;
}

Cell::Cell(): Cell(false, false, false, false) {}

bool Cell::GetChangeability(Direction dir) const {
    switch (dir) {
        case Direction::top:
            return top_changeable;
        case Direction::down:
            return down_changeable;
        case Direction::right:
            return right_changeable;
        case Direction::left:
            return left_changeable;
    }
}

void Cell::SetChangeability(Direction dir, bool changeable) {
    switch (dir) {
        case Direction::top:
            top_changeable = changeable;
            return;
        case Direction::down:
            down_changeable = changeable;
            return;
        case Direction::right:
            right_changeable = changeable;
            return;
        case Direction::left:
            left_changeable = changeable;
            return;
    }
}

bool Cell::WallExists(Direction dir) const {
    switch (dir) {
        case Direction::top:
            return top_;
        case Direction::down:
            return down_;
        case Direction::right:
            return right_;
        case Direction::left:
            return left_;
    }
}

Cell Cell::operator-(const Cell &other) const {
    bool new_top = top_ ^ other.top_;
    bool new_down = down_ ^ other.down_;
    bool new_right = right_ ^ other.right_;
    bool new_left = left_ ^ other.left_;
    return {new_top, new_down, new_right, new_left};
}

Cell Cell::operator/(const Cell &other) const {
    bool new_top = top_ | other.top_;
    bool new_down = down_ | other.down_;
    bool new_right = right_ | other.right_;
    bool new_left = left_ | other.left_;
    return {new_top, new_down, new_right, new_left};
}

Cell Cell::operator%(const Cell &other) const {
    bool new_top = top_ & other.top_;
    bool new_down = down_ & other.down_;
    bool new_right = right_ & other.right_;
    bool new_left = left_ & other.left_;
    return {new_top, new_down, new_right, new_left};
}

bool Cell::operator==(const Cell &other) const {
    return top_ == other.top_ &&
           down_ == other.down_ &&
           right_ == other.down_ &&
           left_ == other.left_;
}