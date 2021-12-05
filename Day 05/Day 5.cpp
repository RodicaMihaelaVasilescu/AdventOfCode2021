#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

vector<int> split(string line, string delimiters = ",. ")
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
      words.push_back(stoi(newWord));
  }
  return words;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  map<pair<int, int>, int> matrixPart1, matrixPart2;

  set <pair<int, int>> pointsPart1, pointsPart2;

  while (getline(cin, line)) {

    auto words = split(line, ",-> ");
    pair<int, int> point1(words[0], words[1]), point2(words[2], words[3]);

    if (point1.first == point2.first)
    {
      //horizontal
      int x = min(point1.second, point2.second);
      int y = max(point1.second, point2.second);
      for (int i = x; i <= y; i++)
      {
        if (matrixPart1[{point1.first, i}] != 0)
        {
          pointsPart2.insert({ point1.first, i });
        }

        if (matrixPart2[{point1.first, i}] != 0)
        {
          pointsPart1.insert({ point1.first, i });
        }

        matrixPart2[{point1.first, i}]++;
        matrixPart1[{point1.first, i}]++;
      }
    }
    else if (point1.second == point2.second)
    {
      // vertical
      int x = min(point1.first, point2.first);
      int y = max(point1.first, point2.first);
      for (int i = x; i <= y; i++)
      {
        if (matrixPart1[{ i, point1.second}] != 0)
        {
          pointsPart2.insert({ i, point1.second });
        }

        if (matrixPart2[{ i, point1.second}] != 0)
        {
          pointsPart1.insert({ { i, point1.second} });
        }

        matrixPart1[{ i, point1.second}]++;
        matrixPart2[{ i, point1.second}]++;
      }
    }
    else
    {
      // diagonals
      int sign1 = point1.first > point2.first ? -1 : 1;
      int sign2 = point1.second > point2.second ? -1 : 1;
      for (int i = 0; i <= abs(abs(point1.first - point2.first)); i++)
      {
        if (matrixPart1[{ point1.first + i * sign1, point1.second + i * sign2}] != 0)
        {
          pointsPart2.insert({ point1.first + i * sign1, point1.second + i * sign2 });
        }
        matrixPart1[{ point1.first + i * sign1, point1.second + i * sign2}]++;
      }
    }
  }

  cout << "Part 1: " << pointsPart1.size() << endl;
  cout << "Part 2: " << pointsPart2.size() << endl;
}