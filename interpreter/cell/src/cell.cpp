#include "cell.h"

cell::cell(bool top, bool down, bool right, bool left) {
    top_exists = top;
    down_exists = down;
    right_exists = right;
    left_exists = left;
    top_changeable = true;
    down_changeable = true;
    left_changeable = true;
    right_changeable = true;
}

cell::cell(): cell(false, false, false, false) {}

bool cell::get_changeability(direction dir) const {
    switch (dir) {
        case direction::top:
            return top_changeable;
        case direction::down:
            return down_changeable;
        case direction::right:
            return right_changeable;
        case direction::left:
            return left_changeable;
    }
}

void cell::set_changeability(direction dir, bool changeable) {
    switch (dir) {
        case direction::top:
            top_changeable = changeable;
            return;
        case direction::down:
            down_changeable = changeable;
            return;
        case direction::right:
            right_changeable = changeable;
            return;
        case direction::left:
            left_changeable = changeable;
            return;
    }
}

bool cell::wall_exists(direction dir) const {
    switch (dir) {
        case direction::top:
            return top_exists;
        case direction::down:
            return down_exists;
        case direction::right:
            return right_exists;
        case direction::left:
            return left_exists;
    }
}

cell cell::operator-(const cell &other) const {
    bool new_top = top_exists ^ other.top_exists;
    bool new_down = down_exists ^ other.down_exists;
    bool new_right = right_exists ^ other.right_exists;
    bool new_left = left_exists ^ other.left_exists;
    return {new_top, new_down, new_right, new_left};
}

cell cell::operator/(const cell &other) const {
    bool new_top = top_exists | other.top_exists;
    bool new_down = down_exists | other.down_exists;
    bool new_right = right_exists | other.right_exists;
    bool new_left = left_exists | other.left_exists;
    return {new_top, new_down, new_right, new_left};
}

cell cell::operator%(const cell &other) const {
    bool new_top = top_exists & other.top_exists;
    bool new_down = down_exists & other.down_exists;
    bool new_right = right_exists & other.right_exists;
    bool new_left = left_exists & other.left_exists;
    return {new_top, new_down, new_right, new_left};
}

bool cell::operator==(const cell &other) const {
    return top_exists == other.top_exists &&
           down_exists == other.down_exists &&
           right_exists == other.down_exists &&
           left_exists == other.left_exists;
}