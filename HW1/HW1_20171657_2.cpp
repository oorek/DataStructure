#include <iostream>
#include <string.h>
using namespace std;

void print(char * input, char * check){
    int len = strlen(input);
    for(int i=0; i<len-1; i++){
        cout << input[i];
        if(check[i] == ' ')
            continue;
        cout << check[i];
    }
    cout << input[len-1] << endl;
}
void concat_blank(int *arr, char * input, char * check){
    int len = strlen(input);
    for(int i=0; i<len;i++){
        arr[i] = input[i] - 48;
    }
    for(int i=0; i<len-1; i++){
        if(check[i] == ' '){
            int tmp = arr[i]*10 + arr[i+1];
            arr[i] = 0;
            arr[i+1] = tmp;
        }
    }
    // [1, 0, 23, 0, 45]
}
bool calculate(char * input, char * check, int target){
    int arr[11];
    // concat blank
    concat_blank(arr, input, check);

    // mult first
    int len = strlen(input);
    for(int i=0; i<len-1; i++){
        if(check[i] == '*'){
            int j=i+1;
            while(j < len-1){
                if(arr[j] != 0)
                    break;
                j++;
            }
            arr[j] = arr[i] * arr[j];
            arr[i] = 0;
        }
    }
    for(int i=0; i<len-1; i++){
        if(check[i] == '+'){
            int j=i+1;
            while(j < len-1){
                if(arr[j] != 0)
                    break;
                j++;
            }
            arr[j] = arr[i] + arr[j];
            arr[i] = 0;
        }
        if(check[i] == '-'){
            int j=i+1;
            while(j < len-1){
                if(arr[j] != 0)
                    break;
                j++;
            }
            arr[j] = arr[i] - arr[j];
            arr[i] = 0;
        }
    }
    if(arr[len-1] == target)
        return true;
    else
        return false;
}
void backtracking(char *input, char  * symbol, char * check, int cur, int target, int *tmp){
    if(cur < 0){
        if(calculate(input, check, target)){
            print(input, check);
            *tmp += 1;
            return;
        }
        return;
    }
    for(int i=0; i<4; i++){
        check[cur] = symbol[i];
        backtracking(input, symbol, check, cur-1, target, tmp);
    }
    check[cur] = 0;
    
}
int main(){
    char symbol[4] = {'+', '-', '*', ' '};
    char input[100];
    char check[100];
    int target;

    cin >> input >> target;
    int len = strlen(input);
    input[len] = '\0';
    
    if(len > 10){
        cout << "Too many input! max 10 length" << endl;
        return 0;
    }
    if(len == 1){
        if(input[0]-48 == target)
            cout << target << endl;
        else
            cout << "None" << endl;
    }
    else{
        int tmp=0;
        backtracking(input, symbol, check, len-2, target, &tmp);
        if(!tmp)
            cout << "None" << endl;
    }

return 0;
}
