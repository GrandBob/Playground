#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
  std::ifstream file("Jour1.txt");
  vector<int> input;

  std::string str;
  int size = 0;
  while (std::getline(file, str)) 
  {
    input.push_back(stoi(str));
    size++;
  }

  int counter = 0;
  int last = -1;
  int sum = 0;
  int b = 0;
  for (int i = 0; (i < size); i++)
  {
    if (i+2 >= size)
      break;
    sum = input[i] + input[i+1] + input[i+2];
    if (last > 0 && sum > last)
    {
      counter++;
    }
    last = sum;
  }
  cout << counter << endl;

  return 0;
}