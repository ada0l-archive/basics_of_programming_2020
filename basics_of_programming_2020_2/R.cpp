#include <iostream>
#include <vector>
// #include <algorithm>
// #include <cmath>

#define CATS
#define SIZE 1000000

using namespace std;

struct Set {
    static const int NONE = -1;
    int *table;
    int capacity;
    int size { 0 };

    Set(int c) : capacity(c) {
        table = new int[c];
        for (int i = 0; i < c; ++i) {
            table[i] = -1;
        }
    }

    int f(int a, int b) {
        return a % b;
    }

    int get_index(int value) {
        int i = f(value, capacity);
        while (true) {
            if (table[i] == value) {
                return i;
            }
            if (table[i] == NONE) {
                return NONE;
            }
            i = (i + 1) % capacity;
        }
    }

    void del(int value) {
        int index = get_index(value);
        if (index != NONE) {
            table[index] = NONE;
        }
    }

    void add(int value) {
        if (size >= capacity)
            return;
        int i = f(value, capacity);
        while (true) {
            if (table[i] == value) {
                return;
            }
            if (table[i] == NONE) {
                table[i] = value;
                ++size;
                return;
            }
            i = (i + 1) % capacity;
        }
    }

    vector<int> get_vector() {
        vector<int> a;
        for (int i = 0; i < capacity; ++i) {
            if (table[i] != NONE) {
                a.push_back(table[i]);
            }
        }
        return a;
    }
};

void swap(vector<int> &a, int i, int j) {
    if (i != j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

void qs_r(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int i = l, j = r, p = a[(l + r) / 2];
    while (i <= j) {
        while (a[i] < p)    i++;
        while (a[j] > p)    j--;
        if (i >= j)         break;
        swap(a, i++, j--);
    }
    qs_r(a, l, j);
    qs_r(a, j + 1, r);
}

void qs(vector<int> &a) {
    qs_r(a, 0, a.size() - 1);
}

int main() {
    freopen("input.txt", "r", stdin);
#ifdef CATS
    freopen("output.txt", "w", stdout);
#endif
    Set s(SIZE);
    int x;
    cin >> x;
    while (x != 0) {
        if (x > 0)
            s.add(x);
        else
            s.del(-x);
        cin >> x;
    }
    vector<int> a = s.get_vector();
    qs(a);
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << " ";
    }
    return 0;
}
