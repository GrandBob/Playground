#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

void print(const int* const fish)
{
  for (int i = 0; i < 9; i++)
  {
    cout << "Fish["<<i<<"] = " << fish[i] << endl;
  }
  cout << endl;
}

template<class E, size_t size>
uint64_t runSimulation(E (&lanternFish)[size])
{
  int nbJours = 256;

  for(int i = 0; i < nbJours; i++)
  {
    cout << "Jour " << i << endl;
    rotate(lanternFish + 0, lanternFish + 1, lanternFish + size);
    lanternFish[6] += lanternFish[size-1];
  }
  return accumulate(lanternFish + 0, lanternFish + size, uint64_t(0));
}

int main(int argc, char* argv[])
{
  auto start = high_resolution_clock::now();
  if (argc < 2)
  {
    cout << "Usage : " << argv[0] << " [input file name]" << endl;
    return 1;
  }
  ifstream file(argv[1]);
  string str;

  std::getline(file, str);
  size_t pos = 0;
  string delimiter(",");
  string token;

  uint64_t FishBang[9] = {0,};
  while ((pos = str.find(delimiter)) != std::string::npos) {
      token = str.substr(0, pos);
      FishBang[stoi(token)]++;
      str.erase(0, pos + delimiter.length());
  }
  FishBang[stoi(str)]++;

  cout << runSimulation(FishBang) << endl;
  
  
  auto stop = high_resolution_clock::now();
  auto ms = duration_cast<microseconds>(stop - start);
  auto sec = duration_cast<seconds>(ms);
  cout << "Time taken by function: " << sec.count() << ","<<ms.count()<< " seconds" << endl;
  return 0;
}