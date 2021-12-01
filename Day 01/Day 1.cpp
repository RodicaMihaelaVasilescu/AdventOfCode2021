#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int number, currentIndex = 0;
  int previousNumber = INT_MAX, previousSum = INT_MAX;
  int part1 = 0, part2 = 0;

  vector<int> numbers;

  while (cin >> number)
  {
    numbers.push_back(number);
    if (number > previousNumber)
    {
      part1++;
    }
    previousNumber = number;

    if (currentIndex >= 2)
    {
      int sum = numbers[currentIndex - 2] + numbers[currentIndex - 1] + numbers[currentIndex];
      if (sum > previousSum)
      {
        part2++;
      }
      previousSum = sum;
    }
    currentIndex++;
  }

  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
}