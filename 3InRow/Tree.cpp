
#include "Tree.h"

// Stvaranje celog stabla igre sa odgovarajucom pocetnom pozicijom i sa datim stepenom (u nasem slucaju 5)
Tree::Tree(Board *b, int mm) : m(mm), root(new TreeNode(b)) {
	Queue q;
	q.push(root);
	q.push(nullptr);

	while (q.first()) {
		TreeNode *next = q.first();
		q.pop();

		// Dodeljujemo vrednost pozicije tekucem cvoru
		next->board->setVal(next->board->evaluate());

		// Ako igra nije zavrsena, dodajemo sinove toj poziciji uz eventualnu propagaciju
		if (!next->board->isFinished()) {
			// Dodajemo decu tekucem cvoru i dodeljujemo vrednost pozicije deci
			for (int i = 0; i < 5; i++) {
				// Tabla b predstavlja sve sinove tekuceg cvora
				Board *b = next->board->drop(i); // Vec joj se dodeljuje i val
				if (b) {
					// Dodajemo decu
					if (!next->firstChild)
						next->firstChild = new TreeNode(b, next);
					else {
						TreeNode *curr = nullptr;
						for (curr = next->firstChild; curr->sibling; curr = curr->sibling);
						curr->sibling = new TreeNode(b, next);
					}

					// Propagacija
					TreeNode *temp = next;
					while (true) {
						// Ako je cvor list, pocinje propagacija
						if (b->isFinished()) {
							if (!temp) // Ako u propagaciji odemo do korena prestajemo sa propagacijom
								break;

							int forParent = temp->firstChild->board->getVal();
							for (TreeNode *curr = temp->firstChild; curr; curr = curr->sibling)
								if (temp->board->getCurrentMove() == 'B') { // Trazimo maksimum od dece
									if (curr->board->getVal() > forParent)
										forParent = curr->board->getVal();

								}
								else { // Na potezu je crveni, pa trazimo minimum od dece
									if (curr->board->getVal() < forParent)
										forParent = curr->board->getVal();
								}

							// Ako se vrednost u ocu menja onda upisujemo novu vrednost i nastavljamo sa propagacijom, a ako se ne menja zavrsavamo propagaciju
							if (temp->board->getVal() != forParent) {
								temp->board->setVal(forParent);
								temp = temp->parent;
							}
							else 
								break;

						}
						else break; // Ako cvor nije zavrsna pozicija onda propagaciju ne pokusavamo
					}
				}
			}
		}

		// Stavljamo u red sve sinove tekuceg cvora
		for (TreeNode *curr = next->firstChild; curr; curr = curr->sibling)
			q.push(curr);

		if (!q.first()) {
			q.pop();
			q.push(nullptr);
		}
	}

	q.pop();
}

// Brisanje stabla (level order)
void Tree::deleteTree() {
	if (!root)
		return;

	Queue q;
	q.push(root);

	while (!q.isEmpty()) {
		TreeNode *next = q.first();
		q.pop();

		// Stavljamo u red sve sinove tekuceg cvora
		for (TreeNode *curr = next->firstChild; curr; curr = curr->sibling)
			q.push(curr);

		// Brisemo cvor next
		delete next;
	}

	root = nullptr;
}

// Ispis stabla igre (level order)
ostream& operator<<(ostream &os, const Tree &t) {
	if (t.numberOfNodes() == 0)
		return os << "Tree is empty!\n";

	os << endl << endl;

	Queue q;
	int level = 0;
	bool indicator = true; // Samo govori da li zapocinjemo ispis novog nivoa
	q.push(t.root);
	q.push(nullptr);

	while (q.first()) {
		TreeNode *next = q.first();
		q.pop();

		if(indicator)
			os << "PRINTING LEVEL " << level << " OF GAME TREE..." << endl << endl;
		indicator = false;
		os << *next->board;

		// Stavljamo u red sve sinove tekuceg cvora
		for (TreeNode *curr = next->firstChild; curr; curr = curr->sibling)
			q.push(curr);

		// Ako je prvi element reda nullptr znaci da smo stigli do kraja tog nivoa, pa brisemo sa pocetka a dodajemo na kraj nullptr
		if (!q.first()) {
			q.pop();
			q.push(nullptr);
			// Prelazak u novi red (ispis po nivoima)
			os << "LEVEL " << level << " OF GAME TREE IS PRINTED!" << endl;
			os << "---------------------------------------------" << endl;
			os << "---------------------------------------------" << endl << endl;
			indicator = true;
			level++;
		}
	}

	// Brisemo jedini preostali granicnik
	q.pop();
	return os;
}

// Odredjivanje broja cvorova u stablu (level order)
int Tree::numberOfNodes() const {
	if (!root)
		return 0;

	Queue q;
	q.push(root);
	int num = 0;

	while (!q.isEmpty()) {
		TreeNode *next = q.first();
		q.pop();
		num++; // Kako skidamo cvorove iz reda, inkrementiramo num

		// Stavljamo u red sve sinove tekuceg cvora
		for (TreeNode *curr = next->firstChild; curr; curr = curr->sibling)
			q.push(curr);
	}
	return num;
}

// Odredjivanje visine stabla (sa granicnikom)
int Tree::height() const {
	if (!root)
		return -1;

	Queue q;
	q.push(root);
	q.push(nullptr);
	int h = -1;

	while (q.first()) {
		TreeNode *next = q.first();
		q.pop();

		for (TreeNode *curr = next->firstChild; curr; curr = curr->sibling)
			q.push(curr);

		if (!q.first()) {
			q.pop();
			q.push(nullptr);
			h++;
		}
	}
	q.pop();
	return h;
}

// Odredjivanje sirine stabla (sa granicnikom)
int Tree::width() const {
	if (!root)
		return 0;

	Queue q;
	int maxWidth = 1, currentWidth = 0;
	q.push(root);
	q.push(nullptr);

	while (q.first()) {
		TreeNode *next = q.first();
		q.pop();

		currentWidth++;

		for (TreeNode *curr = next->firstChild; curr; curr = curr->sibling)
			q.push(curr);

		if (!q.first()) {
			q.pop();
			q.push(nullptr);
			if (currentWidth > maxWidth)
				maxWidth = currentWidth;
			currentWidth = 0;
		}
	}

	q.pop();
	return maxWidth;
}
