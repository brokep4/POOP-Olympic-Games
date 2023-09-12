#pragma once
#include "Competitor.h"
#include "Athlete.h"
#include <vector>

using namespace std;

class TeamCompetitor : public Competitor
{
	vector<Athlete*> athletes_;
public:
	TeamCompetitor(Discipline* discipline, OlympicGames* olgames, Country* country, Medal medal, vector<Athlete*> athletes) :
		Competitor(discipline, olgames, country, medal), athletes_(athletes) {}
	CompetitionType getCompetitionType()const override;
	int getHeight() const override;
	int getHeightCnt() const override;
	int getWeight() const override;
	int getWeightCnt() const override;
	int getNumberOfAthletes() const override;
	virtual vector<Athlete*> getAthletes()const override;
};