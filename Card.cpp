#include "Card.h"

using namespace std;


Card::Card(char suite, int num) : suite(suite), num(num), hidden(false) {
}

Card::~Card() {}

char Card::gColor() {
	if (suite == 's' || suite == 'c') {
		return 'b';
	} else {
		return 'r';
	}
}

void Card::displayc() {
	if (hidden == true) {
		std::cout << "[ D ] ";
		return;
	}
	if (this->num < 10) {
		std::cout << '[' << suite << ' ' << num << "] ";
	} else {
		std::cout << '[' << suite << num << "] ";
	}
}

// force shows the card even if hidden
void Card::forcedisplayc() {
	if (this->num < 10) {
		std::cout << '[' << suite << ' ' << num << "] ";
	} else {
		std::cout << '[' << suite << num << "] ";
	}
}

void Card::hidec() {
	hidden = true;
}

void Card::showc() {
	hidden = false;
}

