#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;
#define MAX_VERTICES 50
typedef struct node *node_pointer;
typedef struct node{
    int vertex;
    node_pointer link;  
};
node_pointer graph[MAX_VERTICES];
bool visited[MAX_VERTICES];
ofstream out("output.txt");
bool dfs(int num){
/*    stack <int> s;
    s.push(num);
    while(!s.empty()){
        int N = s.top();
        visited[N] = true;
        for(node_pointer tmp=graph[N]; tmp; tmp = tmp->link){
            if(!visited[tmp->vertex]){
                s.push(tmp->vertex);
            }
        }
    }*/
    if(!visited[num]){
        out << num << " ";
        visited[num] = true;
        for(node_pointer tmp=graph[num]; tmp; tmp = tmp->link){
            if(!visited[tmp->vertex]){
                dfs(tmp->vertex);
            }
        }
        return true;
    }
    return false;
}
int main(){
    string str;
    ifstream file("input.txt");

    getline(file, str);
    stringstream ss(str);
   // cout << str << endl;
    int total_vertex = stoi(str);
   // cout << total_vertex << endl;
    int i=0;
    while(getline(file, str)){
        stringstream ss(str);
       // cout << str << endl;
        for(int j=0;j<total_vertex*2; j+=2){
            if(str[j] == '1'){
                node_pointer tmp = (node_pointer)malloc(sizeof(node));
                tmp->vertex = j/2;
                tmp->link = NULL;
                if(graph[i] == NULL){
                    graph[i] = tmp;
                }
                else{
                    node_pointer t = graph[i];
                    node_pointer p = t;
                    while(t){
                        p = t;
                        t = t->link;
                    }
                    p->link = tmp;
                }
            }
        }
        i++;
    }
  /*  for(int i=0; i<total_vertex; i++){
        node_pointer t = graph[i];
        while(t){
            cout << t->vertex << " ";
            t = t->link;
        }
        cout << endl;
    }*/
    for(int i=0; i<total_vertex; i++){
        if(dfs(i)){
            out << endl;
        }
    }
    return 0;
}