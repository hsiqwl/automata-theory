#ifndef REGEX_ITERATOR_H
#define REGEX_ITERATOR_H
#include <iterator>
#include <vector>

class match_result;

template<bool is_const>
class match_result_iterator{
private:
    friend class match_result;

    friend class match_result_iterator<!is_const>;

    typedef std::conditional_t<is_const, std::vector<std::string>::const_iterator, std::vector<std::string>::iterator> node_type;

    node_type value;

    match_result_iterator(node_type value): value(value) {}

public:
    typedef std::string val_type;

    typedef std::conditional_t<is_const, val_type, const val_type>& reference;

    template<bool other_const>
    match_result_iterator(const match_result_iterator<other_const>& other) noexcept requires (is_const >= other_const){
        value = other.value;
    }

    template<bool other_const>
    match_result_iterator(match_result_iterator<other_const>&& other) noexcept requires(is_const >= other_const){
        value = std::move(other.value);
    }

    template<bool other_const>
    match_result_iterator& operator = (const match_result_iterator<other_const>& other) noexcept requires(is_const >= other_const){
        if(this != &other){
            value->clear();
            value = other.value;
        }
        return *this;
    }

    template<bool other_const>
    match_result_iterator& operator = (match_result_iterator<other_const>&& other) noexcept requires(is_const >= other_const){
        if(this != &other) {
            value->clear();
            value = std::move(other.value);
        }
        return *this;
    }

    template<bool other_const>
    bool operator == (const match_result_iterator<other_const>& other) noexcept {
        return value == other.value;
    }

    template<bool other_const>
    bool operator != (const match_result_iterator<other_const>& other) noexcept{
        return value != other.value;
    }

    match_result_iterator& operator ++ (){
        ++value;
        return *this;
    }

    match_result_iterator operator ++ (int){
        node_type prev = value;
        ++value;
        return match_result_iterator(prev);
    }

    match_result_iterator operator + (int n){
        return match_result_iterator(value + n);
    }

    reference operator * () const noexcept{
        return *value;
    }
};


#endif //REGEX_ITERATOR_H
