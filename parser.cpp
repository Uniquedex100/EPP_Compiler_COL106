/* Do NOT add/remove any includes statements from this header file */
// /* unless EXPLICTLY clarified on Piazza. */
// #include<iostream>
// using namespace std;


#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

// void traverse(ExprTreeNode* root){
//     if(root == NULL){
//         // cout<<"Null"<<endl;
//     }
//     else{
//         // cout<<root->type<<endl;
//         // cout<<"went left"<<endl;
//         traverse(root->left);
//         // cout<<"went right"<<endl;
//         traverse(root->right);
//         // cout<<"went up"<<endl;
//     } 
// }

void Parser::parse(vector<string> expression){
    // cout<<"inside parse"<<endl;
    ExprTreeNode* root = new ExprTreeNode("UltimateEqual",-1);
    expr_trees.push_back(root);
    // _______________________________________________________________
    ExprTreeNode* fleft = new ExprTreeNode("VAR",-1);
    fleft->id = expression[0];
    root->left = fleft;
    vector<ExprTreeNode*> parent;
    parent.push_back(root);
    ExprTreeNode* current = root;
    for(int i = 2;i<int(expression.size());i++){
        if(expression[i] == "("){
            ExprTreeNode* temp = new ExprTreeNode();
            if(current->left == NULL || current->type == "equal"){
                current->left = temp;
                current = current->left;
                // cout<<"went left"<<code[i]<<endl;
            }
            else {
                current->right = temp;
                current = current->right;
                // cout<<"went right"<<code[i]<<endl;
            }
            parent.push_back(current);
        }
        else if(expression[i] == ")"){
            // cout<<current->type<<endl;
            parent.pop_back();
            current = parent[int(parent.size())-1];
            // cout<<"went up"<<code[i]<<endl;
            // cout<<current->type<<endl;
        }
        else if(expression[i] == "+"){
            current->type = "ADD";
            // cout<<"added add"<<code[i]<<endl;
        }
        else if(expression[i] == "-"){
            current->type = "SUB";
            // cout<<"added sub"<<code[i]<<endl;
        }
        else if(expression[i] == "*"){
            current->type = "MUL";
            // cout<<"added mul"<<code[i]<<endl;
        }
        else if(expression[i] == "/"){
            current->type = "DIV";
            // cout<<"added div"<<code[i]<<endl;
        }
        else if(int(expression[i][0])=='-'){
            ExprTreeNode* node = new ExprTreeNode("VAL",stoi(expression[i]));
            if(current->left == NULL){
                current->left = node;
            }
            else {
                current->right = node;
            }
        }
        else if(int(expression[i][0])<=57 && int(expression[i][0]>=48)){
            ExprTreeNode* node = new ExprTreeNode("VAL",stoi(expression[i]));
            if(current->left == NULL){
                current->left = node;
            }
            else {
                current->right = node;
            }
        }
        else {
            ExprTreeNode* node = new ExprTreeNode("VAR",-1);
            node->id = expression[i];
            if(current->left == NULL){
                current->left = node;
            }
            else current->right = node;
        }
    }
    if(expression[0] == "ret"){
        root->left->type = "RET";
    }
    else if(expression[0] == "del"){
        root->left->type = "DEL";
    }
    else{
        symtable->insert(expression[0]);
    }
    // cout<<"Traverse : "<<endl;
    // traverse(root);
}



Parser::~Parser(){
    for(int i = 0;i<int(expr_trees.size());i++){
        delete expr_trees[i];
    }
    // cout<<"Parser destructor got called"<<endl;
}