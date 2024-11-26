#ifndef TRANSMISSION
#define TRANSMISSION

#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

string readFile(const string &path);

void printZValues(vector<int> &v);

vector<int> zNaive(string S);

int analyzeTransmission(string tpath = "transmission1.txt", string mpath = "mcode1.txt");

pair<int, string> longestPalindrome(const string &s);

void analyzePalindromes(const vector<string> &files);

pair<int, int> longestCommonSubstring(const string &s1, const string &s2);

#endif 
