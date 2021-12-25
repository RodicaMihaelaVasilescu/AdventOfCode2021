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

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  vector<string> matrix;

  while (getline(cin, line)) {
    matrix.push_back(line);
  }
  vector<string> initialMatrix;
  int round = 0;
  do
  {
    round++;
    initialMatrix = matrix;
    for (auto i = 0; i < matrix.size(); i++)
    {
      for (auto j = 0; j < matrix[i].size(); j++)
      {
        int x = i;
        int y = (j + 1)%matrix[i].size();
        if (initialMatrix[i][j] == '>' && initialMatrix[x][y] == '.')
        {
          swap(matrix[i][j], matrix[x][y]);
        }
      }
    }
    auto matrix2 = matrix;

    for (auto i = 0; i < matrix.size(); i++)
    {
      for (auto j = 0; j < matrix[i].size(); j++)
      {
        int x = (i + 1) % matrix.size();
        int y = j;
        if (matrix2[i][j] == 'v' && matrix2[x][y] == '.')
        {
          swap(matrix[i][j], matrix[x][y]);
        }
      }
    }


  } while (initialMatrix != matrix);

  cout << round;

}