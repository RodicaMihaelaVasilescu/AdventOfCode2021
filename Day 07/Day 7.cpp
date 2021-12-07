#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <limits.h>

using namespace std;

vector<int> split(string line, string delimiters = ",./;")
{
  vector<int> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(stoi(line.substr(0, index)));
  }

  while (index != -1) {
    index++;
    line = line.substr(index, line.length() - index);
    index = line.find_first_of(delimiters);
    auto newWord = line.substr(0, index);
    if (!newWord.empty())
    {
      words.push_back(stoi(newWord));
    }
  }
  return words;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  cin >> line;

  auto crabSubmarines = split(line);

  int minimumFuelPart1 = INT_MAX, minimumFuelPart2 = INT_MAX;

  for (int i = 0; i < crabSubmarines.size(); i++)
  {
    int fuelPart1 = 0, fuelPart2 = 0;
    for (int j = 0; j < crabSubmarines.size(); j++)
    {
      fuelPart1 += abs(crabSubmarines[j] - crabSubmarines[i]);
      fuelPart2 += abs(crabSubmarines[j] - i) * (abs(crabSubmarines[j] - i) + 1) / 2;
    }

    minimumFuelPart1 = min(minimumFuelPart1, fuelPart1);
    minimumFuelPart2 = min(minimumFuelPart2, fuelPart2);
  }

  cout << "Part 1: " << minimumFuelPart1 << endl;
  cout << "Part 2: " << minimumFuelPart2 << endl;
  return 0;
}