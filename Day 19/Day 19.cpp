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
#include <queue>

using namespace std;


vector<int> splitToInt(string line, string delimiters = ",./;")
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

set<beacon> solutionPart1;
map<int, bool> mappedTo0;
beacon coordinates(-1, -1, -1);
map<int, beacon> mapFinalCoordinates;
bool getNumberOfCommonBeacons(int id, int id2, vector<beacon> beacon1, vector<beacon>& beacon2)
{
  int common = 0;
  map<string, map<int, int>> fr;
  map<string, int> maximum;
  int i = 0;

  for (auto b1 : beacon1)
  {
    int j = 0;
    for (auto b2 : beacon2)
    {
      fr[{"x+x"}][b1.x + b2.x]++;
      fr[{"x+y"}][b1.x + b2.y]++;
      fr[{"x+z"}][b1.x + b2.z]++;
      fr[{"x-x"}][b1.x - b2.x]++;
      fr[{"x-y"}][b1.x - b2.y]++;
      fr[{"x-z"}][b1.x - b2.z]++;

      fr[{"y+x"}][b1.y + b2.x]++;
      fr[{"y+y"}][b1.y + b2.y]++;
      fr[{"y+z"}][b1.y + b2.z]++;
      fr[{"y-x"}][b1.y - b2.x]++;
      fr[{"y-y"}][b1.y - b2.y]++;
      fr[{"y-z"}][b1.y - b2.z]++;

      fr[{"z+x"}][b1.z + b2.x]++;
      fr[{"z+y"}][b1.z + b2.y]++;
      fr[{"z+z"}][b1.z + b2.z]++;
      fr[{"z-x"}][b1.z - b2.x]++;
      fr[{"z-y"}][b1.z - b2.y]++;
      fr[{"z-z"}][b1.z - b2.z]++;

      j++;
    }
    i++;
  }

  int MAX = 0;
  int x = -1, y = -1, z = -1;
  vector<int> v;

  vector<string> rotations{ "","","" };
  map<char, char> m;
  map<char, char> sign;
  for (auto i : fr)
  {
    int Max = 0;
    for (auto j : i.second)
    {
      Max = max(Max, j.second);
      MAX = max(Max, MAX);
      if (j.second >= 12)
      {
        int bkp = 0;
        m[i.first[0]] = i.first[2];
        if (i.first[0] == 'x')
        {
          x = j.first;
          rotations[0] = i.first;
          sign[i.first[2]] = i.first[1];
        }
        else if (i.first[0] == 'y')
        {
          y = j.first;
          rotations[1] = i.first;
          sign[i.first[2]] = i.first[1];
        }
        else if (i.first[0] == 'z')
        {
          z = j.first;
          rotations[2] = i.first;
          sign[i.first[2]] = i.first[1];
        }
      }
    }
    maximum[i.first] = Max;
  }
  int id3 = id;
  int id4 = id2;
  coordinates.x = x;
  coordinates.y = y;
  coordinates.z = z;
  if (id == 4 && id2 == 2)
  {
    int bkp = 0;
  }
  if (MAX >= 12 && !mappedTo0[id2])
  {
    mappedTo0[id2] = true;
    for (auto& i : beacon2)
    {
      if (i.x == 686)
      {
        int bkp = 0;
      }
      beacon p(0, 0, 0);
      //int a, b, c;
      //if (m['x'] == 'x') a = x; else if (m['x'] == 'y') a = y; else a = z;
      //if (m['y'] == 'x') b = x; else if (m['y'] == 'y') b = y; else b = z;
      //if (m['z'] == 'x') c = x; else if (m['z'] == 'y') c = y; else c = z;

   /*   if (sign['x'] == '-') p.x = i.x - a; else p.x = a - i.x;
      if (sign['y'] == '-') p.y = i.y - b; else p.y = b - i.y;
      if (sign['z'] == '-') p.z = i.z - c; else p.z = c - i.z;*/
      if (rotations[0] == "x+x")
      {
        p.x = x - i.x;
      }
      if (rotations[0] == "x+y")
      {
        p.x = x - i.y;
      }
      if (rotations[0] == "x+z")
      {
        p.x = x - i.z;
      }
      if (rotations[0] == "x-x")
      {
        p.x = x + i.x;
      }
      if (rotations[0] == "x-y")
      {
        p.x = x + i.y;
      }
      if (rotations[0] == "x-z")
      {
        p.x = x + i.z;
      }
      //----------------------------------------
      if (rotations[1] == "y+x")
      {
        p.y = y - i.x;
      }
      if (rotations[1] == "y+y")
      {
        p.y = y - i.y;
      }
      if (rotations[1] == "y+z")
      {
        p.y = y - i.z;
      }
      if (rotations[1] == "y-x")
      {
        p.y = y + i.x;
      }
      if (rotations[1] == "y-y")
      {
        p.y = y + i.y;
      }
      if (rotations[1] == "y-z")
      {
        p.y = y + i.z;
      }
      //------------------------------------------------

      if (rotations[2] == "z+x")
      {
        p.z = z - i.x;
      }
      if (rotations[2] == "z+y")
      {
        p.z = z - i.y;
      }
      if (rotations[2] == "z+z")
      {
        p.z = z - i.z;
      }
      if (rotations[2] == "z-x")
      {
        p.z = z + i.x;
      }
      if (rotations[2] == "z-y")
      {
        p.z = z + i.y;
      }
      if (rotations[2] == "z-z")
      {
        p.z = z + i.z;
      }

      i = p;
      solutionPart1.insert(p);
    }
  }

  return MAX >= 12;
}

