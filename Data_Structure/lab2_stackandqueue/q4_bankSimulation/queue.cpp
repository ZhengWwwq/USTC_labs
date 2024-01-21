#include"queue.h"

bool queue::isEmpty() {
	if (top == base) {
		return true;
	}
	return false;
}

void queue::push(int num) {
	no[top] = num;
	top++;
}

void queue::pop() {
	base++;
}

int queue::front() {
	return no[base];
}

int queue::size() {
	return top - base;
}