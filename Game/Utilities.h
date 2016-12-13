#pragma once
#include <string>
#include <vector>
#include <functional>
#include <cctype>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Utilities
{
public:
	Utilities(void);
	~Utilities(void);
	void Trim(string& str);
	void Trim(string& str, const string& chars);
	void TrimVector(vector<string>& v);
	void TrimVector(vector<string>& v, const string& chars);
	void ToLowerString(string& str);
	vector<string> &split(const string &s, char delim, vector<string> &elems);
	vector<string> split(const string &s, char delim);
	string IntToString(int val);
};