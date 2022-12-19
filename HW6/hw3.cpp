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
typedef struct node{
    int vertex;
    node_pointer link;  
};
typedef struct Edge{
    int u, v, w;
    Edge(): Edge(-1, -1, 0){}
    Edge(int u1, int v1, int w1): u(u1), v(v1), w(w1){}
    bool operator <(const Edge& O)const{return w < O.w;}
};
node_pointer graph[MAX_VERTICES];
node_pointer Graph[MAX_VERTICES];
bool visited[MAX_VERTICES];
bool Visited[MAX_VERTICES];
Edge e[MAX_EDGES];
int uf[1000];
int arr[100];
int total_vertex;
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
        visited[num] = true;
       // printf("%d\n", num);
        arr[num] = num;
        for(node_pointer tmp=graph[num]; tmp; tmp = tmp->link){
            if(!visited[tmp->vertex]){
                dfs(tmp->vertex);
            }
        }
        return true;
    }
    return false;
}
bool Dfs(int num){
    if(!Visited[num]){
        Visited[num] = true;
        cout << num << " ";
        for(node_pointer tmp=Graph[num]; tmp; tmp = tmp->link){
            if(!Visited[tmp->vertex]){
                Dfs(tmp->vertex);
            }
        }
        return true;
    }
    return false;
}
void prim(int cnt, int Vertex){
    int C=0;
    bool V[MAX_EDGES];
    fill(V, V+MAX_EDGES, false);
    V[e[0].u] = true;
    for(int i=0;;i++){
        if((V[e[i].u] && !V[e[i].v]) || (!V[e[i].u] && V[e[i].v])){
            if(merge(e[i].u, e[i].v)){
               // printf("%d %d\n", e[i].u, e[i].v);
                if(!V[e[i].v])
                    V[e[i].v] = true;
                else if(!V[e[i].u])
                    V[e[i].u] = true;
                node_pointer tmp = (node_pointer)malloc(sizeof(node));
                tmp->vertex = e[i].v;
                tmp->link = NULL;
                if(Graph[e[i].u] == NULL){
                    Graph[e[i].u] = tmp;
                }
                else{
                    node_pointer t = Graph[e[i].u];
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
                if(Graph[e[i].v] == NULL){
                    Graph[e[i].v] = temp;
                }
                else{
                    node_pointer t = Graph[e[i].v];
                    node_pointer p = t;
                    while(t){
                        p = t;
                        t = t->link;
                    }
                    p->link = temp;
                }
                if(++C == Vertex-1)break;
            }
        }
    }

}
int main(){
    string str;
    ifstream file("input.txt");
    getline(file, str);
    total_vertex = stoi(str);
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
            node_pointer tmp = (node_pointer)malloc(sizeof(node));
            tmp->vertex = j;
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
        i++;
    }

    for(int k=0; k<total_vertex; k++){
        fill(arr, arr+100,-1);
        if(dfs(k)){
            string str;
            ifstream file1("input.txt");
            getline(file1, str);
            int I=0;
            int count=0;
            int Vertex=0;
            while(getline(file1, str)){
                stringstream ss(str);
                string token;
                int j=-1;
                bool flag = false;
                while(ss >> token){
                    j++;
                    if(token[0] == '-')
                        continue;
                    if(arr[I] == I && !flag){
                        flag = true;
                        Vertex++;
                    }
                    if(I > j && (arr[I] == I)){
                        count++;
                        e[count-1] = Edge(I,j,stoi(token));
                    }
                }
                I++;
            }
           // printf("%d %d %d\n", arr[1], arr[3], arr[6]);
           // printf("%d %d\n", count, Vertex);
            sort(e, e+count);
            fill(uf, uf+MAX_VERTICES, -1);
            prim(count, Vertex);
            for(int m=0;m<count;m++){
                e[m].u = -1;
                e[m].v = -1;
                e[m].w = 0;
            }

            fill(Visited, Visited+MAX_VERTICES, false);
            Dfs(k);
            cout << endl;
            for(int m=0; m<MAX_VERTICES;m++)
                Graph[m] = NULL;
        }
    }
    return 0;
}