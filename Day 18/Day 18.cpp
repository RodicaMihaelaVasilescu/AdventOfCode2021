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
#include <queue>

using namespace std;

int isThereAPairNestedInside4Pairs(string s, pair<int, int>& p)
{
  int noOfOpenings = 0;
  char lastCh = -1;
  char beforelastCh = -1;
  int indexLastOpenBracket = -1;
  for (int i = 0; i != s.size(); i++)
  {
    // If any pair is nested inside four pairs, the leftmost such pair explodes.
    if (noOfOpenings > 4 && beforelastCh == '[' && lastCh == ',' && s[i] == ']')
    {
      p = { indexLastOpenBracket, i };
      return true;
    }

    if (s[i] == '[')
    {
      noOfOpenings++;
      beforelastCh = lastCh;
      lastCh = s[i];
      indexLastOpenBracket = i;
    }
    else if (s[i] == ']')
    {
      noOfOpenings--;
      beforelastCh = lastCh;
      lastCh = s[i];
    }
    else if (s[i] == ',')
    {
      beforelastCh = lastCh;
      lastCh = s[i];
    }
  }

  return false;
}

pair <int, int> getIndexRightRegularNumber(string s, int i)
{
  int j = 0;
  while (i < s.size())
  {
    if (isdigit(s[i]))
    {
      j = i;
      while (i < s.size() && isdigit(s[i]))
      {
        i++;
      }
      return { j, i - 1 };
    }
    i++;
  }
  return { -1,-1 };
}

pair <int, int> getIndexLeftRegularNumber(string s, int i)
{
  int j = 0;
  while (i >= 0)
  {
    if (isdigit(s[i]))
    {
      j = i;
      while (i >= 0 && isdigit(s[i]))
      {
        i--;
      }
      return { i + 1,j };
    }
    i--;
  }
  return { -1,-1 };
}

pair<int, int> parseStringToInt(string s, pair<int, int> i)
{
  string s2 = s.substr(i.first + 1, i.second - i.first - 1);
  int index = s2.find_first_of(",");
  int value = stoi(s2.substr(0, index));
  return { value,stoi(s2.substr(index + 1, s2.size() - index - 1)) };
}
string explode(string s, pair<int, int> i)
{

  bool isCurrentRegular = 0;
  int isNextRegular = 0;
  int endOfPair = 0;
  auto value = parseStringToInt(s, i);
  pair<int, int> left = getIndexLeftRegularNumber(s, i.first);

  bool replacedWith0 = false;
  pair<int, int> right = getIndexRightRegularNumber(s, i.second);
  if (right != make_pair(-1, -1))
  {
    int rightValue = stoi(s.substr(right.first, right.second - right.first + 1));
    rightValue += value.second;

    s.replace(right.first, right.second - right.first + 1, to_string(rightValue));
    s.replace(i.first, i.second - i.first + 1, "0");
    replacedWith0 = true;
  }

  if (left != make_pair(-1, -1))
  {
    int leftValue = stoi(s.substr(left.first, left.second - left.first + 1));
    leftValue += value.first;
    int i2 = i.first;
    while (s[i2] != ',')
    {
      i2++;
    }
    i2--;
    if (!replacedWith0)
    {
      s.replace(i.first, i.second - i.first + 1, "0");
    }
    s.replace(left.first, left.second - left.first + 1, to_string(leftValue));
  }
  return s;
}

bool canSplit(string s, pair<int, int>& p)
{
  int j = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (isdigit(s[i]))
    {
      j = i;
      while (isdigit(s[j]))
      {
        j++;
      }
      if (j != i + 1)
      {
        p = { i, j - 1 };
        return true;
      }
    }
  }
  return false;
}


string splitSnailfish(string s, pair<int, int> i)
{
  auto value = stoi(s.substr(i.first, i.second - i.first + 1));
  string newPair = "[" + to_string(value / 2) + "," + to_string(value / 2 + value % 2) + "]";
  s.replace(i.first, i.second - i.first + 1, newPair);
  return s;
}


void addSnailfish(string& snailfish)
{
  //If any pair is nested inside four pairs, the leftmost such pair explodes.
  bool stop = false;
  while (!stop)
  {
    pair<int, int> index{ 0,0 };
    stop = true;
    while (isThereAPairNestedInside4Pairs(snailfish, index))
    {
      //cout << "explode ";
      auto newSnailfish = explode(snailfish, index);
      snailfish = newSnailfish;
      //cout << snailfish << endl;
      stop = false;
    }
    while (canSplit(snailfish, index))
    {
      //cout << "split ";
      auto newSnailfish = splitSnailfish(snailfish, index);
      snailfish = newSnailfish;
      //cout << snailfish << endl;
      stop = false;
      while (isThereAPairNestedInside4Pairs(snailfish, index))
      {
        //cout << "explode ";
        auto newSnailfish = explode(snailfish, index);
        snailfish = newSnailfish;;
        //cout << snailfish << endl;
      }
    }
  }
}

bool is_number(const std::string& s)
{
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int getSum(string line)
{
  int sum = 0;
  while (line.size() > 2)
  {
    char beforeLast = 0;
    char last = 0;

    int indexBeforeLast = -1;
    int indexLast = -1;

    int  right = 0;
    int  left = 0;
    for (int i = 0; i != line.size(); i++)
    {
      if (beforeLast == '[' && last == ',' && line[i] == ']')
      {
        int sum = left * 3 + right * 2;
        line.replace(indexBeforeLast, i - indexBeforeLast + 1, to_string(sum));
        if (is_number(line))
        {
          return stoi(line);
        }
        break;
      }
      if (!isdigit(line[i]))
      {
        beforeLast = last;
        last = line[i];
        indexBeforeLast = indexLast;
        indexLast = i;
      }
      if (isdigit(line[i]))
      {
        left = right;
        right = 0;
        while (isdigit(line[i]))
        {
          right = right * 10 + (line[i] - '0');
          i++;
        }
        i--;
      }
    }
  }
  return sum;
}

vector<int> split2(string line, string delimiters = ",./;")
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
    {
      words.push_back(stoi(newWord));
    }
  }
  return words;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  string result = "";

  vector<string> input;
  while (getline(cin, line))
  {
    input.push_back(line);
    if (result == "")
    {
      result = line;
      continue;
    }
    line = "[" + result + "," + line + "]";
    addSnailfish(line);
    result = line;
    //cout << line << endl;

  }
  cout << "Part 1: " << getSum(line) << endl;

  int Max = 0;
  for (auto i : input)
  {
    for (auto j : input)
    {
      if (i != j)
      {
        string line = "[" + i + "," + j + "]";
        addSnailfish(line);
        int x = getSum(line);
        Max = max(x, Max);
      }
    }
  }
  cout << "Part 2: " << Max << endl;
}