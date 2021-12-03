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

string getGammaRate(vector<string> binaryNumbers)
{
  map<int, int> frequencyBit1;
  map<int, int> frequencyBit0;

  string gamma = binaryNumbers[0];

  for (auto number : binaryNumbers)
  {
    for (int bitIndex = 0; bitIndex < number.size(); bitIndex++)
    {
      if (number[bitIndex] == '0')
      {
        frequencyBit0[bitIndex]++;
      }
      else
      {
        frequencyBit1[bitIndex]++;
      }

      gamma[bitIndex] = frequencyBit1[bitIndex] >= frequencyBit0[bitIndex] ? '1' : '0';
    }
  }
  return gamma;
}

string getEpsilonRate(vector<string> binaryNumbers)
{
  map<int, int> frequencyBit1;
  map<int, int> frequencyBit0;

  string gamma = binaryNumbers[0];

  for (auto number : binaryNumbers)
  {
    for (int bitIndex = 0; bitIndex < number.size(); bitIndex++)
    {
      if (number[bitIndex] == '0')
      {
        frequencyBit0[bitIndex]++;
      }
      else
      {
        frequencyBit1[bitIndex]++;
      }

      gamma[bitIndex] = frequencyBit1[bitIndex] < frequencyBit0[bitIndex] ? '1' : '0';
    }
  }
  return gamma;
}

vector<string> getBinaryNumbersHavingSpecifiedRateIndex(vector<string> binaryNumbers, int index, char rate)
{
  vector<string> binaryNumbersHavingSpecifiedRate;

  for (auto number : binaryNumbers)
  {
    if (number[index] == rate)
    {
      binaryNumbersHavingSpecifiedRate.push_back(number);
    }
  }
  return binaryNumbersHavingSpecifiedRate;
}

string getOxygenGeneratorRating(vector<string> binaryNumbers)
{
  int index = 0;
  while (binaryNumbers.size() != 1)
  {
    auto gamma = getGammaRate(binaryNumbers);
    binaryNumbers = getBinaryNumbersHavingSpecifiedRateIndex(binaryNumbers, index, gamma[index]);
    index++;
  }
  return binaryNumbers[0];
}

string getCO2ScrubberRating(vector<string> binaryNumbers)
{
  int index = 0;
  while (binaryNumbers.size() != 1)
  {
    auto epsilon = getEpsilonRate(binaryNumbers);
    binaryNumbers = getBinaryNumbersHavingSpecifiedRateIndex(binaryNumbers, index, epsilon[index]);
    index++;
  }
  return binaryNumbers[0];
}

int binaryToDecimal(string binaryNumber)
{
  return stoi(binaryNumber, 0, 2);
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);


  string binaryNumber;
  vector<string> binaryNumbers;

  while (cin >> binaryNumber)
  {
    binaryNumbers.push_back(binaryNumber);
  }

  auto gamma = getGammaRate(binaryNumbers);
  auto epsilon = getEpsilonRate(binaryNumbers);
  cout << "Part 1: " << binaryToDecimal(gamma) * binaryToDecimal(epsilon) << endl;

  auto oxygenGeneratorRating = getOxygenGeneratorRating(binaryNumbers);
  auto CO2ScrubberRating = getCO2ScrubberRating(binaryNumbers);
  cout << "Part 2: " << binaryToDecimal(oxygenGeneratorRating) * binaryToDecimal(CO2ScrubberRating) << endl;
}