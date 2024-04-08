#include "character_class.h"

character_class::character_class(char range_min, char range_max): character_class(range_min, range_max, {}){}

character_class::character_class(char range_min, char range_max, std::string_view singles):
    token(token::token_type::terminal), range_min(range_min), range_max(range_max), singles(singles){}