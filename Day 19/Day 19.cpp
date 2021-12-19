#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct beacon
{
  int x, y, z;

  beacon(int a, int b, int c)
  {
    x = a;
    y = b;
    z = c;
  }
};

inline bool operator< (const beacon& b1, const beacon& b2)
{
  return b1.x < b2.x || b1.x == b2.x && b1.y < b2.y || b1.x == b2.x && b1.y == b2.y && b1.z < b2.z;
}

vector<int> splitStringToVectorInt(string line, string delimiters = ",./;")
{
  vector<int> words;

  auto index = line.find_first_of(delimiters);
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

beacon coordinates(-1, -1, -1);

bool doScannersSeeAtLeast12Beacons(vector<beacon> beacon1, vector<beacon>& beacon2)
{
  map<string, map<int, int>> operation_resultFrequency;

  for (auto b1 : beacon1)
  {
    for (auto b2 : beacon2)
    {
      operation_resultFrequency[{"x+x"}][b1.x + b2.x]++;
      operation_resultFrequency[{"x+y"}][b1.x + b2.y]++;
      operation_resultFrequency[{"x+z"}][b1.x + b2.z]++;
      operation_resultFrequency[{"x-x"}][b1.x - b2.x]++;
      operation_resultFrequency[{"x-y"}][b1.x - b2.y]++;
      operation_resultFrequency[{"x-z"}][b1.x - b2.z]++;

      operation_resultFrequency[{"y+x"}][b1.y + b2.x]++;
      operation_resultFrequency[{"y+y"}][b1.y + b2.y]++;
      operation_resultFrequency[{"y+z"}][b1.y + b2.z]++;
      operation_resultFrequency[{"y-x"}][b1.y - b2.x]++;
      operation_resultFrequency[{"y-y"}][b1.y - b2.y]++;
      operation_resultFrequency[{"y-z"}][b1.y - b2.z]++;

      operation_resultFrequency[{"z+x"}][b1.z + b2.x]++;
      operation_resultFrequency[{"z+y"}][b1.z + b2.y]++;
      operation_resultFrequency[{"z+z"}][b1.z + b2.z]++;
      operation_resultFrequency[{"z-x"}][b1.z - b2.x]++;
      operation_resultFrequency[{"z-y"}][b1.z - b2.y]++;
      operation_resultFrequency[{"z-z"}][b1.z - b2.z]++;
    }
  }

  int maximumFrequency = 0;
  map<char, char> axesMapping;
  map<char, char> sign;

  for (auto opResFr : operation_resultFrequency)
  {
    for (auto resultFrequency : opResFr.second)
    {
      maximumFrequency = max(maximumFrequency, resultFrequency.second);
      if (resultFrequency.second >= 12)
      {
        axesMapping[opResFr.first[0]] = opResFr.first[2];
        sign[opResFr.first[0]] = opResFr.first[1];
        opResFr.first[0] == 'x' ? coordinates.x = resultFrequency.first :
          opResFr.first[0] == 'y' ? coordinates.y = resultFrequency.first : coordinates.z = resultFrequency.first;
      }
    }
  }

  if (maximumFrequency >= 12)
  {
    for (auto& beacon : beacon2)
    {
      int a = axesMapping['x'] == 'x' ? beacon.x : axesMapping['x'] == 'y' ? beacon.y : beacon.z;
      int b = axesMapping['y'] == 'x' ? beacon.x : axesMapping['y'] == 'y' ? beacon.y : beacon.z;
      int c = axesMapping['z'] == 'x' ? beacon.x : axesMapping['z'] == 'y' ? beacon.y : beacon.z;

      beacon.x = sign['x'] == '+' ? coordinates.x - a : coordinates.x + a;
      beacon.y = sign['y'] == '+' ? coordinates.y - b : coordinates.y + b;
      beacon.z = sign['z'] == '+' ? coordinates.z - c : coordinates.z + c;
    }
    return true;
  }

  return false;
}

map<int, vector <beacon>> readInput()
{
  map<int, vector <beacon>> scanners;

  string line;
  int scannerId = -1;

  while (getline(cin, line)) {
    if (line.empty())
    {
      continue;
    }
    if (line.find("scanner") != string::npos)
    {
      scannerId++;
    }
    else
    {
      auto coordinates = splitStringToVectorInt(line);
      beacon b(coordinates[0], coordinates[1], coordinates[2]);
      scanners[scannerId].push_back(b);
    }
  }
  return scanners;
}

int getDistanceBetweenTwoBeacons(beacon i, beacon j)
{
  return sqrt(pow(i.x - j.x, 2) + pow(i.y - j.y, 2) + pow(i.z - j.z, 2));
}

int getManhattanDistance(beacon i, beacon j)
{
  return abs(i.x - j.x) + abs(i.y - j.y) + abs(i.z - j.z);
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  map<int, vector <beacon>> scanners = readInput();

  queue<int> scannersMappedToZero;
  scannersMappedToZero.push(0);

  map<int, bool> isScannerMappedToZero;
  isScannerMappedToZero[0] = true;

  set<beacon> scannersCoordinatesToZero;
  while (!scannersMappedToZero.empty())
  {
    auto scannerId = scannersMappedToZero.front();
    scannersMappedToZero.pop();

    for (auto& scanner : scanners)
    {
      if (!isScannerMappedToZero[scanner.first])
      {
        if (doScannersSeeAtLeast12Beacons(scanners[scannerId], scanner.second))
        {
          scannersMappedToZero.push(scanner.first);
          isScannerMappedToZero[scanner.first] = true;
          scannersCoordinatesToZero.insert(coordinates);
        }
      }
    }
  }

  set<beacon> allBeaconsMappedToZero;

  for (auto i : scanners)
  {
    for (auto j : i.second)
    {
      allBeaconsMappedToZero.insert(j);
    }
  }

  cout << "Part 1: " << allBeaconsMappedToZero.size() << endl;

  int maximumDistance = 0;

  for (auto i : scannersCoordinatesToZero)
  {
    for (auto j : scannersCoordinatesToZero)
    {
      maximumDistance = max(maximumDistance, getManhattanDistance(i, j));
    }
  }

  cout << "Part 2: " << maximumDistance << endl;
}