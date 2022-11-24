#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;
#define MAX_SIZE 24
typedef struct node *node_pointer;
typedef struct node{
    string name;
    node_pointer link;
};
node_pointer seq[MAX_SIZE];
short int out[MAX_SIZE];
node_pointer Name[MAX_SIZE];
int cnt;
void pop(node_pointer top, node_pointer x){
    string d = top->name;
    int A;
    for(int i=0;i<cnt;i++)
        if(Name[i]->name.compare(d) == 0)
            A = i;
    x = seq[A];
    top = top->link;
}
void push(int j, node_pointer x, node_pointer y, node_pointer top){
    out[j] = 1;
    y = x->link;
    x->link = top;
    top = x;
    x = y;
}
bool check(int s, int t, string second, string third){
    node_pointer x, y, top;
    if(!out[s]){
        out[s] = 1;
        x = seq[s]; top = NULL;
        for(;;){
            while(x){
                int j=0;
                string S = x->name;
                if(S == third){
                    return true;
                }
                else{
                    for(int i=0;i<cnt;i++){
                        if(Name[i]->name.compare(S) == 0){
                            j = i;
                        }
                        if(!out[j]){
                            push(j, y, x, top);
                        }
                        else
                            x = x->link;
                    }
                }
            }
            if(!top)break;
            pop(top, x);
        }
    }
    return false;
}
int main(){
    string str;
    ifstream file("input.txt");
    ofstream out("output.txt");
    
    while (getline(file, str)){
      //  cout << str << '\n';
        stringstream ss(str);
        // 스트림을 통해, 문자열을 공백 분리해 변수에 할당
        string first, second, third;
        ss >> first >> second >> third;
       // cout << first << endl;
       // cout << second << endl;
       // cout << third << endl;
        if(first.compare("P")==0){
            Name[cnt] = (node_pointer)malloc(sizeof(node));
            Name[cnt]->name = second;
            cnt++;
            //x->link = seq[x->num];
            //seq[x->num] = x;
        }
        else if(first.compare("F")==0){
            int s,t;
            for(int i=0;i<cnt;i++){
                 if(Name[i]->name.compare(second) == 0){
                    s = i;
                 }
                 if(Name[i]->name.compare(third) == 0)
                    t = i;
            }
            node_pointer x = (node_pointer)malloc(sizeof(node));
            x->name = Name[t]->name;
            x->link = seq[s];
            seq[s] = x;
            node_pointer xx = (node_pointer)malloc(sizeof(node));
            xx->name = Name[s]->name;
            xx->link = seq[t];
            seq[t] = xx;
        }
        else if(first.compare("U")==0){
            int s,t;
            for(int i=0;i<cnt;i++){
                 if(Name[i]->name.compare(second) == 0){
                    s = i;
                 }
                 if(Name[i]->name.compare(third) == 0)
                    t = i;
            }
            node_pointer tmp, before;
            for(tmp = seq[s]; tmp != NULL; before = tmp, tmp = tmp->link){
                if(tmp->name.compare(third) == 0){
                    before->link = tmp->link;
                    free(tmp);
                }
            }
            for(tmp = seq[t]; tmp != NULL; before = tmp, tmp = tmp->link){
                if(tmp->name.compare(second) == 0){
                    before->link = tmp->link;
                    free(tmp);
                }
            }

        }
        else if(first.compare("L")==0){
            int s;
            for(int i=0; i<cnt; i++){
                if(Name[i]->name.compare(second) == 0){
                    s = i;
                }
            }
            //Print out the friends of the specified person.
            node_pointer tmp;
            for(tmp=seq[s]; tmp!= NULL; tmp=tmp->link){
                //cout << tmp->name << endl;
                out << tmp->name << " ";
            }
            out << endl;
        }
        else if(first.compare("Q")==0){
            //Check whether the two people are friends. If so, print “Yes”; if not, print “No"
            int s,t;
            for(int i=0;i<cnt;i++){
                 if(Name[i]->name.compare(second) == 0){
                    s = i;
                 }
                 if(Name[i]->name.compare(third) == 0)
                    t = i;
            }
            bool flag = check(s, t, second, third);
            if(flag)
                out << "Yes" << endl;
            else
                out << "No" << endl;
        }
        else if(first.compare("X")==0){
            return 0;
        }
    }
    out.close();
    return 0;
}