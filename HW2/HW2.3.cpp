#include <iostream>
using namespace std;

class Student{
private:
    char last_name[50];
    char first_name[50];
public:
    Student(){
        //strcpy(last_name, "");
        //strcpy(first_name, "");
        init_str(last_name);
        init_str(first_name);
    }
    void init_str(char * name){
        name[0] = '\0';
    }
    void replace_strcpy(char *str1, char * str2){
        int i=0;
        while(1){
            if(str2[i] == '\0'){
                break;
            }
            str1[i] = str2[i];
            i++;
        }
        str1[i] = '\0';
    }
    int replace_strcmp(char *str1, char *str2){
        int len1 = replace_strlen(str1);
        int len2 = replace_strlen(str2);
        if (len1 >= len2){
            int i=0;
            while(1){
                if(str2[i] == '\0'){
                    if(str1[i] == '\0')
                        return 0;
                    else
                        return 1;
                }
                if(str1[i] == str2[i]){
                    i++;
                }
                else if(str1[i] > str2[i]){
                    if(str1[i] >= 97 && str2[i] <= 90 && str2[i] >= 65){ //str1은 소문자, str2는 대문자
                        if(str1[i] >= str2[i] + 32)
                            return 1;
                        else return -1;
                    }
                    return 1;
                }
                else{
                    if(str2[i] >= 97 && str1[i] <= 90 && str1[i] >= 65){ 
                        if(str2[i] >= str1[i] + 32)
                            return -1;
                        else return 1;
                    }
                    return -1;
                }
            }
        }
        else{
            int i=0;
            while(1){
                if(str1[i] == '\0'){
                    return -1;
                }
                if(str2[i] == str1[i]){
                    i++;
                }
                else if(str2[i] > str1[i]){
                    if(str2[i] >= 97 && str1[i] <= 90 && str1[i] >= 65){ //str1은 소문자, str2는 대문자
                        if(str2[i] >= str1[i] + 32)
                            return -1;
                        else return 1;
                    }
                    return -1;
                }
                else{
                    if(str1[i] >= 97 && str2[i] <= 90 && str2[i] >= 65){ //str1은 소문자, str2는 대문자
                        if(str1[i] >= str2[i] + 32)
                            return 1;
                        else return -1;
                    }
                    return 1;
                }
            }
        }

    }
    int replace_strlen(char * str){
        int i=0;
        int cnt=0;
        while(1){
            if(str[i++] == '\0'){
                break;
            }
            cnt++;
        }
        return cnt;
    }
    void allocate(char * n_l, char * n_f){
        //strcpy(last_name, n_l);
        //strcpy(first_name, n_f);
        replace_strcpy(last_name, n_l);
        replace_strcpy(first_name, n_f);
    }
    bool compare(Student s){
        if(!replace_strcmp(this->last_name, s.last_name)){
            return (replace_strcmp(this->first_name, s.first_name) > 0) ? false : true;
        }
        else
            return (replace_strcmp(this->last_name, s.last_name) > 0) ? false : true;
    }
    void print(){
        cout << last_name << " ";
        cout << first_name << endl;
    }
    void copy(Student *tmp){
        init_str(this->last_name);
        init_str(this->first_name);
        replace_strcpy(this->last_name, tmp->last_name);
        replace_strcpy(this->first_name, tmp->first_name);
    }
};

int replace_str(char * buffer_name){
    int i=0;
    int cnt=0;
    while(1){
        if(buffer_name[i] < 32){
            break;
        }
        i++;
        cnt++;
    }
    return cnt;
}
void parse(char * name, char *n_f, char *n_l){
    int i=0;
    int j=0;

    //int len = strlen(name);
    int len = replace_str(name);
    while(name[i] != ' '){
        if(i < len){
            n_f[i] = name[i];
            i++;
            n_f[i] = '\0';
        }
        if(i == len){
            n_l[0] = '\0';
            return;
        }
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
    int num=0;
    int mul=0;
    for (int i=0;i<5;i++){
        int tmp = n[i];
        if(tmp == '\n' || tmp == 0){
            break;
        }
        else{
            if(i> 0)
                mul = 10;
            num *= mul;
            num += (tmp-48);
        }
    }

    Student * p = new Student[num];
    char buffer_name[101];
    char buffer_last_name[50];
    char buffer_first_name[50];
    for(int i=0; i<num; i++){
        fgets(buffer_name, 100, fp1);
        int len = replace_str(buffer_name);
        //printf("%d\n", len);
        //if(buffer_name[len-1] == '\n')
        buffer_name[len] = '\0';
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