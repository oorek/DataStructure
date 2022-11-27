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
int N;
int arr[30];
bool check[10000];
template<class T>
class BST{
public:
    T root = NULL;
    BST(){
    }
    ~BST(){
        // needs revise
        free(root);
    }
    int find_pivot(int start, int end){
        for(int i=start+1;i<=end;i++){
            if(arr[start] < arr[i])
                return i-1;
        }
        return end;
    }
    void make_bst(int start, int end, T parent, bool flag){
        if(start < end){
            int pivot = find_pivot(start, end);
            T tmp = (T)malloc(sizeof(node));
            tmp->leftChild = NULL;
            tmp->rightChild = NULL;
            tmp->key = arr[start];
            if(root == NULL){
                root = tmp;
                root->parent = root;
            }
            else if(flag == true){
                tmp->parent = parent;
                parent->leftChild = tmp;
            }
            else{
                tmp->parent = parent;
                parent->rightChild = tmp;                
            }

            make_bst(start+1, pivot, tmp, true);
            make_bst(pivot+1, end, tmp, false);
        }
        else if(start == end){
            T tmp = (T)malloc(sizeof(node));
            tmp->leftChild = NULL;
            tmp->rightChild = NULL;
            tmp->key = arr[start];
            if(flag){
                parent->leftChild = tmp;
                tmp->parent = parent;
            }
            else{
                parent->rightChild = tmp;
                tmp->parent = parent;
            }
        }    
    }
    void inorder(T tmp){
        if(tmp){
            inorder(tmp->leftChild);
            cout << tmp->key << " ";
            inorder(tmp->rightChild);
        }
    }
    void postorder(T tmp){
        if(tmp){
            postorder(tmp->leftChild);
            postorder(tmp->rightChild);
            cout << tmp->key << " ";
        }
    }

};
int main(){
    cin >> N;
    bool flag= false;
    for(int i=0;i<10000;i++){
        check[i] = false;
    }
    for(int i=0;i<N;i++){
        cin >> arr[i];
        if(check[arr[i]] == true){
            flag = true;
        }
        check[arr[i]] = true;

    }
    if(flag){
        cout << "cannot construct BST\n";
        return 0;
    }
    BST<treePointer> Tree;
    Tree.make_bst(0, N-1, NULL, true);
    cout << "Inorder: ";
    Tree.inorder(Tree.root);
    cout << endl;
    cout << "Postorder: ";
    Tree.postorder(Tree.root);
    cout << endl;
    return 0;
}