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
#include <stack>

using namespace std;

int getScore(string line)
{
  int score = 0;
  stack <char> brackets;

  map<char, bool> isClosingBracket;
  isClosingBracket[')'] = true;
  isClosingBracket['}'] = true;
  isClosingBracket[']'] = true;
  isClosingBracket['>'] = true;

  map<char, char> closingBracket;
  closingBracket['('] = ')';
  closingBracket['['] = ']';
  closingBracket['{'] = '}';
  closingBracket['<'] = '>';

  map<char, char> openingBracket;
  openingBracket[')'] = '(';
  openingBracket[']'] = '[';
  openingBracket['}'] = '{';
  openingBracket['>'] = '<';

  map<char, int> scoring;
  scoring[')'] = 3;
  scoring[']'] = 57;
  scoring['}'] = 1197;
  scoring['>'] = 25137;

  for (char ch : line)
  {
    if (!isClosingBracket[ch])
    {
      brackets.push(ch);
    }
    else if (isClosingBracket[ch])
    {
      if (brackets.top() == openingBracket[ch])
      {
        brackets.pop();
      }
      else
      {
        return scoring[ch];
      }
    }
  }

  return score;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;

  int sum = 0;
  while (cin >> line)
  {
    sum += getScore(line);
  }

  cout << sum;
}