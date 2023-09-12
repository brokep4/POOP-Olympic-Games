#include "Competitor.h"

Discipline* Competitor::getDiscipline() const
{
	return discipline_;
}

OlympicGames* Competitor::getOlympicGames() const
{
	return olGames_;
}

Country* Competitor::getCountry() const
{
	return country_;
}

Medal Competitor::getMedal() const
{
	return medal_;
}

Sport* Competitor::getSport() const
{
	return discipline_->getSport();
}
