#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
#define N 100//存放多项式最大数量

typedef struct LNode{
    float num;//系数
    int power;//指数
    struct LNode *next;
}LNode, *LinkList;//定义链表存储多项式

static LinkList p[N];//存储实际使用的多项式

LinkList CreateList(LinkList &L);//输入并创建多项式，带头结点
void PrintList(LinkList L);//遍历链表，有头结点,升序
LinkList ListAddition(LinkList P,LinkList Q,int key);//加法
LinkList ListSubtraction(LinkList P,LinkList Q,int key);//减法
float ListEvaluation(LinkList L,float num);//多项式求值
void DestroyList(LinkList &L);//销毁多项式
void ClearList(LinkList &L);//清空多项式
void InsertNode(LinkList &L, int power, float num);//插入新的结点
void DeleteNode(LinkList &L, int power);//删除指数为power的项
void ChangeNode(LinkList &L,int power,float cnum,int cpower);//修改指数为power项的系数和指数
void ListDifferential(LinkList L,int n);//对多项式进行n次微分
void Indefinite_Intergral(LinkList L);//对多项式进行不定积分
float Definite_Intergral(LinkList L,int a,int b);//对多项式从a积到b
LinkList Multiplication(LinkList L1,LinkList L2,int key);//两个多项式的乘法
LinkList PowerList(LinkList L,int n,int key);//L1的n次幂
LinkList DivisionLink(LinkList L1, LinkList L2,int key);//两个多项式除法
void ShowMenu();//菜单

int factorial(int n)//求n的阶乘
{
    if(n==0 || n==1)
    {
        return 1;
    }
    else if(n<0)
    {
        cout<<"无法计算"<<n<<"的阶乘"<<endl;
    }
    int num = 1;
    for(int i=2;i<=n;i++)
    {
        num*=i;
    }
    return num;
}

void ListSort(LinkList &L)//对链表进行排序（降序）冒泡排序
{
    int i,j;
    int tempp;
    float tempn;
    LNode *p,*q;
    q = L->next;
    p = q->next;
    while(q->next)
    {
        while(p)
        {
            if(q->power < p->power)//交换pq值
            {
                tempp = q->power;
                q->power = p->power;
                p->power = tempp;
                tempn = q->num;
                q->num = p->num;
                p->num = tempn;
                if(p->next!=NULL)
                {
                    p = p->next;
                }
                else{
                    break;
                }
            }
            
            else{
                p = p->next;
            }
        }
        q = q->next;
        p = q->next;
    }
    //再考虑若有两项指数相同，合成一项
    q = L->next;
    p = q->next;
    while(p)
    {
        if(q->power == p->power)//如果发现两项指数相同，则合成一项
        {
            L->num--;//项数-1
            q->num += p->num;//都加到q项
            q->next = p->next;//直接指向p下一个，绕过p
            delete(p);//销毁重复多余结点
            if(q->next == NULL)
            {
                return;
            }
            p=q->next;
        }
        q = q->next;
        p = p->next;//都往前一位        
    }

    
}

void AppendElement(LinkList &S,float num,int power)//在列表S末尾添加新节点
{
    S->num ++;//节点数加一
    LNode *p,*q;
    p = (LinkList)malloc(sizeof(LNode));
    p->num = num;
    p->power = power;
    p->next = NULL;

    q = S;
    while(q->next)
    {
        q = q->next;
    }
    q->next = p;
}

LinkList CreateList(LinkList &L){//输入并创建多项式，带头结点
    int n;//多项式项数
    cout<<"请输入多项式项数"<<endl;
    cin>>n;
    cout<<"请输入每一项系数和指数"<<endl;
    L = (LinkList)malloc(sizeof(LNode));
    L-> num = n;//存储项数
    L->power =0;
    L->next = NULL;
    int i;
    for( i = n ; i>0 ; --i)
    {
        LNode *p = (LinkList)malloc(sizeof(LNode));
        cout<<"请输入第"<<n-i+1<<"项系数和指数："<<endl;
        cin>>p->num>>p->power;
        p->next = L->next;
        L->next = p;
    }
    ListSort(L);//防止错误输入还是再排个序吧
    return L;//生成降序的多项式
}

void PrintList(LinkList L){//遍历链表，有头结点,升序
    LNode *s;
    if(L->num == 0 || L == NULL)
    {
        cout<<"该多项式为0"<<endl;
        exit;
    }
    cout<<"该多项式项数为"<<L->num<<endl;//输出项数
    s=L->next;
    cout<<s->num<<"x^"<<s->power<<" ";//先输出一项为了好看
    s = s->next;
    while (s!=NULL) {
        if(s->num != 0)
        {
            cout<<"+"<<s->num<<"x^"<<s->power<<" ";
        }
        s=s->next;
    }
    cout<<endl;
}

