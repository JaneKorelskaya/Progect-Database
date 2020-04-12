#pragma once  
#include "date.h" 
#include <map>
#include <string> 
#include <set>  
#include <vector>
#include <functional> 
#include <iostream>  
#include <algorithm> 
#include <iterator> 

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	pair<Date, string> Last(const Date& date) const;

	int RemoveIf(function<bool(const Date& date, const string& even)> pred);

	vector<pair<Date, string>> FindIf(function<bool(const Date& date, const string& even)> pred) const;

	void Print(ostream& os) const;

private:
	map<Date, vector<string>> storage; 
	map<Date, set<string>> adds;
}; 

ostream& operator<<(ostream& os, const map<Date, vector<string>>& m);
ostream& operator<<(ostream& os, pair<Date, string> p);
