#include<iostream>
#include<stdlib.h>
using namespace std;

class stack{//栈类
    private:
        char st[100];
        int len=0;
    public:
        //判断栈空
        bool isempty(){
        if(len == 0){
            return true;
        }
        return false;
        }
        
        //栈的长度
        int length(){
            return len;
        }

        //入栈
        void push(char s){
        st[len] = s;
        len++;
        }

        //出栈
        void pop(){
            len--;
        }

        //栈顶元素
        char top(){
            return st[len-1];
        }
};
class parenthesis{//括号类
    private:
        char brackets[100];
        int braLen=0;
    public:
        void initBrackets(){//初始化这个串
            char c;
            cout<<"please input the parenthesis:"<<endl;
            while(c!='@'){//@为结束符
                cin>>c;
                brackets[braLen]=c;
                braLen++;
            }
        }

        void printBrackets(){
            for(int i=0;i<braLen;i++){
                cout<<brackets[i];
            }
        }

        bool isValid(){//判断括号是否匹配
            stack stk;
            for(int i=0;i<braLen;i++){
                switch(brackets[i]){
                    case '(':
                        stk.push(brackets[i]);
                        break;
                    case '[':
                        if(stk.top()=='{'||stk.isempty()){
                            stk.push(brackets[i]);
                        }
                        else{
                            return false;
                        }
                        break;
                    case '{':
                        if(stk.isempty()){
                            stk.push(brackets[i]);
                        }
                        else{
                            return false;
                        }
                        break;
                    case ')':
                        if(!stk.isempty() && stk.top()=='('){
                            stk.pop();
                        }
                        else{
                            return false;
                        }
                        break;
                    case ']':
                        if(!stk.isempty() && stk.top()=='['){
                            stk.pop();
                        }
                        else{
                            return false;
                        }
                        break;
                    case '}':
                        if(!stk.isempty() && stk.top()=='{'){
                            stk.pop();
                        }
                        else{
                            return false;
                        }
                        break;
                    default:
                        break;
                }
            }
            if(stk.isempty()){
                return true;
            }
            return false;
        }
};

int main(){
    parenthesis p;
    int num;//表达式数量
    cout<<"The amount of expressions:";
    cin>>num;
    for(int i=0;i<num;i++){
        p.initBrackets();//输入这个表达式
        if(p.isValid()){//判断是否匹配
            cout<<"the parenthesis is paired"<<endl;
        }
        else{
            cout<<"the parenthesis is not paired"<<endl;
        }
    }
    system("pause");
    return 0;
}