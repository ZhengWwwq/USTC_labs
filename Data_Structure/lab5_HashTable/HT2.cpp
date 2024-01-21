#include<iostream>
#include<stdlib.h>
using namespace std;

//链表定义
typedef struct LinkNode{
    int val;
    LinkNode *next;
}LinkNode, *LinkList;

class HashTable{
private:
    LinkList *elem;         //哈希表的内容
    int* depth;             //每个链表的深度
    int count;              //当前数据元素个数
    int size;               //哈希表的长度
    int *success;           //成功查找次数
    int *unsuccess;         //失败查找次数
    int maxdepth;           //最大的深度

public:
    void initHash();        //初始化哈希表

    int Hashing(int key);   //哈希函数

    void PrintHash();       //打印结果

    float SuccessASL();      //查找成功的平均查找长度

    float UnsuccessASL();    //查找失败的平均查找长度
};

void HashTable::initHash(){
    cout<<"请输入关键字个数：";
    cin>>count;
    cout<<"请输入所有关键字：";
    //用nums数组临时存储所有内容
    int nums[count];
    for(int i=0;i<count;i++){
        cin>>nums[i];
    }
    cout<<"请输入哈希表长度：";
    cin>>size;

    //构造哈希表
    //初始化所有的哈希表结点和成功/失败查找次数
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
    //通过链地址法将每个关键字存入哈希表中
    for(int i=0;i<count;i++){
        LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
        p->val = nums[i];
        p->next = nullptr;
        if(elem[Hashing(nums[i])] == nullptr){
            elem[Hashing(nums[i])] = p;
        }
        else{
            LinkNode *q = elem[Hashing(nums[i])];
            //找到对应位置的末节点
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
    //通过除留余数法得到的哈希函数
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
    cout<<"哈希表的地址：\t";
    for(int i=0;i<size;i++){
        cout<<i<<"\t";
    }
    cout<<endl;
    cout<<"表中的关键字：\t";
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
    cout<<"成功查找次数：\t";
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
    cout<<"失败查找次数：\t";
    for(int i=0;i<size;i++){
        cout<<unsuccess[i]<<"\t";
    }
    cout<<endl;
    cout<<"查找成功的平均查找长度：\t"<<SuccessASL()<<endl;
    cout<<"查找失败的平均查找长度：\t"<<UnsuccessASL()<<endl;
}

int main(){
    while(1){
        HashTable HT1;
        HT1.initHash();
        HT1.PrintHash();
        system("pause");
    }
}