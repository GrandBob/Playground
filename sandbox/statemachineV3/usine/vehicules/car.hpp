#include "vehicule.hpp"

class Car : Vehicule
{
public:
  Car() : type(VehiculeType::CAR) {}
  ~Car() {}

private:
  int seat;
  int doors;
  int wheels;
  string model;
  string color;
}