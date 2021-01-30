#include <iostream>

#define CATS
//#define n 100

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
#ifdef CATS
    freopen("output.txt", "w", stdout);
#endif
    int n = 100;
    int ***a = new int**[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int *[n];
        for (int j = 0; j < n; ++j) {
            a[i][j] = new int[n];
            for (int k = 0; k < n; ++k) {
                a[i][j][k] = 0;
            }
        }
    }
    int n_commands, command, x, y, z, x1, y1, z1, value, answer;
    cin >> n_commands;
    for (int i = 0; i < n_commands; ++i) {
        cin >> command;
        if (command == 1) {
            cin >> x >> y >> z >> value;
            a[x - 1][y - 1][z - 1] = value;
        } else {
            cin >> x >> y >> z >> x1 >> y1 >> z1;
            answer = 0;
            for (int i = x - 1; i < x1; i++) {
                for (int j = y - 1; j < y1; ++j) {
                    for (int k = z - 1; k < z1; ++k) {
                        answer += a[i][j][k];
                    }
                }
            }
            cout << answer << "\n";
        }
    }
    return 0;
}
