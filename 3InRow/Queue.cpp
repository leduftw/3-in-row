
#include "Queue.h"

// Stvaranje praznog reda
Queue::Queue() {
	front = rear = nullptr;
	length = 0;
}

// Kopiranje reda
void Queue::copy(const Queue& q) {
	length = q.length;
	front = rear = nullptr;

	for (Node *curr = q.front; curr; curr = curr->next)
		rear = (front ? rear->next : front) = new Node(curr->info);
}

// Brisanje reda
void Queue::deleteQueue() {
	while (front) {
		Node *old = front;
		front = front->next;
		delete old;
	}
	rear = nullptr;
	length = 0;
}

// Umetanje elementa u red - dodavanje na kraj liste
void Queue::push(TreeNode *n) {
	rear = (front ? rear->next : front) = new Node(n);
	length++;
}

// Brisanje elementa iz reda - brisanje sa pocetka liste bez vracanja skinutog elementa
void Queue::pop() {
	if (isEmpty()) {
		cout << "Queue is empty!" << endl;
		exit(1);
	}
	else {
		Node *old = front;
		if (front == rear)
			front = rear = nullptr;
		else
			front = front->next;

		length--;
		delete old;
	}
}


