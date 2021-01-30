#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fot("output.txt");
    int n, i, j;
    fin >> n;
    int a[n];
    for (i = 0; i < n; i++) {
        fin >> a[i];
    }
    bool flag;
    for (i = 0; i < n; i++) {
        flag = 1;
        for (j = 0; j < n; j++) {
            if (a[j] % a[i] != 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            fot << a[i];
            return 0;
        }
    }

    fot << -1;

    return 0;
}
