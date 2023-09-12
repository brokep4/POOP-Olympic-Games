#include "IndividualCompetitor.h"

CompetitionType IndividualCompetitor::getCompetitionType() const
{
	return CompetitionType::Individual;
}

int IndividualCompetitor::getHeight() const
{
	if (athlete_->getHeight() == -1)return 0;
	return athlete_->getHeight();
}

int IndividualCompetitor::getHeightCnt() const
{
	if (athlete_->getHeight() == -1)return 0;
	return 1;
}

int IndividualCompetitor::getWeight() const
{
	if (athlete_->getWeight() == -1)return 0;
	return athlete_->getWeight();
}

int IndividualCompetitor::getWeightCnt() const
{
	if (athlete_->getWeight() == -1)return 0;
	return 1;
}

int IndividualCompetitor::getNumberOfAthletes() const
{
	return 1;
}

vector<Athlete*> IndividualCompetitor::getAthletes()const
{
	vector<Athlete*> v; v.push_back(athlete_);
	return v;
}
