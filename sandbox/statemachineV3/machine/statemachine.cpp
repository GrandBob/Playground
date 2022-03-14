#include "statemachine.hpp"

StateMachine::StateMachine()
{
  State::init<Idle>(*this, state);
}

bool StateMachine::go()
{
  return state->run();
}

void StateMachine::next()
{
  state->next();
}