#include "single_character.h"

single_character::single_character(char c): terminal_token(terminal_token::terminal_type::single_character) {
    value = c;
}