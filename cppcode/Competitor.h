#pragma once
#include "Discipline.h"
#include "OlympicGames.h"
#include "Country.h"
#include "Enums.h"
#include "Athlete.h"
#include <vector>
using namespace std;

class Competitor
{
	Discipline* discipline_;
	OlympicGames* olGames_;
	Country* country_;
	Medal medal_;
public:
	Competitor(Discipline* discipline, OlympicGames* olgames, Country* country, Medal medal) : discipline_(discipline), olGames_(olgames), country_(country), medal_(medal) {}
	virtual CompetitionType getCompetitionType()const = 0;
	Discipline* getDiscipline() const;
	OlympicGames* getOlympicGames() const;
	Country* getCountry() const;
	Medal getMedal() const;
	Sport* getSport() const;
	virtual int getHeight() const = 0;
	virtual int getHeightCnt() const = 0;
	virtual int getWeight() const = 0;
	virtual int getWeightCnt() const = 0;
	virtual int getNumberOfAthletes() const = 0;
	virtual vector<Athlete*> getAthletes()const = 0;
};