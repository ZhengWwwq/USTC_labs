#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
#define N 100//��Ŷ���ʽ�������

typedef struct LNode{
    float num;//ϵ��
    int power;//ָ��
    struct LNode *next;
}LNode, *LinkList;//��������洢����ʽ

static LinkList p[N];//�洢ʵ��ʹ�õĶ���ʽ

LinkList CreateList(LinkList &L);//���벢��������ʽ����ͷ���
void PrintList(LinkList L);//����������ͷ���,����
LinkList ListAddition(LinkList P,LinkList Q,int key);//�ӷ�
LinkList ListSubtraction(LinkList P,LinkList Q,int key);//����
float ListEvaluation(LinkList L,float num);//����ʽ��ֵ
void DestroyList(LinkList &L);//���ٶ���ʽ
void ClearList(LinkList &L);//��ն���ʽ
void InsertNode(LinkList &L, int power, float num);//�����µĽ��
void DeleteNode(LinkList &L, int power);//ɾ��ָ��Ϊpower����
void ChangeNode(LinkList &L,int power,float cnum,int cpower);//�޸�ָ��Ϊpower���ϵ����ָ��
void ListDifferential(LinkList L,int n);//�Զ���ʽ����n��΢��
void Indefinite_Intergral(LinkList L);//�Զ���ʽ���в�������
float Definite_Intergral(LinkList L,int a,int b);//�Զ���ʽ��a����b
LinkList Multiplication(LinkList L1,LinkList L2,int key);//��������ʽ�ĳ˷�
LinkList PowerList(LinkList L,int n,int key);//L1��n����
LinkList DivisionLink(LinkList L1, LinkList L2,int key);//��������ʽ����
void ShowMenu();//�˵�

int factorial(int n)//��n�Ľ׳�
{
    if(n==0 || n==1)
    {
        return 1;
    }
    else if(n<0)
    {
        cout<<"�޷�����"<<n<<"�Ľ׳�"<<endl;
    }
    int num = 1;
    for(int i=2;i<=n;i++)
    {
        num*=i;
    }
    return num;
}

void ListSort(LinkList &L)//������������򣨽���ð������
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
            if(q->power < p->power)//����pqֵ
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
    //�ٿ�����������ָ����ͬ���ϳ�һ��
    q = L->next;
    p = q->next;
    while(p)
    {
        if(q->power == p->power)//�����������ָ����ͬ����ϳ�һ��
        {
            L->num--;//����-1
            q->num += p->num;//���ӵ�q��
            q->next = p->next;//ֱ��ָ��p��һ�����ƹ�p
            delete(p);//�����ظ�������
            if(q->next == NULL)
            {
                return;
            }
            p=q->next;
        }
        q = q->next;
        p = p->next;//����ǰһλ        
    }

    
}

