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

void replaceAll(string& s, const string& search, const string& replace)
{
  for (size_t pos = 0; ; pos += replace.length())
  {
    // Locate the substring to replace
    pos = s.find(search, pos);
    if (pos == string::npos) break;
    // Replace by erasing and inserting
    s.erase(pos, search.length());
    s.insert(pos, replace);
  }
}
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

vector<int> split2(string line, string delimiters = ",./;")
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
int minX, maxX, minY, maxY;
vector<int> line{ -1, -1, -1, 0, 0, 0, 1, 1, 1 };
vector<int> column{ -1,  0 , 1, -1, 0, 1, -1, 0 , 1 };

void addPadding(vector<string>& input, int n)
{
  if (n < 1)
  {
    return;
  }
  string paddingMargin(n, '.');
  string paddingLine(n * 2 + input[0].size(), '.');
  for (auto& i : input)
  {
    i = paddingMargin + i + paddingMargin;
  }

  for (int i = 0; i < n; i++)
  {
    input.insert(input.begin(), paddingLine);
    input.push_back(paddingLine);
  }
}
void trimMatrix(vector<string>& input, int i1, int i2, int j1, int j2)
{
  vector<string> newInput;
  int line = 0;
  for (auto& i : input)
  {
    if (line >= i1 && line <= i2)
    {
      newInput.push_back(i.substr(j1, j2 - j1 + 1));
    }
    line++;
  }
  input = newInput;
}
void print(vector<string> input)
{
  for (auto& i : input)
  {
    cout << i << endl;
  }
  cout << endl;
}

int getNextImage(string enhacement, vector<string>& input)
{
  int nr = 0;
  int minx = INT_MAX, miny = INT_MAX, maxx = 0, maxy = 0;
  vector<string> output = input;
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < input[i].size(); j++)
    {
      string binary;
      if (i == 5 && j == 10)
      {
        int bkp = 0;
      }
      for (int d = 0; d < line.size(); d++)
      {
        int x = i + line[d];
        int y = j + column[d];
        char ch = '.';
        if (x >= 0 && x < input.size() && y >= 0 && y < input[i].size())
        {
          ch = input[x][y];
        }
        if (ch == '#')
        {
          binary += "1";
        }
        else if (ch == '.')
        {
          binary += "0";
        }
      }
      long long dec = -1;
      dec = stoll(binary, 0, 2);
      output[i][j] = enhacement[dec];
      if (output[i][j] == '#')
      {
        minx = min(minx, i);
        maxx = max(maxx, i);
        miny = min(miny, j);
        maxy = max(maxy, j);
      }

    }
  }

  input = output;
  trimMatrix(input, 1, input.size()-2, 1, input[0].size()-2);
  for (auto i : input)
  {
    for (auto j : i)
    {
      if (j == '#')
      {
        nr++;
      }
    }
  }
  return nr;
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<string> input;
  string enhacement;

  cin >> enhacement;
  while (getline(cin, line)) {
    if (line.empty())
    {
      continue;
    }
    input.push_back(line);
  }


  int round = 0;
  int pad = input.size();
  addPadding(input, 100);
  while (round++ < 50)
  {
    int nr = getNextImage(enhacement, input);
    if (round == 2 || round == 50)
    {
      //print(input);
      cout << nr << endl;
    }
  }

}