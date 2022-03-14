#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

void getAverageBits(const vector<string>& input, vector<int>& bitmap, int size)
{
  for (string str : input)
  {
    for(int j = 0; j < size; j++)
    {
      if (str[j] == '1')
        bitmap[j]++;
      else
        bitmap[j]--;
    }
  }
}

vector<int> getMostCommonBits(const vector<string>& input, int size)
{
  vector<int> bitmap = {0};
  bitmap.resize(size);
  getAverageBits(input, bitmap, size);

  for(int i = 0; i < size; i++)
  {
    if (bitmap[i] >= 0)
      bitmap[i] = 1;
    else
      bitmap[i] = 0;
  }
  return bitmap;
}

vector<int> getLeastCommonBits(const vector<string>& input, int size)
{
  vector<int> bitmap = {0};
  bitmap.resize(size);
  getAverageBits(input, bitmap, size);

  for(int i = 0; i < size; i++)
  {
    if (bitmap[i] >= 0)
      bitmap[i] = 0;
    else
      bitmap[i] = 1;
  }
  return bitmap;
}

bool searchAndDestroy(vector<string>& input, const vector<int>& bitmap, int bit)
{
  for (auto ite = input.begin(); ite != input.end();)
  {
    int val = (*ite)[bit] - '0';
    if (val == bitmap[bit]) 
      ++ite;
    else 
      ite = input.erase(ite);
  }
  return (input.size() == 1);
}

string searchForOxygenGeneratorRating(vector<string> input)
{
  int size = input[0].size();
  vector<int> bitmap = getMostCommonBits(input, size);
  
  int bit = 0;
  while(!searchAndDestroy(input, bitmap, bit))
  {
    if (input.size() == 0)
      return "aie aie aie";
    bitmap = getMostCommonBits(input, size);
    bit++;
  }
  return input[0];
}

string searchForCO2GeneratorRating(vector<string> input)
{
  int size = input[0].size();
  vector<int> bitmap = getLeastCommonBits(input, size);

  int bit = 0;
  while(!searchAndDestroy(input, bitmap, bit))
  {
    if (input.size() == 0)
      return "aie aie aie";
    bitmap = getLeastCommonBits(input, size);
    bit++;
  }
  return input[0];
}

int main()
{
  std::ifstream file("Jour3.txt");
  vector<string> input;

  std::string str;
  while (std::getline(file, str)) 
  {
    input.push_back(str);
  }

  string oxygen = searchForOxygenGeneratorRating(input);
  string co2 = searchForCO2GeneratorRating(input);
  int o = stoi(oxygen, nullptr, 2);
  int c = stoi(co2, nullptr, 2);
  cout << oxygen << " => " << o << endl;
  cout << co2 << " => " << c << endl;
  cout << o * c << endl;

  return 0;
}

/*
int main()
{
  std::ifstream file("Jour3.txt");
  vector<int> bitmap = {0};
  vector<string> input;

  int strSize = 0;
  std::string str;
  while (std::getline(file, str)) 
  {
    if (!strSize)
    {
      strSize = str.size();
      bitmap.resize(strSize);
    }
    input.push_back(str);

    for(int i = 0; i < strSize; i++)
    {
      if (str[i] == '1')
        bitmap[i]++;
      else
        bitmap[i]--;
    }
  }

  string gamma = "";
  string epsilon = "";
  for(int i = 0; i < strSize; i++)
  {
    if (bitmap[i] > 0)
    {
      gamma += "1";
      epsilon += "0";
    }
    else
    {
      gamma += "0";
      epsilon += "1";
    }
  }
  int gammaRate = stoi(gamma, nullptr, 2);
  int epsilonRate = stoi(epsilon, nullptr, 2);
  cout << gammaRate << endl;
  cout << epsilonRate << endl;
  cout << gammaRate * epsilonRate  << endl;

    return 0;
}
*/