int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  string line;
  int scanner = -1;
  map<int, vector <beacon>> scannerMap;
  while (getline(cin, line)) {
    int i = line.find("scanner ");
    if (i == -1 && !line.empty())
    {
      auto words = splitToInt(line);
      beacon b(words[0], words[1], words[2]);
      scannerMap[scanner].push_back(b);
    }
    else if (i > -1)
    {
      scanner++;
    }
  }
  for (auto& i : scannerMap)
  {
    sort(i.second.begin(), i.second.end(), [](beacon b1, beacon b2)
      {
        return b1.x < b2.x || b1.x == b2.x && b1.y < b2.y || b1.x == b2.x && b1.y == b2.y && b1.z < b2.z;
      });
  }
  map<pair<int, int>, tuple<int, int, int>> myMap;
  queue<int> mappedToZero;
  mappedToZero.push(0);
  map<int, bool> visited;
  set<beacon> final;
  while (!mappedToZero.empty())
  {
    auto i = mappedToZero.front();
    mappedToZero.pop();
    for (auto j = 0; j < scannerMap.size(); j++)
    {
      if (!visited[i] && !visited[j] && i != j)
      {
        if (getNumberOfCommonBeacons(i, j, scannerMap[i], scannerMap[j])) {
          myMap[{i, j}] = { coordinates.x, coordinates.y, coordinates.z };
          mappedToZero.push(j);
          final.insert(coordinates);
          //cout << i << ", " << j << ": " << coordinates.x << ", " << coordinates.y << ", " << coordinates.z << endl;

        }
      }
    }
    visited[i] = true;
  }
  set<beacon> solutionPart1;

  long long max1 = 0;
  long long max2 = 0;

  beacon bmax1(0, 0, 0);
  beacon bmax2(0, 0, 0);


  for (auto i : scannerMap)
  {
    //cout << i.first << ": " << endl;
    for (auto j : i.second)
    {
      solutionPart1.insert(j);
      //cout << j.x << "," << j.y << "," << j.z << endl;
    }
    //cout << "---------------------------\n";
  }
  cout << "Part 1: " << solutionPart1.size() << endl;

  for (auto i : final)
  {
    for (auto j : final)
    {
      if (!(i.x == j.x && i.y == j.y && i.z == j.z))
      {
        long long distance = sqrt(pow(i.x - j.x, 2) + pow(i.y - j.y, 2) + pow(i.z - j.z, 2));
        if (distance > max1)
        {
          max1 = distance;
          bmax1 = i;
          bmax2 = j;
        }
      }
    }
  }
  //cout << "---------------------------\n";

  cout << "Part 2: " << abs(bmax1.x - bmax2.x) + abs(bmax1.y - bmax2.y) + abs(bmax1.z - bmax2.z) << endl;

}