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

vector<string> split(string line, string delimiters = ",./;= ->")
{
  vector<string> words;
  if (line.empty())
  {
    return words;
  }

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


unsigned long long getDifferenceBetweenMinAndMaxValue(map<char, unsigned long long > mapping)
{
  unsigned long long Min = ULLONG_MAX, Max = 0;
  for (auto letterValuePair : mapping)
  {
    Max = max(letterValuePair.second, Max);
    Min = min(letterValuePair.second, Min);
  }
  return Max - Min;
}

map<string, unsigned long long> computeNextMapping(map<string, string> polymersMapping, map<string, unsigned long long> twoLettersFrequency)
{
  map<string, unsigned long long> newMappingOfTwoLettersFrequency;
  for (auto twoLettersFrequencyPair : twoLettersFrequency)
  {
    // for each ab -> c, add two pairs: ac, cb 
    string a = string(1, twoLettersFrequencyPair.first[0]);
    string b = string(1, twoLettersFrequencyPair.first[1]);
    string c = polymersMapping[twoLettersFrequencyPair.first];
    string ac = a + c;
    string cb = c + b;
    newMappingOfTwoLettersFrequency[ac] += twoLettersFrequency[twoLettersFrequencyPair.first];
    newMappingOfTwoLettersFrequency[cb] += twoLettersFrequency[twoLettersFrequencyPair.first];
  }
  return newMappingOfTwoLettersFrequency;
}

map<char, unsigned long long > getLettersFrequency(string polymerTemplate, map<string, unsigned long long> twoLettersFrequencyMapping)
{
  map<char, unsigned long long > firstLetterFrequency;
  for (auto twoLettersFrequencyPair : twoLettersFrequencyMapping)
  {
    firstLetterFrequency[twoLettersFrequencyPair.first[0]] += twoLettersFrequencyMapping[twoLettersFrequencyPair.first];
  }
  firstLetterFrequency[polymerTemplate[polymerTemplate.size() - 1]]++;
  return firstLetterFrequency;
}

map<string, unsigned long long> getTwoLettersFrequencyMapping(string polymerTemplate)
{
  map<string, unsigned long long> twoLettersFrequencyMapping;
  for (int i = 0; i < polymerTemplate.size() - 1; i++)
  {
    string twoLettersPair;
    twoLettersPair += polymerTemplate[i];
    twoLettersPair += polymerTemplate[i + 1];
    twoLettersFrequencyMapping[twoLettersPair] ++;
  }
  return twoLettersFrequencyMapping;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string polymerTemplate;
  map<string, string> polymersMapping;
  map<char, unsigned long long int> frequency;

  string line;
  while (getline(cin, line)) {
    if (line.empty())
    {
      continue;
    }
    auto words = split(line);
    if (words.size() == 1)
    {
      polymerTemplate = line;
      continue;
    }
    polymersMapping[words[0]] = words[1];
  }

  //example: for NNCB, twoLettersFrequencyMapping has {NN,1}, {NC,1}, {CB,1}
  map<string, unsigned long long> twoLettersFrequencyMapping = getTwoLettersFrequencyMapping(polymerTemplate);

  for (int step = 0; step <= 40; step++)
  {
    if (step == 10 || step == 40)
    {
      map<char, unsigned long long > lettersFrequencyMap = getLettersFrequency(polymerTemplate, twoLettersFrequencyMapping);
      cout << getDifferenceBetweenMinAndMaxValue(lettersFrequencyMap) << endl;
    }
    // characters from a string "abcdef" will result in a new string: "a" + mapping of "ab" , "b" + mapping of "bc", ... , + "f" 
    // in other words,the characters will be:
    // the mappings of "ab", "bc", "cd", .. "ef"
    // the first letter of every mapping "ab", "bc", "cd", "de", "ef" => "a", "b", "c", "d", "e"
    // the last letter of the string, "f"
    twoLettersFrequencyMapping = computeNextMapping(polymersMapping, twoLettersFrequencyMapping);
  }
}