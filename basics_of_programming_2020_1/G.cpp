#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fot("output.txt");
    int sum = 0, a, n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> a;
        sum += a;
    }
    fot << sum;
    return 0;
}
