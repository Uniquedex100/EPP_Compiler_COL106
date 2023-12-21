// #include<iostream>
// using namespace std;
#include "symtable.h"

// void traverse(SymNode* root){
//     if(root == NULL){
//     }
//     else{
//         cout<<root->key<<endl;
//         traverse(root->left);
//         traverse(root->right);
//     } 
// }
SymbolTable::SymbolTable(){
    size = 0; //main thing b size, because ocrwbe we do need a root right?
    root = NULL;
}

//leaf nodes have a height of 0;
//NULL values have a height of -1;
int balanceFactor(SymNode* node){
    if(node == NULL){return 0;}
    else if(node->left == NULL && node->right == NULL){
        return 0;
    }
    else if (node->left == NULL){
        return -1 * (node->right->height+1);
    }
    else if(node->right == NULL){
        return 1* (node->left->height+1);
    }
    else return node->left->height - node->right->height;
}
void updateheighter(SymNode* node){
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

SymNode* bal(SymNode* current){
    if(balanceFactor(current)>1){
        if(balanceFactor(current->left)>=0){
            return current->LeftLeftRotation();
        }
        else return current->LeftRightRotation();
    }
    else if(balanceFactor(current)<-1){
        if(balanceFactor(current->right)<=0){
            return current->RightRightRotation();
        }
        else return current->RightLeftRotation();
    }
    return current;
}
SymNode* inserter(string k, SymNode* current){
    if(current == NULL){return new SymNode(k);}
    else if(k<current->key){
        if(current->left == NULL){
            current->left = new SymNode(k);
        } 
        else{
            current->left = inserter(k,current->left);
        } 
    }
    else if(k>current->key){
        if(current->right == NULL){
            current->right = new SymNode(k);
        }
        else{
            current->right = inserter(k,current->right);
        } 
    }
    updateheighter(current);
    current = bal(current);
    return current;
}
void SymbolTable::insert(string k){
    this->root = inserter(k,this->root);
    size++;
}

SymNode* remover(string k, SymNode* current){
    if(k<current->key){
        current->left = remover(k,current->left);
    }
    else if(k>current->key){
        current->right = remover(k,current->right);
    }
    else{
        if(current->left == NULL && current->right == NULL){
            delete current;return NULL;
        }
        else if(current->left == NULL){
            SymNode* temp = current->right;
            delete current;return temp;
        }
        else if(current->right == NULL){
            SymNode* temp = current->left;
            delete current;return temp;
        }
        else{
            SymNode* successor = current->right;
            while(successor->left!=NULL){successor = successor->left;}
            string temp = current->key;current->key = successor->key;
            successor->key = temp;
            int idx = current->address;current->address = successor->address;
            successor->address = idx;
            current->right = remover(temp,current->right);
        }
    }
    updateheighter(current);
    current = bal(current);
    return current;
}
void SymbolTable::remove(string k){
    root = remover(k,root);
    size--;
}


int searcher(string k, SymNode* current){
    if(current == NULL){return -1;}
    else if(k == current->key){return current->address;}
    else if(k < current->key){return searcher(k,current->left);}
    else if(k > current->key){return searcher(k,current->right);}
    return 0;
}
int SymbolTable::search(string k){
    return searcher(k,root);
}

void assigner(string k,int idx, SymNode* current){
    if(current == NULL){}
    else if(k == current->key){current->address = idx;}
    else if(k < current->key){assigner(k,idx,current->left);}
    else if(k > current->key){assigner(k,idx,current->right);}
}
void SymbolTable::assign_address(string k,int idx){
    assigner(k,idx,root);
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void destroy(SymNode* current){
    if(current == NULL){return;}
    destroy(current->left);
    destroy(current->right);
    delete current;
}
SymbolTable::~SymbolTable(){
    destroy(root);
}



// int main(){
//     cout<<"Started : "<<endl;
//     SymbolTable* gojo = new SymbolTable();
//     gojo->insert("a");gojo->assign_address("a",10);
//     cout <<"Ignore : " << gojo->search("a") <<endl;
//     gojo->insert("b");gojo->assign_address("b",11);
//     cout << "Ignore : "<< gojo->search("b") <<endl;
//     gojo->insert("c");gojo->assign_address("c",12);
//     cout << "Ignore : "<< gojo->search("c") <<endl;
//     gojo->insert("d");gojo->assign_address("d",13);
//     cout << "Ignore : "<< gojo->search("d") <<endl;
//     gojo->insert("e");gojo->assign_address("e",14);
//     cout << "Ignore : "<< gojo->search("e") <<endl;
//     traverse(gojo->get_root());
//     gojo->remove("a");
//     gojo->remove("b");
//     gojo->remove("c");
//     gojo->insert("f");gojo->assign_address("f",15);
//     cout << "Ignore : "<< gojo->search("f") <<endl;
//     gojo->insert("g");gojo->assign_address("g",16);
//     cout << "Ignore : "<< gojo->search("g") <<endl;
//     gojo->insert("h");gojo->assign_address("h",17);
//     cout << "Ignore : "<< gojo->search("h") <<endl;
//     gojo->insert("i");gojo->assign_address("i",18);
//     cout << "Ignore : "<< gojo->search("i") <<endl;
//     gojo->insert("j");gojo->assign_address("j",19);
//     cout << "Ignore : "<< gojo->search("j") <<endl;
//     traverse(gojo->get_root());
// }

/*
        S
    i       t
 h     p

*/
