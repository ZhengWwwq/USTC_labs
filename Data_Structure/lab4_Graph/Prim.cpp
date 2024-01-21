#include<iostream>
using namespace std;

//ʹ��ͼ���ڽ�����ʽ�洢
#define MAX_VERTIX_NUM 20//���������
int visited[MAX_VERTIX_NUM];    //visited�������ڱ���ʱ�ж��Ƿ������
typedef struct ArcNode{
    int adjvex;                 //�û���ָ��Ķ����λ��
    int weight;                 //����Ȩ��
    struct ArcNode *nextarc;    //ָ����һ������ָ��
}ArcNode;
typedef struct VNode{
    int data;                   //���������
    ArcNode *firstarc;          //����ĵ�һ����
}VNode,AdjList[MAX_VERTIX_NUM+1];
typedef struct ALGraph{
    AdjList vertices;
    int vexnum,arcnum;          //���������ͻ�������
}ALGraph;

class Graph{
private:
    ALGraph G;
    //�����ṹ�������¼������С�ı�
    struct{
        int adjvex;
        int lowcost;
    }closeedge[MAX_VERTIX_NUM+1];

public:
    void InitGraph();//�������ͼ

    void PrintGraph();//��ӡͼ

    void MinSpanTree_PRIM();//��prim�㷨������С������

    int min();//�ҵ���С�Ļ�
};

void Graph::InitGraph(){
    cout<<"������ͼ�Ķ�������";
    cin>>G.vexnum;
    cout<<"������ͼ�Ļ�������";
    cin>>G.arcnum;
    //��ʼ��ÿ�����㣨��0�����ã�
    for(int i=1;i<=G.arcnum;i++){
        G.vertices[i].data = i;
        G.vertices[i].firstarc = nullptr;
    }
    cout<<"����ÿһ�������ӵ���������ͻ��ĳ���"<<endl;
    for(int i=0;i<G.arcnum;i++){
        int head,tail;//��ǰ����������ͷ
        int length;
        cin>>head>>tail>>length;
        ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = tail;
        p->nextarc = nullptr;
        p->weight = length;
        //����������ӵ����������
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
        //ͷβ����һ��
        ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
        t->adjvex = head;
        t->nextarc = nullptr;
        t->weight = length;
        //����������ӵ����������
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
    //�ӵ�һ�����㿪ʼ
    //��ʼ����������
    for(int i=1;i<=G.vexnum;i++){
        closeedge[i] = {0,0};
    }
    for(ArcNode *p = G.vertices[1].firstarc;p!=nullptr;p = p->nextarc){
        closeedge[p->adjvex] = {1,p->weight};
    }
    //һ��������vexnum-1����
    for(int j = 2;j<=G.vexnum;j++){
        int k = min();

        sum += closeedge[k].lowcost;

        //���¸�������
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
    //��λ��һ��pos
    for(int i=1;i<=G.vexnum;i++){
        if(closeedge[i].lowcost != 0){
            pos = i;
            break;
        }
    }
    //�ҵ���С��pos
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