#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string command;
  int nr;
  pair<long, long> part1, part2;
  long long aim = 0;

  while (cin >> command >> nr)
  {
    if (command == "forward")
    {
      part1.second += nr;

      part2.second += nr;
      part2.first += aim * nr;
    }
    else if (command == "down")
    {
      part1.first += nr;
      aim += nr;
    }
    else if (command == "up")
    {
      part1.first -= nr;
      aim -= nr;
    }
  }

  cout << "Part 1: " << part1.first * part1.second << endl;
  cout << "Part 2: " << part2.first * part2.second << endl;

}