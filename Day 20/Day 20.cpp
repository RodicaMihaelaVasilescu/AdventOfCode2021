#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

vector<int> line{ -1, -1, -1, 0, 0, 0, 1, 1, 1 };
vector<int> column{ -1,  0 , 1, -1, 0, 1, -1, 0 , 1 };

void addPadding(vector<string>& input, int paddingSize)
{
  if (paddingSize < 1)
  {
    return;
  }
  string leftAndRightPadding(paddingSize, '.');
  string topAndBottomPadding(paddingSize * 2 + input[0].size(), '.');
  for (auto& line : input)
  {
    line = leftAndRightPadding + line + leftAndRightPadding;
  }

  while (paddingSize--)
  {
    input.insert(input.begin(), topAndBottomPadding);
    input.push_back(topAndBottomPadding);
  }
}
void trimMatrix(vector<string>& input, int trimSize)
{
  vector<string> newInput;
  int row = 0;
  for (auto& line : input)
  {
    if (row >= trimSize && row < input.size() - trimSize)
    {
      line.erase(0, trimSize);
      line.erase(line.size() - trimSize, trimSize);
      newInput.push_back(line);
    }
    row++;
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

int countPixels(vector<string> input, char ch)
{
  int sum = 0;
  for (auto i : input)
  {
    for (auto j : i)
    {
      if (j == ch)
      {
        sum++;
      }
    }
  }
  return sum;
}

int getLightPixelsNumber(string enhacement, vector<string>& input)
{
  vector<string> output = input;
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < input[i].size(); j++)
    {
      string binary;
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

      long long dec = stoll(binary, 0, 2);
      output[i][j] = enhacement[dec];
    }
  }

  input = output;
  trimMatrix(input, 1);
  return countPixels(input, '#');
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<string> input;
  string imageEnhacementAlgorithm;

  cin >> imageEnhacementAlgorithm;
  while (getline(cin, line)) {
    if (line.empty())
    {
      continue;
    }
    input.push_back(line);
  }

  int round = 0;
  addPadding(input, 100);
  while (round++ < 50)
  {
    int lightPixelsNumber = getLightPixelsNumber(imageEnhacementAlgorithm, input);
    if (round == 2)
    {
      //print(input);
      cout << "Part 1: " << lightPixelsNumber << endl;
    }
    if (round == 50)
    {
      //print(input);
      cout << "Part 2: " << lightPixelsNumber << endl;
    }
  }

}