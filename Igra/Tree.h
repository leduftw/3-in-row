
#ifndef TREE_H
#define TREE_H

#include "Queue.h"

// M-arno stablo
class Tree {

	int m;
	TreeNode *root;

	void deleteTree();

public:
	// Konstruktor i destruktor (Stablo ne sme da se kopira i premesta)
	Tree(Board *, int);
	Tree(const Tree &t) = delete;

	~Tree() {
		deleteTree();
	}

	// Stablo ne sme da se dodeljuje
	Tree& operator=(const Tree &t) = delete;

	// Ispis stabla, odredjivanje broja cvorova stabla, odredjivanje visine stabla i odredjivanje sirine stabla
	friend ostream& operator<<(ostream &, const Tree &);
	int numberOfNodes() const;
	int height() const;
	int width() const;

};

#endif
