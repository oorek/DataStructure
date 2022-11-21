#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAX_SIZE 50
typedef enum{head, entry} tagfield;
typedef struct max_node * matrix_pointer;
typedef struct entry_node{
    int row;
    int col;
    int value;
};
typedef struct max_node{
    matrix_pointer down;
    matrix_pointer right;
    tagfield tag;
    union{
        matrix_pointer next;
        entry_node entry;
    }u;
};
matrix_pointer hdnode[MAX_SIZE];
matrix_pointer hdnode_t[MAX_SIZE];
void parse(int *row, int *col, int *num_terms, FILE *fp1){
    *row=0;
    *col=0;
    *num_terms=0;
    
    char n[10];
    for(int i=0;i<10;i++)
        n[i] = 0;
    fgets(n, 10, fp1);
    int tok1 = 0;
    int tok2 = 0;
    int end = 0;
    bool flag = false;
    for(int i=0;i<10;i++){
        char tmp = n[i];
        if(tmp == ' '){
            if(!flag){
                tok1 = i;
                flag = true;
            }
            else{
                tok2 = i;
            }
        }
        else if(tmp < 48 && tmp != '-'){
            end = i;
            break;
        }
    }
    int mul=0;
    
    for(int i=0;i<tok1;i++){
        if(i>0)
            mul=10;
        *row *= mul;
        if(n[i] >= 48)
            *row +=(n[i]-48);
    }
    if(n[0] == '-')
        *row *= -1;
    mul=0;
    for(int i=tok1+1;i<tok2;i++){
        if(i>tok1+1)
            mul=10;
        *col *= mul;
        if(n[i] >= 48)
            *col +=(n[i]-48);
    }
    if(n[tok1+1] == '-')
        *col *= -1;
    mul=0;
    for(int i=tok2+1;i<end;i++){
        if(i>tok2+1)
            mul=10;
        *num_terms *= mul;
        if(n[i] >= 48)
            *num_terms +=(n[i]-48);
    }
    if(n[tok2+1] == '-')
        *num_terms *= -1;
}
matrix_pointer mread(FILE * fp1){
    int num_heads;
    int cur_row;
    if(fp1 == NULL)
        exit(1);

    int row, col, num_terms;
    parse(&row, &col, &num_terms, fp1);
    num_heads = (row>col)?row:col;
    matrix_pointer node = (matrix_pointer)malloc(sizeof(max_node));
    node->tag = entry;
    node->u.entry.row = row;
    node->u.entry.col = col;
    node->u.entry.value = num_terms;
    if(!num_heads)
        node->right = node;
    else{
        for(int i=0;i<num_heads;i++){
            matrix_pointer tmp = (matrix_pointer)malloc(sizeof(max_node));
            hdnode[i] = tmp;
            tmp->tag = head;
            hdnode[i]->right = tmp;
            tmp->u.next = tmp;
        }
        cur_row=0;
        matrix_pointer last;
        last= hdnode[0];
        for(int i=0; i<num_terms;i++){
            char n[10];
            // input 받기 
            int rrow, ccol, vvalue;
            parse(&rrow, &ccol, &vvalue, fp1);
            //printf("%d %d %d\n", rrow, ccol, vvalue);
            if(rrow > cur_row){
                last->right = hdnode[cur_row];
                cur_row = rrow;
                last = hdnode[rrow];
            }
            matrix_pointer tmp = (matrix_pointer)malloc(sizeof(max_node));
            tmp->tag = entry;
            tmp->u.entry.row = rrow;
            tmp->u.entry.col = ccol;
            tmp->u.entry.value = vvalue;
            last->right = tmp;
            last = tmp;
            hdnode[ccol]->u.next->down = tmp;
            hdnode[ccol]->u.next = tmp;
        }
        last->right = hdnode[cur_row];
        for(int i=0; i<col;i++)
            hdnode[i]->u.next->down = hdnode[i];
        for(int i=0; i<num_heads;i++)
            hdnode[i]->u.next = hdnode[i+1];
        hdnode[num_heads-1]->u.next = node;
        node->right = hdnode[0];
    }
    //printf("address node %u\n", node);
    return node;
}
matrix_pointer mtranspose(matrix_pointer node){
    matrix_pointer t_node;
    int row, col, num_terms, num_heads;
    row = node->u.entry.col;
    col = node->u.entry.row;
    num_heads = (row > col)?row:col; 
    num_terms = node->u.entry.value;
    matrix_pointer tmp = (matrix_pointer)malloc(sizeof(max_node));
    tmp->tag = entry;
    tmp->u.entry.row = row;
    tmp->u.entry.col = col;
    tmp->u.entry.value = num_terms;
    t_node = tmp;
    for(int i=0; i<num_heads; i++){
        matrix_pointer temp = (matrix_pointer)malloc(sizeof(max_node));
        temp->tag = head;
        hdnode_t[i] = temp;
        hdnode_t[i]->right = temp;
        temp->u.next = temp;
    }
    matrix_pointer last, Last;
    int last_row=0;
    for(int i=0; i<num_heads;i++){
        last = hdnode_t[i];
        matrix_pointer traverse = hdnode[i]->down;
        while(traverse != hdnode[i]){
            last_row = i;
            printf("%d\n", i);
            matrix_pointer temp = (matrix_pointer)malloc(sizeof(max_node));
            temp->tag = entry;
            temp->u.entry.row = traverse->u.entry.col;
            temp->u.entry.col = traverse->u.entry.row;
            temp->u.entry.value = traverse->u.entry.value;
            printf("%d %d %d %d\n", i, temp->u.entry.row, temp->u.entry.col,temp->u.entry.value);
            Last = hdnode_t[temp->u.entry.col];
            Last->u.next->down = temp;
            Last->u.next = temp;
    
            last->right = temp;
            last = temp;
            traverse = traverse->down;
        }
        last->right = hdnode_t[i];
    }
    last->right = hdnode_t[last_row];
    for(int i=0; i<col;i++)
        hdnode_t[i]->u.next->down = hdnode_t[i];
    for(int i=0; i<num_heads;i++)
        hdnode_t[i]->u.next = hdnode_t[i+1];
    hdnode_t[num_heads-1]->u.next = t_node;
    t_node->right = hdnode_t[0];
    printf("address node %u\n",t_node);
    return t_node;
}
void mwrite(matrix_pointer node, FILE * fp2){
    matrix_pointer tmp;
    matrix_pointer head = node->right;
    printf("\n num_rows=%d, num_cols=%d\n", node->u.entry.row, node->u.entry.col);
    printf(" The matrix by row, column, and value: \n\n");
    for(int i=0; i< node->u.entry.row;i++){
        for(tmp=head->right; tmp != head; tmp = tmp->right){
            printf("%5d%5d%5d\n",tmp->u.entry.row, tmp->u.entry.col, tmp->u.entry.value);
        }
        head = head->u.next;
    }

}
int main(){
    FILE *fp1 = fopen("input.txt", "r");
    FILE *fp2 = fopen("output.txt", "w");
    matrix_pointer node = mread(fp1);
    matrix_pointer t_node = mtranspose(node);
    printf("address node %u\n",t_node);
    mwrite(t_node, fp2);
    fclose(fp1);
    fclose(fp2);    

    return 0;
}