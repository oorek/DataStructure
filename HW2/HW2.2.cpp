#include <iostream>
#include <string.h>
using namespace std;

int main(){
    int n;
    bool arr[101];
    for(int i=0;i<101;i++)
        arr[i] = false;
    cin >> n;
    int flag=0;
    int max = 0;
    int min = 101;
    for(int i=0; i<n; i++){
        int tmp;
        cin >> tmp;
        if(!arr[tmp])
            arr[tmp] = true;
        else{
            flag = 1;
        }
        if(max < tmp)
            max = tmp;
        if(min > tmp)
            min = tmp;
    }
    if(flag){
        cout << '0' << endl;
        return 0;
    }
    for(int i=min; i<=max; i++){
        if(!arr[i]){
            cout << '0' << endl;
            return 0;
        }
    }    
    cout << '1' << endl;
    return 0;
}