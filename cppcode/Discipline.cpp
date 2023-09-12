#include "Discipline.h"

string Discipline::getName() const
{
	return name_;
}

Sport* Discipline::getSport() const
{
	return sport_;
}
