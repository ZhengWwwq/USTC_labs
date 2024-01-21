#include<iostream>
using namespace std;

//ʹ��ͼ���ڽӾ���ʽ�洢
#define MAX_VERTIX_NUM 20       //���������
int visited[MAX_VERTIX_NUM];    //visited�������ڱ���ʱ�ж��Ƿ������

typedef struct {
    
}MGraph;

class Graph{
private:
    int vexes[MAX_VERTIX_NUM];   //��������
    int ArcCell[MAX_VERTIX_NUM][MAX_VERTIX_NUM];    //�ڽӾ���
    int vexnum,arcnum;           //ͼ�ĵ�ǰ�������ͻ���
    int visited[MAX_VERTIX_NUM];

public:
    void InitGraph();//�������ͼ

    void DFSTraverse();//DFS����

    void DFS(int v);

    void BFSTraverse();//BFS����

    void BFS(int v);

    void PrintGraph();//��ӡͼ
};

void Graph::InitGraph(){
    cout<<"������ͼ�Ķ�������";
    cin>>vexnum;
    cout<<"������ͼ�Ļ�������";
    cin>>arcnum;
    //��ʼ��ÿ�����㣨��0�����ã�
    for(int i=1;i<=arcnum;i++){
        vexes[i] = i;
    }
    //��ʼ���ڽӾ���
    for(int i=1;i<=vexnum;i++){
        for(int j=1;j<=vexnum;j++){
            ArcCell[i][j] = 0;
        }
    }
    cout<<"����ÿһ�������ӵ���������"<<endl;
    for(int i=0;i<arcnum;i++){
        int head,tail;//��ǰ����������ͷ
        cin>>head>>tail;
        ArcCell[head][tail] = 1;
        ArcCell[tail][head] = 1;
    }
}

void Graph::PrintGraph(){
    for(int i=1;i<=vexnum;i++){
        cout<<vexes<<": ";
        for(int j = 1 ;j<=vexnum;j++){
            if(ArcCell[i][j]>0)
                {
                    cout<<i<<"-"<<j<<" ";
                }
        }
        cout<<endl;
    }
}

void Graph::DFSTraverse(){
    //��ʼ��һ��visited����
    for(int i=1;i<=vexnum;i++){
        visited[i]=0;
    }
    int start;
    cout<<"DFS�������Ϊ��";
    cin>>start;
    DFS(start);
    cout<<endl;
}

void Graph::DFS(int start){
    visited[start] = 1;
    cout<<start<<" ";
    for(int i = 1;i<=vexnum;i++){
        if(ArcCell[start][i]>0&&visited[i]==0){
            DFS(i);
        }
    }
}

void Graph::BFSTraverse(){
    //��ʼ��һ��visited����
    for(int i=1;i<=vexnum;i++){
        visited[i]=0;
    }
    int start;
    cout<<"������BFS������㣺";
    cin>>start;
    BFS(start);
}

void Graph::BFS(int start){
//ʹ�ö��У�����̫�鷳д�˾��ø���������ˣ�
    int queue[100];
    int front = 0;
    int back = 0;

    queue[back] = start;
    back++;
    visited[start] = 1;
    cout<<start<<" ";
    while(back>front){//���зǿ�
        for(int i=1;i<=vexnum;i++){
            if(ArcCell[front][i]>0 && visited[i]==0){
                queue[back++] = i;
                visited[i] = 1;
                cout<<i<<" ";
            }
        }
        front++;//�൱�ڳ���
    }
}

int main(){
    Graph G;
    G.InitGraph();
    G.DFSTraverse();
    G.BFSTraverse();
    return 0;
}