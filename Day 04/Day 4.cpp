#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> split(string line, string delimiters = ",./; ")
{
  vector<int> words;

  int index = line.find_first_of(delimiters);
  if (!line.substr(0, index).empty())
  {
    words.push_back(stoi(line.substr(0, index)));
  }

  while (index != string::npos) {
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

bool hasSameLine(vector<vector<int>> matrix, set<int> subset)
{
  for (auto line : matrix)
  {
    bool hasLineDistinctNumbers = false;
    for (auto number : line)
    {
      if (subset.find(number) == subset.end())
      {
        hasLineDistinctNumbers = true;
      }
    }
    if (!hasLineDistinctNumbers)
    {
      return true;
    }
  }
  return false;
}

bool hasSameColumn(vector<vector<int>> matrix, set<int> subset)
{
  for (int columnIndex = 0; columnIndex != matrix[0].size(); columnIndex++)
  {
    vector<int> column;
    bool hasColumnDistinctNumbers = false;

    for (auto line : matrix)
    {
      if (subset.find(line[columnIndex]) == subset.end())
      {
        hasColumnDistinctNumbers = true;
      }
    }
    if (!hasColumnDistinctNumbers)
    {
      return true;
    }
  }
}

vector<int> getListOfWinnerBoards(vector<vector<vector<int>>> bingoSubsystem, set <int> subset)
{
  vector<int>indexes;
  int index = 0;

  for (auto matrix : bingoSubsystem)
  {
    if (hasSameLine(matrix, subset) || hasSameColumn(matrix, subset))
    {
      indexes.insert(indexes.begin(), index);
    }
    index++;
  }

  return indexes;
}

int getSumUnmarkedNumbers(vector<vector<int>> matrix, set<int> numbers)
{
  int sum = 0;
  for (auto line : matrix)
  {
    for (auto number : line)
    {
      if (find(numbers.begin(), numbers.end(), number) == numbers.end())
      {
        sum += number;
      }
      else
      {
        int nt = 0;
      }
    }
  }
  return sum;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  cin >> line;
  vector<int> numbers = split(line);

  vector<vector<vector<int>>> bingoSubsystem;

  vector<vector<int>> matrix;

  while (getline(cin, line))
  {
    if (line.empty())
    {
      if (matrix.size() != 0)
      {
        bingoSubsystem.push_back(matrix);
      }
      matrix.clear();
    }
    else
    {
      matrix.push_back(split(line));
    }
  }

  bingoSubsystem.push_back(matrix);

  int subsetSize = 4;

  set<int> selectedNumbers;

  map<int, int> frequencyWinners;

  int solutionPart1 = 0;
  int solutionPart2 = 0;

  for (int i = 0; i < numbers.size(); i++)
  {
    selectedNumbers.insert(numbers[i]);

    auto winners = getListOfWinnerBoards(bingoSubsystem, selectedNumbers);
    if (winners.size() != 0)
    {
      if (solutionPart1 == 0)
      {
        solutionPart1 = getSumUnmarkedNumbers(bingoSubsystem[winners[0]], selectedNumbers) * numbers[i];
      }

      for (auto index : winners)
      {
        if (frequencyWinners[index] == 0)
        {
          solutionPart2 = getSumUnmarkedNumbers(bingoSubsystem[index], selectedNumbers) * numbers[i];
        }
        frequencyWinners[index]++;
      }
    }
  }

  cout << "Part 1: " << solutionPart1 << endl;
  cout << "Part 2: " << solutionPart2 << endl;
}