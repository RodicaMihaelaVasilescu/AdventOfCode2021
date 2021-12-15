// credits : https://www.geeksforgeeks.org/min-cost-path-dp-6/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
/* Minimum Cost Path using Dijkstra’s shortest path
algorithm with Min Heap by dinglizeng */
#include <stdio.h>
#include <queue>
#include <limits.h>
using namespace std;

/* define the number of rows and the number of columns */
int R, C;

vector<int> dx{ 1,-1, 0, 0 };
vector<int> dy{ 0, 0, 1,-1 };

/* The data structure to store the coordinates of \\
the unit square and the cost of path from the top left. */
struct Cell {
  int x;
  int y;
  int cost;
};

/* The compare class to be used by a Min Heap.
* The greater than condition is used as this
is for a Min Heap based on priority_queue.
*/
class mycomparison
{
public:
  bool operator() (const Cell& lhs, const Cell& rhs) const
  {
    return (lhs.cost > rhs.cost);
  }
};

/* To verify whether a move is within the boundary. */
bool isSafe(int x, int y) {
  return x >= 0 && x < R&& y >= 0 && y < C;
}

/* This solution is based on Dijkstra’s shortest path algorithm
* For each unit square being visited, we examine all
  possible next moves in 4 directions,
* calculate the accumulated cost of path for each
  next move, adjust the cost of path of the adjacent
  units to the minimum as needed.
* then add the valid next moves into a Min Heap.
* The Min Heap pops out the next move with the minimum
accumulated cost of path.
* Once the iteration reaches the last unit at the lower
right corner, the minimum cost path will be returned.
*/
int minCost(map<pair<int, int>, int> cost, int m, int n) {

  /* the array to store the accumulated cost
  of path from top left corner */
  map<pair<int, int>, int> dp;

  /* the array to record whether a unit
  square has been visited */
  map<pair<int, int>, bool>  visited;

  /* Initialize these two arrays, set path cost
  to maximum integer value, each unit as not visited */
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      dp[{i, j}] = INT_MAX;
      visited[{i, j}] = false;
    }
  }

  /* Define a reverse priority queue.
  * Priority queue is a heap based implementation.
  * The default behavior of a priority queue is
    to have the maximum element at the top.
  * The compare class is used in the definition of the Min Heap.
  */
  priority_queue<Cell, vector<Cell>, mycomparison> pq;

  /* initialize the starting top left unit with the
  cost and add it to the queue as the first move. */
  dp[{0, 0}] = cost[{0, 0}];
  pq.push({ 0, 0, cost[{0, 0}] });

  while (!pq.empty()) {

    /* pop a move from the queue, ignore the units
    already visited */
    Cell cell = pq.top();
    pq.pop();
    int x = cell.x;
    int y = cell.y;
    if (visited[{x, y}]) continue;

    /* mark the current unit as visited */
    visited[{x, y}] = true;

    /* examine all non-visited adjacent units in 4 directions
    * calculate the accumulated cost of path for
    each next move from this unit,
    * adjust the cost of path for each next adjacent
    units to the minimum if possible.
    */
    for (int i = 0; i < dx.size(); i++) {
      int next_x = x + dx[i];
      int next_y = y + dy[i];
      if (isSafe(next_x, next_y) && !visited[{next_x, next_y}]) {
        dp[{next_x, next_y}] = min(dp[{next_x, next_y}],
          dp[{x, y}] + cost[{next_x, next_y}]);
        pq.push({ next_x, next_y, dp[{next_x, next_y}] });
      }
    }
  }

  /* return the minimum cost path at the lower
  right corner */
  return dp[{R - 1, C - 1}] - dp[{0, 0}];
}

/* Driver program to test above functions */
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  string inputLine;
  map<pair<int, int>, int> cost;
  R = 0;
  vector<string> input;
  while (getline(cin, inputLine))
  {
    int nr2 = 0;
    for (auto i : inputLine)
    {
      cost[{R, nr2}] = i - '0';
      nr2++;
    }
    input.push_back(inputLine);
    R++;
  }
  C = inputLine.size();
  cout << "Part 1: " << minCost(cost, 0, 0) << endl;

  vector<string> input2 = input;
  for (int k = 1; k < 5; k++)
  {
    int offset = C * k;
    int line = 0;
    for (auto i : input)
    {
      string s = i;
      int column = 0;
      for (auto j : i)
      {
        cost[{line, offset + column}] = cost[{line, column}] + k;
        if (cost[{line, offset + column}] >= 10)
        {
          cost[{line, offset + column}] %= 10;
          cost[{line, offset + column}]++;
        }
        input2[line] += to_string(cost[{line, offset + column}]);
        column++;
      }
      line++;
    }
  }
  C = C * 5;
  for (int k = 1; k < 5; k++)
  {
    int offset = R * k;
    int line = 0;
    for (auto i : input2)
    {
      int column = 0;
      for (auto j : i)
      {
        cost[{offset + line, column}] = cost[{line, column}] + k;
        if (cost[{offset + line, column}] >= 10)
        {
          cost[{offset + line, column}] %= 10;
          cost[{offset + line, column}] ++;
        }
        column++;

      }
      line++;
    }
  }
  R = R * 5;
  cout << "Part 2: " << minCost(cost, 0, 0) << endl;

  return 0;
}
