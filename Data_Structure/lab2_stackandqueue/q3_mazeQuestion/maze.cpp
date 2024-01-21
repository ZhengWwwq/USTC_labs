#include"maze.h"


void maze::createMaze() {
	//1为路0为墙
	cout << "请输入行列数：";
	cin >> line >> col;
	cout << "请输入迷宫（1为路，0为墙）：" << endl;
	for (int i = 1; i <= line; i++) {
		for (int j = 1; j <= col; j++) {
			cin >> Maze[i][j];
		}
	}
	cout << "请输入迷宫起点坐标：";
	cin >> startx >> starty;
	cout << "请输入迷宫终点坐标：";
	cin >> endx >> endy;
};

void maze::printMaze() {
	for (int i = 1; i <= line; i++) {
		for (int j = 1; j <= col; j++) {
			cout << Maze[i][j] << ' ';
		}
		cout << endl;
	}
};

int maze::findSolution() {//使用bfs算法找到迷宫最短路径
	int No = 0;//用来记录每个结点在总结点pathes里的位置
	node current;//当前结点
	//初始化起点
	current.x = startx;
	current.y = starty;
	current.step = 0;
	current.prior = -1;
	current.no = No;
	pathes[No] = current;
	No++;
	queue path;//路径队列
	path.push(current);
	while (!path.isEmpty()) {
		current = path.front();
		path.pop();
		if (current.x == endx && current.y == endy) {
			return current.no;
		}
		for (int i = 0; i < 4; i++) {//每一个方向以此遍历
			int cx = current.x + dx[i];
			int cy = current.y + dy[i];
			if (cx<1 || cx>line || cy<1 || cy>col || Maze[cx][cy] == 0 || Maze[cx][cy] == -1) {
				continue;
			}
			node next;
			next.x = cx;
			next.y = cy;
			next.step = current.step + 1;
			next.prior = current.no;
			next.no = No;
			pathes[No] = next;//记录这个位置
			No++;
			path.push(next);
			Maze[next.x][next.y] = -1;//标记已经遍历过的位置
		}
	}
	return -1;
}

void maze::printSolution(int n) {
	if (n == -1) {
		cout << "no solution" << endl;
		return;
	}
	int nos[MAXQSIZE] = { 0 };
	int length = 0;
	node t = pathes[n];
	while (t.prior != -1) {
		nos[length] = t.no;
		t = pathes[t.prior];
		length++;
	}
	for (int i = length; i > 0; i--) {
		cout << "(" << pathes[nos[i]].x << "," << pathes[nos[i]].y << ")" << "->";
	}
	cout << "(" << pathes[nos[0]].x << "," << pathes[nos[0]].y << ")";
	return;
}