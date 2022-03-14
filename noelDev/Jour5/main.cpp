#include "MapGrid.hpp"
#include <fstream>
#include <regex>
#include <string>
#include <tuple>

tuple<string, string> split(string str, const string& delim)
{
  string part1 = str.substr(0, str.find(delim));
  str.erase(0, str.find(delim) + delim.length());
  return make_tuple(part1, str);
}

bool getPosFromInput(string str, int& x1, int& y1, int& x2, int& y2)
{
  string part1, part2;
  tie(part1, part2) = split(str, " -> ");
  string s_x1, s_y1;
  tie(s_x1, s_y1) = split(part1, ",");
  string s_x2, s_y2;
  tie(s_x2, s_y2) = split(part2, ",");  

  x1 = stoi(s_x1.c_str());
  y1 = stoi(s_y1.c_str());
  x2 = stoi(s_x2.c_str());
  y2 = stoi(s_y2.c_str());
  return (x1 == x2 || y1 == y2);
}

int main(int argc, char* argv[])
{
  int size = 1000;
  if (argc < 2)
  {
    cout << "Usage : " << argv[0] << " [input file name]" << endl;
    return 1;
  }
  if (argc >= 3)
    size = stoi(argv[2]);
  ifstream file(argv[1]);
  string str;
  
  MapGrid grid(size);
  int x1, y1, x2, y2;
  while (std::getline(file, str)) 
  {
    getPosFromInput(str, x1, y1, x2, y2);
    grid.draw(x1, y1, x2, y2);
  }
  grid.print();
  cout << grid.getNumberOfOverlap() << endl;
  return 0;
}