#include <iostream>
#include <string>
#include "../machine/statemachine.hpp"

class Sequence : StateMachine 
{
public:
  bool create() = 0;
  bool build() = 0;
  bool paint() = 0;
  bool validation() = 0;

protected:
  struct Create : public State {
      using State::State;
      bool run() { getMachine()->create(); return true; }
      void next() { change<Build>(); }
  };

  struct Build : public State {
      using State::State;
      bool run() { getMachine()->build(); return true; }
      void next() { change<Paint>(); }
  };

  struct Paint : public State {
      using State::State;
      bool run() { getMachine()->paint(); return false; }
      void next() { change<Validation>(); }
  };

  struct Validation : public State {
      using State::State;
      bool run() { getMachine()->validation(); return false; }
      void next() { change<Create>(); }
  };
};

class Usine : Sequence {
public:
  Usine() {}
  ~Usine() {}

  bool create() { add(2, 345); return true; };
  bool build() { wow(12); return true; };
  bool paint() { print(); return true; };
  bool validation() { print(); return true; };

  void newOrder() {}

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

  Vehicule v;
};