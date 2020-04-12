#include "database.h"
using namespace std;

void Database::Add(const Date& date, const string& event) { 
		if (adds[date].count(event) == 0) { 
			adds[date].insert(event);
			storage[date].push_back(event);
	    }
	}

pair<Date, string> Database::Last(const Date& date) const { 
		if (storage.empty()) {
			throw invalid_argument("");
		}
		try {
			if (storage.at(date).empty()) {
				throw invalid_argument("");
			} 

			return make_pair(date, storage.at(date).back());
		}
		catch (out_of_range&) {
		}
		auto it = storage.upper_bound(date);
		if (it == storage.begin()) {
			throw invalid_argument("");
		}
		else {
			it--;
			if (!it->second.empty()) {
				return make_pair(it->first, it->second.back());
			}
			else {
				throw invalid_argument("");
			}
		}
	}


int Database::RemoveIf(function<bool(const Date& date, const string& even)> pred) { 
	int counter = 0;   
	for (auto& it : storage) {
		const Date& d = it.first;
		auto sp = stable_partition(it.second.begin(), it.second.end(), [=](const string& e) { 
			return pred(d, e); }); 
		auto dist = sp - it.second.begin();
		for (auto i = it.second.begin(); i != sp; ++i)
			adds[d].erase(*i);
		it.second.erase(it.second.begin(), sp);
		counter += dist;
	} 
	for (auto it = storage.begin(); it != storage.end(); ) {
		if (it->second.empty()) {
			adds.erase(it->first);;
			storage.erase(it++);
		} 
		else {
			++it;
		}
	}
	
	
	return counter;
} 

vector<pair<Date, string>> Database::FindIf(function<bool(const Date& date, const string& even)> pred) const { 
	vector <pair<Date, string>> finds;
	for (auto it1 : storage) {
		for (auto it2 : it1.second) {
			if (pred(it1.first, it2))
				finds.push_back({ it1.first, it2 });
		}
	} 
	return finds;
}

void Database::Print(ostream& os) const {
		os << storage;
	}


ostream& operator<<(ostream& os, const map<Date, vector<string>>& m) { 
	for (const auto& item : m) {
		for (const string& event : item.second) {
			os << item.first << " " << event << endl;
		}
	} 
	return os;
}

ostream& operator<<(ostream& os, pair<Date, string> p) {
	os << p.first << " " << p.second;
	return os;
}
