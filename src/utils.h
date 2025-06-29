#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
using namespace std;

vector<string> get_array_from_file(string src);
vector<string> linear_search_pre(vector<string> v, string str);
bool linear_search_exact(vector<string> v, string str);
int KMPSearch(string pat, string txt);
vector<string> search(vector<string> v, string pat);

#endif
