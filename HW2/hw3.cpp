#include <iostream>
#include <string.h>
using namespace std;

class Student{
private:
    char last_name[50];
    char first_name[50];
public:
    Student(){
        strcpy(last_name, "");
        strcpy(first_name, "");
    }
    void allocate(char * n_l, char * n_f){
        strcpy(last_name, n_l);
        strcpy(first_name, n_f);
    }
    bool compare(Student s){
        if(!strcmp(this->last_name, s.last_name)){
            return (strcmp(this->first_name, s.first_name) > 0) ? false : true;
        }
        else
            return (strcmp(this->last_name, s.last_name) > 0) ? false : true;
    }
    void print(){
        cout << last_name << " ";
        cout << first_name << endl;
    }
    void copy(Student *tmp){
        strcpy(this->last_name, "");
        strcpy(this->first_name, "");
        strcpy(this->last_name, tmp->last_name);
        strcpy(this->first_name, tmp->first_name);
    }
};
void parse(char * name, char *n_f, char *n_l){
    int i=0;
    int j=0;

    int len = strlen(name);
    while(name[i] != ' '){
        n_f[i] = name[i];
        i++;
        n_f[i] = '\0';
    }
    i+=1;
    while(i < len)
        n_l[j++] = name[i++];
    n_l[j] = '\0';
}
void selection_sort(Student * p, int num){
    for(int i=0; i<num; i++){
        Student *tmp = &p[i];
        for(int j=i+1; j<num; j++){
            if(!(tmp->compare(p[j]))){
                tmp = &p[j];
            }
        }
        if(tmp != &p[i]){
            Student * ttmp = new Student;
            ttmp->copy(tmp);
            tmp->copy(&p[i]);
            p[i].copy(ttmp);
        }
    }
}
int main(){
    FILE * fp1 = fopen("student.txt", "r");
    if( fp1 == NULL ){                                                         
        return -1;   
    }
    char n[5];
    fgets(n, 5, fp1);
    int num = (*n - 48);
    Student * p = new Student[num];
    char buffer_name[101];
    char buffer_last_name[50];
    char buffer_first_name[50];
    for(int i=0; i<num; i++){
        fgets(buffer_name, 100, fp1);
        int len = strlen(buffer_name);
        if(buffer_name[len-1] == '\n')
           buffer_name[len-1] = '\0';
        parse(buffer_name, buffer_last_name, buffer_first_name);
        p[i].allocate(buffer_last_name, buffer_first_name);
        
        for(int i=0; i<101;i++)
            buffer_name[i] = '\0';
        for(int i=0; i<50; i++){
            buffer_last_name[i] = '\0';
            buffer_first_name[i] = '\0';
        }
    }
    selection_sort(p, num);
    for(int i=0; i<num; i++){
        p[i].print();
    }

    fclose(fp1);
    return 0;
}