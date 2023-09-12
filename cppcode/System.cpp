#include "System.h"

bool System::checkStoreInt(const string& s, int* p, string specialString, int specialValue)
{
	regex reg("[0-9]+");
	if (s == specialString)
	{
		*p = specialValue;
		return true;
	}
	if (!regex_match(s, reg))return false;
	*p = stoi(s);
	return true;
}

bool System::checkStoreDouble(const string& s, double* p, string specialString, double specialValue)
{
	try
	{
		if (specialString == s)
		{
			*p = specialValue;
		}
		else *p = stod(s);
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool System::loadGroupMode(string path)
{
	string line;
	ifstream f(path);
	if (!f.is_open())
	{
		cout << "[Error] Failed to open given file on path: " << path << "; function loadGroupMode\n";
		return false;
	}
	int i = 0;
	while (getline(f, line))
	{
		++i;
		//if (i > 100)break;
		vector <string> tokens = OlympicGames::splitBy(line, '!');
		if (tokens.size() != 8 && tokens.size() != 7)
		{
			cout << "[Error while line parsing, on loadGroupMode] Wrong number of ! " << line << "\n";
			continue;
		}
		string olGamesName = tokens[0];
		string city = tokens[1];
		string sportName = tokens[2];
		string disciplineName = tokens[3];
		string competitionTypeName = tokens[4]; //individual or team
		string countryName = tokens[5];
		string competitors = tokens[6];
		Medal medal = medalNameToEnum((tokens.size() < 8 ? "" : tokens[7]));
		OlympicGames* olgames = System::getOrAddOlympicGamesByName(olGamesName, city);
		Sport* sport = System::getOrAddSportByName(sportName);
		CompetitionType competitionType;
		if (competitionTypeName != "Individual" && competitionTypeName != "Team")
		{
			cout << "[Error while line parsing, on loadGroupMode] Competition type can be either Individual or Team " << line << "\n";
			continue;
		}
		if (competitionTypeName == "Individual")competitionType = CompetitionType::Individual;
		else competitionType = CompetitionType::Team;
		Country* country = System::getOrAddCountryByName(countryName);
		Discipline* discipline = System::getOrAddDisciplineByName(disciplineName, sportName);
		if (competitionType == CompetitionType::Individual)
		{
			int athleteIdx;
			if (!checkStoreInt(competitors, &athleteIdx, "1", 1))
			{
				cout << "[Error while line parsing, on loadGroupMode] Invalid Competitor Id(must be integer) " << line << "\n";
				continue;
			}
			Athlete* athlete = System::getAthleteById(athleteIdx);
			Competitor* competitor = new IndividualCompetitor(discipline, olgames, country, medal, athlete);
			allCompetitors_.push_back(competitor);
		}
		else
		{
			/*
			Competitor* competitor = new TeamCompetitor(discipline, olgames, country, medal, nullptr);
			allCompetitors_.push_back(competitor);
			*/
			//cout << "SIZE: " << getAthletesVector(competitors).size() << endl;
			//cout << "OMG " << competitors << endl;
			vector <Athlete*> athletesVector = getAthletesVector(competitors);
			Competitor* competitor = new TeamCompetitor(discipline, olgames, country, medal, athletesVector);
			allCompetitors_.push_back(competitor);
		}
	}
	f.close();
	return true;
}

bool System::loadIndividualMode(string path, int year)
{
	string line;
	ifstream f(path);
	if (!f.is_open())
	{
		cout << "[Error] Failed to open given file on path: " << path << "; function loadGroupMode\n";
		return false;
	}
	int i = 0;
	while (getline(f, line))
	{
		++i;
		//if (i > 100)break;
		vector <string> tokens = OlympicGames::splitBy(line, '!');
		if (tokens.size() != 8 && tokens.size() != 7)
		{
			cout << "[Error while line parsing, on loadIndividualMode] Wrong number of ! " << line << "\n";
			continue;
		}
		string olGamesName = tokens[0];

		vector<string> toks = OlympicGames::splitBy(olGamesName, ' ');
		int yy = -1;
		try
		{
			yy = atoi(toks[0].c_str());
		}
		catch (...)
		{
			cout << "[Error while line parsing, on loadIndividualMode] Bad Olympic Games name" << endl;
			continue;
		}
		if (yy != year)continue;

		string city = tokens[1];
		string sportName = tokens[2];
		string disciplineName = tokens[3];
		string competitionTypeName = tokens[4]; //individual or team
		string countryName = tokens[5];
		string competitors = tokens[6];
		Medal medal = medalNameToEnum((tokens.size() < 8 ? "" : tokens[7]));
		OlympicGames* olgames = System::getOrAddOlympicGamesByName(olGamesName, city);
		Sport* sport = System::getOrAddSportByName(sportName);
		CompetitionType competitionType;
		if (competitionTypeName != "Individual" && competitionTypeName != "Team")
		{
			cout << "[Error while line parsing, on loadIndividualMode] Competition type can be either Individual or Team " << line << "\n";
			continue;
		}
		if (competitionTypeName == "Individual")competitionType = CompetitionType::Individual;
		else competitionType = CompetitionType::Team;
		Country* country = System::getOrAddCountryByName(countryName);
		Discipline* discipline = System::getOrAddDisciplineByName(disciplineName, sportName);
		if (competitionType == CompetitionType::Individual)
		{
			int athleteIdx;
			if (!checkStoreInt(competitors, &athleteIdx, "1", 1))
			{
				cout << "[Error while line parsing, on loadIndividualMode] Invalid Competitor Id(must be integer) " << line << "\n";
				continue;
			}
			Athlete* athlete = System::getAthleteById(athleteIdx);
			Competitor* competitor = new IndividualCompetitor(discipline, olgames, country, medal, athlete);
			allCompetitors_.push_back(competitor);
		}
		else
		{
			/*
			Competitor* competitor = new TeamCompetitor(discipline, olgames, country, medal, nullptr);
			allCompetitors_.push_back(competitor);
			*/
			//cout << "SIZE: " << getAthletesVector(competitors).size() << endl;
			//cout << "OMG " << competitors << endl;
			vector <Athlete*> athletesVector = getAthletesVector(competitors);
			Competitor* competitor = new TeamCompetitor(discipline, olgames, country, medal, athletesVector);
			allCompetitors_.push_back(competitor);
		}
	}
	f.close();
	return true;
}

bool System::loadAthletes(string path)
{
	string line;
	ifstream f(path);
	if (!f.is_open())
	{
		cout << "[Error] Failed to open given file on path: " << path << "; function loadAthletes\n";
		return false;
	}
	cout << "File opened successfully!\n";
	int i = 0;
	while (getline(f, line))
	{
		//if (++i >= 100)break;
		/*
		regex reg("[!]+");
		sregex_token_iterator iter(line.begin(), line.end(), reg, -1);
		sregex_token_iterator end;

		vector<string> tokens(iter, end);
		*/

		vector <string> tokens = OlympicGames::splitBy(line, '!');

		if (tokens.size() != 6)
		{
			cout << "[Error while line parsing, on loadAthletes] Wrong number of ! " << line << "\n";
			continue;
		}
		int id, age, height/*, weight*/;
		double weight;
		if (!checkStoreInt(tokens[0], &id, "1", 1)) { cout << "[Error while line parsing, on loadAthletes] Bad id " << line << "\n"; continue; }
		Athlete::Gender gender;
		if (tokens[2] == "M")gender = Athlete::Gender::M;
		else if (tokens[2] == "F")gender = Athlete::Gender::F;
		else { cout << "[Error while line parsing, on loadAthletes] Wrong gender " << line << "\n"; continue; }
		if (!checkStoreInt(tokens[3], &age, "NA", -1)) { cout << "[Error while line parsing, on loadAthletes] Bad age " << line << "\n"; continue; }
		if (!checkStoreInt(tokens[4], &height, "NA", -1)) { cout << "[Error while line parsing, on loadAthletes] Bad height " << line << "\n"; continue; }
		if (!checkStoreDouble(tokens[5], &weight, "NA", -1.00)) { cout << "[Error while line parsing, on loadAthletes] Bad weight " << line << "\n"; continue; }
		Athlete* athlete = new Athlete(id, tokens[1], gender, age, height, weight);
		allAthletes_[athlete->getId()] = athlete;
		//allAthletes_.push_back(athlete);
	}
	f.close();
	return true;
}

void System::outputAthletes()
{
	/*
	for (auto athl : allAthletes_)
	{
		cout << athl->getId() << "-" << athl->getName() << "-" << (athl->getGender() == Athlete::Gender::M ? "M" : "F") << "-" << athl->getAge() << "-" << athl->getHeight() << "-" << athl->getWeight() << endl;
	}
	*/
	//for_each(allAthletes_.begin(), allAthletes_.end(), [](Athlete* athl) {
		//cout << athl->getId() << "-" << athl->getName() << "-" << (athl->getGender() == Athlete::Gender::M ? "M" : "F") << "-" << athl->getAge() << "-" << athl->getHeight() << "-" << athl->getWeight() << endl;
		//});
	for (auto p : allAthletes_)
	{
		Athlete* athl = p.second;
		cout << athl->getId() << "-" << athl->getName() << "-" << (athl->getGender() == Athlete::Gender::M ? "M" : "F") << "-" << athl->getAge() << "-" << athl->getHeight() << "-" << athl->getWeight() << endl;
	}
}

Medal System::medalNameToEnum(string name)
{
	if (name == "Gold")return Medal::Gold;
	if (name == "Silver")return Medal::Silver;
	if (name == "Bronze")return Medal::Bronze;
	return Medal::None;
}

vector<Athlete*> System::getAthletesVector(string& competitors)
{
	vector<Athlete*> ret;
	regex reg("[\\[\\]' ]");
	competitors = regex_replace(competitors, reg, "");
	vector<string> pom = OlympicGames::splitBy(competitors, ',');
	for (auto s : pom)
	{
		int idx;
		if (!checkStoreInt(s, &idx, "1", 1))
		{
			cout << "[Error while parsing team athletes, getAthletesVector function]\n";
			return ret;
		}
		Athlete* athlete = getAthleteById(idx);
		if (athlete == nullptr)
		{
			cout << "[Error while parsing team athletes, getAthletesVector function] No athlete with given id!\n";
			return ret;
		}
		ret.push_back(athlete);
	}
	return ret;
}

Filter* System::generateFilter(string sportName, string country, int year, CompetitionType* competitionType, Medal* medal)
{
	vector<Filter*> filters;
	if (sportName != "")
	{
		vector<void*> params;
		params.push_back((void*)getSportByName(sportName));
		filters.push_back(new Filter([](Filter* f, void* p) -> bool {
			if (p == nullptr)return false;
			return ((Competitor*)p)->getSport() == (Sport*)(f->parameters[0]);
			}, params));
	}
	if (country != "")
	{
		vector<void*> params;
		params.push_back((void*)getCountryByName(country));
		filters.push_back(new Filter([](Filter* f, void* p) -> bool {
			if (p == nullptr)return false;
			return ((Competitor*)p)->getCountry() == (Country*)(f->parameters[0]);
			}, params));
	}
	if (year != -1)
	{
		vector<void*> params;
		params.push_back((void*)(new int(year)));
		filters.push_back(new Filter([](Filter* f, void* p) -> bool {
			if (p == nullptr)return false;
			return ((Competitor*)p)->getOlympicGames()->getYear() == *((int*)f->parameters[0]);//((Competitor*)p)->getCountry() == (Country*)(f->parameters[0]);
			}, params));
	}
	if (competitionType != nullptr)
	{
		vector<void*> params;
		params.push_back((void*)competitionType);
		filters.push_back(new Filter([](Filter* f, void* p) -> bool {
			if (p == nullptr)return false;
			return ((Competitor*)p)->getCompetitionType() == *((CompetitionType*)(f->parameters[0]));
			}, params));
	}
	if (medal != nullptr)
	{
		vector<void*> params;
		params.push_back((void*)medal);
		filters.push_back(new Filter([](Filter* f, void* p) -> bool {
			if (p == nullptr)return false;
			return ((Competitor*)p)->getMedal() == *((Medal*)(f->parameters[0]));
			}, params));
	}
	vector<void*> params;
	Filter* f = new Filter([](Filter* f, void* p) -> bool {return true; }, params);
	for (auto filter : filters)
	{
		f = f->logicalAnd(filter);
	}
	return f;
}


Country* System::getOrAddCountryByName(string name)
{
	Country* c = getCountryByName(name);
	if (c != nullptr)return c;
	c = new Country(name);
	allCountries_.push_back(c);
	return c;
}

Discipline* System::getOrAddDisciplineByName(string name, string sportName)
{
	Discipline* discipline = getDisciplineByName(name, sportName);
	if (discipline != nullptr)return discipline;
	Sport* sport = System::getOrAddSportByName(sportName);
	discipline = new Discipline(name, sport);
	allDisciplines_.push_back(discipline);
	return discipline;
}

OlympicGames* System::getOrAddOlympicGamesByName(string name, string city)
{
	OlympicGames* ol = getOlympicGamesByName(name, city);
	if (ol != nullptr)return ol;
	ol = new OlympicGames(name, city);
	allOlympicGames_.push_back(ol);
	return ol;
}

Sport* System::getOrAddSportByName(string name)
{
	Sport* sport = getSportByName(name);
	if (sport != nullptr)return sport;
	sport = new Sport(name);
	allSports_.push_back(sport);
	return sport;
}

Country* System::getCountryByName(string name)
{
	auto it = find_if(allCountries_.begin(), allCountries_.end(), [&](Country* country) {return country->getName() == name; });
	if (it != allCountries_.end())return *it;
	return nullptr;
}

Discipline* System::getDisciplineByName(string name, string sportName)
{
	auto it = find_if(allDisciplines_.begin(), allDisciplines_.end(), [&](Discipline* discipline) {return discipline->getName() == name; });
	if (it != allDisciplines_.end())return *it;
	return nullptr;
}

OlympicGames* System::getOlympicGamesByName(string name, string city)
{
	auto it = find_if(allOlympicGames_.begin(), allOlympicGames_.end(), [&](OlympicGames* olgames) {return olgames->getName() == name; });
	if (it != allOlympicGames_.end())return *it;
	return nullptr;
}

Sport* System::getSportByName(string name)
{
	auto it = find_if(allSports_.begin(), allSports_.end(), [&](Sport* sport) {return sport->getName() == name; });
	if (it != allSports_.end())return *it;
	return nullptr;
}

Athlete* System::getAthleteById(int id)
{
	//auto it = find_if(allAthletes_.begin(), allAthletes_.end(), [&](Athlete* athlete) {return athlete->getId() == id; });
	//if (it != allAthletes_.end())return *it;
	//return nullptr;
	if (allAthletes_.find(id) == allAthletes_.end())return nullptr;
	return allAthletes_[id];
}

vector<CountryMedals*> System::getCountrySuccess(string olympicGamesName)
{
	vector<CountryMedals*> successes;
	vector<Competitor*> competitors;
	map<Country*, CountryMedals*> mp;
	vector<void*> params;
	params.push_back((void*)getOlympicGamesByName(olympicGamesName,""));
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *new Filter([](Filter* f, void* p) -> bool {
		return ((Competitor*)p)->getOlympicGames() == (OlympicGames*)f->parameters[0]; }, params));
	for_each(competitors.begin(), competitors.end(), [&](Competitor* c) {
		if (!mp[c->getCountry()])
		{
			CountryMedals* cm;
			mp[c->getCountry()] = cm = new CountryMedals();
			cm->bronzeCnt = 0; cm->silverCnt = 0; cm->goldCnt = 0; cm->country = c->getCountry();
		}
		if(c->getMedal() == Medal::Bronze)mp[c->getCountry()]->bronzeCnt++;
		if (c->getMedal() == Medal::Silver)mp[c->getCountry()]->silverCnt++;
		if (c->getMedal() == Medal::Gold)mp[c->getCountry()]->goldCnt++;
		});
	for (auto pair : mp)
	{
		successes.push_back(pair.second);
	}
	return successes;
}

double System::averageHeight(Filter* test)
{
	double s = 0;
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	//int cnt = competitors.size();
	//cout << "SIZE: " << allCompetitors_.size() << endl;

	int cnt = 0;
	for (auto competitor : competitors)
	{
		cnt += competitor->getHeightCnt();
		s += competitor->getHeight();
	}

	return (cnt == 0 ? 0 : s/cnt);
}

double System::averageWeight(Filter* test)
{
	double s = 0;
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	//int cnt = competitors.size();
	//cout << "SIZE: " << allCompetitors_.size() << endl;

	int cnt = 0;
	for (auto competitor : competitors)
	{
		cnt += competitor->getWeightCnt();
		s += competitor->getWeight();
	}

	return (cnt == 0 ? 0 : s / cnt);
}

int System::numberOfDisciplines(Filter* test)
{
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	set<Discipline*> disc;
	for (auto comp : competitors)
	{
		disc.insert(comp->getDiscipline());
	}
	return disc.size();
}
int System::numberOfParticipants(Filter* test)
{
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	/*
	for (auto c : competitors)
	{
		cout << c->getCountry()->getName() << " " << c->getOlympicGames()->getName() << " " << c->getSport()->getName() << " " << c->getDiscipline()->getName() << " " << (c->getCompetitionType() == CompetitionType::Individual ? "Ind" : "Team") << endl;
		cout << "~~~~~~~~~~~~~~~~\n";
		for (auto cc : c->getAthletes())
		{
			cout << cc->getName() << " ";
		}
		cout << "~~~~~~~~~~~~~~~~\n";
	}
	*/
	return competitors.size();
}

map<string, int> System::numberOfParticipants2(Filter* test)
{
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	map<string, int> mapa;
	for (auto comp : competitors)
	{
		mapa[comp->getCountry()->getName()]++;
	}
	return mapa;
}

map<string, int> System::numberOfDisciplines2(Filter* test)
{
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	map<string, int> mapa;
	map<string, set<string>*> pommapa;
	for (auto comp : competitors)
	{
		if (!pommapa[comp->getOlympicGames()->getName()])
			pommapa[comp->getOlympicGames()->getName()] = new set<string>;
		pommapa[comp->getOlympicGames()->getName()]->insert(comp->getDiscipline()->getName());
	}
	for (auto par : pommapa)
	{
		if (!par.second)continue;
		mapa[par.first] = par.second->size();
		delete par.second;
	}
	return mapa;
}

map<string, double> System::averageWeight2(Filter* test)
{
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	map<string, double> mapaS;
	map<string, double> mapaCnt;
	map<string, double> finalMap;
	for (auto competitor : competitors)
	{
		mapaCnt[competitor->getOlympicGames()->getName()] += competitor->getWeightCnt();
		mapaS[competitor->getOlympicGames()->getName()] += competitor->getWeight();
	}
	for (auto par : mapaCnt)
	{
		if (par.second)
			finalMap[par.first] = mapaS[par.first] / par.second;
	}
	return finalMap;
}

map<string, double> System::averageHeight2(Filter* test)
{
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *test);
	map<string, double> mapaS;
	map<string, double> mapaCnt;
	map<string, double> finalMap;
	for (auto competitor : competitors)
	{
		mapaCnt[competitor->getOlympicGames()->getName()] += competitor->getHeightCnt();
		mapaS[competitor->getOlympicGames()->getName()] += competitor->getHeight();
	}
	for (auto par : mapaCnt)
	{
		if(par.second)
			finalMap[par.first] = mapaS[par.first] / par.second;
	}
	return finalMap;
}

