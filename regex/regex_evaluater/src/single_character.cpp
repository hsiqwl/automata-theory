#include "single_character.h"

single_character::single_character(char c): token(token::token_type::terminal) {
    value = c;
}