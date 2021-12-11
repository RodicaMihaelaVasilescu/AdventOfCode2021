#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

vector<int> line{ 1,-1, 0, 0, -1, -1, 1, 1 };
vector<int> column{ 0, 0,-1, 1, -1 , 1,-1, 1 };

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


  int sumPart1 = 0;
  long long step = 0;

  while (true) {
    auto flashed = matrix;
    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[0].size(); j++) {
        if (flashed[i][j] != -1)
        {
          matrix[i][j]++;
        }
        if (matrix[i][j] - '0' > 9)
        {
          matrix[i][j] = '0';
          flashed[i][j] = -1;
          sumPart1++;
          queue<pair<int, int>> q;
          q.push({ i,j });
          while (!q.empty()) {
            auto currentPoint = q.front();
            q.pop();
            for (int direction = 0; direction < line.size(); direction++)
            {
              int x = currentPoint.first + line[direction];
              int y = currentPoint.second + column[direction];
              if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size())
              {
                if (flashed[x][y] != -1)
                {
                  matrix[x][y]++;
                }
                if (matrix[x][y] - '0' > 9)
                {
                  matrix[x][y] = '0';
                  flashed[x][y] = -1;
                  sumPart1++;
                  q.push({ x,y });
                }
              }
            }
          }
        }
      }
    }

    step++;
    if (step == 100)
    {
      cout << "Part 1: " << sumPart1 + 1 << endl;
    }

    bool flash = true;
    for (auto i : flashed)
    {
      for (auto ch : i)
      {
        if (ch != -1)
        {
          flash = false;
        }
      }
    }

    if (flash)
    {
      cout << "Part 2: " << step << endl;
      return 0;
    }
  }
  return 1;
}