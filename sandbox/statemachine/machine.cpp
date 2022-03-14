#include "machine.hpp"

void Machine::start()
{
    LevelState::init<High>(*this, levelState);
    DirectionState::init<Left>(*this, directionState);
}

void Machine::Red::paint(Machine::Color color)
{
     if (color == BLUE) change<Blue>();
     else ColorState::paint(color);
}

void Machine::Blue::paint(Machine::Color color)
{
     if (color == RED) change<Red>();
     else ColorState::paint(color);
}