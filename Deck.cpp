#include "Deck.h"

Deck::Deck() {
	ind = 0;
	showing = 3;
}

void Deck::add_back(Card c) {
	this->v.push_back(c);
}

void Deck::draw() {
	showing = 3;
	if (ind < v.size() - 3) {
		this->ind += 3;
	} else {
		this->ind = 0;
	}
}

void Deck::showthree() {
	for (int i = 0; i < showing; i++) {
		v[ind + i].forcedisplayc();
	}
}
	