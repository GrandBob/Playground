#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage : " << argv[0] << " [input file name]" << endl;
    return 1;
  }
  ifstream file(argv[1]);
  string str;
  while (std::getline(file, str)) 
  {
    cout << str << endl;
  }
  return 0;
}