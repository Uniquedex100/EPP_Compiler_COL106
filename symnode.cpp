/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

// #include<iostream> 
// using namespace std;


#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key = "NullKey";
    height = 0;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
}

void updateheight(SymNode* node){
    if(node == NULL){return;}
    else if(node->left == NULL && node->right == NULL){
        node->height = 0;
    }
    else if(node->left == NULL){
        node->height = node->right->height + 1;
    }
    else if(node->right == NULL){
        node->height = node->left->height + 1;
    }
    else node->height = max(node->left->height,node->right->height) + 1;
}

SymNode* SymNode::LeftLeftRotation(){
    // cout<<"leftleftrotation called"<<endl;
    if(this == NULL) return this;
    if(this->left == NULL) return this;
    SymNode* a = this;
    SymNode* b = this->left;
    SymNode* t2 = b->right;
    SymNode* p = this->par;
    b->par = p;
    b->right = a; //
    a->par = b;
    a->left = t2; //
    if(t2 != NULL) t2->par = a;
    updateheight(a);
    updateheight(b);
    return b;
}

SymNode* SymNode::RightRightRotation(){
    // cout<<"rightrightrotation called"<<endl;
    if(this == NULL) return this;
    if(this->right == NULL) return this;
    SymNode* a = this;
    SymNode* b = this->right;
    SymNode* t2 = b->left;
    SymNode* p = this->par;
    b->par = p;
    b->left = a; //
    a->par = b;
    a->right = t2; //
    if(t2 != NULL) t2->par = a;
    updateheight(a);
    updateheight(b);
    return b;
}

SymNode* SymNode::LeftRightRotation(){
    // cout<<"LeftRightRotation called"<<endl;
    if(this == NULL) return this;
    if(this->left == NULL) return this;
    this->left = this->left->RightRightRotation();
    // cout<<"leftleftrotation called"<<endl;
    SymNode* a = this;
    SymNode* b = this->left;
    SymNode* t2 = b->right;
    SymNode* p = this->par;
    b->par = p;
    b->right = a; //
    a->par = b;
    a->left = t2; //
    if(t2 != NULL) t2->par = a;
    updateheight(a);
    updateheight(b);
    return b;
}

SymNode* SymNode::RightLeftRotation(){
    // cout<<"RightLeftRotation called"<<endl;
    if(this == NULL) return this;
    if(this->right == NULL) return this;
    this->right = this->right->LeftLeftRotation();
    // cout<<"rightrightrotation called"<<endl;
    SymNode* a = this;
    SymNode* b = this->right;
    SymNode* t2 = b->left;
    SymNode* p = this->par;
    b->par = p;
    b->left = a; //
    a->par = b;
    a->right = t2; //
    if(t2 != NULL) t2->par = a;
    updateheight(a);
    updateheight(b);
    return b;
}

SymNode::~SymNode(){
}