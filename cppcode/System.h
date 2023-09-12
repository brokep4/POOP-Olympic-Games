#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include "Athlete.h"
#include "Sport.h"
#include "Discipline.h"
#include "Country.h"
#include "OlympicGames.h"
#include "Competitor.h"
#include "IndividualCompetitor.h"
#include "TeamCompetitor.h"
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <tuple>

using namespace std;

struct CountryMedals
{
	Country* country;
	int goldCnt;
	int silverCnt;
	int bronzeCnt;
	bool operator<(CountryMedals& op)
	{
		if (goldCnt < op.goldCnt)return true;
		if (goldCnt > op.goldCnt)return false;
		if (silverCnt < op.silverCnt)return true;
		if (silverCnt > op.silverCnt)return false;
		return bronzeCnt < op.bronzeCnt;
	}
	bool operator==(CountryMedals& op)
	{
		return goldCnt == op.goldCnt && silverCnt == op.silverCnt && bronzeCnt == op.bronzeCnt;
	}
};

//All parameters that are being used should be created dynamically
//Also they should be unique and used only by single filter instance
//Therefore, destructor can delete them when filter is being deleted as well
//Or not, this will be fixed later
class Filter
{
	typedef bool(*PF)(Filter*, void*);
	PF test_;
public:
	vector<void*> parameters;
	Filter(PF test, vector<void*> params) : test_(test), parameters(params) {}
	bool operator()(void* p)
	{
		return test_(this, p);
	}
	Filter* logicalAnd(Filter* f)
	{
		vector<void*> params;
		params.push_back((void*)f);
		params.push_back((void*)this);
		Filter* filter = new Filter([](Filter* f, void* p) -> bool {
			Filter* f1 = (Filter*)f->parameters[0];
			Filter* f2 = (Filter*)f->parameters[1];
			return (*f1)(p) && (*f2)(p);
			}, params);
		return filter;
	}
	Filter* logicalOR(Filter* f)
	{
		vector<void*> params;
		params.push_back((void*)f);
		params.push_back((void*)this);
		Filter* filter = new Filter([](Filter* f, void* p) -> bool {
			Filter* f1 = (Filter*)f->parameters[0];
			Filter* f2 = (Filter*)f->parameters[1];
			return (*f1)(p) || (*f2)(p);
			}, params);
		return filter;
	}
};

class System
{

	map<int, Athlete*> allAthletes_;//vector <Athlete*> allAthletes_;
	vector <Competitor*> allCompetitors_;
	vector <Country*> allCountries_;
	vector <Discipline*> allDisciplines_;
	vector <OlympicGames*> allOlympicGames_;
	vector <Sport*> allSports_;
	//This function will try to write number written in string s, to integer to which p is pointing
	//if s == specialString, then it will write specialValue to integer to which p is pointing
	//function will return true if s consists of digits, or if it is equal to specialString
	bool checkStoreInt(const string& s, int* p, string specialString, int specialValue);

	//This function will try to write number written in string s, to double to which p is pointing
	//if s == specialString, then it will write specialValue to double to which p is pointing
	//function will return true if s consists of digits, or if it is equal to specialString
	bool checkStoreDouble(const string& s, double* p, string specialString, double specialValue);

	Medal medalNameToEnum(string name);

	vector<Athlete*> getAthletesVector(string& competitors);

	//This function will try to find Country with given name in vector allCountries_, if not found it will create new Country with given name, and then add to vector
	//Anyway, it will return pointer to mem. location where information about that Country is stored
	Country* getOrAddCountryByName(string name);

	//This function will try to find Discipline with given name in vector allDisciplines_, if not found it will create new Discipline with given name, and then add to vector
	//Anyway, it will return pointer to mem. location where information about that Discipline is stored
	Discipline* getOrAddDisciplineByName(string name, string sportName);

	//This function will try to find Olympic Games with given name in vector allOlympicGames_, if not found it will create new Olympic Games with given name, and then add to vector
	//Anyway, it will return pointer to mem. location where information about that Olympic Games is stored
	OlympicGames* getOrAddOlympicGamesByName(string name, string city);

	//This function will try to find Sport with given name in vector allSports_, if not found it will create new Sport with given name, and then add to vector
	//Anyway, it will return pointer to mem. location where information about that Sport is stored
	Sport* getOrAddSportByName(string name);

	//This function will try to find Country with given name in vector allCountries_, if not found it will return null
	Country* getCountryByName(string name);

	//This function will try to find Discipline with given name in vector allDisciplines_, if not found it will return null
	Discipline* getDisciplineByName(string name, string sportName);

	//This function will try to find Olympic Games with given name in vector allOlympicGames_, if not found it will return null
	OlympicGames* getOlympicGamesByName(string name, string city);

	//This function will try to find Sport with given name in vector allSports_, if not found it will return null
	Sport* getSportByName(string name);

	//This function will try to find Athlete with given name in vector allAthletes_, if not found it will return null
	Athlete* getAthleteById(int id);
	
	vector<CountryMedals*> getCountrySuccess(string olympicGamesName);

public:

	bool loadGroupMode(string path);
	bool loadIndividualMode(string path, int year);
	bool loadAthletes(string path);
	void outputAthletes();
	

	Filter* generateFilter(string sportName, string country, int year, CompetitionType* competitionType, Medal* medal);

	double averageHeight(Filter* test);
	double averageWeight(Filter* test);
	int numberOfDisciplines(Filter* test);
	int numberOfParticipants(Filter* test);

	map<string, int> numberOfParticipants2(Filter* test);
	map<string, int> numberOfDisciplines2(Filter* test);
	map<string, double> averageWeight2(Filter* test);
	map<string, double> averageHeight2(Filter* test);

	int numberOfSportsAtLeastOneMedal(string countryName);//1
	vector<Country*> threeBestCountries(string olympicGamesName);//2
	//vector<CountryMedals*> allBestCountries(string olympicGamesName);//2
	vector<CountryMedals*> allCountriesSuccess(string olympicGamesName);
	vector<Country*> countriesAtLeastOnceBestOverall();//3
	vector<Athlete*> tenYoungestAthletesWithMedalOnDebut();//4 not done
	vector<pair<Country*, Athlete*>> getAllAthletesMedalIndividualAndTeam();//5
	set<Athlete*> allAthletesThatCompeted(string olympicGamesName);//POM 6
	vector<Athlete*> allAthletesThatCompeted(string olympicGamesName1, string olympicGamesName2);//6
	vector<Competitor*> getTeams(string countryName, string olympicGamesName);//7
	vector<string> numberOfCities() const;//8

	void testOutputCountries(int limit);
	void testOutputOlympicGames(int limit);
	void testOutputCompetitors(int limit);

	~System();
};