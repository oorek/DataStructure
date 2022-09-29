#include <iostream>
#include <string.h>
using namespace std;

void kmp(char *s, char * p, int *failure, bool *success_idx){
    int s_len = strlen(s);
    int p_len = strlen(p);
    for(int i=0, j=0; i<s_len && j<p_len;){
        if(s[i] == p[j]){
            if(j == p_len-1){
                success_idx[i-j] = true;
                i = i-j + 1;
                j=0;
                continue;
            }
            i++;
            j++;
        }
        else{
            if(j!=0){
                j = failure[j-1] + 1;
            }
            else{
                i++;
                j=0;
            }
        }
    }
}
void init_failure(char *p, int * failure){
    int len = strlen(p);
    failure[0] = -1;
    
    for(int j=1; j<len;j++){
        int i = failure[j-1];
        while(p[j] != p[i+1] && (i>=0))
            i = failure[i];
        if(p[j] == p[i+1])
            failure[j] = i+1;
        else
            failure[j] = -1;
    }
    
}
int main(){
    char s[31];
    char p[31];
    int failure[31];
    bool success_idx[30];

    for(int i=0; i<30; i++)
        success_idx[i] = false;

    cin >> s >> p;
   // int len = strlen(p);

    init_failure(p, failure);
    kmp(s,p,failure, success_idx);
    for(int i=0; i<30; i++){
        if(success_idx[i])
            cout << i << endl;
    }
    
    return 0;
}