LinkList ListAddition(LinkList P,LinkList Q,int key)//加法
{
    LinkList S;//加法结果
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    LNode *p,*q;//用于遍历P和Q
    p = P->next;
    q = Q->next;
    int num=0;//记录项数
    while(p && q)//都非空
    {
        if(p->power > q->power)//p比q高次
        {
            AppendElement(S,p->num,p->power);
            p=p->next;
        }
        else if(p->power < q->power)//q比p高次
        {
            AppendElement(S,q->num,q->power);
            q = q->next;
        }
        else//同次
        {
            if((p->num + q->num) == 0)//如果出现为0
            {
                num--;
            }
            else{
                AppendElement(S,(p->num + q->num),p->power);
            }
            p = p->next;
            q = q->next;
        }
        num++;
    }
    //如果P或Q遍历到头，未到头的剩下的都给S
    while(p)
    {
        AppendElement(S,p->num,p->power);
        p=p->next;
        num++;
    }
    while(q)
    {
       AppendElement(S,q->num,q->power);
        q=q->next;
        num++;
    }
    S->num = num;
    ListSort(S);
    if(key == 1)
    {
        PrintList(S);  
    }
    return S;
    
}

LinkList ListSubtraction(LinkList P,LinkList Q,int key)//减法
{
    LinkList S;//减法结果
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    LNode *p,*q;//用于遍历P和Q
    p = P->next;
    q = Q->next;
    int num=0;//记录项数
    while(p && q)//都非空
    {
        if(p->power > q->power)//p比q高次
        {
            AppendElement(S,p->num,p->power);
            p=p->next;
        }
        else if(p->power < q->power)//q比p高次
        {
            AppendElement(S,q->num,q->power);
            q = q->next;
        }
        else//同次
        {
            if((p->num - q->num) == 0)//如果出现为0
            {
                num--;
            }
            else{
                AppendElement(S,(p->num - q->num),p->power);
            }
            p = p->next;
            q = q->next;
        }
        num++;
    }
    //如果P或Q遍历到头，未到头的剩下的都给S
    while(p)
    {
        AppendElement(S,p->num,p->power);
        p=p->next;
        num++;
    }
    while(q)
    {
       AppendElement(S,-q->num,q->power);
        q=q->next;
        num++;
    }
    S->num = num;
    ListSort(S);
    if(key == 1)
    {
        PrintList(S);
    }
    return S; 
}

float ListEvaluation(LinkList L,float num)//多项式求值
{
    LNode *p;//遍历链表
    p = L->next;
    float sum = 0;//求值存入sum
    while(p)
    {
        float data=1;//存储num^power次幂
        for(int i=0;i<p->power;i++)
        {
            data *= num;
        }
        data *= p->num;
        sum += data;
        p = p->next;
    }
    return sum;
}

void DestroyList(LinkList &L)//销毁多项式
{
    LNode *p;//用于遍历L
    if(L == NULL)//已为空表
    {
        return;
    }
    while(L)
    {
        p = L->next;
        delete(L);//以此删除头结点
        L = p;
    }
}

void ClearList(LinkList &L)//清空多项式
{
    LNode *p;//遍历L
    p = L->next;
    L->num = 0;//项数改成0
    while(p)
    {
        p->num = 0;
        p->power = 0;
        p = p->next;
    }
}

void InsertNode(LinkList &L, int power, float num)//插入新的结点
{
    AppendElement(L, num, power);
    ListSort(L);
}

void DeleteNode(LinkList &L, int power)//删除指数为power的项
{
    LNode *p=L;//用于遍历链表
    LNode *q;
    while(p->next)
    {
        if(p->next->power == power)//找到对应结点
        {
            q = p->next;
            p->next = q->next;//直接指向下一个结点
            delete(q);//删除这个结点
            L->num--;//项数-1
            return;
        }
        p = p->next;
    }
    if(!(p->next))
    {
        cout<<"未找到该项"<<endl;
    }
    return;
}

void ChangeNode(LinkList &L,int power,float cnum,int cpower)//修改指数为power项的系数和指数，改为cpower和cnum
{
    LNode *p=L;//用于遍历链表
    LNode *q;
    while(p->next)
    {
        if(p->next->power == power)//找到对应结点
        {
            p->next->power = cpower;//修改数据
            p->next->num = cnum;
            ListSort(L);//防止指数改变导致不为降序，重新排列一遍
            return;
        }
        p = p->next;
    }
    if(!(p->next))
    {
        cout<<"未找到该项"<<endl;
    }
    return;
}

