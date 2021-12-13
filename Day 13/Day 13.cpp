//warning: run this solution in release mode..

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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

int linesNumber, columnsNumber;
map<pair<int, int>, bool> matrix;

void foldHorizontal(int foldingNumber)
{
  linesNumber = foldingNumber;

  for (int j = 0; j <= columnsNumber; j++)
  {
    for (int i = 0; i <= linesNumber; i++)
    {
      if (matrix[{i, j}] == 0)
      {
        matrix[{ i, j}] = matrix[{2 * foldingNumber - i, j}];
      }
    }
  }
}

void foldVertical(int foldingNumber)
{
  columnsNumber = foldingNumber;
  for (int i = 0; i <= linesNumber; i++)
  {
    for (int j = 0; j <= columnsNumber; j++)
    {
      if (matrix[{i, j}] == 0)
      {
        matrix[{ i, j}] = matrix[{i, 2 * foldingNumber - j}];
      }
    }
  }
}

void fold(pair<string, int> folding)
{
  if (folding.first == "horizontal")
  {
    foldHorizontal(folding.second);
  }
  else
  {
    foldVertical(folding.second);
  }
}

void print()
{
  int nr = 0;
  for (int i = 0; i <= linesNumber; i++)
  {
    for (int j = 0; j <= columnsNumber; j++)
    {
      if (matrix[{i, j}])
      {
        cout << "#";
        nr++;
      }
      else
      {
        cout << " ";
      }
    }
    cout << endl;
  }
}

int getDotsNumber()
{
  int dotsNumber = 0;
  for (int i = 0; i <= linesNumber; i++)
  {
    for (int j = 0; j <= columnsNumber; j++)
    {
      if (matrix[{i, j}])
      {
        dotsNumber++;
      }
    }
  }

  return dotsNumber;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;

  vector<pair<string, int>> foldInstructions;
  while (getline(cin, line)) {
    if (line.empty())
    {
      continue;
    }

    auto words = split(line);
    if (words[0] == "fold")
    {
      foldInstructions.push_back({ words[words.size() - 2] == "y" ? "horizontal" : "vertical",
        stoi(words[words.size() - 1]) });
    }
    else
    {
      int x = stoi(words[1]);
      int y = stoi(words[0]);
      linesNumber = max(linesNumber, x);
      columnsNumber = max(columnsNumber, y);
      matrix[{x, y}] = true;
    }
  }

  fold(foldInstructions[0]);
  cout << "Part 1: " << getDotsNumber() << endl;

  for (auto folding : foldInstructions)
  {
    fold(folding);
  }

  cout << "Part 2: " << endl;
  print();
}