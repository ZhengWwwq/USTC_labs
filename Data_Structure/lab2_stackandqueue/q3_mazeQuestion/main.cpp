#include"stack.h"
#include"queue.h"
#include"maze.h"
#include<stdlib.h>


int main() {
	

	while (1) {
		maze m;
		m.createMaze();
		m.printSolution(m.findSolution());
		cout << endl;
		system("pause");
	}
	
	return 0;
}