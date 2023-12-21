/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
//Hello



#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    for(int i = 0;i<mem_limit;i++){
        least_mem_loc.push_heap(i);
    }
    memory_size = mem_limit;
    output_file = out_file;
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<string> res;
    for(int i = 0;i<int(code.size());i++){
        targ.parse(code[i]);
        vector<string> temp = generate_targ_commands();
        for(int j = 0;j<int(temp.size());j++){
            res.push_back(temp[j]);
        }
    }
    write_to_file(res);
}

string convert_to_string(int a){
    string res = "";
    if(a == 0){
        res = "0";return res;   
    }
    while(a>=1){
        char b = '0' + (a - (a/10)*10);
        res = b + res ;
        a/=10;
    }
    return res;
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> res;
    ExprTreeNode* root = targ.expr_trees[int(targ.expr_trees.size())-1];
    if(root->left->type == "DEL"){
        int address = targ.symtable->search(root->right->id);
        targ.symtable->remove(root->right->id);
        least_mem_loc.push_heap(address);
        string ans = convert_to_string(address);
        ans = "DEL = mem[" + ans + "]\n";
        res.push_back(ans);
    }
    else{
        ExprTreeNode* current = root->right;
        vector<ExprTreeNode* > stk;
        vector<ExprTreeNode* > p;
        stk.push_back(current);
        while(!stk.empty()){
            current = stk[int(stk.size())-1];
            stk.pop_back();
            p.push_back(current);
            if(current->right != NULL) stk.push_back(current->right);
            if(current->left != NULL) stk.push_back(current->left);
        }
        while(!p.empty()){
            current = p[int(p.size())-1];
            if(current->type == "ADD"){
                res.push_back("ADD\n");
            }
            else if(current->type == "SUB"){
                res.push_back("SUB\n");
            }
            else if(current->type == "MUL"){
                res.push_back("MUL\n");
            }
            else if(current->type == "DIV"){
                res.push_back("DIV\n");
            }
            else if(current->type == "VAL"){
                string ans = convert_to_string(current->num);
                ans = "PUSH " + ans + "\n";
                res.push_back(ans);
            }
            else if(current->type == "VAR"){
                string ans = convert_to_string(targ.symtable->search(current->id));
                ans = "PUSH mem[" + ans + "]\n";
                res.push_back(ans);
            }
            p.pop_back();
        }
        if(root->left->type == "RET"){
            res.push_back("RET = POP\n");
        }
        else{// Casual
            if(targ.symtable->search(root->left->id) == -1){
                int address = least_mem_loc.get_min();
                least_mem_loc.pop();
                targ.symtable->assign_address(root->left->id,address);
                string ans = convert_to_string(address);
                ans = "mem[" + ans + "] = POP";
                res.push_back(ans);   
            }
            else{
                string ans = convert_to_string(targ.symtable->search(root->left->id));
                ans = "mem[" + ans + "] = POP";
                res.push_back(ans);  
            }
        }
    }
    res.push_back("\n");
    return res;
}

void EPPCompiler::write_to_file(vector<string> commands) {
    std::ofstream output(output_file);
    if (output.is_open()) {
        for (int i = 0; i < int(commands.size()); i++) {
            output << commands[i];
        }
        output << endl;
        output.close();
    } else {
    }
}

EPPCompiler::~EPPCompiler(){

}
