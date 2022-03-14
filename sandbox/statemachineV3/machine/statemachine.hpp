#include "state/state.hpp"

class StateMachine
{
public:
    StateMachine();
    ~StateMachine() {}
    bool go();
    void next();

protected:
    static void print(const std::string &str) { std::cout << str << std::endl; }
    static void unhandledEvent() { print("unhandled event"); }

protected:
    struct State : public GenericState<Machine, State> {
        using GenericState::GenericState;
        virtual bool run() { unhandledEvent(); return true; }
        virtual void next() { unhandledEvent(); }
        void start() {
          if (getMachine()->getData() == nullptr) {
            change<InError>();
          }
          else{
            run();
          }
        }
    };

private:
    StateRef<State> state;
};