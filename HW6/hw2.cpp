#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;
#define MAX_EDGES 100
#define MAX_VERTICES 50
ofstream out("output.txt");
typedef struct node *node_pointer;
typedef struct Edge{
    int u, v, w;
    Edge(): Edge(-1, -1, 0){}
    Edge(int u1, int v1, int w1): u(u1), v(v1), w(w1){}
    bool operator <(const Edge& O)const{return w < O.w;}
};
typedef struct node{
    int vertex;
    node_pointer link;
};
Edge e[MAX_EDGES];
node_pointer graph[MAX_VERTICES];
bool visited[MAX_VERTICES];
int uf[1000];
int find(int a){
    if(uf[a] < 0) return a;
    return uf[a] = find(uf[a]);
}
bool merge(int a, int b){
    a = find(a);
    b = find(b);
    if(a==b) return false;
    uf[b] = a;
    return true;
}
bool dfs(int num){
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
int kruskal(int total_vertex){
    int result=0, cnt=0;
    for(int i=0;;i++){
        if(merge(e[i].u, e[i].v)){
            result+=e[i].w;
            node_pointer tmp = (node_pointer)malloc(sizeof(node));
            tmp->vertex = e[i].v;
            tmp->link = NULL;
            if(graph[e[i].u] == NULL){
                graph[e[i].u] = tmp;
            }
            else{
                node_pointer t = graph[e[i].u];
                node_pointer p = t;
                while(t){
                    p = t;
                    t = t->link;
                }
                p->link = tmp;
            }
            node_pointer temp = (node_pointer)malloc(sizeof(node));
            temp->vertex = e[i].u;
            temp->link = NULL;
            if(graph[e[i].v] == NULL){
                graph[e[i].v] = temp;
            }
            else{
                node_pointer t = graph[e[i].v];
                node_pointer p = t;
                while(t){
                    p = t;
                    t = t->link;
                }
                p->link = temp;
            }
            if(++cnt == total_vertex-1)break;
        }
    }
    return result;
}
int main(){
    string str;
    ifstream file("input.txt");
    getline(file,str);
    stringstream ss(str);
    int total_vertex = stoi(str);

    int i=0;
    int cnt=0;
    while(getline(file, str)){
        stringstream ss(str);
        string token;
        int j=-1;
        while(ss >> token){
            j++;
            if(token[0] == '-')
                continue;
            if(i > j){
                cnt++;
                e[cnt-1] = Edge(i,j,stoi(token));
            }
        }
        i++;
    }
    sort(e, e+cnt);
    for(int k=0;k<cnt;k++)
        printf("%d %d %d\n", e[k].u, e[k].v, e[k].w);
    fill(uf, uf+cnt, -1);
    out << kruskal(total_vertex) << endl;
    dfs(0);
}
