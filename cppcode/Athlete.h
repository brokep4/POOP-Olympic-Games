#pragma once
#include <string>

using namespace std;

class Athlete
{
public:
	enum class Gender { M, F };
private:
	int id_;
	string name_;
	Gender gender_;
	int age_;
	int height_;
	double weight_;//int weight_;
public:
	Athlete(int id, string name, Gender gender, int age, int height, double /*int*/ weight);
	int getId();
	string getName();
	Gender getGender();
	int getAge();
	int getHeight();
	int getWeight();
};