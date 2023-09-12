#pragma once
#include "Competitor.h"
#include "Athlete.h"
#include "OlympicGames.h"
#include "Enums.h"
#include "Country.h"
#include "Discipline.h"
#include <vector>

using namespace std;

class IndividualCompetitor : public Competitor
{
	Athlete* athlete_;
public:
	IndividualCompetitor(Discipline* discipline, OlympicGames* olgames, Country* country, Medal medal, Athlete* athlete) :
		Competitor(discipline, olgames, country, medal), athlete_(athlete) {}
	CompetitionType getCompetitionType()const override;
	int getHeight() const override;
	int getHeightCnt() const override;
	int getWeight() const override;
	int getWeightCnt() const override;
	int getNumberOfAthletes() const override;
	virtual vector<Athlete*> getAthletes()const override;
};