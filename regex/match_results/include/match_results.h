#ifndef REGEX_MATCH_RESULTS_H
#define REGEX_MATCH_RESULTS_H
#include "regex_engine.h"
#include "iterator.h"

class match_result{
private:
    std::vector<std::string> submatch;

public:
    typedef match_result_iterator<true> const_iterator;

    typedef match_result_iterator<false> iterator;

    match_result(regex& executor, std::string_view string);

    iterator begin();

    iterator end();

    const_iterator cbegin();

    const_iterator cend();

    std::string& operator [] (int index);

    const std::string& operator [] (int index) const;
};


#endif //REGEX_MATCH_RESULTS_H
