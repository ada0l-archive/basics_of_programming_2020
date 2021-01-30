#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> all;
int n = 3, k = n;

void permutations_rec(int *a, int p) {
    if (p >= n) {
        vector<int> tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp[i] = a[i];
        }
        all.push_back(tmp);
        return;
    }
    for (int i = 0; i < k; ++i) {
        bool found = false;
        for (int j = 0; j < p && !found; ++j) {
            if (a[j] == i) {
                found = true;
            }
        }
        if (!found) {
            a[p] = i;
            permutations_rec(a, p + 1);
        }
    }
}

char get_number(char *number, int i)
{
    return number[i + 1];
}

char get_char(char *number, int i)
{
    int index;
    if (i == 0) index = 0;
    if (i == 1) index = 4;
    if (i == 2) index = 5;
    return number[index];
}


int main(int argc, char *argv[]) {
    freopen("number.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int *a = new int[n];
    permutations_rec(a, 0);

    int n = 6;
    char number[n];
    for (int i = 0; i < n; ++i) { cin >> number[i]; }
    cout << all.size() << "\n";
    for (int i = 0; i < all.size(); ++i) {
        for (int j = 0; j < all.size(); ++j) {
            // all[i] -- char
            // all[j] -- number
            cout << get_char(number, all[i][0]);
            cout << get_number(number, all[j][0]);
            cout << get_number(number, all[j][1]);
            cout << get_number(number, all[j][2]);
            cout << get_char(number, all[i][1]);
            cout << get_char(number, all[i][2]);
            cout << "\n";
        }
    }

    return 0;
}
