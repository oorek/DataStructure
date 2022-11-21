#include <iostream>
#include <stdlib.h>
using namespace std;
#define COMPARE(x,y) (x<y)?-1:((x==y)?0:1)
typedef struct poly_node * poly_pointer;
typedef struct poly_node{
    int coef;
    int expon;
    poly_pointer link;
};
void parse(int *coef, int *expon, FILE *fp1){
    *coef = 0;
    *expon = 0;
    char n[10];
    for(int i=0;i<10;i++)
        n[i] = 0;
    fgets(n, 10, fp1);
    int tok = 0;
    int end = 0;
    for(int i=0;i<10;i++){
        char tmp = n[i];
        if(tmp == ' '){
            tok = i;
        }
        else if(tmp < 48 && tmp != '-'){
            end = i;
            break;
        }
    }
    int mul=0;
    
    for(int i=0;i<tok;i++){
        if(i>0)
            mul=10;
        *coef *= mul;
        if(n[i] >= 48)
            *coef +=(n[i]-48);
    }
    if(n[0] == '-')
        *coef *= -1;
    mul=0;
    for(int i=tok+1;i<end;i++){
        if(i>tok+1)
            mul=10;
        *expon *= mul;
        if(n[i] >= 48)
            *expon +=(n[i]-48);
    }
    if(n[tok+1] == '-')
        *expon *= -1;
}
poly_pointer mread(FILE *fp1, poly_pointer P){
    if(fp1 == NULL)
        exit(1);
    int term=0;
    char n[5];
    for(int i=0;i<5;i++)
        n[i] = 0;
    fgets(n, 5, fp1);
    int end= 0;
    for(int i=0; i<5;i++){
        int tmp = n[i];
        if(tmp<48){
            end = i;
            break;
        }
    }
    int mul=0;
    for(int i=0;i<end;i++){
        if(i>0)
            mul=10;
        term *= mul;
        if(n[i] >= 48)
            term +=(n[i]-48);
    }
    poly_pointer start = (poly_pointer)malloc(sizeof(poly_node));
    P = start;
    for(int i=0;i<term;i++){
        int coef, expon;
        parse(&coef, &expon, fp1);
        poly_pointer temp = (poly_pointer)malloc(sizeof(poly_node));
        temp->coef = coef;
        temp->expon = expon;
        temp->link = temp;
        P->link = temp;
        P = temp;
    }
    P->link = start->link;
    P = start->link;
    free(start);
    return P;
}
poly_pointer attach(int coef_a, int expon_a, int coef_b, int expon_b, poly_pointer *start, poly_pointer buffer){
    int coef, expon;
    coef = coef_a * coef_b;
    expon = expon_a + expon_b;
    if(buffer == NULL){
        *start = (poly_pointer)malloc(sizeof(poly_node));
        (*start)->link = (*start);
        buffer = *start;
    }
    poly_pointer tmp = (poly_pointer)malloc(sizeof(poly_node));
    tmp->coef = coef;
    tmp->expon = expon;
    buffer -> link = tmp;
    buffer = tmp;
    return buffer;
}
poly_pointer padd(poly_pointer buffer, poly_pointer buffer2, poly_pointer d){
    poly_pointer start_d = (poly_pointer)malloc(sizeof(poly_node));
    d = start_d;
    d->link = start_d;
    if(buffer2 == NULL){
        poly_pointer S = buffer;
        poly_pointer before_S = buffer;
        for(buffer; before_S->link != S;before_S = buffer,buffer=buffer->link){
            poly_pointer temp = (poly_pointer)malloc(sizeof(poly_node));
            temp->coef = buffer->coef;
            temp->expon = buffer->expon;
            d -> link = temp;
            d = temp; 
        }
        d->link = start_d->link;
        d = start_d->link;
        free(start_d);
        return d;
    }
    else{
        poly_pointer start_buffer = buffer;
        poly_pointer start_buffer2 = buffer2;
        poly_pointer bef = buffer;
        poly_pointer bef2 = buffer2;
        int cnt=0;
        do{
           // printf("cnt : %d\n", cnt++);
           // printf("%d %d\n", buffer->coef, buffer->expon);
           // printf("%d %d\n", buffer2->coef, buffer2->expon);
            poly_pointer tmp;
            switch(COMPARE(buffer->expon,buffer2->expon)){
                case -1:
                    tmp = (poly_pointer)malloc(sizeof(poly_node));
                    tmp->coef = buffer2->coef;
                    tmp->expon = buffer2->expon;
                    d->link = tmp;
                    d = tmp;
                    bef2 = buffer2;                   
                    buffer2=buffer2->link;
                    break;
                case 0:           
                    if(buffer->coef + buffer2->coef == 0){    
                        bef = buffer;
                        bef2 = buffer2;                  
                        buffer = buffer->link;
                        buffer2 = buffer2->link;
                    }
                    else{
                        tmp = (poly_pointer)malloc(sizeof(poly_node));
                        tmp->coef = buffer->coef + buffer2->coef;
                        tmp->expon = buffer->expon;   
                        bef = buffer;
                        bef2 = buffer2;                           
                        buffer = buffer->link;
                        buffer2 = buffer2->link;
                        d->link = tmp;
                        d = tmp;
                    }
                    break;
                case 1:                
                    tmp = (poly_pointer)malloc(sizeof(poly_node));
                    tmp->coef = buffer->coef;
                    tmp->expon = buffer->expon;
                    d->link = tmp;
                    d = tmp;  
                    bef = buffer;                                      
                    buffer=buffer->link;
                    break;
            }
        }while(bef->link != start_buffer && bef2->link != start_buffer2);
        if(bef2->link == start_buffer2){
            while(buffer != start_buffer){
                poly_pointer tmp = (poly_pointer)malloc(sizeof(poly_node));
                tmp->coef = buffer->coef;
                tmp->expon = buffer->expon;   
                d->link = tmp;
                d = tmp;
                buffer = buffer->link;
            }
        }else{
            while(buffer2 != start_buffer2){
                poly_pointer tmp = (poly_pointer)malloc(sizeof(poly_node));
                tmp->coef = buffer2->coef;
                tmp->expon = buffer2->expon;   
                d->link = tmp;
                d = tmp;
                buffer2 = buffer2->link;
            }            
        }
        d->link = start_d->link;
        d = start_d->link;
        free(start_d);
        buffer = buffer->link;
        while(buffer != start_buffer){
            poly_pointer tmp = buffer;
            buffer = buffer->link;
            free(tmp);
        }
        free(buffer);
        buffer2 = buffer2->link;
        while(buffer2 != start_buffer2){
            poly_pointer tmp = buffer2;
            buffer2 = buffer2->link;
            free(tmp); 
        }
        free(buffer2);
        return d;
    }
    
}
poly_pointer pmult(poly_pointer a, poly_pointer b, poly_pointer d){
    poly_pointer traverse_a, traverse_b;
    traverse_a = a;
    traverse_b = b;
    poly_pointer before_a=a;
    for(traverse_a ;before_a->link != a; before_a = traverse_a, traverse_a = traverse_a->link){
      // printf("%d %d\n", traverse_a->coef, traverse_a->expon);
        poly_pointer buffer = NULL, start = NULL;
        int coef_a, expon_a;
        coef_a = traverse_a->coef;
        expon_a = traverse_a->expon;
        poly_pointer before_b=b;
        for(traverse_b=b; before_b->link != b; before_b = traverse_b, traverse_b = traverse_b->link){
            int coef_b, expon_b;
            coef_b = traverse_b->coef;
            expon_b = traverse_b->expon;
            buffer = attach(coef_a, expon_a, coef_b, expon_b, &start, buffer);
        }
        buffer->link = start->link;
        buffer = start->link; 
        free(start);
        poly_pointer buffer2 = d;
        d = padd(buffer, buffer2, d);
    }
    return d;
}
void pwrite(poly_pointer d, FILE *fp3){
    poly_pointer d_start = d;
    int cnt=0;
    poly_pointer tmp = d;
    for(tmp; tmp->link != d_start; tmp=tmp->link){
        cnt++;
    }
    cnt++;
    fprintf(fp3, "%d\n", cnt);
    for(d; d->link != d_start; d=d->link){
        fprintf(fp3, "%d %d\n", d->coef, d->expon);
    }
    fprintf(fp3, "%d %d\n", d->coef, d->expon);

}
int main(){
    FILE *fp1 = fopen("a.txt", "r");
    FILE *fp2 = fopen("b.txt", "r");
    FILE *fp3 = fopen("d.txt", "w");
    poly_pointer a, b, d = NULL;
    a = mread(fp1, a);
    b = mread(fp2, b);
    d = pmult(a, b, d);
    pwrite(d,fp3);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}