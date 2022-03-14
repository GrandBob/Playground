#include <iostream>
#include <string>
#include <memory>
#include <vector>

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
    static const char* stateName() { return "GenericState"; };

protected:
    template <class ConcreteState>
    void change() {
        exit();
        std::cout << "Change state from <"<< this->stateName() <<"> to <"<<ConcreteState::stateName()<<">" << std::endl;
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

class Actor {
public:
  virtual bool runIdle() = 0;
  virtual bool runDo() = 0;
  virtual bool runInError() = 0;
  virtual bool runEnd() = 0;
};

class MyData : public Actor {
    public:
      MyData() {}
      ~MyData() {}

    bool runIdle() { add(2, 345); return true; };
    bool runDo() { wow(12); return true; };
    bool runInError() { print(); return true; };
    bool runEnd() { print(); return true; };

    private:
      void add(int m_a, int m_b) { a+=m_a; b+=m_b; };
      void wow(int index) 
      {
        for(int i = 0; i < index; i++)
        {
            a++;
        }
      };
      void print() { std::cout << "A = " << a << " | B = " << b << std::endl; };

    private:
      int a = 0;
      int b = 100;      
};

class Machine
{
public:
    Machine(Actor* o);
    ~Machine() {}
    bool go();
    void next();

    Actor* getData() { return data; };
    const char* getStateName() { return state->stateName(); };
private:
    static void print(const std::string &str) { std::cout << str << std::endl; }
    static void unhandledEvent() { print("unhandled event"); }

private:
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
        static const char* stateName() { return "State"; };
    };

    struct Idle : public State {
        using State::State;
        bool run() { getMachine()->getData()->runIdle(); return true; }
        void next() { change<Do>(); }
        static const char* stateName() { return "Idle"; };
    };

    struct Do : public State {
        using State::State;
        bool run() { getMachine()->getData()->runDo(); return true; }
        void next() { change<End>(); }
        static const char* stateName() { return "Do"; };
    };

    struct InError : public State {
        using State::State;
        bool run() { getMachine()->getData()->runInError(); return false; }
        void next() { change<End>(); }
        static const char* stateName() { return "InError"; };
    };

    struct End : public State {
        using State::State;
        bool run() { getMachine()->getData()->runEnd(); return false; }
        void next() { change<Idle>(); }
        static const char* stateName() { return "End"; };
    };

private:
    Actor *data;
    StateRef<State> state;
};

Machine::Machine(Actor *o) : data(o)
{
  State::init<Idle>(*this, state);
}

bool Machine::go()
{
  return state->run();
}

void Machine::next()
{
  state->next();
}

int main()
{
  MyData data;
  Machine m(&data);
  while(m.go())
    m.next();
  std::cout << "---------" << std::endl;
  return 0;
}