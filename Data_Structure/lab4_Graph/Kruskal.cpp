#include<iostream>
using namespace std;

//ʹ��ͼ���ڽ�����ʽ�洢
#define MAX_VERTIX_NUM 20//���������
#define MAX_ARCS_NUM 200//��໡������
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
    struct{
        int start;
        int end;
        int weight;
    }arcs[MAX_ARCS_NUM];        //��¼���л�����ͷ��Ȩ��
    int nodes[MAX_VERTIX_NUM];  //��¼���ж������ڵ���ͨ����

public:
    void InitGraph();//�������ͼ

    void PrintGraph();//��ӡͼ

    void MinSpanTree_Kruskal();//��kruskal�㷨������С������

    void sort();//�����л���Ȩ�شӵ͵�������

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
        //��ʼ��arcs����
        arcs[i+1] = {head,tail,length};
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

void Graph::MinSpanTree_Kruskal(){//��kruskal�㷨������С������
    //�Ƚ����еĻ�����
    sort();

    //��ʼ��������ͨ��������
    for(int t=1;t<=G.vexnum;t++){
        nodes[t] = t;
    }
    
    int sum = 0;
    int pos = 1;
    for(int i=1;i<G.vexnum;i++){//һ����vexnum-1����
        //�ҵ���һ�����������ͨ������ͬ�Ļ�
        while(nodes[arcs[pos].start] == nodes[arcs[pos].end]){
            pos++;
        }
        //ѡ�������
        sum += arcs[pos].weight;
        //���������������ͨ������ͬ
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

void Graph::sort(){//��ð������
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