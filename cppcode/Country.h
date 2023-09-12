#pragma once
#include <string>
using namespace std;

class Country
{
	string name_;
public:
	string getName() const;
	Country(string name) : name_(name) {}
};