int System::numberOfSportsAtLeastOneMedal(string countryName)
{
	vector<Competitor*> comps;

	//copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(comps), [&](Competitor* comp) {return countryName == comp->getCountry()->getName(); });
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(comps), *generateFilter("", countryName, -1, nullptr, new Medal(Medal::Bronze)));
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(comps), *generateFilter("", countryName, -1, nullptr, new Medal(Medal::Silver)));
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(comps), *generateFilter("", countryName, -1, nullptr, new Medal(Medal::Gold)));
	set<Sport*> sports;
	for_each(comps.begin(), comps.end(), [&](Competitor* competitor) {sports.insert(competitor->getSport()); });
	return sports.size();
}

vector<Country*> System::threeBestCountries(string olympicGamesName)
{
	vector<Country*> countries;
	//vector<CountryMedals*> medals = getCountrySuccess(olympicGamesName);
	//sort(medals.begin(), medals.end(), [](CountryMedals* a, CountryMedals* b) {return *b < *a; });
	vector<CountryMedals*> medals = allCountriesSuccess(olympicGamesName);
	for (int i = 0; i < min(3, (int)medals.size()); i++)countries.push_back(medals[i]->country);
	return countries;
}

vector<CountryMedals*> System::allCountriesSuccess(string olympicGamesName)
{
	vector<CountryMedals*> medals = getCountrySuccess(olympicGamesName);
	sort(medals.begin(), medals.end(), [](CountryMedals* a, CountryMedals* b) {return *b < *a; });
	return medals;
}

