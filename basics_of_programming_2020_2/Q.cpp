#include <iostream>
#include <vector>
// #include <algorithm>
// #include <cmath>

#define CATS

using namespace std;

vector<int> prefix_function(string s);
int getPosition(string str, string substr);

int main() {
    freopen("input.txt", "r", stdin);
#ifdef CATS
    freopen("output.txt", "w", stdout);
#endif
    string str, substr;
    getline(cin, str);
    getline(cin, substr);
    cout << getPosition(str, substr);
    return 0;
}

vector<int> prefix_function(string s) {
    vector<int> p(s.size());
    p[0] = 0;
    int i = 1;
    int j = 0;
    while (i < s.size()) {
        if (s[i] != s[j])
            if (j == 0)
                p[i++] = 0;
            else
                j = p[j - 1];
        else
            p[i++] = ++j;
    }
    return p;
}

int getPosition(string str, string substr) {
    int k = 0;
    int l = 0;
    vector<int> p = prefix_function(substr);
    while (k < str.size()) {
        if (l == substr.size())
            return k - substr.size() + 1;
        if (str[k] == substr[l]) {
            k++; l++;
        } else {
            if (l != 0)
                l = p[l - 1];
            else
                k++;
        }
    }
    if (l == substr.size())
        return k - substr.size() + 1;

    return -1;
}
