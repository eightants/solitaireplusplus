#include <cstdlib>
#include <string>
#include <ctime>
#include <map>
#include "Card.cpp"
#include "Deck.cpp"

bool checkWin(vector<vector<Card>> f) {
	for (int i = 0; i < f.size(); i++) {
		if (f[i].size() != 13) {
			return false;
		}
	}
	return true;
}

int main() {
	cout << endl;
	cout << "******************************" << endl;
	cout << " Solitaire++" << endl;
	cout << endl;
	cout << " Command line solitaire" << endl;
	cout << endl;
	cout << " By Anthony Teo @eightants" << endl;
	cout << "******************************" << endl;
	
	
	cout << endl << endl;
	cout << "Instructions" << endl;
	cout << "------------" << endl;
	cout << "[ D ] = face down card" << endl;
	cout << "[h 8] = [suite number]" << endl;
	cout << "The above card is the 8 of Hearts" << endl << endl;
	cout << "Select a row to move and possible movements will be suggested, " << endl;
	cout << "Choose from the suggested moves. " << endl << endl;
	
	// SETUP
	srand ( time(NULL) );
	char choice;
	
	// match key with selection
	map<char, int> foundeck;
	foundeck['1'] = 0;
	foundeck['2'] = 1;
	foundeck['3'] = 2;
	foundeck['4'] = 3;
	foundeck['5'] = 4;
	foundeck['6'] = 5;
	foundeck['7'] = 6;
	foundeck['z'] = 10;
	foundeck['x'] = 11;
	foundeck['c'] = 12;
	foundeck['v'] = 13;
	foundeck['a'] = 20;
	foundeck['s'] = 21;
	
	// sets up a deck of 52 cards
	Deck md = Deck();
	vector<char> sui = {'c', 's', 'h', 'd'};
	// generates the 52 cards
	for (int i = 0; i < sui.size(); i++) {
		for (int j = 1; j < 14; j++) {
			Card c = Card(sui.at(i), j);
			c.hidec();
			md.add_back(c);
		}
	}
	// takes random cards from the generated deck to populate the table
	vector<vector<Card>> table;
	for (int i = 0; i < 7; i++) {
		vector<Card> row;
		table.push_back(row);
	}
	for (int i = 0; i < 7; i++) {
		for (int j = i; j < 7; j++) {
				// takes a random card, adds it to table, remove from deck
				int temp = (rand() % md.v.size());
				if (j != i) {
					md.v[temp].hidec();
				} else {
					md.v[temp].showc();
				}
				table[j].push_back(md.v[temp]);
				md.v.erase(md.v.begin() + temp);
		}
	}
	
	// generates foundations 4 decks
	vector<vector<Card>> foundation;
	for (int i = 0; i < 4; i++) {
		vector<Card> temp;
		foundation.push_back(temp);
	}
	
	// DISPLAY AND GAME MECHANICS
	// while win condition not met
	int step = 1;
	while (checkWin(foundation) != true) {
		// finds the longest row on table
		int tmax = 0;
		for (int i = 0; i < table.size(); i++) {
			if (table[i].size() > tmax) {
				tmax = table[i].size();
			}
		}	
		
		// display step number
		cout << endl;
		cout << "---------------" << endl;
		cout << " MOVE " << step << endl;
		cout << "---------------" << endl;
		cout << "Cards remaining in deck: " << md.gsize() << endl;
		cout << endl;

		// display foundations
		cout << " (Z)   (X)   (C)   (V)           (A) to select, (S) to draw" << endl;
		for (int i = 0; i < 4; i++) {
			if (foundation[i].size() == 0) {
				cout << "[   ] ";
			} else {
				foundation[i][foundation[i].size() - 1].forcedisplayc();
			}
		}
		
		//display deck
		cout << "         [ Deck ] ";
		md.showthree();
		
		cout << endl << endl;
		
		// display table
		cout << " (1)   (2)   (3)   (4)   (5)   (6)   (7)  "<< endl;
		for (int i = 0; i < tmax; i++) {
			for (int j = 0; j < table.size(); j++) {
				if (i < table[j].size()) {
					table[j][i].displayc();
				}
				else {
					cout << "      ";
				}
			}
			cout << endl;
		}
		cout << "Enter 'e' to exit" << endl;
		
		
		// takes user input then gives available next moves
		cout << "Select a row to move: ";
		cin >> choice;
		if (choice == 'e') {
			return 0;
		}
		
		int temp = foundeck[choice];
		int upper = 0;
		// vector for potential moves
		vector<int> potential;
		
		// TABLE SELECTED
		Card chosen = Card('j', 100);
		// if card from table selected
		if (temp < 7) {
			for (int i = 0; i < table[temp].size(); i++) {
				if (table[temp][i].hidden == false) {
					upper = i;
					break;
				}
			}
			// selected card
			chosen = table[temp][upper];
			// compares selected against other rows on table, appending options to vector
			for (int j = 0; j < 7; j++) {
				if (j != temp) {
					// cout << "col " << chosen.gColor() << chosen.gNum() << " vs ";
					// cout << "col " << table[j][table[j].size() - 1].gColor() << table[j][table[j].size() - 1].gNum() << endl;
					if (chosen.gNum() == 13 && table[j].size() == 0) {
						potential.push_back(j);
					}
					if ((table[j][table[j].size() - 1].gNum() == (chosen.gNum() + 1)) && (chosen.gColor() != table[j][table[j].size() - 1].gColor())) {
						potential.push_back(j);
					}
				}
			}
			// compares end card against foundation decks
			for (int j = 0; j < 4; j++) {
				if (foundation[j].size() > 0) {
					if ((foundation[j][foundation[j].size() - 1].gSuite() == table[temp][table[temp].size() - 1].gSuite()) && (foundation[j][foundation[j].size() - 1].gNum() == (table[temp][table[temp].size() - 1].gNum() - 1))) {
						potential.push_back(j + 10);
					}
				} else if (table[temp][table[temp].size() - 1].gNum() == 1) {
					potential.push_back(j + 10);
				}
			}
		} else if (temp < 14 && (foundation[temp - 10].size() > 0)) {
			// else if FOUNDATION SELECTED
			chosen = foundation[temp - 10][foundation[temp - 10].size() - 1];
			// compares selected against other rows on table, appending options to vector
			for (int j = 0; j < 7; j++) {
				// cout << "col " << chosen.gColor() << chosen.gNum() << " vs ";
				// cout << "col " << table[j][table[j].size() - 1].gColor() << table[j][table[j].size() - 1].gNum() << endl;
				if ((table[j][table[j].size() - 1].gNum() == (chosen.gNum() + 1)) && (chosen.gColor() != table[j][table[j].size() - 1].gColor())) {
					potential.push_back(j);
				}
			}
		} else if (temp == 20) {
			// DECK SELECTED
			if (md.showing == 0) {
				md.draw();
			} else {
				chosen = md.v[md.ind + md.showing - 1];
				// compares with table
				for (int j = 0; j < 7; j++) {
					// cout << "col " << chosen.gColor() << chosen.gNum() << " vs ";
					// cout << "col " << table[j][table[j].size() - 1].gColor() << table[j][table[j].size() - 1].gNum() << endl;
					if ((table[j][table[j].size() - 1].gNum() == (chosen.gNum() + 1)) && (chosen.gColor() != table[j][table[j].size() - 1].gColor())) {
						potential.push_back(j);
					}
				}
				// compares against foundation decks
				for (int j = 0; j < 4; j++) {
					if (foundation[j].size() > 0) {
						if ((foundation[j][foundation[j].size() - 1].gSuite() == chosen.gSuite()) && (foundation[j][foundation[j].size() - 1].gNum() == (chosen.gNum() + 1))) {
							potential.push_back(j + 10);
						}
					} else if (chosen.gNum() == 1) {
						potential.push_back(j + 10);
					}
				}
			}
		} else if (temp == 21) {
			md.draw();
		} else {
			cout << "Invalid entry!" << endl;
		}
			
		// translates the indexes into key presses control
		vector<char> todo;
		for (int i = 0; i < potential.size(); i++) {
			map<char, int>::iterator it;
			for (it = foundeck.begin(); it != foundeck.end(); it++) {
				if (it->second == potential[i]) {
					todo.push_back(it->first);
				}
			}
		}
		
		// returns possible moves
		cout << "Possible moves: ";
		if (todo.size() == 0) {
			cout << "none" << endl;
		} else {
			for (int i = 0; i < todo.size(); i++) {
				cout << "(" << todo[i] << ")  ";
			}
			char entry;
			cout << endl;
			cout << "Make your choice: ";
			cin >> entry;
			bool validchoice = false;
			for (int i = 0; i < todo.size(); i++) {
				if (todo[i] == entry) {
					validchoice = true;
					break;
				}
			}
			if (validchoice != true) {
				
				cout << "> Invalid choice! <" << endl;
				continue;
			}
			int move = foundeck[entry];
			// depends on where user chooses to move to
			// moving from TABLE to TABLE
			if (move < 7 && temp < 7) {
				if ((table[temp].size() - 1) != upper){
					// moving a row that has multiple cards face up
					for (int i = upper; i < table[temp].size(); i++) {
						table[move].push_back(table[temp][i]);
					}
					for (int i = (table[temp].size() - 1); i >= upper; i--) {
						table[temp].pop_back();
					}
				} else {
					table[move].push_back(chosen);
					table[temp].pop_back();
				}
				for (int i = 0; i < 7; i++) {
					// ensures the last card is always faceup
					table[i][table[i].size() - 1].showc();
				}
			} else if (move < 7 && temp == 20) {
				// moving from DECK to TABLE
				md.v.erase(md.v.begin() + (md.ind + md.showing - 1));
				table[move].push_back(chosen);
				md.showing--;
				// last card faceup
				for (int i = 0; i < 7; i++) {
					table[i][table[i].size() - 1].showc();
				}
			} else if (move < 14 && temp == 20) {
				// moving from DECK to FOUNDATION
				md.v.erase(md.v.begin() + (md.ind + md.showing - 1));
				foundation[move - 10].push_back(chosen);
				md.showing--;
			} else if (move < 14 && temp < 7) {
				// moving from TABLE to FOUNDATION
				foundation[move - 10].push_back(table[temp][table[temp].size() - 1]);
				table[temp].pop_back();
				// last card faceup
				for (int i = 0; i < 7; i++) {
					table[i][table[i].size() - 1].showc();
				}
			} else if (move < 7 && temp < 14) {
				// moving from FOUNDATION to TABLE
				table[move].push_back(foundation[temp - 10][foundation[temp - 10].size() - 1]);
				foundation[temp - 10].pop_back();
			} else {
				cout << "Error processing move" << endl;
			}
		}
		step++;
	}

	cout << "---------------" << endl;
	cout << " YOU WIN!" << endl;
	cout << "---------------" << endl;
	return 0;
	
	
	// MECHANICS
	// if 1-7, check uppermost revealed card against 1-7 and check against foundation
	// if A, check against 1-7 and foundation
	// if foundation, check against 1-7
}