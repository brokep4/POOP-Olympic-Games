#pragma once
#include <string>
#include "Sport.h"
using namespace std;

class Discipline
{
	string name_;
	Sport* sport_;
public:
	string getName() const;
	Sport* getSport() const;
	Discipline(string name, Sport* sport) : name_(name), sport_(sport) {}
};