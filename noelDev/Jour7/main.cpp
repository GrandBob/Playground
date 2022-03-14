#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;

int distance(int a, int b)
{
  return (a > b) ? a - b : b - a;
}

int claculateMoveCost(int a, int b)
{
  int moves = distance(a, b);

  int cost = 0;
  while (moves != 0)
    cost += moves--;

  return cost;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage : " << argv[0] << " [input file name]" << endl;
    return 1;
  }
  ifstream file(argv[1]);
  string str;
  size_t pos = 0;
  string delimiter(",");
  string token;
  multiset<int, greater<int>> crabPos;

  std::getline(file, str);
  while ((pos = str.find(delimiter)) != std::string::npos) {
      token = str.substr(0, pos);
      crabPos.insert(stoi(token));
      str.erase(0, pos + delimiter.length());
  }
  crabPos.insert(stoi(str));
  int max = *crabPos.begin();

  int fuelCost = -1;
  int calculatedFueldCost = 0;
  for (int i = 0; i < max; i++)
  {
    for(auto it = crabPos.begin(); it != crabPos.end(); it++)
      calculatedFueldCost += claculateMoveCost(i, *it);
    if (calculatedFueldCost < fuelCost || fuelCost == -1)
      fuelCost = calculatedFueldCost;
    calculatedFueldCost = 0;
  }

  cout << fuelCost << endl;

  return 0;
}