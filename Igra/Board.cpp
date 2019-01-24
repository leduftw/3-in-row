
#include "Board.h"

// Kopiranje table
void Board::copy(const Board &b) {
	val = b.val;
	currentMove = b.currentMove;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			board[i][j] = b.board[i][j];
}

// Ispis table
ostream& operator<<(ostream &os, const Board &b) {
	for (int i = 0; i < 5; i++, os << endl)
		for (int j = 0; j < 5; j++)
			os << b.board[i][j] << ' ';

	int status = b.evaluate();

	os << "Next move: ";
	if (status == 1)
		os << "Blue has won the game!" << endl;
	else if (status == -1)
		os << "Red has won the game!" << endl;
	else if (status == 0)
		os << "The game is finished! It is a draw!" << endl;
	else
		os << b.currentMove << endl;

	os << "Value of current position: " << b.evaluate() << endl;
	os << "Winning player: " << b.val << endl;
	return os << "---------------------------------------------" << endl << endl;
}

// Ucitavanje table
istream& operator>>(istream &is, Board &b) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			is >> b.board[i][j];
	return is;
}

/*
	Skeniranjem table utvrdjujemo da li je plavi pobedio (+1),
	da li je crveni pobedio (-1), da li je tabla puna a nema pobednika (0)
	ili da se igra jos (+10 ili -10)
*/
int Board::evaluate() const {
	// Razlikujemo 4 oblika: 3 u vrsti, 3 u koloni, 3 u dijagonali sa pozitivnim i negativnim nagibom (2 oblika)
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			// 3 iste u vrsti
			if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] != 'O')
				return board[i][j] == 'B' ? 1 : -1;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			// 3 iste u koloni
			if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] != 'O')
				return board[i][j] == 'B' ? 1 : -1;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			// Dijagonala sa negativnim nagibom
			if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] != 'O')
				return board[i][j] == 'B' ? 1 : -1;

	for (int i = 0; i < 3; i++)
		for (int j = 2; j < 5; j++)
			// Dijagonala sa pozitivnim nagibom
			if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] != 'O')
				return board[i][j] == 'B' ? 1 : -1;

	// Provera da li je cela tabla popunjena
	if (board[0][0] != 'O' && board[0][1] != 'O' && board[0][2] != 'O' && board[0][3] != 'O' && board[0][4] != 'O')
		return 0;

	// Ako nema pobednika, a nije ni nereseno, onda vracamo +10 ili -10
	// Ako je na potezu plavi onda to znaci da je pre njega igrao crveni pa se trazi minimum (upisuje se +10), u suprotnom -10
	return (currentMove == 'B') ? 10 : -10;
}

// Odigravanje poteza
Board* Board::drop(int col) {
	Board *b = new Board(*this);

	// Ako je na potezu bio plavi, nakon odigranog poteza ce igrati crveni i obrnuto
	if (b->currentMove == 'B')
		b->setCurrentMove('R');
	else
		b->setCurrentMove('B');

	// Kuglica se ne moze ubaciti u kolonu koja je vec puna
	if (b->board[0][col] != 'O')
		return nullptr;

	int depth = 4;
	// Sigurno ima neko slobodno mesto u toj koloni, pa ne moramo nista dodatno proveravati depth >= 0
	while (b->board[depth][col] != 'O')
		depth--;

	b->board[depth][col] = currentMove;
	b->setVal(b->evaluate());
	return b;
}

