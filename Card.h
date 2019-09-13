#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

class Card {
public: 
	Card();
	Card(char, int);
	~Card();
	char gSuite() {return this->suite;}
	int gNum() {return this->num;}
	char gColor();
	void displayc();
	void forcedisplayc();
	void hidec();
	void showc();
	bool hidden;
private: 
	int num;
	char suite;
};

#endif