#pragma once
#include <string>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

enum class Season {Winter=0, Summer, ERROR};

class OlympicGames
{
	string name_;
	string city_;
	int year_;
	Season season_;
public:

	static vector <string> splitBy(string line, char c);

	OlympicGames(string name, string city) : name_(name), city_(city) {
		vector<string> v = splitBy(name, ' ');
		year_ = atoi(v[0].c_str());
		//season_ = v[1];
		if (v[1] == "Winter")season_ = Season::Winter;
		else if (v[1] == "Summer")season_ = Season::Summer;
		else
		{
			season_ = Season::ERROR;
			cout << "[Error while Olympic Games constructor, this shouldn't have happened]" << endl;
		}
	}
	string getName() const;
	int getYear() const;
	Season getSeason() const;
	string getCity() const;
};