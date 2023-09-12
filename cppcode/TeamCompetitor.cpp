#include "TeamCompetitor.h"

CompetitionType TeamCompetitor::getCompetitionType() const
{
	return CompetitionType::Team;
}

int TeamCompetitor::getHeight() const
{
	int s = 0;
	for (auto athlete : athletes_)
	{
		if (athlete->getHeight() == -1)continue;
		s += athlete->getHeight();
	}
	return s;
}

int TeamCompetitor::getHeightCnt() const
{
	int s = 0;
	for (auto athlete : athletes_)
	{
		if (athlete->getHeight() == -1)continue;
		s++;
	}
	return s;
}

int TeamCompetitor::getWeight() const
{
	int s = 0;
	for (auto athlete : athletes_)
	{
		if (athlete->getWeight() == -1)continue;
		s += athlete->getWeight();
	}
	return s;
}

int TeamCompetitor::getWeightCnt() const
{
	int s = 0;
	for (auto athlete : athletes_)
	{
		if (athlete->getWeight() == -1)continue;
		s++;
	}
	return s;
}

int TeamCompetitor::getNumberOfAthletes() const
{
	return athletes_.size();
}

vector<Athlete*> TeamCompetitor::getAthletes() const
{
	return athletes_;
}
