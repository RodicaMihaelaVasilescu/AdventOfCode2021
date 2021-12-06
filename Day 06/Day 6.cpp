#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <map>

using namespace std;

long long getSolution(string line, int number)
{
  map<int, long long> frequencyOfNumbers;

  for (auto ch : line)
  {
    if (ch != ',')
    {
      frequencyOfNumbers[ch - '0']++;
    }
  }

  int counter = 0;
  while (counter < number)
  {
    for (int i = 0; i <= 8; i++)
    {
      frequencyOfNumbers[i - 1] = frequencyOfNumbers[i];
    }
    frequencyOfNumbers[6] += frequencyOfNumbers[-1];
    frequencyOfNumbers[8] = frequencyOfNumbers[-1];
    frequencyOfNumbers[-1] = 0;
    counter++;
  }

  unsigned long long sum = 0;
  for (auto i : frequencyOfNumbers)
  {
    sum += i.second;
  }
  return sum;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string input;
  cin >> input;

  cout << "Part 1: " << getSolution(input, 80) << endl;
  cout << "Part 2: " << getSolution(input, 256) << endl;
}