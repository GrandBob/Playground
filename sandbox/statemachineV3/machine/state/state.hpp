#include <iostream>
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
    static void init(StateMachine &m, StateRef<State> &state) {
        state = StateRef<State>(new ConcreteState(m, state));
        state->start();
    }

    StateMachine* getMachine() { return &m; };

protected:
    template <class ConcreteState>
    void change() {
        exit();
        init<ConcreteState>(m, state);
    }

private:
    virtual void start() {}
    virtual void exit() {}

protected:
    StateMachine &m;

private:
    StateRef<State> &state;
};