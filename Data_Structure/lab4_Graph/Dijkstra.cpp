#include<iostream>
using namespace std;

//ʹ��ͼ���ڽ�����ʽ�洢
#define MAX_VERTIX_NUM 20       //���������
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

public:
    void InitGraph();//�������ͼ

    void PrintGraph();//��ӡͼ

    void ShortestPath_DIJ();//��Dijkstra�㷨����㵽�յ����󳤶�
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
        int head,tail,length;//��ǰ����������ͷ
        cin>>head>>tail>>length;
        ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = tail;
        p->weight = length;
        p->nextarc = nullptr;
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
    }
}

void Graph::ShortestPath_DIJ(){
    int D[G.vexnum+1];
    int S[G.vexnum+1];//���ڱ�ʾ�Ƿ����Ѿ�ѡ��������
    for(int k = 1;k<=G.vexnum;k++){
        D[k] = 0;S[k] = 0;
    }
    int begin,end;
    cout<<"�����������յ㣺";
    cin>>begin>>end;
    S[begin] = 1;           //�������S��
    D[begin] = 0;
    //�Ȱ����Ķ�Ӧ�Ļ�����
    for(ArcNode *p = G.vertices[begin].firstarc;p;p = p->nextarc){
        D[p->adjvex] = p->weight;
    }
    //һ��ѭ��vexnum-1��
    for(int i=1;i<G.vexnum;i++){
        int min;        //�ҵ�V-S������·����̵�
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
        S[min] = 1;//���������S��
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