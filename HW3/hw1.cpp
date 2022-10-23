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
            stack[i] = 0;
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
        stack[top--] = 0;
    }
    T Top(){
        if(top < 0)
            cout << "error" << endl;
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
void infix_to_postfix(char * infix, char * postfix, int * isp, int * icp){
    int infix_n = 0;
    int postfix_n=0;
    Stack<char> st;
    while(1){
        char sym = infix[infix_n++];
        if(sym == '-'){
            if(infix_n == 1){
                sym = '#';
            }
            else if(infix[infix_n - 2] == '('){
                sym = '#';
            }
        }
        precedence sym_pre = getToken(sym);
        if(sym_pre != operand){
            if(sym_pre == eos){
                while(!st.isempty()){
                    char c = st.Top();
                    st.pop();
                    postfix[postfix_n++] = c;
                }
                return;
            }
            int sym_precedence = icp[sym_pre];
            if(!st.isempty()){
                char top_sym = st.Top();
                precedence top_pre = getToken(top_sym);
                int top_precedence = isp[top_pre];

                if(sym_precedence > top_precedence){
                    if(sym_precedence == 19){
                        while(isp[getToken(st.Top())] != 0){
                            char c = st.Top();
                            st.pop();
                            postfix[postfix_n++] = c;
                        }
                        st.pop(); // '(' pop
                    }
                    else
                        st.push(sym);
                }
                else{

                    while(isp[getToken(st.Top())] >= sym_precedence){
                        char c = st.Top();
                        st.pop();
                        postfix[postfix_n++] = c;
                        if(st.isempty())
                            break;
                    }
                    st.push(sym);
                }
                
            }
            else{
                st.push(sym);
            }
        }
        else{
            postfix[postfix_n++] = sym;
        }
    }
}
int cal(int op1, int op2, char Operator){
    switch(Operator){
        case '+' : return op1 + op2;
        case '-' : return op1 - op2;
        case '*' : return op1 * op2;
        case '/' : return op1 / op2;
        case '%' : return op1 % op2;
    }
}
int cal_postfix(char * postfix){
    int n=0;
    Stack<int> st;
    while(1){
        char sym = postfix[n++];
        precedence sym_pre = getToken(sym);
        if(sym_pre == operand){
            st.push(sym-48);
        }
        else if(sym_pre == eos){
            int val = st.Top();
            st.pop();
            return val;
        }
        else{
            if(!st.isempty()){
                int top = st.Top();
                if(sym_pre == unary){
                    st.pop();
                    st.push(top*(-1));
                }
                else{
                    int operand1 = st.Top();
                    st.pop();
                    int operand2 = st.Top();
                    st.pop();
                    int val = cal(operand2, operand1, sym);
                    st.push(val);
                }
            }
        }
        
    }
    
}
int main(){
    char infix[30];
    char postfix[30];
    char symbol_ascii[9];
    // lparen, rparen, unary, plus, minus, times, divide, mod, eos
    int isp[] = {0,19,15,12,12,13,13,13,0};
    int icp[] = {20,19,15,12,12,13,13,13,0};
    /*
    symbol_ascii[0] = 40;
    symbol_ascii[1] = 41;
    symbol_ascii[2] = 35;
    symbol_ascii[3] = 43;
    symbol_ascii[4] = 45;
    symbol_ascii[5] = 42;
    symbol_ascii[6] = 47;
    symbol_ascii[7] = 37;*/
    
    for(int i=0; i<30;i++){
        infix[i] = '\0';
        postfix[i] = '\0';
    }

    cin >> infix;
    
    infix_to_postfix(infix, postfix, isp, icp);
    
    cout << postfix << endl;

    cout << cal_postfix(postfix) << endl;

    return 0;
}

//github