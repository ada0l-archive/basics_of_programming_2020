#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fot("output.txt");
    int a, b;

    fin >> a >> b;
    if ((a + b - 1) % 4 == 0)
        fot << a + b - 1;
    else
        fot << 0;

    return 0;
}
