#ifndef INTERPRETER_GENERIC_OBJECT_FACTORY_H
#define INTERPRETER_GENERIC_OBJECT_FACTORY_H
#include <memory>
#include <unordered_map>
#include <stdexcept>

template<class Key, class Base, class ... Args>
class generic_object_factory {
    typedef std::unique_ptr<Base> (*creator_ptr)(Args ...);

    template<class Derived>
    static std::unique_ptr<Base> creator(Args ... args) {
        return std::make_unique<Derived>(args ...);
    }

    std::unordered_map<Key, creator_ptr> factory_map;

public:
    generic_object_factory() = default;

    bool is_registered(Key id) {
        return factory_map.contains(id);
    }

    template<class Derived>
    void register_class(Key id) {
        if (!is_registered(id))
            factory_map[id] = &creator<Derived>;
        else
            throw std::logic_error("Class is already registered with same key");
    }

    creator_ptr get_creator(Key id) {
        if (is_registered(id))
            return factory_map[id];
        else
            throw std::logic_error("Requested creator is not registered");
    }
};


#endif //INTERPRETER_GENERIC_OBJECT_FACTORY_H
