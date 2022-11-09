#include <iostream>
#include <string.h>
using namespace std;
#define MAX_TOP 30

typedef enum {lparen, rparen, unary, Plus, Minus, times, divide, mod, eos, operand} precedence;

template<class T> 
class Stack{
private:
    int top;
    T stack[MAX_TOP];
public:
    Stack(){
        top = -1;
        for(int i=0; i<MAX_TOP; i++)
            stack[i] = '\0';
    }
    void push(T tmp){
        if(top + 1 < MAX_TOP){
            top += 1;
            stack[top] = tmp;
        }
        else{
            cout << "no more memory!" << endl;
        }
    }
    void pop(){
        stack[top--] = '\0';
    }
    T Top(){
        if(top < 0){
            cout << "error" << endl;
            exit(0);
        }
        else
            return stack[top];
    }
    bool isempty(){
        if(top < 0)
            return true;
        return false;
    }

};
precedence getToken(char tmp){
    switch (tmp){
        case '(' : return lparen;
        case ')' : return rparen;
        case '#' : return unary;
        case '+' : return Plus;
        case '-' : return Minus;
        case '*' : return times;
        case '/' : return divide;
        case '%' : return mod;
        case '\0' : return eos;
        default : return operand;
    }
}
//github
void inverse(char *infix, char * ri){
    int len = strlen(infix);
    for(int i=0;i<len;i++){
        ri[i] = infix[len-(i+1)];
    }
    for(int i=0; i<len;i++){
        if(ri[i] == ')'){
            ri[i] = '(';
            continue;
        }
        else if(ri[i] == '(')
            ri[i] = ')';
    }
}
void infix_to_prefix(char *infix, char *prefix, int *isp, int *icp){
    Stack<string> Operand;
    Stack<char> Operator;
    char reverse_infix[30];
    for(int i=0;i<30;i++)
        reverse_infix[i] = 0;
    inverse(infix, reverse_infix);
    int n=0;
    while(1){
        char sym = reverse_infix[n++];
        if(sym == '-'){
            if(n == 1)
                sym = '#';
            else if(reverse_infix[n] == ')')
                sym = '#';
        }
        char tmp_sym[2] = {sym, '\0'};
        string s(tmp_sym);
        precedence sym_pre = getToken(sym);
        if(sym_pre == eos){
            while(!Operator.isempty()){
                char x = Operator.Top();
                Operator.pop();
                string operand1 = Operand.Top();
                Operand.pop();
                string operand2 = Operand.Top();
                Operand.pop();
                string tmp = x + operand1 + operand2;
                Operand.push(tmp);
            }
            string ans = Operand.Top();
            strcpy(prefix, ans.c_str());
            Operand.pop();
            break;
        }
        else if(sym_pre == operand){
            Operand.push(s);
        }
        else{
            if(!Operator.isempty()){
                char top_sym = Operator.Top();
                precedence top_pre = getToken(top_sym);
                int top_precedence = isp[top_pre];
                int sym_precedence = icp[sym_pre];
                if(sym_precedence >= top_precedence){
                    if(sym_precedence == 19){
                        while(isp[getToken(Operator.Top())] != 0){
                            char c = Operator.Top();
                            if(c == '#'){
                                Operator.pop();
                                string operand1 = Operand.Top();
                                Operand.pop();
                                string tmp = operand1 + c;
                                Operand.push(tmp);
                                break;
                            }
                            Operator.pop();
                            string operand1 = Operand.Top();
                            Operand.pop();
                            string operand2 = Operand.Top();
                            Operand.pop();
                            string tmp = c + operand1 + operand2;
                            Operand.push(tmp);
                        }
                        Operator.pop();
                    }
                    else
                        Operator.push(sym);
                }
                else{
                    while(isp[getToken(Operator.Top())] >= sym_precedence){
                        char c = Operator.Top();
                        Operator.pop();
                        string operand1 = Operand.Top();
                        Operand.pop();
                        string operand2 = Operand.Top();
                        Operand.pop();
                        string tmp = c + operand1 + operand2;
                        Operand.push(tmp);
                        if(Operator.isempty())
                            break;
                    }
                    Operator.push(sym);
                }
            }
            else{
                Operator.push(sym);
            }
        }
    }

}

int main(){
    //typedef enum {lparen, rparen, unary, Plus, Minus, times, divide, mod, eos, operand} precedence;
    char infix[30];
    char prefix[30];
    // lparen, rparen, unary, plus, minus, times, divide, mod, eos
    int isp[] = {0,19,15,12,12,13,13,13,0};
    int icp[] = {20,19,15,12,12,13,13,13,0};

    for(int i=0; i<30;i++){
        infix[i] = '\0';
        prefix[i] = '\0';
    }
    cout << "Infix: ";
    cin >> infix;

    infix_to_prefix(infix, prefix, isp, icp);

    cout << "Prefix: " << prefix << endl;

    return 0;
}