vector<Country*> System::countriesAtLeastOnceBestOverall()
{
	vector<Country*> countries;
	for (auto olgames : allOlympicGames_)
	{
		//vector<Country*> top3 = threeBestCountries(olgames->getName());
		//if(top3.size() > 0)countries.push_back(top3[0]);
		vector<CountryMedals*> top = allCountriesSuccess(olgames->getName());
		if (top.size() > 0)countries.push_back(top[0]->country);
		if (top.size() > 1)
		{
			int i = 1;
			while (top[i] == top[i - 1])countries.push_back(top[i]->country),i++;
		}
	}
	sort(countries.begin(), countries.end());
	countries.erase(unique(countries.begin(), countries.end()), countries.end());
	return countries;
}

vector<string> System::numberOfCities() const
{
	set<string> cities;
	for_each(allOlympicGames_.begin(), allOlympicGames_.end(), [&](OlympicGames* olgames) {cities.insert(olgames->getCity()); });
	/*
	for (auto city : cities)
	{
		cout << "CITY: " << city << endl;
	}
	*/
	vector<string> _cities;
	copy(cities.begin(), cities.end(), back_inserter(_cities));
	return _cities;
}

vector<Athlete*> System::tenYoungestAthletesWithMedalOnDebut()
{
	vector<Athlete*> athletes;
	//tuple<int,Season,bool>
	//at the end of function it will represent year and season of debut, bool will represent that athlete didn't win medal
	//the reason for bool being like this lies in tuple comaprison, he can compete on same OL games and once win and other time not
	//but lexicographically less will be when he didn't win, so we won't catch that he has actually won medal
	map<Athlete*, tuple<int,Season,bool>> debut;
	for_each(allCompetitors_.begin(), allCompetitors_.end(), [&](Competitor* c) {
		for (auto athlete : c->getAthletes())
		{
			if (athlete->getAge() == -1)continue;//NA age
			//if(!debut[athlete])debut[athlete] = 
			if (debut.find(athlete) == debut.end())debut[athlete] = make_tuple(c->getOlympicGames()->getYear(), c->getOlympicGames()->getSeason(), (c->getMedal() == Medal::None));
			else
			{
				tuple<int,Season,bool> tup = make_tuple(c->getOlympicGames()->getYear(), c->getOlympicGames()->getSeason(), (c->getMedal() == Medal::None));
				if (debut[athlete] > tup)debut[athlete] = tup;
			}
		}
		});
	for (auto pair : debut)
	{
		if (get<2>(pair.second) != false)continue;
		athletes.push_back(pair.first);
	}
	sort(athletes.begin(), athletes.end(), [](Athlete* a, Athlete* b) {return a->getAge() < b->getAge(); });
	if(athletes.size() > 10)athletes.erase(athletes.begin()+10, athletes.end());
	return athletes;
}

