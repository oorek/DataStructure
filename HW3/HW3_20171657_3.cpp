#include <iostream>
#include <string.h>
using namespace std;
#define MAX_SIZE 100

typedef struct{
    short int row;
    short int col;
    short int dir;
}element;
typedef struct{
    short int vert;
    short int horiz;
}offsets;

class Queue{
private:
    int Front;
    int Rear;
    element queue[MAX_SIZE];
public:
    Queue(){          
        Front = 0;
        Rear = 0;
    }
    void addq(element tmp){ // push rear
        if((Rear + 1) % MAX_SIZE != Front){
            Rear = (Rear + 1) % MAX_SIZE;
            queue[Rear] = tmp;
        }
        else{
            cout << "no more space\n";
        }
        //cout << Front << Rear << endl;
    }
    void deleteq(){ //pop front
        if(!empty()){
            queue[Front+1] = {0,0,0};
            Front = (Front + 1) % MAX_SIZE;
        }
        else{
            cout << "warning queue empty\n";
        }
    }
    element front(){
        if(!empty()){
            return queue[Front+1];
        }
        else{
            cout << "warning queue empty\n";
            exit(0);
        }
    }
    bool empty(){
        if(Front == Rear)
            return true;
        return false;
    }
};
void bfs(int n, int m, char map[][101], bool visited[][101], offsets *move, short int path[][101]){
    bool found=false;
    visited[0][0] = true;
    Queue q;
    element a = {0,0,0};
    q.addq(a);
    while(!q.empty() && !found){
        element cur = q.front();
        q.deleteq();
        short int row = cur.row;
        short int col = cur.col;
        short int dir = cur.dir;
        while(dir < 8){
            short int nextRow = row + move[dir].vert;
            short int nextCol = col + move[dir].horiz;
            if(nextRow >= 0 && nextCol >= 0 && nextRow < n && nextCol < m){
                if(nextRow == n-1 && nextCol == m-1){
                    if(dir >= 4)
                        path[nextRow][nextCol] = dir - 4;
                    else
                        path[nextRow][nextCol] = dir + 4;
                    found = true;
                    break;
                }
                else if(map[nextRow][nextCol] == '0' && !visited[nextRow][nextCol]){
                    visited[nextRow][nextCol] = true;
                    if(dir >= 4)
                        path[nextRow][nextCol] = dir - 4;
                    else
                        path[nextRow][nextCol] = dir + 4;
                    element tmp = {nextRow, nextCol, 0};
                    q.addq(tmp);
                }
            }
            dir++;
        }
    }
    if(found){
        pair<int,int> tmp[1000]; 
        int x = n-1;
        int y = m-1;
        int i=0;
        cout << "The path is : " << endl << "row" << " " << "col" << endl;
        while(x !=0 || y!= 0 ){
            tmp[i].first = x+1;
            tmp[i++].second = y+1;
            //cout << x+1 << " " << y+1 << endl;
            int dir = path[x][y];
            x += move[dir].vert;
            y += move[dir].horiz;
        }
        tmp[i].first = x+1;
        tmp[i++].second = y+1;
        for(int j=i-1;j>=0;j--)
            cout << tmp[j].first << " " << tmp[j].second << endl;
        //cout << x+1 << " " << y+1 << endl;
    }
    else{
        cout << " No path!\n";
    }
}
void init_move(offsets *move){
    move[0].vert = -1, move[0].horiz = 0;
    move[1].vert = -1, move[1].horiz = 1;
    move[2].vert = 0, move[2].horiz = 1;
    move[3].vert = 1, move[3].horiz = 1;
    move[4].vert = 1, move[4].horiz = 0;
    move[5].vert = 1, move[5].horiz = -1;
    move[6].vert = 0, move[6].horiz = -1;
    move[7].vert = -1, move[7].horiz = -1;
}
int main(){
    int N, M;
    N = 0;
    M = 0;
    FILE *fp1 = fopen("input.txt", "r");
    if(fp1 == NULL)
        return -1;
    char n[10];
    fgets(n, 10, fp1);
    int tok = 0;
    int end = 0;
    for(int i=0;i<10;i++){
        int tmp = n[i];
        if(tmp == ' '){
            tok = i;
        }
        else if(tmp < 48){
            end = i;
            break;
        }
    }
    int mul=0;
    for(int i=0;i<tok;i++){
        if(i>0)
            mul=10;
        N *= mul;
        N += (n[i]-48);
    }
    mul=0;
    for(int i=tok+1;i<end;i++){
        if(i>0)
            mul=10;
        M *= mul;
        M += (n[i]-48);
    }
    char map[101][101];
    bool visited[101][101];
    char tmp[101];
    short int path[101][101];

    for(int j=0;j<101;j++)
        tmp[j] = 0;
    for(int i=0;i<N;i++){
    //while(fgets(tmp, M*2, fp1) != NULL){
        fgets(tmp, M*2+1, fp1);
        int len = strlen(tmp);
        int k=0;
        for(int j=0; j<len;j++){
            if(tmp[j] != ' '){
                map[i][k++] = tmp[j];
            }
        }
        for(int j=0;j<101;j++)
            tmp[j] = 0;
    }
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            visited[i][j] = false;
            path[i][j] = -1;
        }
    }

    offsets move[8];
    init_move(move);

    bfs(N,M,map, visited, move, path);

    fclose(fp1);

    return 0;
}