void AppendElement(LinkList &S,float num,int power)//���б�Sĩβ����½ڵ�
{
    S->num ++;//�ڵ�����һ
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

LinkList CreateList(LinkList &L){//���벢��������ʽ����ͷ���
    int n;//����ʽ����
    cout<<"���������ʽ����"<<endl;
    cin>>n;
    cout<<"������ÿһ��ϵ����ָ��"<<endl;
    L = (LinkList)malloc(sizeof(LNode));
    L-> num = n;//�洢����
    L->power =0;
    L->next = NULL;
    int i;
    for( i = n ; i>0 ; --i)
    {
        LNode *p = (LinkList)malloc(sizeof(LNode));
        cout<<"�������"<<n-i+1<<"��ϵ����ָ����"<<endl;
        cin>>p->num>>p->power;
        p->next = L->next;
        L->next = p;
    }
    ListSort(L);//��ֹ�������뻹�����Ÿ����
    return L;//���ɽ���Ķ���ʽ
}

void PrintList(LinkList L){//����������ͷ���,����
    LNode *s;
    if(L->num == 0 || L == NULL)
    {
        cout<<"�ö���ʽΪ0"<<endl;
        exit;
    }
    cout<<"�ö���ʽ����Ϊ"<<L->num<<endl;//�������
    s=L->next;
    cout<<s->num<<"x^"<<s->power<<" ";//�����һ��Ϊ�˺ÿ�
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

LinkList ListAddition(LinkList P,LinkList Q,int key)//�ӷ�
{
    LinkList S;//�ӷ����
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    LNode *p,*q;//���ڱ���P��Q
    p = P->next;
    q = Q->next;
    int num=0;//��¼����
    while(p && q)//���ǿ�
    {
        if(p->power > q->power)//p��q�ߴ�
        {
            AppendElement(S,p->num,p->power);
            p=p->next;
        }
        else if(p->power < q->power)//q��p�ߴ�
        {
            AppendElement(S,q->num,q->power);
            q = q->next;
        }
        else//ͬ��
        {
            if((p->num + q->num) == 0)//�������Ϊ0
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
    //���P��Q������ͷ��δ��ͷ��ʣ�µĶ���S
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

LinkList ListSubtraction(LinkList P,LinkList Q,int key)//����
{
    LinkList S;//�������
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    LNode *p,*q;//���ڱ���P��Q
    p = P->next;
    q = Q->next;
    int num=0;//��¼����
    while(p && q)//���ǿ�
    {
        if(p->power > q->power)//p��q�ߴ�
        {
            AppendElement(S,p->num,p->power);
            p=p->next;
        }
        else if(p->power < q->power)//q��p�ߴ�
        {
            AppendElement(S,q->num,q->power);
            q = q->next;
        }
        else//ͬ��
        {
            if((p->num - q->num) == 0)//�������Ϊ0
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
    //���P��Q������ͷ��δ��ͷ��ʣ�µĶ���S
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

float ListEvaluation(LinkList L,float num)//����ʽ��ֵ
{
    LNode *p;//��������
    p = L->next;
    float sum = 0;//��ֵ����sum
    while(p)
    {
        float data=1;//�洢num^power����
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

void DestroyList(LinkList &L)//���ٶ���ʽ
{
    LNode *p;//���ڱ���L
    if(L == NULL)//��Ϊ�ձ�
    {
        return;
    }
    while(L)
    {
        p = L->next;
        delete(L);//�Դ�ɾ��ͷ���
        L = p;
    }
}

void ClearList(LinkList &L)//��ն���ʽ
{
    LNode *p;//����L
    p = L->next;
    L->num = 0;//�����ĳ�0
    while(p)
    {
        p->num = 0;
        p->power = 0;
        p = p->next;
    }
}

void InsertNode(LinkList &L, int power, float num)//�����µĽ��
{
    AppendElement(L, num, power);
    ListSort(L);
}

void DeleteNode(LinkList &L, int power)//ɾ��ָ��Ϊpower����
{
    LNode *p=L;//���ڱ�������
    LNode *q;
    while(p->next)
    {
        if(p->next->power == power)//�ҵ���Ӧ���
        {
            q = p->next;
            p->next = q->next;//ֱ��ָ����һ�����
            delete(q);//ɾ��������
            L->num--;//����-1
            return;
        }
        p = p->next;
    }
    if(!(p->next))
    {
        cout<<"δ�ҵ�����"<<endl;
    }
    return;
}

void ChangeNode(LinkList &L,int power,float cnum,int cpower)//�޸�ָ��Ϊpower���ϵ����ָ������Ϊcpower��cnum
{
    LNode *p=L;//���ڱ�������
    LNode *q;
    while(p->next)
    {
        if(p->next->power == power)//�ҵ���Ӧ���
        {
            p->next->power = cpower;//�޸�����
            p->next->num = cnum;
            ListSort(L);//��ָֹ���ı䵼�²�Ϊ������������һ��
            return;
        }
        p = p->next;
    }
    if(!(p->next))
    {
        cout<<"δ�ҵ�����"<<endl;
    }
    return;
}

void ListDifferential(LinkList L,int n)//�Զ���ʽ����n��΢��
{
    if(n<0)
    {
        cout<<"����������ѧ����B1"<<endl;
        return;
    }
    LNode *p = L->next;//���ڱ�������
    LinkList S;//�������ʽ
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    while(p)
    {
        int power = p->power - n;
        float num = p->num;
        for(int i=0;i<n;i++)
        {
            num *= (p->power-i);//����΢�ֺ��ϵ��
        }
        AppendElement(S,num,power);
        p = p->next;
    }
    ListSort(S);
    PrintList(S);
}

void Indefinite_Intergral(LinkList L)//�Զ���ʽ���в�������
{
    LNode *p=L->next;//��������L
    int power=p->power;
    float num;//���ڴ洢ÿһ������ֺ��ϵ����ָ��
    //�����ȴ����һ��Ϊ�˴�ӡ��������ÿ�
    if(power != -1)//���ǵ�1/x����Ϊlnx
    {
        power = p->power+1;
        num = (p->num / (p->power + 1));
        cout<<num<<"x^"<<power<<" ";
    }
    else{//����a/x
        num = p->num;
        cout<<num<<"lnx"<<" ";
    }
    p=p->next;
    while(p)
    {
        if(p->power != -1)//���ǵ�1/x����Ϊlnx
        {
            power = p->power+1;
            num = (p->num / (p->power + 1));
            cout<<"+"<<num<<"x^"<<power<<" ";
        }
        else{//����a/x
            num = p->num;
            cout<<"+"<<num<<"lnx"<<" ";
        }
        p=p->next;
    }
    cout<<endl;
}

float Definite_Intergral(LinkList L,int a,int b)//�Զ���ʽ��a����b
{
    LNode *p=L->next;//��������L
    int power;
    float num;//���ڴ洢ÿһ������ֺ��ϵ����ָ��
    float value=0;//�������ܺ�
    //�����ȴ����һ��Ϊ�˴�ӡ��������ÿ�
    while(p)
    {
        if(p->power != -1)//���ǵ�1/x����Ϊlnx
        {
            power = p->power+1;
            num = (p->num / (p->power + 1));
            value += num*(pow(b,power)-pow(a,power));
        }
        else{//����a/x
            num = p->num;
            if(a==0||b==0)
            {
                cout<<"����ln0����"<<endl;
                exit;
            }
            value += num*(log(b)-log(a));//ţ�١���������Ĺ�ʽ
        }
        p=p->next;
    }
    cout<<value<<endl;
    return value;
}

LinkList Multiplication(LinkList L1,LinkList L2,int key)//��������ʽ�ĳ˷���ͬʱ�������ɵĶ���ʽ,key��ʾ�Ƿ�������ӡ����
{
    //����˼·���Ƽӷ�
    LinkList S;//�˷����
    S =(LinkList)malloc(sizeof(LNode));
    S->next = NULL;
    LNode *p,*q,*s;//pq���ڱ���L1��L2��s���ڴ洢���ɵĽ��
    p = L1->next;
    
    //˼·ΪL1��ÿһ�����γ�L2��ÿһ�������ɵ��±�һ��ListSort����
    while(p)//����L1ÿһ��
    {
        q = L2->next;
        while(q)//����L2ÿһ��
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

LinkList PowerList(LinkList L,int n,int key)//L1��n����
{
    LinkList S;//���
    S = (LinkList)malloc(sizeof(LNode));
    S = L;
    for(int i=0;i<n-1;i++)//n-1���۳�
    {
        S = Multiplication(S, L, 0);//0Ϊ����ӡÿ�εĳ˻�
    }
    if(key == 1)
    {
        PrintList(S);
    }
    return S;
}

LinkList DivisionLink(LinkList L1, LinkList L2,int key)//��������ʽ����,L1/L2
{
    LinkList L[3];//���������б�L[1]��ʾ�̣�L[2]��ʾ����
    L[1] = (LinkList)malloc(sizeof(LNode));
    L[2] = (LinkList)malloc(sizeof(LNode));
    L[1]->next = NULL;L[2]->next = NULL;
    while(L1->next->power >= L2->next->power)//һ��һ���
    {
        LinkList T;//�洢ÿһ�γ����õ���һ����
        T = (LinkList)malloc(sizeof(LNode));
        T->next = NULL;
        InsertNode(L[1],(L1->next->power)-(L2->next->power),L1->next->num/L2->next->num);//��һ�����
        InsertNode(T,(L1->next->power)-(L2->next->power),L1->next->num/L2->next->num);
        L1 = ListSubtraction(L1,Multiplication(L2,T,0),0);//L1-TL2������
    }
    if(L1->next->power < L2->next->power)//ʣ�µ�ȫ������
    {
        //���ʣ��L1��������
        L[2] = L1;
    }
    ListSort(L[1]);
    ListSort(L[2]);
    if(key == 1)
    {
        cout<<"��Ϊ��"<<endl;
        PrintList(L[1]);
        cout<<"����Ϊ��"<<endl;
        PrintList(L[2]);
    }
    return *L;
}

void ShowMenu()//�˵�
{
    int key,i,j,k,power;
    float num,num1;
    cout<<"����ʽ������"<<endl;
    cout<<"1.��������ʽ"<<endl;
    cout<<"2.�������ʽ"<<endl;
    cout<<"3.����ʽ���"<<endl;
    cout<<"4.����ʽ���"<<endl;
    cout<<"5.����ʽ��ֵ"<<endl;
    cout<<"6.����ʽ����"<<endl;
    cout<<"7.����ʽ���"<<endl;
    cout<<"8.����ʽ�޸�"<<endl;
    cout<<"9.����ʽ΢��"<<endl;
    cout<<"10.����ʽ��������"<<endl;
    cout<<"11.����ʽ������"<<endl;
    cout<<"12.����ʽ�˷�"<<endl;
    cout<<"13.����ʽ�˷�"<<endl;
    cout<<"14.����ʽ����"<<endl;
    cout<<"0.�˳�"<<endl;
    cout<<"�������Ӧ�������"<<endl;
    cin>>key;
    if(key<0||key>13)
    {
        cout<<"ʳ��ʳ�ͱ�"<<endl;
    }
    switch(key)
    {
        case 1:
            cout<<"��ֵ����i������ʽ:"<<endl;
            cin>>i;
            p[i] = CreateList(p[i]);
            break;

        case 2:
            cout<<"�����i������ʽ��"<<endl;
            cin>>i;
            PrintList(p[i]);
            break;

        case 3:
            cout<<"��i��j������ʽ��ͣ�"<<endl;
            cin>>i;
            cin>>j;
            ListAddition(p[i],p[j],1);
            cout<<"�����ֵ��:(0��Ϊ����ֵ)��";
            cin>>k;
            p[k] = ListAddition(p[i],p[j],0);
            break;

        case 4:
            cout<<"��i��j������ʽ��"<<endl;
            cin>>i;
            cin>>j;
            ListSubtraction(p[i],p[j],1);
            cout<<"�����ֵ��:(0��Ϊ����ֵ)��";
            cin>>k;
            p[k] = ListSubtraction(p[i],p[j],0);
            break;

        case 5:
            cout<<"��i������ʽ��ֵnum:";
            cin>>i>>num;
            cout<<ListEvaluation(p[i],num);
            break;

        case 6:
            cout<<"���٣�";
            cin>>i;
            DestroyList(p[i]);
            break;

        case 7:
            cout<<"��գ�";
            cin>>i;
            ClearList(p[i]);
            break;

        case 8:
            cout<<"�޸ģ�"<<endl;
            cin>>i;
            PrintList(p[i]);
            cout<<"1.�����½ڵ�  2.ɾ�����н��  3.�޸����н��  0.�˳�"<<endl;
            cin>>j;
        switch(j){
            case 1:
                cout<<"ϵ����ָ����";
                cin>>num>>power;
                InsertNode(p[i],power,num);
                break;

            case 2:
                cout<<"ɾ����ָ����";
                cin>>power;
                DeleteNode(p[i],power);
                break;

            case 3:
                cout<<"�޸��޸�ָ��Ϊ  ���ϵ����ָ������Ϊ  ��  ��";
                cin>>j>>num>>power;
                ChangeNode(p[i],j,num,power);
                break;
            }
            break;

        case 9:
            cout<<"΢�ֵ� ������ʽ ��:"<<endl;
            cin>>i>>j;
            ListDifferential(p[i],j);
            break;

        case 10:
            cout<<"���ֵ� ������ʽ:"<<endl;
            cin>>i;
            Indefinite_Intergral(p[i]);
            break;

        case 11:
            cout<<"���ֵ� ������ʽ��  ��  :"<<endl;
            cin>>i>>num>>num1;
            Definite_Intergral(p[i],num,num1);
            break;

        case 12:
            cout<<"�� ������ʽ���� ������ʽ";
            cin>>i>>j;
            Multiplication(p[i],p[j],1);
            break;

        case 13:
            cout<<"��  ������ʽ^  ����";
            cin>>i>>power;
            PowerList(p[i],power,1);
            break;

        case 14:
            cout<<"��  ������ʽ�µ�  ������ʽ";
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