vector<pair<Country*, Athlete*>> System::getAllAthletesMedalIndividualAndTeam()
{
	vector<pair<Country*, Athlete*>> v;
	vector<void*> params;
	Filter* filterI = new Filter([](Filter* f, void* c) -> bool {
		return ( ((Competitor*)c)->getMedal() == Medal::Bronze || ((Competitor*)c)->getMedal() == Medal::Silver || ((Competitor*)c)->getMedal() == Medal::Gold )
			&& ((Competitor*)c)->getCompetitionType() == CompetitionType::Individual;
		}, params);
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *filterI);
	set<pair<Country*, Athlete*>> sI;
	for (auto c : competitors)for (auto a : c->getAthletes())sI.insert({ c->getCountry(),a });

	competitors.clear();

	Filter* filterT = new Filter([](Filter* f, void* c) -> bool {
		return (((Competitor*)c)->getMedal() == Medal::Bronze || ((Competitor*)c)->getMedal() == Medal::Silver || ((Competitor*)c)->getMedal() == Medal::Gold)
			&& ((Competitor*)c)->getCompetitionType() == CompetitionType::Team;
		}, params);
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), *filterT);
	set<pair<Country*, Athlete*>> sT;
	for (auto c : competitors)for (auto a : c->getAthletes())sT.insert({ c->getCountry(),a });

	set<pair<Country*, Athlete*>> intersect;
	set_intersection(sI.begin(), sI.end(), sT.begin(), sT.end(),
		std::inserter(intersect, intersect.begin()));

	for (auto a : intersect)v.push_back(a);

	return v;
}

