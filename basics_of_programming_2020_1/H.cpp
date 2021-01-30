#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fot("output.txt");
    int a_max = 0, a, n;
    fin >> n;
    fin >> a_max;
    for (int i = 0; i < n - 1; i++) {
        fin >> a;
        if (a_max < a) {
            a_max = a;
        }
    }
    fot << a_max;
    return 0;
}
