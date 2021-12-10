#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<string> split(string line, string delimiters = ",./;")
{
  vector<string> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(line.substr(0, index));
  }

  while (index != -1) {
    index++;
    line = line.substr(index, line.length() - index);
    index = line.find_first_of(delimiters);
    auto newWord = line.substr(0, index);
    if (!newWord.empty())
    {
      words.push_back(newWord);
    }
  }
  return words;
}

int segmentToInt(string segment)
{
  sort(segment.begin(), segment.end());
  map<string, int> segmentToInt
  {
    {"abcefg", 0},
    {"cf", 1},
    {"acdeg", 2},
    {"acdfg", 3},
    {"bcdf", 4},
    {"abdfg", 5},
    {"abdefg", 6},
    {"acf", 7},
    {"abcdefg", 8},
    {"abcdfg", 9}
  };
  return segmentToInt[segment];
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  map<char, char> m;

  long long sumPart1 = 0;
  long long sumPart2 = 0;

  string line;
  while (getline(cin, line)) {

    map<char, int> lettersFrequency;

    auto lineWords = split(line, "|");
    auto theFirst10Words = split(lineWords[0], " ");
    auto theLast4Words = split(lineWords[1], " ");

    string fourLetter;
    string eightLetter;
    string oneLetter;

    for (auto& word : theFirst10Words)
    {
      if (word.size() == 4)
      {
        fourLetter = word;
      }
      if (word.size() == 7)
      {
        eightLetter = word;
      }
      if (word.size() == 2)
      {
        oneLetter = word;
      }

      for (auto letter : word)
      {
        lettersFrequency[letter]++;
      }
    }

    for (auto letter : lettersFrequency)
    {
      if (letter.second == 6)
      {
        m[letter.first] = 'b';
      }
    }
    for (auto letter : oneLetter)
    {
      if (lettersFrequency[letter] == 9)
      {
        m[letter] = 'f';
      }
      if (lettersFrequency[letter] == 8)
      {
        m[letter] = 'c';
      }

    }
    for (auto letter : fourLetter)
    {
      if (lettersFrequency[letter] == 7)
      {
        m[letter] = 'd';
        lettersFrequency[letter] = 0;
      }
      if (lettersFrequency[letter] == 8)
      {
        m[letter] = 'c';
        lettersFrequency[letter] = 0;
      }

    }
    for (auto letter : eightLetter)
    {

      if (lettersFrequency[letter] == 8)
      {
        m[letter] = 'a';
        lettersFrequency[letter] = 0;
      }
      if (lettersFrequency[letter] == 7)
      {
        m[letter] = 'g';
        lettersFrequency[letter] = 0;
      }
      if (lettersFrequency[letter] == 4)
      {
        m[letter] = 'e';
        lettersFrequency[letter] = 0;
      }

    }

    int numberOfFourDigits = 0;
    for (auto word : theLast4Words)
    {
      string newWord = "";
      for (auto letter : word)
      {
        newWord += m[letter];
      }
      int number = segmentToInt(newWord);
      numberOfFourDigits = numberOfFourDigits * 10 + number;
      if (number == 1 || number == 4 || number == 7 || number == 8)
      {
        sumPart1++;
      }
    }
    sumPart2 += numberOfFourDigits;
  }

  cout << "Part 1: " << sumPart1 << endl;
  cout << "Part 2: " << sumPart2 << endl;
}