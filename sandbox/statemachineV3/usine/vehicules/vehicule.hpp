
enum VehiculeType {
  DEFAULT = 0,
  CAR,
  MOTORBIKE,
  TRUCK
}

class Vehicule 
{
public:
  Vehicule() : type(VehiculeType::DEFAULT) {}
  ~Vehicule() {}

private:
  VehiculeType type;
}