#include <iostream>
#include <fstream>
#include <string>
#include "symnode.cpp"
#include "symtable.cpp"

void visit(SymNode* t, string& s) {
    if (t==nullptr)
        return;
    s = s + t->key + " ";
    cout<<s.length()<<endl;
    cout<<t->key.length()<<"lllll"<<endl;
}

void inorder(SymNode* t, string& s) {
    if (t==NULL)
        return;
    inorder(t->left, s);
    visit(t, s);
    inorder(t->right, s);
}

int get_height(SymNode* t) {
    if (t == NULL)
        return -1;
    return max(get_height(t->left), get_height(t->right)) + 1;
}

bool is_balanced(SymNode* t) {
    if (t == NULL)
        return true;
    int lh = get_height(t->left);
    int rh = get_height(t->right);
    return is_balanced(t->left) && is_balanced(t->right) && (lh-rh > -2) && (lh-rh < 2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fstream ans;
    string fname = "AroyTest/ans_avl.txt";
    ans.open(fname, ios::in);
    int i = 0;
    int o = 0;
    ifstream q("AroyTest/testcase_avl.txt");
    char a;
    string b;
    string d;
    string sa;
    SymbolTable* s = new SymbolTable();
    while (q.good()) {
        q >> a;
        i++;
        if (a == '1') {
            q >> b;
            // cin >> b;
            // cout << "let me insert\n";
            s->insert(b);
            cout<<"ding dongg"<<endl;
        }
        if (a == '2') {
            q >> b;
            o++;
            getline(ans, sa);
            int c = s->search(b);
            if (c != stoi(sa)) {
                cout << "Incorrect answer " << c << " at input line " << i << " corresponding to output " << stoi(sa) << " at line " << o << "\n";
                delete s;
                break;
            }
        }
        if (a == '3') {
            q >> b;
            s->remove(b);
        }
        if (a == '4') {
            q >> b;
            q >> d;
            s->assign_address(b, stoi(d));
        }
        if (a == '5') {
            o++;
            getline(ans, sa);
            int c = s->get_size();
            if (c != stoi(sa)) {
                cout << "Incorrect answer " << c << " at input line " << i << " corresponding to output " << stoi(sa) << " at line " << o << "\n";
                delete s;
                break;
            }
        }
        if (a == '1'||a == '3') {
            o++;
            string st = "";
            inorder(s->get_root(), st);
            cout<<"print hua?"<<endl;
            getline(ans, sa);
            cout<<sa<<endl;
            cout<<"bhaika inorder "<<st<<endl;
            cout<<endl;
            cout<<"hona chahiya "<<sa;
            cout<<"iski maa ki chut";
            cout<<"fff"<<endl;
            string pingu="";
            cout<<sa.length()<<endl;
            cout<<st.length()<<endl;
            cout<<(sa==st)<<endl;
            cout<<"f0"<<endl;
            if (sa != st) {
                cout<<"f1"<<endl;
                cout << "Incorrect inorder traversal\n" << st << "\nat input line " << i << " corresponding to output\n" << sa << "\nat line " << o << "\n";
                delete s;
                break;
            }
            if (!is_balanced(s->get_root())) {
                cout<<"f2"<<endl;
                cout << "AVL tree unbalanced at input line " << i << "(output  line: " << o << ")\n";
                delete s;
                break;
            }
            cout<<"f3"<<endl;
        }
        cout << "Input line " << i << " processed successfully(output line: " << o << ")\n";
    }
    delete s;
    return 0;
}