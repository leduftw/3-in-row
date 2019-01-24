
#include "Tree.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(nullptr));
	double rnd;
	int choice1, choice2;
	char player1, player2, color;

	// Zagrevanje generatora
	for (int i = 0; i < 100; i++)
		rnd = rand();

	bool end = false;
	Tree *t = nullptr;
	Board *b = nullptr;
	clock_t tStart;

	while (!end) {
		cout << "\n1. Start new game and create game tree\n"
			"2. Print game tree\n"
			"3. Delete game tree\n"
			"0. Terminate\n\n"
			"Your choice? ";

		cin >> choice1;

		switch (choice1) {
		case 1:
			do {
				cout << "\nGame mode:\n"
					<< "1. Choose color for first player\n"
					<< "2. Random color for first player\n\n"
					"Your choice? ";

				cin >> choice2;
				if (!(choice2 != 1 xor choice2 != 2))
					cout << "Invalid command! Please try again." << endl;
			} while (choice2 != 1 && choice2 != 2);

			switch (choice2) {
			case 1:
				do {
					cout << "\nEnter the color for the first player: ";
					cin >> color;
					if (!(color != 'B' xor color != 'R'))
						cout << "Invalid color! Please try again." << endl;
				} while (color != 'B' && color != 'R');

				if (color == 'B') {
					player1 = 'B';
					player2 = 'R';
				}
				else {
					player1 = 'R';
					player2 = 'B';
				}

				break;

			case 2:
				rnd = (double)rand() / RAND_MAX;
				if (rnd < 0.5) {
					player1 = 'R';
					player2 = 'B';
				}
				else {
					player1 = 'B';
					player2 = 'R';
				}

				break;

			default:
				cout << "Invalid command!\n";
				break;
				
			}

			b = new Board(player1);
			cout << "\nEnter current position on the board:" << endl;
			cin >> *b;
			cout << endl;

			delete t;
			cout << "Creating game tree..." << endl;
			tStart = clock();
			t = new Tree(b, 5);
			cout << "Game tree created in " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " seconds." << endl << endl;
			cout << "Player who makes first move: " << player1 << endl;
			cout << "Number of nodes in game tree: " << t->numberOfNodes() << endl;
			cout << "Height of game tree: " << t->height() << endl;
			cout << "Width of game tree: " << t->width() << endl;

			break;

		case 2:
			if (t) {
				cout << "Game tree:" << endl;
				cout << *t;
			}
			else
				cout << "Game tree is not yet created!\n";

			break;

		case 3:
			if (t) {
				cout << "Deleting..." << endl;
				delete t;
				cout << "Game tree deleted." << endl;
			}
			t = nullptr;
			break;

		case 0:
			end = true;
			break;

		default:
			cout << "Invalid command!\n";
			break;

		}
	}
	// Brisemo stablo (ako korisnik nije obrisao)
	if (t) {
		cout << "Deleting..." << endl;
		delete t;
		cout << "Game tree deleted." << endl;
	}
}