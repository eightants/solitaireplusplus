#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <vector>
#include "Card.h"

class Deck {
public: 
	Deck();
	void add_back(Card);
	void draw();
	int gsize() {return v.size();}
	vector<Card> v;
	void showthree();
	int ind;
	int showing;
	
private:
	int three;
};

#endif