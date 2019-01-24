
#ifndef QUEUE_H
#define QUEUE_H

#include "Board.h"

// Cvor stabla - pokazivac na tablu, pokazivac na oca, desnog brata i najstarijeg (najlevljeg) sina
struct TreeNode {
	Board *board;
	TreeNode *parent, *sibling, *firstChild;

	TreeNode(Board *b, TreeNode *par = nullptr, TreeNode *sib = nullptr, TreeNode *child = nullptr) {
		board = b;
		parent = par;
		sibling = sib;
		firstChild = child;
	}


};

// Red neogranicenog kapaciteta (realizovan kao ulancana lista)
class Queue {

	// Cvor liste - pokazivac na cvor stabla i na naredni element liste
	struct Node {
		TreeNode *info;
		Node *next;

		Node(TreeNode *data, Node *n = nullptr) {
			info = data;
			next = n;
		}
	};

	// front pokazuje na prvi element liste, a rear na poslednji
	Node *front, *rear;
	int length;

	void copy(const Queue &);

	void move(Queue &q) {
		front = q.front;
		rear = q.rear;
		length = q.length;
		q.front = q.rear = nullptr;
	}

	void deleteQueue();

public:
	// Konstruktori i destruktor
	Queue();

	Queue(const Queue &q) {
		copy(q);
	}

	Queue(Queue &&q) {
		move(q);
	}

	~Queue() {
		deleteQueue();
	}

	// Preklapanje operatora dodele
	// Kopirajuca i premestajuca varijanta
	Queue& operator=(const Queue &q) {
		if (this != &q) {
			deleteQueue();
			copy(q);
		}
		return *this;
	}

	Queue& operator=(Queue &&q) {
		if (this != &q) {
			deleteQueue();
			move(q);
		}
		return *this;
	}

	// Duzina reda
	int getLength() const {
		return length;
	}

	// Provera da li je red prazan
	bool isEmpty() const {
		return length == 0;
	}

	// Ocitavanje elementa sa pocetka reda
	TreeNode* first() const {
		return front->info;
	}

	void push(TreeNode *);
	void pop();

};

#endif