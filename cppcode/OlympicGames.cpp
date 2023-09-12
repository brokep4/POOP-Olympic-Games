#include "OlympicGames.h"

string OlympicGames::getName() const
{
	return name_;
}

int OlympicGames::getYear() const
{
	return year_;
}

Season OlympicGames::getSeason() const
{
	return season_;
}

string OlympicGames::getCity() const
{
	return city_;
}

vector<string> OlympicGames::splitBy(string line, char c)
{
	string r = "[";
	r += c;
	r += "]+";
	//regex reg("[!]+");
	regex reg(r);
	sregex_token_iterator iter(line.begin(), line.end(), reg, -1);
	sregex_token_iterator end;

	vector<string> tokens(iter, end);

	return tokens;
}