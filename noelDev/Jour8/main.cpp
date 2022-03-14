#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void split(string delimiter, string str, vector<string> &res)
{
  res.clear();
  size_t pos = 0;
  string tmp;
  while (pos != std::string::npos) {
      pos = str.find(delimiter);
      tmp = str.substr(0, pos);
      if (tmp != "")
        res.push_back(tmp);
      str.erase(0, pos + delimiter.length());   
  }
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
  vector<vector<string>> inputs;
  while (std::getline(file, str)) 
  {
    cout << str << endl;
    vector<string> tmp;
    split("|", str, tmp);
    split(" ", tmp[1], tmp);
    inputs.push_back(tmp);
  }

  for (auto input : inputs)
  {
    for (auto digit: input)
      cout << digit << endl;
    cout << endl;
  }

  return 0;
}