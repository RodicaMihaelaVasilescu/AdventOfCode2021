#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <sstream>

using namespace std;

vector<string> split(string line, string delimiters = ",./;= ")
{
  vector<string> words;
  if (line.empty())
  {
    return words;
  }

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
    {
      words.push_back(newWord);
    }
  }
  return words;
}

pair<int, int> x;
pair<int, int> y;

int getMaximumYProbe(int i, int j)
{
  int highestYProbe = 0;
  int xVelocity = i;
  int yVelocity = j;
  int xProbe = 0;
  int yProbe = 0;
  map<int, int> frequency;

  while (frequency[yVelocity] < 1000 && frequency[xVelocity] < 1000 && frequency.size() < 10000)
  {
    frequency[xVelocity]++;
    frequency[yVelocity]++;
    if (xProbe >= x.first && xProbe <= x.second && yProbe >= y.first && yProbe <= y.second)
    {
      return highestYProbe;
    }
    if (xProbe > x.second && yProbe < y.second)
    {
      return -1;
    }
    xProbe += xVelocity;
    yProbe += yVelocity;
    highestYProbe = max(yProbe, highestYProbe);

    if (xVelocity == 0)
    {

    }
    else if (xProbe < 0)
    {
      xVelocity++;
    }
    else if (xProbe > 0)
    {
      xVelocity--;
    }
    yVelocity--;
  }
  return -1;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  while (getline(cin, line)) {

    vector<string> words = split(line);
    for (int i = 0; i < words.size(); i++)
    {
      if (words[i] == "x")
      {
        int a = stoi(words[i + 1]);
        int b = stoi(words[i + 2]);
        x = { min(a, b), max(a,b) };
      }
      if (words[i] == "y")
      {
        int a = stoi(words[i + 1]);
        int b = stoi(words[i + 2]);
        y = { min(a, b), max(a,b) };
      }
    }
  }

  int validVelocitiesNumber = 0;
  int maximumYProbe = 0;
  for (int i = -200; i < 200; i++)
  {
    for (int j = -200; j < 200; j++)
    {
      int yProbe = getMaximumYProbe(i, j);
      if (yProbe > -1)
      {
        validVelocitiesNumber++;
        maximumYProbe = max(yProbe, maximumYProbe);
      }
    }
  }

  cout << "Part 1: " << maximumYProbe << endl;
  cout << "Part 2: " << validVelocitiesNumber;
  int n;

}