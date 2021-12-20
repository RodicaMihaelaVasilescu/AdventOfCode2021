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

vector<int> values;

int getId4(string s, int& i)
{
  string stringOf4Bits;
  bool ok = s[i] - '0';
  do
  {
    ok = s[i] - '0';
    i++;
    stringOf4Bits += s.substr(i, 4);
    i += 4;
  } while (ok);
  long long n = stoll(stringOf4Bits, 0, 2);
  cout << n << endl;
  values.push_back(n);
  return n;
}

void getPacketAndId(string& s, int& sumPackets, int& i)
{
  i = 6;
  if (s.size() < 10)
  {
    return;
  }
  int packetVersion = stoll(s.substr(0, 3), 0, 2);
  sumPackets += packetVersion;
  int id = stoll(s.substr(3, 3), 0, 2);
  int lengthTypeId = s[6] - '0';
  if (id == 0)
  {
    cout << "+\n";
  }
  if (id == 1)
  {
    cout << "*\n";
  }
  if (id == 2)
  {
    cout << "min\n";
  }
  if (id == 3)
  {
    cout << "max\n";
  }
  if (id == 5)
  {
    cout << ">\n";
  }
  if (id == 6)
  {
    cout << "<\n";
  }
  if (id == 7)
  {
    cout << "=\n";
  }


  if (id == 4)
  {
    long long value = getId4(s, i);
    return;
    if (s.size() < 10)
    {
      return;
    }
    s = s.substr(i, s.size() - i);
    getPacketAndId(s, sumPackets, i);
  }
  else if (lengthTypeId == 0)
  {
    string L;
    i++;
    L += s.substr(i, 11);
    long long nrPackets = stoll(L, 0, 2);
    i += 11;
    L = s.substr(11, 15);
    i += 4;
    nrPackets = stoll(L, 0, 2);
    if (s.size() < 10)
    {
      return;
    }
    s.erase(0, i);
    i = 0;
    int ok = true;
    while (nrPackets > 0 && ok)
    {
      getPacketAndId(s, sumPackets, i);
      if (s.size() < 10 || s.size() < i)
      {
        return;
      }
      s.erase(0, i);
      nrPackets -= i;
      i = 0;
      ok = false;
      for (auto x : s)
      {
        if (x != '0')
        {
          ok = true;
        }
      }
    }
  }
  else if (lengthTypeId == 1)
  {
    i++;
    string L = s.substr(i, 11);
    long long nrPackets = stoll(L, 0, 2);
    i += 11;
    if (i > s.size())
    {
      return;
    }
    s.erase(0, i);
    i = 0;
    bool ok = true;
    while (nrPackets > 0 && ok)
    {
      getPacketAndId(s, sumPackets, i);
      s.erase(0, i);
      nrPackets--;
      i = 0;
      ok = false;
      for (auto x : s)
      {
        if (x != '0')
        {
          ok = true;
        }
      }
    }
  }
}
int main()
{
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  map<string, string> hexaToBinary{
   {"0" , "0000"},
   {"1" , "0001"},
   {"2" , "0010"},
   {"3" , "0011"},
   {"4" , "0100"},
   {"5" , "0101"},
   {"6" , "0110"},
   {"7" , "0111"},
   {"8" , "1000"},
   {"9" , "1001"},
   {"A" , "1010"},
   {"B" , "1011"},
   {"C" , "1100"},
   {"D" , "1101"},
   {"E" , "1110"},
   {"F" , "1111"}
  };

  string line;

  string s;
  cin >> line;
  for (auto x : line)
  {
    string h;
    h += x;
    s += hexaToBinary[h];
  }
  int sum = 0, i = 0;
  getPacketAndId(s, sum, i);

  cout << "Part 1: " << sum;

}