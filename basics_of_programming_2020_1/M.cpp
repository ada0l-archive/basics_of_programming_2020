//
// Created by andrey on 21.10.2020.
//

#include <iostream>
#include <fstream>

using namespace std;


int main() {
    ifstream fin("input.txt");
    ofstream fot("output.txt");
    int x,
        total = 0;
    fin >> x;

    while (x > 0) {
        total += x % 2;
        x /= 2;
    }

    fot << total;

    return 0;
}