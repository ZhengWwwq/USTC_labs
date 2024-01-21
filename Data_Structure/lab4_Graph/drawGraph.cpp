#include<iostream>
#include<graphics.h>
#include<stdlib.h>
using namespace std;

//��ͼ�õ�������
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//ʹ��ͼ���ڽ�����ʽ�洢
#define MAX_VERTIX_NUM 20//���������
int visited[MAX_VERTIX_NUM];    //visited�������ڱ���ʱ�ж��Ƿ������
typedef struct ArcNode {
    int adjvex;                 //�û���ָ��Ķ����λ��
    struct ArcNode* nextarc;    //ָ����һ������ָ��
}ArcNode;
typedef struct VNode {
    int data;                   //���������
    ArcNode* firstarc;          //����ĵ�һ����
}VNode, AdjList[MAX_VERTIX_NUM + 1];
typedef struct ALGraph {
    AdjList vertices;
    int vexnum, arcnum;          //���������ͻ�������
}ALGraph;

class Graph {
private:
    ALGraph G;

    int pos[MAX_VERTIX_NUM + 1][2];//��¼ÿ����������

public:
    void InitGraph();//�������ͼ

    void DFSTraverse();//DFS����

    void DFS(int v);

    void BFSTraverse();//BFS����

    void BFS(int v);

    void PrintGraph();//��ӡͼ

    void DrawGraph();//�������ͼ
};

void Graph::InitGraph() {
    cout << "������ͼ�Ķ�������";
    cin >> G.vexnum;
    cout << "������ͼ�Ļ�������";
    cin >> G.arcnum;
    //��ʼ��ÿ�����㣨��0�����ã�
    for (int i = 1; i <= G.arcnum; i++) {
        G.vertices[i].data = i;
        G.vertices[i].firstarc = nullptr;
    }
    cout << "����ÿһ�������ӵ���������" << endl;
    for (int i = 0; i < G.arcnum; i++) {
        int head, tail;//��ǰ����������ͷ
        cin >> head >> tail;
        ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = tail;
        p->nextarc = nullptr;
        //����������ӵ����������
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
        //ͷβ����һ��
        ArcNode* t = (ArcNode*)malloc(sizeof(ArcNode));
        t->adjvex = head;
        t->nextarc = nullptr;
        //����������ӵ����������
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
    //��ʼ��һ��visited����
    for (int i = 1; i <= G.vexnum; i++) {
        visited[i] = 0;
    }
    pos[1][0] = 0;
    pos[1][1] = 0;
    int start;
    cout << "DFS�������Ϊ��";
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
    //��ʼ��һ��visited����
    for (int i = 1; i <= G.vexnum; i++) {
        visited[i] = 0;
    }
    int start;
    cout << "������BFS������㣺";
    cin >> start;
    BFS(start);
}

void Graph::BFS(int start) {
    //ʹ�ö��У�����̫�鷳д�˾��ø���������ˣ�
    int queue[100];
    int front = 0;
    int back = 0;

    queue[back] = start;
    back++;
    visited[start] = 1;
    cout << start << " ";
    while (back > front) {//���зǿ�
        ArcNode* p = G.vertices[queue[front]].firstarc;
        while (p != nullptr) {
            if (visited[p->adjvex] == 0) {
                queue[back++] = p->adjvex;
                visited[p->adjvex] = 1;
                cout << p->adjvex << " ";
            }
            p = p->nextarc;
        }
        front++;//�൱�ڳ���
    }
}

void Graph::DrawGraph() {
    //  ����һ�����ΪWINDOW_WIDTH���߶�ΪWINDOW_HEIGHT�Ĵ��壬���ð�ɫ����ɫˢ�´��塣
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    setbkcolor(WHITE);
    setlinecolor(BLACK);
    settextcolor(BLACK);
    cleardevice();
    

    //��dfs�����õ���˳����
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