#include"stack.h"

void stack::push(int x,int y) {
	nums[size][0] = x;
	nums[size][1] = y;
	size++;
};

void stack::pop() {
	size--;
};

int* stack::top() {
	return nums[size - 1];
}

bool stack::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
};

void stack::printstack() {
	for (int i = 0; i < size; i++) {
		cout << nums[i] << "\n";
	}
};