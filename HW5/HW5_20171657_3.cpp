#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;
typedef struct node *treePointer;
typedef struct node{
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
};
template<class T>
class BST{
private:
    T root=NULL;
public:
    BST(){
    }
    ~BST(){
        // needs revise
        free(root);
    }
    T search(T root, int num){
        T parent = root;
        if(root == NULL){
            return NULL;
        }
        while(root != NULL){
            parent = root;
            if(num == root->key){
                return NULL;
            }
            else if(num < root->key){
                root = root->leftChild;
            }
            else{
                root = root->rightChild;
            }
        }
        return parent;
    }
    void push(int num){
        T temp = search(root, num);
        if(temp || !root){
            T ptr = (T)malloc(sizeof(node));
            ptr->key = num;
            ptr->leftChild=NULL;
            ptr->rightChild=NULL;
            if(root){
                if(num < temp->key){
                    temp->leftChild = ptr;
                    ptr->parent = temp;
                }
                else {
                    temp->rightChild = ptr;
                    ptr->parent = temp;
                }
            }
            else{
                root = ptr;
                root->parent = root;
            }
            cout << "Push " << num << endl;
        }
        else{
            cout << "Exist number\n";
        }
    }
    void top(){
        T traverse = root;
        while(1){
            if(!traverse->rightChild){
                break;
            }
            else
                traverse = traverse->rightChild;
        }
        cout << "The top is " << traverse->key << endl;
    }
    void pop(){
        if(root == NULL){
            cout << "The queue is empty\n";
            return;
        }
        int num;
        T traverse = root;
        T Parent = traverse;
        while(1){
            Parent = traverse->parent;
            if(!traverse->rightChild){
                break;
            }
            else{
                traverse = traverse->rightChild;
            }
        }
        num = traverse->key;
        if(traverse->leftChild){
            T parent = traverse;
            T traverse2 = traverse->leftChild;
            while(1){
                parent = traverse2->parent;
                if(!traverse2->rightChild){
                    break;
                }
                else
                    traverse2 = traverse2->rightChild;
            }
            traverse->key = traverse2->key;
            /*if(traverse2->leftChild)
                parent->rightChild = traverse2->leftChild;
            else   
                parent->leftChild = NULL;*/
            if(traverse == parent){
                parent->leftChild = traverse2->leftChild;
                if(traverse2->leftChild)
                    traverse2->leftChild->parent = parent;
            }
            else{
                parent->rightChild = traverse2->leftChild;
                if(traverse2->leftChild)
                    traverse2->leftChild->parent = parent;
            }

            free(traverse2);
        }
        else{
            Parent->rightChild = NULL;
            if(traverse == root){
                root = NULL;
            }
            else
                free(traverse);
        }
        cout << "Pop " << num << endl;
    }
};
int main(){
    BST<treePointer> Tree;
    while(1){
        string str;
        getline(cin, str);
        stringstream ss(str);
        string first, second;
        ss >> first >> second;
        if(first.compare("q")==0){
            break;
        }
        else if(first.compare("push")==0){
            Tree.push(atoi((char*)second.c_str()));
        }
        else if(first.compare("top")==0){
            Tree.top();
        }
        else if(first.compare("pop")==0){
            Tree.pop();
        }
    }

    return 0;
}