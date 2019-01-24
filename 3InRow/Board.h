
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;

class Board {

	char board[5][5];
	int val; // Ovde ce biti smestena vrednost koja govori ko pobedjuje
	char currentMove;

	void copy(const Board &);

public:
	// Konstruktori
	Board(char curr) {
		currentMove = curr;
	}

	Board(const Board &b) {
		copy(b);
	}

	// Getter i setter metode
	int getVal() const {
		return val;
	}

	void setVal(int newVal) {
		val = newVal;
	}

	char getCurrentMove() const {
		return currentMove;
	}

	void setCurrentMove(char newMove) {
		currentMove = newMove;
	}

	// Izracunavanje trenutnog stanja na tabli, odigravanje poteza, proveravanje da li je partija zavrsena, ispis table i ucitavanje table
	int evaluate() const;
	Board* drop(int);

	bool isFinished() const {
		return !(val == 10 || val == -10);
	}

	friend ostream& operator<<(ostream &, const Board &);
	friend istream& operator>>(istream &, Board &);

};

#endif
