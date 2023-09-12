// ConsoleApplication17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "System.h"

int main()
{

	System s;
	cout << "Enter path to athletes.txt: ";
	string path;
	cin >> path;
	if (!s.loadAthletes(path))return 0;

	cout << "Which mode(Group - 1, Individual - 2), any other number will exit program" << endl;
	int mode;
	cin >> mode;
	if (mode == 1)
	{
		cout << "Enter path to events.txt: ";
		string path;
		cin >> path;
		if (!s.loadGroupMode(path))return 0;
	}
	else if (mode == 2)
	{
		cout << "Enter path to events.txt: ";
		string path;
		cin >> path;
		cout << "Enter year: ";
		int year;
		cin >> year;
		if (!s.loadIndividualMode(path, year))return 0;
	}
	else return 0;

	//s.testOutputCompetitors(-1);

	while (1)
	{
		cout << "MENU" << endl;
		cout << "1. Number of participants" << endl;
		cout << "2. Number of disciplines" << endl;
		cout << "3. Average height" << endl;
		cout << "4. Average weight" << endl;
		cout << "5. Number of differents sports where given country has won at least one medal" << endl;
		cout << "6. Top three countries by success on given Olympic games" << endl;
		cout << "7. Countries that were best overall at least once" << endl;
		cout << "8. Ten youngest athletes with medal on debut" << endl;
		cout << "9. All pairs of country-athlete, where athlete has medal in both team and individual" << endl;
		cout << "10. All athletes that competed on given pair of Olympic games" << endl;
		cout << "11. All teams that given country had on given Olympic games" << endl;
		cout << "12. All cities where Olympic games where held" << endl;
		cout << "-9. Exit" << endl;
		int option;
		cin >> option;
		getchar();
		if (option == -9)
		{
			return 0;
		}
		else if (option >= 1 && option <= 4)
		{
			cout << "If you don't want some filter write -1" << endl;
			cout << "Filter by sport name:";
			string sportName;
			//getchar();
			getline(cin, sportName);
			cout << "Filter by country:";
			//getchar();
			string countryName;
			getline(cin, countryName);

			//cout << "OVO:" << sportName << "~~~~~~~~~~~~~~~~~OVO:" << countryName << endl;

			cout << "Filter by year:";
			int year;
			cin >> year;
			cout << "Filter by type(Team or Individual):";
			string type;
			cin >> type;
			cout << "Filter by medal(Gold, Silver, Bronze, None):";
			string medal;
			cin >> medal;
			Medal* med=nullptr;
			CompetitionType* compt=nullptr;
			if (sportName == "-1")sportName = "";
			if (countryName == "-1")countryName = "";
			if (type == "Team")compt = new CompetitionType(CompetitionType::Team);
			if (type == "Individual")compt = new CompetitionType(CompetitionType::Individual);
			if (medal == "Gold")med = new Medal(Medal::Gold);
			if (medal == "Silver")med = new Medal(Medal::Silver);
			if (medal == "Bronze")med = new Medal(Medal::Bronze);
			if (medal == "None")med = new Medal(Medal::None);
			Filter* f = s.generateFilter(sportName, countryName, year, compt, med);
			if (option == 1)
			{
				cout << "Result: " << s.numberOfParticipants(f) << endl;
			}
			else if (option == 2)
			{
				cout << "Result: " << s.numberOfDisciplines(f) << endl;
			}
			else if (option == 3)
			{
				cout << "Result: " << s.averageHeight(f) << endl;
			}
			else
			{
				cout << "Result: " << s.averageWeight(f) << endl;
			}
		}
		else if (option == 5)
		{
			cout << "Enter country name:";
			string countryName;
			getline(cin, countryName);
			//cin.getline(countryName);
			//cin >> countryName;
			cout << "Result: " << s.numberOfSportsAtLeastOneMedal(countryName) << endl;
		}
		else if (option == 6)
		{
			cout << "Enter Olympic games year:";
			string year;
			cin >> year;
			cout << "Enter Olympic games season(Winter/Summer):";
			string olympicGamesName;
			cin >> olympicGamesName;//getline(cin, olympicGamesName);
			olympicGamesName = year + " " + olympicGamesName;
			vector<Country*> v = s.threeBestCountries(olympicGamesName);
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto c : v)
			{
				cout << c->getName() << endl;
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		else if (option == 7)
		{
			vector<Country*> v = s.countriesAtLeastOnceBestOverall();
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto c : v)
			{
				cout << c->getName() << endl;
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		else if (option == 8)
		{
			vector<Athlete*> athletes = s.tenYoungestAthletesWithMedalOnDebut();
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto a : athletes)
			{
				cout << a->getName() << " " << a->getAge() << endl;
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		else if (option == 9)
		{
			vector<pair<Country*, Athlete*>> v = s.getAllAthletesMedalIndividualAndTeam();
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto p : v)
			{
				cout << p.first->getName() << " - " << p.second->getName() << endl;
			}
			cout << "Total: " << v.size() << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		if (option == 10)
		{
			cout << "Enter Olympic games year:";
			string year1;
			cin >> year1;
			cout << "Enter Olympic games season(Winter/Summer):";
			string season1;
			cin >> season1;
			cout << "Enter Olympic games year:";
			string year2;
			cin >> year2;
			cout << "Enter Olympic games season(Winter/Summer):";
			string season2;
			cin >> season2;
			string olympicGamesName1 = year1 + " " + season1;
			string olympicGamesName2 = year2 + " " + season2;
			vector<Athlete*> athletes = s.allAthletesThatCompeted(olympicGamesName1, olympicGamesName2);
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto a : athletes)
			{
				cout << a->getName() << endl;
			}
			cout << "Total: " << athletes.size() << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		else if (option == 11)
		{
			cout << "Enter country name:";
			string countryName;
			getline(cin, countryName);
			cout << "Enter Olympic games year:";
			string year;
			cin >> year;
			cout << "Enter Olympic games season(Winter/Summer):";
			string olympicGamesName;
			cin >> olympicGamesName;//getline(cin, olympicGamesName);
			olympicGamesName = year + " " + olympicGamesName;
			vector<Competitor*> v = s.getTeams(countryName, olympicGamesName);
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto c : v)
			{
				//cout << p.first->getName() << " - " << p.second->getName() << endl;
				cout << c->getDiscipline()->getName() << " " << c->getNumberOfAthletes() << endl;
			}
			cout << "Total: " << v.size() << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
		else if (option == 12)
		{
			//s.numberOfCities()
			vector<string> cities = s.numberOfCities();
			cout << "~~~~~~~~~~~RESULT~~~~~~~~~~~\n";
			for (auto c : cities)
			{
				cout << c << endl;
			}
			cout << "Total: " << cities.size() << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		}
	}
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
