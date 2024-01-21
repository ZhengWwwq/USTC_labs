#include<iostream>
using namespace std;

//使用图的邻接矩阵方式存储
#define MAX_VERTIX_NUM 20       //最多结点数量
int visited[MAX_VERTIX_NUM];    //visited数组用于遍历时判断是否遍历过

typedef struct {
    
}MGraph;

class Graph{
private:
    int vexes[MAX_VERTIX_NUM];   //顶点向量
    int ArcCell[MAX_VERTIX_NUM][MAX_VERTIX_NUM];    //邻接矩阵
    int vexnum,arcnum;           //图的当前顶点数和弧数
    int visited[MAX_VERTIX_NUM];

public:
    void InitGraph();//生成这个图

    void DFSTraverse();//DFS遍历

    void DFS(int v);

    void BFSTraverse();//BFS遍历

    void BFS(int v);

    void PrintGraph();//打印图
};

void Graph::InitGraph(){
    cout<<"请输入图的顶点数：";
    cin>>vexnum;
    cout<<"请输入图的弧数量：";
    cin>>arcnum;
    //初始化每个顶点（第0个不用）
    for(int i=1;i<=arcnum;i++){
        vexes[i] = i;
    }
    //初始化邻接矩阵
    for(int i=1;i<=vexnum;i++){
        for(int j=1;j<=vexnum;j++){
            ArcCell[i][j] = 0;
        }
    }
    cout<<"输入每一条弧连接的两个顶点"<<endl;
    for(int i=0;i<arcnum;i++){
        int head,tail;//当前这条弧的两头
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
    //初始化一下visited数组
    for(int i=1;i<=vexnum;i++){
        visited[i]=0;
    }
    int start;
    cout<<"DFS遍历起点为：";
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
    //初始化一下visited数组
    for(int i=1;i<=vexnum;i++){
        visited[i]=0;
    }
    int start;
    cout<<"请输入BFS遍历起点：";
    cin>>start;
    BFS(start);
}

void Graph::BFS(int start){
//使用队列（队列太麻烦写了就用个数组代替了）
    int queue[100];
    int front = 0;
    int back = 0;

    queue[back] = start;
    back++;
    visited[start] = 1;
    cout<<start<<" ";
    while(back>front){//队列非空
        for(int i=1;i<=vexnum;i++){
            if(ArcCell[front][i]>0 && visited[i]==0){
                queue[back++] = i;
                visited[i] = 1;
                cout<<i<<" ";
            }
        }
        front++;//相当于出队
    }
}

int main(){
    Graph G;
    G.InitGraph();
    G.DFSTraverse();
    G.BFSTraverse();
    return 0;
}