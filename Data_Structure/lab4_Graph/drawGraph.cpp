#include<iostream>
#include<graphics.h>
#include<stdlib.h>
using namespace std;

//画图用到的数据
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//使用图的邻接链表方式存储
#define MAX_VERTIX_NUM 20//最多结点数量
int visited[MAX_VERTIX_NUM];    //visited数组用于遍历时判断是否遍历过
typedef struct ArcNode {
    int adjvex;                 //该弧所指向的顶点的位置
    struct ArcNode* nextarc;    //指向下一条弧的指针
}ArcNode;
typedef struct VNode {
    int data;                   //顶点的内容
    ArcNode* firstarc;          //顶点的第一条弧
}VNode, AdjList[MAX_VERTIX_NUM + 1];
typedef struct ALGraph {
    AdjList vertices;
    int vexnum, arcnum;          //顶点数量和弧的数量
}ALGraph;

class Graph {
private:
    ALGraph G;

    int pos[MAX_VERTIX_NUM + 1][2];//记录每个结点的坐标

public:
    void InitGraph();//生成这个图

    void DFSTraverse();//DFS遍历

    void DFS(int v);

    void BFSTraverse();//BFS遍历

    void BFS(int v);

    void PrintGraph();//打印图

    void DrawGraph();//画出这个图
};

void Graph::InitGraph() {
    cout << "请输入图的顶点数：";
    cin >> G.vexnum;
    cout << "请输入图的弧数量：";
    cin >> G.arcnum;
    //初始化每个顶点（第0个不用）
    for (int i = 1; i <= G.arcnum; i++) {
        G.vertices[i].data = i;
        G.vertices[i].firstarc = nullptr;
    }
    cout << "输入每一条弧连接的两个顶点" << endl;
    for (int i = 0; i < G.arcnum; i++) {
        int head, tail;//当前这条弧的两头
        cin >> head >> tail;
        ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = tail;
        p->nextarc = nullptr;
        //给这个弧连接到这个顶点上
        if (G.vertices[head].firstarc == nullptr) {
            G.vertices[head].firstarc = p;
        }
        else {
            ArcNode* q = G.vertices[head].firstarc;
            while (q->nextarc != nullptr) {
                q = q->nextarc;
            }
            q->nextarc = p;
        }
        //头尾互换一下
        ArcNode* t = (ArcNode*)malloc(sizeof(ArcNode));
        t->adjvex = head;
        t->nextarc = nullptr;
        //给这个弧连接到这个顶点上
        if (G.vertices[tail].firstarc == nullptr) {
            G.vertices[tail].firstarc = t;
        }
        else {
            ArcNode* q = G.vertices[tail].firstarc;
            while (q->nextarc != nullptr) {
                q = q->nextarc;
            }
            q->nextarc = t;
        }
    }
}

void Graph::PrintGraph() {
    for (int i = 1; i <= G.vexnum; i++) {
        cout << G.vertices[i].data << ": ";
        for (ArcNode* p = G.vertices[i].firstarc; p; p = p->nextarc) {
            cout << i << "-" << p->adjvex << " ";
        }
        cout << endl;
    }
}

void Graph::DFSTraverse() {
    //初始化一下visited数组
    for (int i = 1; i <= G.vexnum; i++) {
        visited[i] = 0;
    }
    pos[1][0] = 0;
    pos[1][1] = 0;
    int start;
    cout << "DFS遍历起点为：";
    cin >> start;
    DFS(start);
    cout << endl;
}

void Graph::DFS(int start) {
    visited[start] = 1;
    cout << start << " ";
    int x = pos[start][1];
    for (ArcNode* p = G.vertices[start].firstarc; p != nullptr; p = p->nextarc) {
        if (visited[p->adjvex] == 0)
        {
            pos[p->adjvex][1] = x;
            x++;
            pos[p->adjvex][0] = pos[start][0] + 1;
            DFS(p->adjvex);
        }
    }
}

void Graph::BFSTraverse() {
    //初始化一下visited数组
    for (int i = 1; i <= G.vexnum; i++) {
        visited[i] = 0;
    }
    int start;
    cout << "请输入BFS遍历起点：";
    cin >> start;
    BFS(start);
}

void Graph::BFS(int start) {
    //使用队列（队列太麻烦写了就用个数组代替了）
    int queue[100];
    int front = 0;
    int back = 0;

    queue[back] = start;
    back++;
    visited[start] = 1;
    cout << start << " ";
    while (back > front) {//队列非空
        ArcNode* p = G.vertices[queue[front]].firstarc;
        while (p != nullptr) {
            if (visited[p->adjvex] == 0) {
                queue[back++] = p->adjvex;
                visited[p->adjvex] = 1;
                cout << p->adjvex << " ";
            }
            p = p->nextarc;
        }
        front++;//相当于出队
    }
}

void Graph::DrawGraph() {
    //  创建一个宽度为WINDOW_WIDTH、高度为WINDOW_HEIGHT的窗体，并用白色背景色刷新窗体。
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(WHITE);
    setlinecolor(BLACK);
    settextcolor(BLACK);
    cleardevice();
    

    //用dfs遍历得到的顺序画树
    for (int i = 1; i <= G.vexnum; i++) {
        setfillcolor(YELLOW);
        fillcircle(200+pos[i][0]*150, 200+pos[i][1]*150, 30);
        char nu = i+48;
        outtextxy(200 + pos[i][0] * 150, 200 + pos[i][1] * 150, nu);
        for (ArcNode* p = G.vertices[i].firstarc; p; p = p->nextarc) {
            line(200 + pos[i][0] * 150, 200 + pos[i][1] * 150, 200 + pos[p->adjvex][0] * 150, 200 + pos[p->adjvex][1] * 150);
        }
    }
    system("pause");
    closegraph();
}

int main() {
    Graph G;
    G.InitGraph();
    //G.PrintGraph();
    G.DFSTraverse();
    G.BFSTraverse();
    system("pause");
    G.DrawGraph();
    return 0;
}