#include"queue.h"

void queue::pop() {
	base++;
};

void queue::push(node p) {
	Queue[top] = p;
	top++;
};

bool queue::isEmpty() {
	if (top == base) {
		return true;
	}
	return false;
};

int queue::size() {
	return top - base;
};

void queue::pushback(queue q2) {
	for (int i = q2.base; i < q2.top; i++) {
		Queue[top].x = q2.Queue[i].x;
		Queue[top].y = q2.Queue[i].x;
		top++;
	}
};

void queue::print() {
	for (int i = base; i < top; i++) {
		cout << Queue[i].x << Queue[i].y;
	}
};

node queue::front() {
	return Queue[base];
}