#include<iostream>
using namespace std;

//使用图的邻接链表方式存储
#define MAX_VERTIX_NUM 20//最多结点数量
int visited[MAX_VERTIX_NUM];    //visited数组用于遍历时判断是否遍历过
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
    //辅助结构体数组记录代价最小的边
    struct{
        int adjvex;
        int lowcost;
    }closeedge[MAX_VERTIX_NUM+1];

public:
    void InitGraph();//生成这个图

    void PrintGraph();//打印图

    void MinSpanTree_PRIM();//用prim算法生成最小生成树

    int min();//找到最小的弧
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
        int head,tail;//当前这条弧的两头
        int length;
        cin>>head>>tail>>length;
        ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = tail;
        p->nextarc = nullptr;
        p->weight = length;
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
        //头尾互换一下
        ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
        t->adjvex = head;
        t->nextarc = nullptr;
        t->weight = length;
        //给这个弧连接到这个顶点上
        if(G.vertices[tail].firstarc == nullptr){
            G.vertices[tail].firstarc = t;
        }
        else{
            ArcNode *q = G.vertices[tail].firstarc;
            while(q->nextarc != nullptr){
                q = q->nextarc;
            }
            q->nextarc = t;
        }
    }
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

void Graph::MinSpanTree_PRIM(){
    int sum = 0;
    //从第一个顶点开始
    //初始化辅助数组
    for(int i=1;i<=G.vexnum;i++){
        closeedge[i] = {0,0};
    }
    for(ArcNode *p = G.vertices[1].firstarc;p!=nullptr;p = p->nextarc){
        closeedge[p->adjvex] = {1,p->weight};
    }
    //一步步连这vexnum-1条弧
    for(int j = 2;j<=G.vexnum;j++){
        int k = min();

        sum += closeedge[k].lowcost;

        //更新辅助数组
        closeedge[k] = {0, 0};
        for(ArcNode *p = G.vertices[k].firstarc;p!=nullptr;p = p->nextarc){
            if(p->weight < closeedge[p->adjvex].lowcost){
                closeedge[p->adjvex] = {k,p->weight};
            }
        }
    }
    cout<<sum;
}

int Graph::min(){
    int pos;
    //定位第一个pos
    for(int i=1;i<=G.vexnum;i++){
        if(closeedge[i].lowcost != 0){
            pos = i;
            break;
        }
    }
    //找到最小的pos
    for(int j = pos+1;j<=G.vexnum;j++){
        if(closeedge[j].lowcost > 0 && closeedge[j].lowcost < closeedge[pos].lowcost){
            pos = j;
        }
    }
    return pos;
}

int main(){
    Graph G;
    G.InitGraph();
    //G.PrintGraph();
    G.MinSpanTree_PRIM();
    return 0;
}