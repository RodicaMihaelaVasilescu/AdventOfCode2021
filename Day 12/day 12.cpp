#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<string> split(string line, string delimiters = ",./;-")
{
  vector<string> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(line.substr(0, index));
  }

  while (index != -1) {
    index++;
    line = line.substr(index, line.length() - index);
    index = line.find_first_of(delimiters);
    auto newWord = line.substr(0, index);
    if (!newWord.empty())
      words.push_back(newWord);
  }
  return words;
}

vector<pair<string, string>> caves;
bool isSmallCave(string i)
{
  return islower(i[0]);
}

bool doesPathContainsCave(vector<string> v, string lowerCase)
{
  for (auto i : v)
  {
    if (i == lowerCase)
    {
      return true;
    }
  }
  return false;
}

bool doesAnySmallCaveOccursTwice(vector<string>path)
{
  map<string, int> smallCavesFrequency;

  for (auto cave : path)
  {
    if (isSmallCave(cave))
    {
      smallCavesFrequency[cave]++;
    }
  }

  for (auto frequency : smallCavesFrequency)
  {
    if (frequency.second == 2)
    {
      return true;
    }
  }
  return false;
}

int getAllPathsPart1(string start, vector<string> path = vector<string>())
{
  path.push_back(start);

  int numberOfPaths = 0;

  if (start == "end")
  {
    numberOfPaths++;
    return numberOfPaths;
  }

  for (auto cave : caves)
  {
    if (cave.first == start)
    {
      if (isSmallCave(cave.second))
      {
        if (!doesPathContainsCave(path, cave.second))
        {
          numberOfPaths += getAllPathsPart1(cave.second, path);
        }
      }
      else
      {
        numberOfPaths += getAllPathsPart1(cave.second, path);
      }
    }
  }
  return numberOfPaths;
}

int getAllPathsPart2(string start, vector<string> path = vector<string>())
{
  path.push_back(start);

  int numberOfPaths = 0;

  if (start == "end")
  {
    numberOfPaths++;
    return numberOfPaths;
  }

  for (auto cave : caves)
  {
    if (cave.first == start)
    {
      if (isSmallCave(cave.second))
      {
        if (!doesPathContainsCave(path, cave.second))
        {
          numberOfPaths += getAllPathsPart2(cave.second, path);
        }
        else if (!doesAnySmallCaveOccursTwice(path))
        {
          numberOfPaths += getAllPathsPart2(cave.second, path);
        }
      }
      else
      {
        numberOfPaths += getAllPathsPart2(cave.second, path);
      }
    }
  }
  return numberOfPaths;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  while (getline(cin, line)) {

    auto words = split(line);
    if (words[1] == "start" || words[0] == "end")
    {
      caves.push_back({ words[1], words[0] });
      continue;
    }

    caves.push_back({ words[0], words[1] });

    if (words[0] != "start" && words[0] != "end")
    {
      caves.push_back({ words[1], words[0] });
    }
  }

  cout << "Part 1: " << getAllPathsPart1("start") << endl;
  cout << "Part 2: " << getAllPathsPart2("start") << endl;
}
