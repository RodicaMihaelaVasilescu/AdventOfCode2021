#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

vector<int> line{ 1,-1, 0, 0 };
vector<int> column{ 0, 0,-1, 1 };

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string inputLine;
  vector<string> matrix;

  while (getline(cin, inputLine))
  {
    matrix.push_back(inputLine);
  }

  int sumLowPoints = 0;
  set<pair<int, int>> lowPoints;

  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[0].size(); j++)
    {
      int lowestNeghbour = INT_MAX;
      for (int direction = 0; direction < line.size(); direction++)
      {
        int x = i + line[direction];
        int y = j + column[direction];
        if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size())
        {
          lowestNeghbour = min(lowestNeghbour, matrix[x][y] - '0');
        }
      }
      if (matrix[i][j] - '0' < lowestNeghbour)
      {
        lowPoints.insert({ i,j });
        sumLowPoints += matrix[i][j] - '0' + 1;
      }
    }
  }

  cout << "Part 1: " << sumLowPoints << endl;

  int sumBasinSizes = 0;
  vector<int> basinSizes;
  for (auto lowPoint : lowPoints)
  {
    queue<pair<int, int>> neighboursQueue;
    set<pair<int, int>> basin;
    neighboursQueue.push(lowPoint);
    while (!neighboursQueue.empty())
    {
      auto currentPoint = neighboursQueue.front();
      neighboursQueue.pop();

      basin.insert(currentPoint);

      for (int direction = 0; direction < line.size(); direction++)
      {
        int x = currentPoint.first + line[direction];
        int y = currentPoint.second + column[direction];
        if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size())
        {
          if (matrix[x][y] - '0' != 9 && basin.find({ x,y }) == basin.end())
          {
            neighboursQueue.push({ x,y });
          }
        }
      }
    }
    basinSizes.push_back(basin.size());
  }

  sort(basinSizes.rbegin(), basinSizes.rend());
  cout << "Part 2: " << basinSizes[0] * basinSizes[1] * basinSizes[2] << endl;

  return 1;
}