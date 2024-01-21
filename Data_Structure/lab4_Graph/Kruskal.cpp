#include<iostream>
using namespace std;

//使用图的邻接链表方式存储
#define MAX_VERTIX_NUM 20//最多结点数量
#define MAX_ARCS_NUM 200//最多弧的数量
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
    struct{
        int start;
        int end;
        int weight;
    }arcs[MAX_ARCS_NUM];        //记录所有弧的两头和权重
    int nodes[MAX_VERTIX_NUM];  //记录所有顶点所在的联通分量

public:
    void InitGraph();//生成这个图

    void PrintGraph();//打印图

    void MinSpanTree_Kruskal();//用kruskal算法构造最小生成树

    void sort();//将所有弧按权重从低到高排序

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
        //初始化arcs数组
        arcs[i+1] = {head,tail,length};
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

void Graph::MinSpanTree_Kruskal(){//用kruskal算法构造最小生成树
    //先将所有的弧排序
    sort();

    //初始化所有联通分量数组
    for(int t=1;t<=G.vexnum;t++){
        nodes[t] = t;
    }
    
    int sum = 0;
    int pos = 1;
    for(int i=1;i<G.vexnum;i++){//一共找vexnum-1个弧
        //找到第一个两个结点联通分量不同的弧
        while(nodes[arcs[pos].start] == nodes[arcs[pos].end]){
            pos++;
        }
        //选中这个弧
        sum += arcs[pos].weight;
        //这个弧两端所属联通分量相同
        for(int j = 1;j<=G.arcnum;j++){
            if(nodes[j]==arcs[pos].end){
                nodes[j] = nodes[arcs[pos].start];
            }
        }
        for(int m = 1;m<=G.vexnum;m++){
            cout<<nodes[m]<<" ";
        }
        cout<<endl;
    }
    cout<<sum;
}

void Graph::sort(){//用冒泡排序
    for(int i=1;i<G.arcnum;i++){
        for(int j=1;j<G.arcnum-i;j++){
            if(arcs[j].weight>arcs[j+1].weight){
                int w = arcs[j].weight;
                arcs[j].weight = arcs[j+1].weight;
                arcs[j+1].weight = w;

                int s = arcs[j].start;
                arcs[j].start = arcs[j+1].start;
                arcs[j+1].start = s;

                int e = arcs[j].end;
                arcs[j].end = arcs[j+1].end;
                arcs[j+1].end = e;
            }
        }
    }
}

int main(){
    Graph G;
    G.InitGraph();
    //G.PrintGraph();
    G.MinSpanTree_Kruskal();
    return 0;
}