void ListDifferential(LinkList L,int n)//对多项式进行n次微分
{
    if(n<0)
    {
        cout<<"建议重修数学分析B1"<<endl;
        return;
    }
    LNode *p = L->next;//用于遍历链表
    LinkList S;//结果多项式
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    while(p)
    {
        int power = p->power - n;
        float num = p->num;
        for(int i=0;i<n;i++)
        {
            num *= (p->power-i);//计算微分后的系数
        }
        AppendElement(S,num,power);
        p = p->next;
    }
    ListSort(S);
    PrintList(S);
}

void Indefinite_Intergral(LinkList L)//对多项式进行不定积分
{
    LNode *p=L->next;//遍历链表L
    int power=p->power;
    float num;//用于存储每一项不定积分后的系数和指数
    //还是先处理第一项为了打印出来整齐好看
    if(power != -1)//考虑到1/x积分为lnx
    {
        power = p->power+1;
        num = (p->num / (p->power + 1));
        cout<<num<<"x^"<<power<<" ";
    }
    else{//积分a/x
        num = p->num;
        cout<<num<<"lnx"<<" ";
    }
    p=p->next;
    while(p)
    {
        if(p->power != -1)//考虑到1/x积分为lnx
        {
            power = p->power+1;
            num = (p->num / (p->power + 1));
            cout<<"+"<<num<<"x^"<<power<<" ";
        }
        else{//积分a/x
            num = p->num;
            cout<<"+"<<num<<"lnx"<<" ";
        }
        p=p->next;
    }
    cout<<endl;
}

float Definite_Intergral(LinkList L,int a,int b)//对多项式从a积到b
{
    LNode *p=L->next;//遍历链表L
    int power;
    float num;//用于存储每一项不定积分后的系数和指数
    float value=0;//最后积分总和
    //还是先处理第一项为了打印出来整齐好看
    while(p)
    {
        if(p->power != -1)//考虑到1/x积分为lnx
        {
            power = p->power+1;
            num = (p->num / (p->power + 1));
            value += num*(pow(b,power)-pow(a,power));
        }
        else{//积分a/x
            num = p->num;
            if(a==0||b==0)
            {
                cout<<"出现ln0错误"<<endl;
                exit;
            }
            value += num*(log(b)-log(a));//牛顿——莱布尼茨公式
        }
        p=p->next;
    }
    cout<<value<<endl;
    return value;
}

LinkList Multiplication(LinkList L1,LinkList L2,int key)//两个多项式的乘法，同时返回生成的多项式,key表示是否给结果打印出来
{
    //整体思路类似加法
    LinkList S;//乘法结果
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    LNode *p,*q,*s;//pq用于遍历L1和L2，s用于存储生成的结点
    p = L1->next;
    
    //思路为L1的每一项依次乘L2的每一项。最后生成的新表一起ListSort处理。
    while(p)//遍历L1每一项
    {
        q = L2->next;
        while(q)//遍历L2每一项
        {
            AppendElement(S,p->num*q->num,p->power+q->power);
            q = q->next;
        }
        p = p->next;
    }
    ListSort(S);
    if(key == 1)
    {
        PrintList(S);
    }
    return S;
}

LinkList PowerList(LinkList L,int n,int key)//L1的n次幂
{
    LinkList S;//结果
    S = (LinkList)malloc(sizeof(LNode));
    S = L;
    for(int i=0;i<n-1;i++)//n-1次累乘
    {
        S = Multiplication(S, L, 0);//0为不打印每次的乘积
    }
    if(key == 1)
    {
        PrintList(S);
    }
    return S;
}

LinkList DivisionLink(LinkList L1, LinkList L2,int key)//两个多项式除法,L1/L2
{
    LinkList L[3];//生成两个列表L[1]表示商，L[2]表示余数
    L[1] = (LinkList)malloc(sizeof(LNode));
    L[2] = (LinkList)malloc(sizeof(LNode));
    L[1]->next = NULL;L[2]->next = NULL;
    while(L1->next->power >= L2->next->power)//一项一项除
    {
        LinkList T;//存储每一次除法得到的一项商
        T = (LinkList)malloc(sizeof(LNode));
        T->next = NULL;
        InsertNode(L[1],(L1->next->power)-(L2->next->power),L1->next->num/L2->next->num);//多一项的商
        InsertNode(T,(L1->next->power)-(L2->next->power),L1->next->num/L2->next->num);
        L1 = ListSubtraction(L1,Multiplication(L2,T,0),0);//L1-TL2继续除
    }
    if(L1->next->power < L2->next->power)//剩下的全是余数
    {
        //最后剩的L1就是余数
        L[2] = L1;
    }
    ListSort(L[1]);
    ListSort(L[2]);
    if(key == 1)
    {
        cout<<"商为："<<endl;
        PrintList(L[1]);
        cout<<"余数为："<<endl;
        PrintList(L[2]);
    }
    return *L;
}

