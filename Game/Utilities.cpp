#include "StdAfx.h"
#include "Utilities.h"

Utilities::Utilities(void)
{
}


Utilities::~Utilities(void)
{
}

void Utilities::Trim(string& str, const string& chars)
{
	std::string::size_type pos = 0;

	pos = str.find_first_not_of(chars);
	str.erase(0, pos);
	pos = str.find_last_not_of(chars);
	str.erase(pos + 1); 
}

void Utilities::Trim(string& str)
{
	string chars = " \f\n\r\t\v";
	std::string::size_type pos = 0;

	pos = str.find_first_not_of(chars);
	str.erase(0, pos);
	pos = str.find_last_not_of(chars);
	str.erase(pos + 1); 
}

void Utilities::TrimVector(vector<string>& v)
{
	int size = v.size();

	for (int i = 0; i < size; i++)
	{
		Trim(v[i]);
	}
}

void Utilities::TrimVector(vector<string>& v, const string& chars)
{
	int size = v.size();

	for (int i = 0; i < size; i++)
	{
		Trim(v[i], chars);
	}
}

void Utilities::ToLowerString(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ptr_fun<int, int>(tolower));
}

vector<string>& Utilities::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> Utilities::split(const string &s, char delim) {
	vector<string> elems;
	return split(s, delim, elems);
}

string Utilities::IntToString(int val)
{
	stringstream ss;
	ss << val;
	return ss.str();
}