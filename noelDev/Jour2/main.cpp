#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
  std::ifstream file("Jour2.txt");
  //map<string, int> input;

  std::string str;
  size_t pos;
  string cmd;
  int val;

  int forward = 0;
  int depth = 0;
  int aim = 0;
  while (std::getline(file, str)) 
  {
    pos = str.find_first_of(' ', 0);
    cmd = str.substr(0, pos);
    val = stoi(str.substr(pos+1, std::string::npos));
    if (cmd == "forward") {
      forward += val;
      depth += val * aim;
    }
    else if (cmd == "down") {
      //depth += val;
      aim += val;
    }
    else {
      //depth	-= val;
      aim -= val;
    }
  }

  cout << "Forward: " << forward << " Depth: " << depth << endl;
  cout << forward * depth << endl;

  return 0;
}