set<Athlete*> System::allAthletesThatCompeted(string olympicGamesName)
{
	set<Athlete*> athletes;
	vector<Competitor*> competitors;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(competitors), [&](Competitor* c) {return c->getOlympicGames()->getName() == olympicGamesName; });
	for_each(competitors.begin(), competitors.end(), [&](Competitor* c) {for (auto athlete : c->getAthletes())athletes.insert(athlete); });
	//sort(athletes.begin(), athletes.end());
	//athletes.erase(unique(athletes.begin(), athletes.end()), athletes.end());
	return athletes;
}

vector<Athlete*> System::allAthletesThatCompeted(string olympicGamesName1, string olympicGamesName2)
{
	set<Athlete*> athl1 = allAthletesThatCompeted(olympicGamesName1);
	set<Athlete*> athl2 = allAthletesThatCompeted(olympicGamesName2);
	//set<Athlete*> sathletes;
	///set_intersection(athl1.begin(), athl1.end(), athl2.begin(), athl2.end(), sathletes.begin());
	//copy(sathletes.begin(), sathletes.end(), std::back_inserter(athletes));
	//vector<Athlete*> athletes(sathletes.begin(),sathletes.end());
	//vector<Athlete*> athletes;
	//athletes.assign(sathletes.begin(), sathletes.end());
	vector<Athlete*> athletes;
	set_intersection(athl1.begin(), athl1.end(), athl2.begin(), athl2.end(), back_inserter(athletes));
	//for (auto a : sathletes)athletes.push_back(a);
	return athletes;
}

