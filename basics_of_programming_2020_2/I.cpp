#include <iostream>
#include <cmath>

using namespace std;

struct Tree {

private:

    long long int *t, none;
    int size, n;

    void push(int v) {
        if (t[v] == none)
            return;
        t[v * 2 + 1] = t[v];
        t[v * 2 + 2] = [v];
        t[v] = none;
    }

    void update(int v, int tl, int tr, int l, int r, long long int value) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            this->t[v] = value;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        update(v * 2 + 1, tl, tm, l, min(r, tm), value);
        update(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r, value);
    }

    long long int sum(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr && this->t[v] != this->none)
            return (r - l + 1) * this->t[v];
        push(v);
        int tm = (tl + tr) / 2;
        long long int answer = 0;
        if (v * 2 + 1 < size)
            answer += sum(v * 2 + 1, tl, tm, l, min(tm, r));
        if (v * 2 + 2 < size)
            answer += sum(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return answer;
    }

public:

    Tree(int n, int none) {
        this->n = n;
        this->size = 4 * n;
        this->t = (long long int*) malloc(size * sizeof(long long int));
        this->none = none;
        for (int i = 0; i < this->size; ++i)
            t[i] = this->none;
    }

    void update(int l, int r, long long int value) {
        update(0, 0, this->n - 1 , l - 1, r - 1, value);
    }

    long long int sum(int l, int r) {
        return sum(0, 0, this->n - 1, l - 1, r - 1);
    }
};

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    Tree *tree = new Tree(n, -1);
    int l, r;
    long long int x;
    char command;
    for (int i = 0; i < k; ++i) {
        std::cin >> command;
        if (command == 'A') {
            std::cin >> l >> r >> x;
            tree->update(l, r, x);
        } else if (command == 'Q') {
            cin >> l >> r;
            std::cout << tree->sum(l, r);
            if (i != k -1) {
                std::cout << "\n";
            }
        }
    }
    return 0;
}
