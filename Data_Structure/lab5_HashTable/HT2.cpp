#include<iostream>
#include<stdlib.h>
using namespace std;

//������
typedef struct LinkNode{
    int val;
    LinkNode *next;
}LinkNode, *LinkList;

class HashTable{
private:
    LinkList *elem;         //��ϣ�������
    int* depth;             //ÿ����������
    int count;              //��ǰ����Ԫ�ظ���
    int size;               //��ϣ��ĳ���
    int *success;           //�ɹ����Ҵ���
    int *unsuccess;         //ʧ�ܲ��Ҵ���
    int maxdepth;           //�������

public:
    void initHash();        //��ʼ����ϣ��

    int Hashing(int key);   //��ϣ����

    void PrintHash();       //��ӡ���

    float SuccessASL();      //���ҳɹ���ƽ�����ҳ���

    float UnsuccessASL();    //����ʧ�ܵ�ƽ�����ҳ���
};

void HashTable::initHash(){
    cout<<"������ؼ��ָ�����";
    cin>>count;
    cout<<"���������йؼ��֣�";
    //��nums������ʱ�洢��������
    int nums[count];
    for(int i=0;i<count;i++){
        cin>>nums[i];
    }
    cout<<"�������ϣ���ȣ�";
    cin>>size;

    //�����ϣ��
    //��ʼ�����еĹ�ϣ����ͳɹ�/ʧ�ܲ��Ҵ���
    maxdepth = 0;
    elem = (LinkList *)malloc(size*sizeof(LinkList));
    depth = (int*)malloc(sizeof(int)*size);
    success = (int*)malloc(size*sizeof(int));
    unsuccess = (int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++){
        elem[i] = nullptr;
        depth[i] = 0;
        success[i] = 0;
        unsuccess[i] = 1;
    }
    //ͨ������ַ����ÿ���ؼ��ִ����ϣ����
    for(int i=0;i<count;i++){
        LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
        p->val = nums[i];
        p->next = nullptr;
        if(elem[Hashing(nums[i])] == nullptr){
            elem[Hashing(nums[i])] = p;
        }
        else{
            LinkNode *q = elem[Hashing(nums[i])];
            //�ҵ���Ӧλ�õ�ĩ�ڵ�
            while(q->next!=nullptr){
                q = q->next;
            }
            q->next = p;  
        }
        depth[Hashing(nums[i])]++;
        if(depth[Hashing(nums[i])]>maxdepth){
            maxdepth = depth[Hashing(nums[i])];
        }
        success[Hashing(nums[i])]++;
        unsuccess[Hashing(nums[i])]++;
    }
}

int HashTable::Hashing(int key){
    //ͨ�������������õ��Ĺ�ϣ����
    return key%size;
}

float HashTable::SuccessASL(){
    float sum = 0;
    for(int i=0;i<size;i++){
        for(int j=1;j<=success[i];j++){
            sum+=j;
        }
    }
    return sum/count;
}

float HashTable::UnsuccessASL(){
    float sum = 0;
    int n = 0;
    for(int i=0;i<size;i++){
        sum+=unsuccess[i];
    }
    return sum/size;
}

void HashTable::PrintHash(){
    cout<<"��ϣ��ĵ�ַ��\t";
    for(int i=0;i<size;i++){
        cout<<i<<"\t";
    }
    cout<<endl;
    cout<<"���еĹؼ��֣�\t";
    for(int i=0;i<size;i++){
        if(elem[i]==nullptr){
            cout<<"-"<<"\t";
        }
        else{
            cout<<elem[i]->val<<"\t";
        }
    }
    cout<<endl;
    for(int d = 2;d<=maxdepth;d++){
        cout<<"\t\t";
        for(int j = 0;j<size;j++){
            if(depth[j]<d){
                cout<<"\t";
            }
            else{
                LinkNode *p = elem[j];
                for(int t = 1;t<d;t++){
                    p = p->next;
                }
                cout<<p->val<<"\t";
            }
        }
        cout<<endl;
    }
    cout<<"�ɹ����Ҵ�����\t";
    for(int i=0;i<size;i++){
        if(success[i]==0){
            cout<<0<<"\t";
        }
        else{
            cout<<1<<"\t";
        }
    }
    cout<<endl;
    for(int d = 2;d<=maxdepth;d++){
        cout<<"\t\t";
        for(int j = 0;j<size;j++){
            if(depth[j]<d){
                cout<<"\t";
            }
            else{
                cout<<d<<"\t";
            }
        }
        cout<<endl;
    }
    cout<<"ʧ�ܲ��Ҵ�����\t";
    for(int i=0;i<size;i++){
        cout<<unsuccess[i]<<"\t";
    }
    cout<<endl;
    cout<<"���ҳɹ���ƽ�����ҳ��ȣ�\t"<<SuccessASL()<<endl;
    cout<<"����ʧ�ܵ�ƽ�����ҳ��ȣ�\t"<<UnsuccessASL()<<endl;
}

int main(){
    while(1){
        HashTable HT1;
        HT1.initHash();
        HT1.PrintHash();
        system("pause");
    }
}