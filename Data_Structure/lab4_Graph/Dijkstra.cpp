#include<iostream>
using namespace std;

//使用图的邻接链表方式存储
#define MAX_VERTIX_NUM 20       //最多结点数量
typedef struct ArcNode{
    int adjvex;                 //该弧所指向的顶点的位置
    int weight;                 //弧的权重
    struct ArcNode *nextarc;    //指向下一条弧的指针
}ArcNode;
typedef struct VNode{
    int data;                   //顶点的内容
    ArcNode *firstarc;          //顶点的第一条弧
}VNode,AdjList[MAX_VERTIX_NUM+1];
typedef struct ALGraph{
    AdjList vertices;
    int vexnum,arcnum;          //顶点数量和弧的数量
}ALGraph;

class Graph{
private:
    ALGraph G;

public:
    void InitGraph();//生成这个图

    void PrintGraph();//打印图

    void ShortestPath_DIJ();//用Dijkstra算法求起点到终点的最大长度
};

void Graph::InitGraph(){
    cout<<"请输入图的顶点数：";
    cin>>G.vexnum;
    cout<<"请输入图的弧数量：";
    cin>>G.arcnum;
    //初始化每个顶点（第0个不用）
    for(int i=1;i<=G.arcnum;i++){
        G.vertices[i].data = i;
        G.vertices[i].firstarc = nullptr;
    }
    cout<<"输入每一条弧连接的两个顶点和弧的长度"<<endl;
    for(int i=0;i<G.arcnum;i++){
        int head,tail,length;//当前这条弧的两头
        cin>>head>>tail>>length;
        ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = tail;
        p->weight = length;
        p->nextarc = nullptr;
        //给这个弧连接到这个顶点上
        if(G.vertices[head].firstarc == nullptr){
            G.vertices[head].firstarc = p;
        }
        else{
            ArcNode *q = G.vertices[head].firstarc;
            while(q->nextarc != nullptr){
                q = q->nextarc;
            }
            q->nextarc = p;
        }
    }
}

void Graph::ShortestPath_DIJ(){
    int D[G.vexnum+1];
    int S[G.vexnum+1];//用于表示是否在已经选过的里面
    for(int k = 1;k<=G.vexnum;k++){
        D[k] = 0;S[k] = 0;
    }
    int begin,end;
    cout<<"请输入起点和终点：";
    cin>>begin>>end;
    S[begin] = 1;           //起点属于S集
    D[begin] = 0;
    //先把起点的对应的弧连上
    for(ArcNode *p = G.vertices[begin].firstarc;p;p = p->nextarc){
        D[p->adjvex] = p->weight;
    }
    //一共循环vexnum-1次
    for(int i=1;i<G.vexnum;i++){
        int min;        //找到V-S集合中路径最短的
        for(int j = 1;j<=G.vexnum;j++){
            if(S[j]==0 && D[j]>0){
                min = j;
                break;
            }
        }
        for(int t = min+1;t<=G.vexnum;t++){
            if(S[t] == 0 && D[t] < D[min] && D[t]>0){
                min = t;
            }
        }
        S[min] = 1;//这个点属于S了
        for(ArcNode *p = G.vertices[min].firstarc;p != nullptr;p = p->nextarc){
            if(D[p->adjvex] == 0 || D[min] + p->weight < D[p->adjvex]){
                D[p->adjvex] = D[min]+p->weight;
            }
        }
    }
    cout<<D[end];
}

void Graph::PrintGraph(){
    for(int i=1;i<=G.vexnum;i++){
        cout<<G.vertices[i].data<<": ";
        for(ArcNode *p = G.vertices[i].firstarc;p;p=p->nextarc){
            cout<<i<<"-"<<p->adjvex<<" "<<p->weight<<" ";
        }
        cout<<endl;
    }
}


int main(){
    Graph G;
    G.InitGraph();
    G.PrintGraph();
    G.ShortestPath_DIJ();
    return 0;
}