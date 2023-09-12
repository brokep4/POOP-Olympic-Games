#include "Athlete.h"

Athlete::Athlete(int id, string name, Gender gender, int age, int height, /*int*/ double weight)
{
	id_ = id;
	name_ = name;
	gender_ = gender;
	age_ = age;
	height_ = height;
	weight_ = weight;
}

int Athlete::getId()
{
	return id_;
}

string Athlete::getName()
{
	return name_;
}

Athlete::Gender Athlete::getGender()
{
	return gender_;
}

int Athlete::getAge()
{
	return age_;
}

int Athlete::getHeight()
{
	return height_;
}

int Athlete::getWeight()
{
	return weight_;
}
