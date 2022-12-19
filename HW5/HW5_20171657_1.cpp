#include <iostream>
#include <stdlib.h>
#include <sstream>
#define MIN -10000000
using namespace std;
typedef struct node *treePointer;
typedef struct node{
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
};
template<class T>
class MaxHeap{
private:
    T root;
public:
    MaxHeap(){
        root = (T)malloc(sizeof(node));
        root->leftChild = NULL;
        root->rightChild = NULL;
        root->parent = root;
        root->key = MIN;
    }
    ~MaxHeap(){
        // needs revise
        free(root);
    }
    bool found(T root, int key){
       // printf("root key %d %d\n", root->key, key);
        if(root != NULL){
            if(root->key == key){
              //  printf("here\n");
                return true;
            }
            bool tmp1=false, tmp2=false;
            if(root->leftChild)
                tmp1 = found(root->leftChild, key);
            if(root->rightChild)
                tmp2 = found(root->rightChild, key);
            return tmp1 || tmp2;
        }
    }
    void insertHeap(char *num){
        int key = atoi(num);
        if(!found(root, key)){
            if(!root->leftChild && !root->rightChild && (root->key == MIN)){
                root -> key = key;
            }
            else{
                T traverse = root;
                T parent = root;
                bool flag = false;
                while(!traverse){
                    parent = traverse;
                    if(!traverse->rightChild){
                        if(!traverse->leftChild)
                            break;
                        //traverse = traverse->leftChild;
                        else{
                            flag = true;
                            break;
                        }
                    }
                    else{
                        traverse = traverse->rightChild;
                    }
                }
                traverse = (T)malloc(sizeof(node));
                traverse->leftChild = NULL;
                traverse->rightChild = NULL;
                traverse->parent = parent;
                traverse->key = key;
                if(flag)
                    parent->rightChild = traverse;
                else
                    parent->leftChild = traverse;

                T tmp = traverse;
                while(tmp != root){
                    if(tmp->key > parent->key){
                        int tmp_key = tmp->key;
                        tmp->key = parent->key;
                        parent->key = tmp_key;
                    }
                    tmp = tmp->parent;
                }
                //cout << "Insert " << key << '\n';
            }
            cout << "Insert " << key << '\n';
        }
        else{
            cout << "Exist Number\n";
        }
    }
    void deleteHeap(char *num){
        if(root->key == MIN){
            cout << "The heap is empty\n";
            return;
        }
        cout << "Delete " <<  root->key << endl;
        T traverse = root;
        T parent = root;
        bool flag = false;
        while(1){
            parent = traverse;
            if(!traverse->rightChild){
                if(!traverse->leftChild)
                    break;
                //traverse = traverse->leftChild;
                else{
                    flag = true;
                    break;
                }
            }
            else{
                traverse = traverse->rightChild;
            }
        }
        if(flag){
            // leftNode 와 switch
            traverse = traverse->leftChild;
            root->key = traverse->key;
            parent->leftChild = NULL;
        }
        else{
            // 현재 노드와 switch
            root->key = traverse->key;
            parent->rightChild= NULL;
        }
        if(traverse == root){
            traverse->key = MIN;
            return;
        }
        free(traverse);   
        T temp = root;
        while(temp->leftChild && temp->rightChild){
            if(temp->leftChild->key < temp->rightChild->key){
                int temp_key = temp->rightChild->key;
                temp->rightChild->key = temp->key;
                temp->key = temp_key;
                temp = temp->rightChild;
            }
            else{
                int temp_key = temp->leftChild->key;
                temp->leftChild->key = temp->key;
                temp->key = temp_key;
                temp = temp->leftChild;                
            }
        }
        if(temp->leftChild){
            if(temp->leftChild->key > temp->key){
                int temp_key = temp->key;
                temp->key = temp->leftChild->key;
                temp->leftChild->key = temp_key;
            }
        }

    }
};

int main(){
    MaxHeap<treePointer> Tree;
    while(1){
        string str;
        getline(cin, str);
        stringstream ss(str); // 초기화 -> ss에 str을 대입
        string first, second;
        ss >> first >> second;  
       // cout << first << " " << second << endl;
        if(first.compare("q")==0)
            break;
        if(first.compare("i")==0){
            Tree.insertHeap((char*)second.c_str());
        }
        else if(first.compare("d")==0){
            Tree.deleteHeap((char*)second.c_str());
        }
    }
    return 0;
}
/*
i 4
i 4
i 5
d
d
d
i 3
q
*/