/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #include<iostream>
// using namespace std;


#include "minheap.h"

//Write your code below this line
int log2(int n) {
    int result = 0;
    while (n >>= 1) {
        result++;
    }
    return result;
}

MinHeap::MinHeap(){
    size = 0;
    root = NULL;
}

int isone(int n,int i){
    n = n>>i;
    if((n & 1) == 1){return 1;}
    return 0;
}

void MinHeap::push_heap(int num){
    HeapNode* node = new HeapNode(num);
    if(size == 0){
        root = node;
        size = 1;
        // this->traverse(root);
        return;
    }
    int n = size+1;
    HeapNode* current = root;
    for(int i = log2(n)-1;i>0;i--){
        if (isone(n,i)){
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    if(isone(n,0)){
        current->right = node;current->right->par = current;current = current->right;
    }
    else{
        current->left = node;current->left->par = current;current = current->left;
    }
    while(current->par!= NULL){
        if(current->val < current->par->val){
            int temp = current->val;
            current->val = current->par->val;
            current->par->val = temp;
            current = current->par;
        }
        else break;
    }
    size++;
    // this->traverse(root);
}

int MinHeap::get_min(){
    if(root!= NULL){
        return root->val;
    }
    else return -2;
}

void swapper(HeapNode* a,HeapNode* b){
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void MinHeap::pop(){
    if(size<1){return;}
    if(size == 1){
        delete root;
        root = NULL;
        size = 0;
        // this->traverse(root);
        return;
    }
    int n = size;
    HeapNode* current = root;
    for(int i = log2(n)-1;i>=0;i--){//Traversal 
        if (isone(n,i)){current = current->right;}
        else {current = current->left;}
    }
    int temp = 0;
    temp = current->val;
    current->val = root->val;
    root->val = temp;
    if(current == current->par->left){current->par->left = NULL;}
    else if(current == current->par->right){current->par->right = NULL;}
    delete current;
    current = root;
    while(current != NULL){
        HeapNode* smallest = current;
        HeapNode* leftChild = current->left;
        HeapNode* rightChild = current->right;
        HeapNode* future;
        if (leftChild != NULL && leftChild->val < smallest->val) {
            smallest = leftChild;future = leftChild;
        }
        if (rightChild != NULL && rightChild->val < smallest->val) {
            smallest = rightChild;future = rightChild;
        }
        if (smallest != current) {
            int temp = current->val;
            current->val = smallest->val;
            smallest->val = temp;
            current = future;
        }
        else{break;}
    }
    size--;
    // this->traverse(root);
}


MinHeap::~MinHeap(){
    if(root!=NULL) delete root;
}

// int main(){
//     MinHeap* gojo = new MinHeap;
//     // gojo->push_heap(3);
//     // cout<<gojo->get_min()<<endl;
//     // gojo->pop();
//     // cout<<gojo->get_min()<<endl;
//     gojo->push_heap(4);
//     gojo->push_heap(3);
//     gojo->push_heap(7);
//     gojo->push_heap(2);
//     gojo->push_heap(9);
//     gojo->push_heap(11);
//     gojo->push_heap(1);
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
//     cout<<gojo->get_min()<<endl;
//     gojo->pop();
// }

//Logic for insertion in node ; 
/* Insertion at end : //I need location to put next element i.e.
Insert at 4 : 100 left -> left;
    n
  n   n
n
Insert at 5 : 101 left ->right;
    n
  n   n
n  n
Insert at 6 : 110 right ->left;
    n
  n   n
n  n n
Insert at 7 : 111 right ->right;
    n
  n   n
n  n n  n
Insert at 8 : 1000 left->left->left;
        n
      n   n
    n  n n  n
   n
*/
