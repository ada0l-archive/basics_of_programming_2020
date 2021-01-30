//
// Created by andrey on 21.10.2020.
//
#include <iostream>
#include <bitset>

using namespace std;


int get_mask(int start, int end) {
    return ((1 << (end - start + 1)) - 1) << (start - 1);
}

int get_int_from_bites_of_int(int x, int start, int end) {
    return (x & get_mask(start, end));
}

int main() {
    int x;
    cin >> x;
    char c;
    cin >> c;

    if (c == 'b') {
        cout << get_int_from_bites_of_int(x, 1, 8);
    } else if (c == 'g') {
        cout << get_int_from_bites_of_int(x, 9, 16);
    } else if (c == 'r') {
        cout << get_int_from_bites_of_int(x, 17, 24);
    }
    return 0;
}

/*
111111111111111111111111
000000000110010000000000
011001000110010001100100
|------||------||------|
222222221111111100000000

 */
