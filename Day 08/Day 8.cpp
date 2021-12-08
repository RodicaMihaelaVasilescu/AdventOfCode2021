//to do: I'll rewrite this
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
      words.push_back(newWord);
  }
  return words;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  map<char, char> m;
  set<string> configurations;
  long long s = 0;
  map<int, int> lettersFr;
  int sum2 = 0;
  while (getline(cin, line)) {

    map<char, int> lettersFrequency;
    map<string, int> wordSize;

    auto input_output = split(line, "|");
    auto words = split(input_output[0], " ");
    auto outputWords = split(input_output[1], " ");

    string fourLetter;
    string eightLetter;
    string oneLetter;

    for (auto& word : outputWords)
    {
      sort(word.begin(), word.end());
      if (word.size() == 4 || word.size() == 7 || word.size() == 2 || word.size() == 3)
      {
        sum2++;
      }
    }

    for (auto& word : words)
    {
      sort(word.begin(), word.end());
      configurations.insert(word);
      wordSize[word] = word.size();
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
      if (letter.second == 9)
      {
        m[letter.first] = 'f';
        lettersFrequency[letter.first] = 0;
      }
      if (letter.second == 6)
      {
        m[letter.first] = 'b';
        lettersFrequency[letter.first] = 0;
      }
      if (letter.second == 4)
      {
        m[letter.first] = 'e';
        lettersFrequency[letter.first] = 0;
      }
    }
    for (auto letter : oneLetter)
    {
      if (lettersFrequency[letter] == 9)
      {
        m[letter] = 'f';
        lettersFrequency[letter] = 0;
      }
      if (lettersFrequency[letter] == 8)
      {
        m[letter] = 'c';
        lettersFrequency[letter] = 0;
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

    vector<string> newWords;
    map<string, int> nrs;
    int nr = 0;
    for (auto word : outputWords)
    {
      string newWord = "";
      for (auto letter : word)
      {
        newWord += m[letter];
      }
      newWords.push_back(newWord);
      sort(newWord.begin(), newWord.end());
      if (newWord == "abcefg")
      {
        nr = nr * 10 + 0;
        nrs[newWord] = 0;
      }
      else  if (newWord == "cf")
      {
        nr = nr * 10 + 1;
        nrs[newWord] = 1;
      }
      else  if (newWord == "acdeg")
      {
        nr = nr * 10 + 2;
        nrs[newWord] = 2;
      }
      else  if (newWord == "acdfg")
      {
        nr = nr * 10 + 3;
        nrs[newWord] = 3;
      }
      else  if (newWord == "bcdf")
      {
        nr = nr * 10 + 4;
        nrs[newWord] = 4;
      }
      else  if (newWord == "abdfg")
      {
        nr = nr * 10 + 5;
        nrs[newWord] = 5;
      }
      else  if (newWord == "abdefg")
      {
        nr = nr * 10 + 6;
        nrs[newWord] = 6;
      }
      else  if (newWord == "acf")
      {
        nr = nr * 10 + 7;
        nrs[newWord] = 7;
      }
      else  if (newWord == "abcdefg")
      {
        nr = nr * 10 + 8;
        nrs[newWord] = 8;
      }
      else  if (newWord == "abcdfg")
      {
        nr = nr * 10 + 9;
        nrs[newWord] = 9;
      }
      else
      {
        int bkp = 0;
      }
    }
    s += nr;

  }

  cout << "Part 2: " << s << endl;

}