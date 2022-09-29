#include <iostream>
#include <string.h>
using namespace std;

void print(char *input, bool * check){
    int len = strlen(input);
    for(int i=0; i<len; i++){
        cout << input[i];
        if(check[i]){
            cout << "/";
        }
    }
    cout << "\n";
}
void backtracking(char * input, bool * check, int cur, bool tmp){
    if(cur < 0){
        if(tmp){
            print(input, check);
        }
        return;
    }
    if(tmp){
       check[cur] = true; 
    }
    backtracking(input, check, cur-1, false);
    backtracking(input, check, cur-1, true);
    check[cur] = false;
}
int main(){
    char input[100];
    bool check[100];
    for(int i=0; i<10; i++)
        check[i] = false;
    
    cin >> input;
    int len = strlen(input);
   
    input[len] = '\0';
    
    if(len > 10){
        cout << "Too many input! max 10 length" << endl;
        return 0;
    }
    if(len == 1)
        cout << input << endl;
    else{
        backtracking(input, check, len-2, false);
        backtracking(input, check, len-2, true);
    }
    return 0;
}