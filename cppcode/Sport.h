#pragma once
#include <string>
using namespace std;

class Sport
{
	string name_;
public:
	Sport(string name) : name_(name) { }
	string getName() const;
};