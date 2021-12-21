#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <sstream>
#include <queue>

using namespace std;

vector<string> split(string line, string delimiters = ",./;")
{
  vector<string> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty()) {
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

int increaseDice(int& dice)
{
  dice = dice % 100 + 1;
  return dice;
}

int solvePart1(int pos1, int pos2, int score1 = 0, int score2 = 0, bool isPlayer1turn = true, int dice = 0, int totalDice = 0)
{
  int prevScore1 = score1, prevScore2 = score2;
  if (isPlayer1turn)
  {
    int sum = increaseDice(dice) + increaseDice(dice) + increaseDice(dice);
    pos1 = (pos1 - 1 + sum) % 10 + 1;
    score1 += pos1;
  }
  else
  {
    int sum = increaseDice(dice) + increaseDice(dice) + increaseDice(dice);
    pos2 = (pos2 - 1 + sum) % 10 + 1;
    score2 += pos2;
  }
  totalDice += 3;
  int losingScore = -1;
  if (score1 >= 1000)
  {
    losingScore = prevScore2;
  }
  else if (score2 >= 1000)
  {
    losingScore = prevScore1;
  }
  if (losingScore > 0)
  {
    return losingScore * totalDice;
  }
  solvePart1(pos1, pos2, score1, score2, !isPlayer1turn, dice, totalDice);
}

map<tuple<int, int, long long, long long>, pair<long long, long long>> dp;

pair<long long, long long> solvePart2(int player1, int player2, long long score1 = 0, long long score2 = 0) {
  if (score1 >= 21 || score2 >= 21)
  {
    return { score1 >= 21, score2 >= 21 };
  }

  if (dp.find({ player1, player2, score1, score2 }) != dp.end())
  {
    return dp[{player1, player2, score1, score2}];
  }

  pair<long long, long long> result;

  for (int dice1 = 1; dice1 <= 3; dice1++)
  {
    for (int dice2 = 1; dice2 <= 3; dice2++)
    {
      for (int dice3 = 1; dice3 <= 3; dice3++)
      {
        auto aux = solvePart2(player2, (player1 + dice1 + dice2 + dice3) % 10, score2, score1 + (player1 + dice1 + dice2 + dice3) % 10 + 1);
        result = { result.first + aux.second, result.second + aux.first };
      }
    }
  }

  dp[{player1, player2, score1, score2}] = result;
  return dp[{player1, player2, score1, score2}];
}


int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string s;
  getline(cin, s);
  long long positionPlayer1 = stoll(split(s, " :")[4]);

  getline(cin, s);
  long long positionPlayer2 = stoll(split(s, " :")[4]);

  cout << "Part 1: " << solvePart1(positionPlayer1, positionPlayer2) << endl;
  auto winners = solvePart2(positionPlayer1 - 1, positionPlayer2 - 1);
  cout << "Part 2: " << max(winners.first, winners.second);
}