vector<Competitor*> System::getTeams(string countryName, string olympicGamesName)
{
	/*
	vector<Competitor*> teams;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(teams), *generateFilter("", countryName, year, new CompetitionType(CompetitionType::Team), nullptr));
	sort(teams.begin(), teams.end(), [](Competitor* a, Competitor* b) {
		if (a->getNumberOfAthletes() == b->getNumberOfAthletes())return a->getDiscipline()->getName() < b->getDiscipline()->getName();
		return a->getNumberOfAthletes() > b->getNumberOfAthletes(); });
	return teams;
	*/
	vector<Competitor*> teams;
	copy_if(allCompetitors_.begin(), allCompetitors_.end(), back_inserter(teams), [&](Competitor* a) {
		return a->getOlympicGames()->getName() == olympicGamesName && a->getCountry()->getName() == countryName && a->getCompetitionType() == CompetitionType::Team;
		});
	sort(teams.begin(), teams.end(), [](Competitor* a, Competitor* b) {
		if (a->getNumberOfAthletes() == b->getNumberOfAthletes())return a->getDiscipline()->getName() < b->getDiscipline()->getName();
		return a->getNumberOfAthletes() > b->getNumberOfAthletes(); });
	return teams;
}

void System::testOutputOlympicGames(int limit)
{
	for (auto olgames : this->allOlympicGames_)
	{
		if (limit == 0)break;
		limit--;
		//cout << country->getName() << " " << country->get
		cout << olgames->getName() << " -> " << olgames->getYear() << " " << (olgames->getSeason() == Season::Winter ? "Winter" : "Summer") << endl;
	}
}

void System::testOutputCompetitors(int limit)
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	for (auto c : allCompetitors_)
	{
		cout << c->getCountry() << " " << c->getDiscipline()->getName() << " " << c->getDiscipline()->getSport()->getName() << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void System::testOutputCountries(int limit)
{
	for (auto competitor : this->allCompetitors_)
	{
		if (limit == 0)break;
		limit--;
		cout << competitor->getSport()->getName() << endl;
	}
}

System::~System()
{
	/*
	for (auto athlete : allAthletes_)
	{
		delete athlete;
	}
	*/
	//for_each(allAthletes_.begin(), allAthletes_.end(), [](Athlete* athlete) {delete athlete; });
	for (auto p : allAthletes_)delete p.second;
	for (auto x : allCompetitors_)delete x;
	for (auto x : allCountries_)delete x;
	for (auto x : allDisciplines_)delete x;
	for (auto x : allOlympicGames_)delete x;
	for (auto x : allSports_)delete x;
}