void ShowMenu()//菜单
{
    int key,i,j,k,power;
    float num,num1;
    cout<<"多项式运算器"<<endl;
    cout<<"1.创建多项式"<<endl;
    cout<<"2.输出多项式"<<endl;
    cout<<"3.多项式求和"<<endl;
    cout<<"4.多项式求差"<<endl;
    cout<<"5.多项式求值"<<endl;
    cout<<"6.多项式销毁"<<endl;
    cout<<"7.多项式清空"<<endl;
    cout<<"8.多项式修改"<<endl;
    cout<<"9.多项式微分"<<endl;
    cout<<"10.多项式不定积分"<<endl;
    cout<<"11.多项式定积分"<<endl;
    cout<<"12.多项式乘法"<<endl;
    cout<<"13.多项式乘方"<<endl;
    cout<<"14.多项式除法"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入对应操作序号"<<endl;
    cin>>key;
    if(key<0||key>13)
    {
        cout<<"食不食油饼"<<endl;
    }
    switch(key)
    {
        case 1:
            cout<<"赋值给第i个多项式:"<<endl;
            cin>>i;
            p[i] = CreateList(p[i]);
            break;

        case 2:
            cout<<"输出第i个多项式："<<endl;
            cin>>i;
            PrintList(p[i]);
            break;

        case 3:
            cout<<"第i和j个多项式求和："<<endl;
            cin>>i;
            cin>>j;
            ListAddition(p[i],p[j],1);
            cout<<"结果赋值给:(0即为不赋值)：";
            cin>>k;
            p[k] = ListAddition(p[i],p[j],0);
            break;

        case 4:
            cout<<"第i和j个多项式求差："<<endl;
            cin>>i;
            cin>>j;
            ListSubtraction(p[i],p[j],1);
            cout<<"结果赋值给:(0即为不赋值)：";
            cin>>k;
            p[k] = ListSubtraction(p[i],p[j],0);
            break;

        case 5:
            cout<<"第i个多项式赋值num:";
            cin>>i>>num;
            cout<<ListEvaluation(p[i],num);
            break;

        case 6:
            cout<<"销毁：";
            cin>>i;
            DestroyList(p[i]);
            break;

        case 7:
            cout<<"清空：";
            cin>>i;
            ClearList(p[i]);
            break;

        case 8:
            cout<<"修改："<<endl;
            cin>>i;
            PrintList(p[i]);
            cout<<"1.插入新节点  2.删除已有结点  3.修改已有结点  0.退出"<<endl;
            cin>>j;
        switch(j){
            case 1:
                cout<<"系数和指数：";
                cin>>num>>power;
                InsertNode(p[i],power,num);
                break;

            case 2:
                cout<<"删除项指数：";
                cin>>power;
                DeleteNode(p[i],power);
                break;

            case 3:
                cout<<"修改修改指数为  项的系数和指数，改为  和  ：";
                cin>>j>>num>>power;
                ChangeNode(p[i],j,num,power);
                break;
            }
            break;

        case 9:
            cout<<"微分第 个多项式 次:"<<endl;
            cin>>i>>j;
            ListDifferential(p[i],j);
            break;

        case 10:
            cout<<"积分第 个多项式:"<<endl;
            cin>>i;
            Indefinite_Intergral(p[i]);
            break;

        case 11:
            cout<<"积分第 个多项式从  到  :"<<endl;
            cin>>i>>num>>num1;
            Definite_Intergral(p[i],num,num1);
            break;

        case 12:
            cout<<"第 个多项式×第 个多项式";
            cin>>i>>j;
            Multiplication(p[i],p[j],1);
            break;

        case 13:
            cout<<"第  个多项式^  次幂";
            cin>>i>>power;
            PowerList(p[i],power,1);
            break;

        case 14:
            cout<<"第  个多项式÷第  个多项式";
            cin>>i>>j;
            DivisionLink(p[i],p[j],1);
            break;

        case 0:
            exit ;
    }
    system("pause");
    system("cls");
}

int main()
{
/* CreateList(p[1]);
    CreateList(p[2]);
    //InsertNode(p[1],3,2.3);
    //ChangeNode(p[1],3,-0.2,6);
    PrintList(p[1]);
    PrintList(p[2]);
    //ListDifferential(p[1],2);
    //Indefinite_Intergral(p[1]);
    //cout<<Definite_Intergral(p[1],2,3);
    //Multiplication(p[1],p[2],1);
    //PowerList(p[1],3,1);
    DivisionLink(p[1],p[2],1);*/
   while(1)
   {
    ShowMenu();
   }
}