#ifndef _LIST_ELEMENT
#define _LIST_ELEMENT
#include<vector>
#include<string>

using namespace std;

struct ListElement
{
	string naughtyNice;
	string countryCode;
	int    postalCode;
	string lastName;
	string firstName;
	vector<string> gifts;
};

#endif
