#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

string readFile(const string &path);

void printZValues(vector<int> &v);

vector<int> zNaive(const string &S);

int analyzeTransmission(const string &tpath, const string &mpath);

pair<int, string> longestPalindrome(const string &s);

void analyzePalindromes(const vector<string> &files);

pair<int, int> longestCommonSubstring(const string &s1, const string &s2);

#endif
