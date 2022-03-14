#ifndef GENERICSTATE_H
#define GENERICSTATE_H

#include <memory>

template <class State>
using StateRef = std::unique_ptr<State>;

template <typename StateMachine, class State>
class GenericState
{
public:
    explicit GenericState(StateMachine &m, StateRef<State> &state) :
        m(m), state(state) {}

    template <class ConcreteState>
    static void init(StateMachine &m, StateRef<State> &state/*, [lambda] action*/) {
        state = StateRef<State>(new ConcreteState(m, state/*, action*/));
        state->entry();
    }

protected:
    template <class ConcreteState>
    void change(/*[lambda] action*/) {
        exit();
        init<ConcreteState>(m, state/*, [lambda] action*/);
    }

    /*void reenter() {
        exit();
        entry();
    }*/

private:
    virtual void entry() {}
    virtual void exit() {}

protected:
    StateMachine &m;

private:
    StateRef<State> &state;
};

#endif // GENERICSTATE_H
