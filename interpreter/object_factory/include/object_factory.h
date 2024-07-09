#ifndef INTERPRETER_GENERIC_OBJECT_FACTORY_H
#define INTERPRETER_GENERIC_OBJECT_FACTORY_H
#include <memory>
#include <unordered_map>
#include <stdexcept>

template<class Key, class Base, class ... Args>
class ObjectFactory {
    typedef std::unique_ptr<Base> (*creator_ptr)(Args &&...);

    template<class Derived>
    static std::unique_ptr<Base> creator(Args &&... args) {
        return std::make_unique<Derived>(std::forward<Args>(args)...);
    }

    std::unordered_map<Key, creator_ptr> factory_map_;

public:
    ObjectFactory() = default;

    bool Registered(Key id) {
        return factory_map_.contains(id);
    }

    template<class Derived>
    void Register(Key id) {
        if (Registered(id))
            factory_map_[id] = &creator<Derived>;
        else
            throw std::logic_error("Class is already registered with same key");
    }

    creator_ptr GetCreator(Key id) {
        if (Registered(id))
            return factory_map_[id];
        else
            throw std::logic_error("Requested creator is not registered");
    }
};


#endif //INTERPRETER_GENERIC_OBJECT_FACTORY_H
