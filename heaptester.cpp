#include <iostream>
#include <fstream>
#include <string>
#include "minheap.cpp"
#include "heapnode.cpp"
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fstream ans;
    string fname = "ans.txt";
    ans.open(fname, ios::in);
    int i = 0;
    int o = 0;
    ifstream q("testcase.txt");
    char a;
    string b;
    string sa;
    MinHeap m = MinHeap();
    // while (cin >> a) {
    while (q.good()) {
        q >> a;
        i++;
        if (a == '1') {
            q >> b;
            // cin >> b;
            m.push_heap(stoi(b));
        }
        if (a== '2') {
            o++;
            getline(ans, sa);
            int c = m.get_min();
            if (c != stoi(sa)) {
                cout << "Incorrect answer " << c << " at input line " << i << " corresponding to output " << stoi(sa) << " at line " << o << "\n";
                break;
            }
        }
        if (a== '3') {
            m.pop();
        }
        cout << "Input line " << i <<" "<<a<< " processed correctly(output line: " << o << ")\n";
    }
}