//
// ex: set ro:
// DO NOT EDIT.
// generated by smc (http://smc.sourceforge.net/)
// from file : create_scanner.sm
//

#ifndef CREATE_SCANNER_SM_H
#define CREATE_SCANNER_SM_H


#define SMC_USES_IOSTREAMS

#include <statemap.h>

// Forward declarations.
class CreateMap;
class CreateMap_start;
class CreateMap_c_state;
class CreateMap_r_state;
class CreateMap_e_state;
class CreateMap_a_state;
class CreateMap_t_state;
class CreateMap_error;
class CreateMap_Default;
class create_scannerState;
class create_scannerContext;
class create_scanner;

class create_scannerState :
    public statemap::State
{
public:

    create_scannerState(const char * const name, const int stateId)
    : statemap::State(name, stateId)
    {};

    virtual void Entry(create_scannerContext&) {};
    virtual void Exit(create_scannerContext&) {};

    virtual void change_state(create_scannerContext& context, const char& c);

protected:

    virtual void Default(create_scannerContext& context);
};

class CreateMap
{
public:

    static CreateMap_start start;
    static CreateMap_c_state c_state;
    static CreateMap_r_state r_state;
    static CreateMap_e_state e_state;
    static CreateMap_a_state a_state;
    static CreateMap_t_state t_state;
    static CreateMap_error error;
};

class CreateMap_Default :
    public create_scannerState
{
public:

    CreateMap_Default(const char * const name, const int stateId)
    : create_scannerState(name, stateId)
    {};

    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_start :
    public CreateMap_Default
{
public:
    CreateMap_start(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void Entry(create_scannerContext&);
    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_c_state :
    public CreateMap_Default
{
public:
    CreateMap_c_state(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_r_state :
    public CreateMap_Default
{
public:
    CreateMap_r_state(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_e_state :
    public CreateMap_Default
{
public:
    CreateMap_e_state(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_a_state :
    public CreateMap_Default
{
public:
    CreateMap_a_state(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_t_state :
    public CreateMap_Default
{
public:
    CreateMap_t_state(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void change_state(create_scannerContext& context, const char& c);
};

class CreateMap_error :
    public CreateMap_Default
{
public:
    CreateMap_error(const char * const name, const int stateId)
    : CreateMap_Default(name, stateId)
    {};

    virtual void Entry(create_scannerContext&);
    virtual void change_state(create_scannerContext& context, const char& c);
};

class create_scannerContext :
    public statemap::FSMContext
{
public:

    explicit create_scannerContext(create_scanner& owner)
    : FSMContext(CreateMap::start),
      _owner(owner)
    {};

    create_scannerContext(create_scanner& owner, const statemap::State& state)
    : FSMContext(state),
      _owner(owner)
    {};

    virtual void enterStartState()
    {
        getState().Entry(*this);
        return;
    }

    inline create_scanner& getOwner()
    {
        return (_owner);
    };

    inline create_scannerState& getState()
    {
        if (_state == NULL)
        {
            throw statemap::StateUndefinedException();
        }

        return dynamic_cast<create_scannerState&>(*_state);
    };

    inline void change_state(const char& c)
    {
        setTransition("change_state");
        getState().change_state(*this, c);
        setTransition(NULL);
    };

private:
    create_scanner& _owner;
};


#endif // CREATE_SCANNER_SM_H

//
// Local variables:
//  buffer-read-only: t
// End:
//
