#include"maze.h"


void maze::createMaze() {
	//1Ϊ·0Ϊǽ
	cout << "��������������";
	cin >> line >> col;
	cout << "�������Թ���1Ϊ·��0Ϊǽ����" << endl;
	for (int i = 1; i <= line; i++) {
		for (int j = 1; j <= col; j++) {
			cin >> Maze[i][j];
		}
	}
	cout << "�������Թ�������꣺";
	cin >> startx >> starty;
	cout << "�������Թ��յ����꣺";
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

int maze::findSolution() {//ʹ��bfs�㷨�ҵ��Թ����·��
	int No = 0;//������¼ÿ��������ܽ��pathes���λ��
	node current;//��ǰ���
	//��ʼ�����
	current.x = startx;
	current.y = starty;
	current.step = 0;
	current.prior = -1;
	current.no = No;
	pathes[No] = current;
	No++;
	queue path;//·������
	path.push(current);
	while (!path.isEmpty()) {
		current = path.front();
		path.pop();
		if (current.x == endx && current.y == endy) {
			return current.no;
		}
		for (int i = 0; i < 4; i++) {//ÿһ�������Դ˱���
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
			pathes[No] = next;//��¼���λ��
			No++;
			path.push(next);
			Maze[next.x][next.y] = -1;//����Ѿ���������λ��
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