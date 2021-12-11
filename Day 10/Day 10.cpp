#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>

using namespace std;

vector<long long> scoresPart2;

long long getScore(string brackets)
{
  deque <char> openBrackets;

  map<char, bool> isClosingBracket;
  isClosingBracket[')'] = true;
  isClosingBracket['}'] = true;
  isClosingBracket[']'] = true;
  isClosingBracket['>'] = true;

  map<char, char> correspondingBracket;
  correspondingBracket['('] = ')';
  correspondingBracket[')'] = '(';
  correspondingBracket['['] = ']';
  correspondingBracket[']'] = '[';
  correspondingBracket['{'] = '}';
  correspondingBracket['}'] = '{';
  correspondingBracket['<'] = '>';
  correspondingBracket['>'] = '<';

  map<char, int> scoringPart1;
  scoringPart1[')'] = 3;
  scoringPart1[']'] = 57;
  scoringPart1['}'] = 1197;
  scoringPart1['>'] = 25137;

  map<char, int> scoringPart2;
  scoringPart2[')'] = 1;
  scoringPart2[']'] = 2;
  scoringPart2['}'] = 3;
  scoringPart2['>'] = 4;

  for (char bracket : brackets)
  {
    if (!isClosingBracket[bracket])
    {
      openBrackets.push_front(bracket);
    }
    else if (isClosingBracket[bracket])
    {
      if (openBrackets.front() == correspondingBracket[bracket])
      {
        openBrackets.pop_front();
      }
      else
      {
        return scoringPart1[bracket];
      }
    }
  }

  long long score = 0;
  while (!openBrackets.empty())
  {
    char closedBracket = correspondingBracket[openBrackets.front()];
    score = score * 5 + scoringPart2[closedBracket];
    openBrackets.pop_front();
  }
  scoresPart2.push_back(score);

  return 0;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;

  long long sumPart1 = 0;
  while (cin >> line)
  {
    sumPart1 += getScore(line);
  }

  sort(scoresPart2.begin(), scoresPart2.end());
  long long part2 = 0;
  if (!scoresPart2.empty())
  {
    part2 = scoresPart2[scoresPart2.size() / 2];
  }

  cout << "Part 1: " << sumPart1 << endl;
  cout << "Part 2: " << part2 << endl;
}