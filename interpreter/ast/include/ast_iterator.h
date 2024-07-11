#ifndef INTERPRETER_AST_ITERATOR_H
#define INTERPRETER_AST_ITERATOR_H
#include <list>
#include "node.h"
#include <utility>

class Ast;

template <bool IsConst>
class AstIterator{
private:
    friend class Ast;

    friend class AstIterator<!IsConst>;

    using iter_t = std::list<Node>::iterator;

    using const_iter_t = std::list<Node>::const_iterator;

    typedef std::conditional_t<IsConst, const_iter_t, iter_t> elem_t;

    elem_t elem_;

    AstIterator(elem_t elem): elem_(elem) {}

public:
    typedef Node value_t;

    typedef std::conditional_t<IsConst, const value_t, value_t>* pointer;

    typedef std::conditional_t<IsConst, const value_t, value_t>& reference;

    template<bool OtherConst>
    AstIterator(const AstIterator<OtherConst>& other) noexcept requires(IsConst >= OtherConst){
        elem_ = other.elem_;
    }

    template<bool OtherConst>
    AstIterator& operator = (const AstIterator<OtherConst>& other) noexcept requires(IsConst >= OtherConst) {
        if (this != &other)
            elem_ = other.elem_;
        return *this;
    };

    template<bool OtherConst>
    bool operator == (const AstIterator<OtherConst>& other) const noexcept{
        return elem_ == other.elem_;
    }

    AstIterator& operator ++ () {
        ++elem_;
        return *this;
    }

    AstIterator operator ++ (int) {
        elem_t returned = elem_;
        ++elem_;
        return {returned};
    }

    AstIterator& operator -- () {
        --elem_;
        return *this;
    }

    AstIterator operator -- (int) {
        elem_t returned = elem_;
        --elem_;
        return {returned};
    }

    pointer operator -> () const noexcept{
        return *elem_;
    }

    reference operator * () const noexcept {
        return *elem_;
    }
};


#endif //INTERPRETER_AST_ITERATOR_H
