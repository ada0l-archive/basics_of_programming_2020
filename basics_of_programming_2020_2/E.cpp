#include <iostream>

using namespace std;

int partition(int *a, int l, int r)
{
    int pivot = a[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j)
    {
        while (a[i] < pivot)    i++;
        while (a[j] > pivot)    j--;
        if (i >= j)             break;
        swap(a[i++], a[j--]);
    }
    return j;
}

void findK(int *a, int l, int r, int k)
{
    if (l < r)
    {
        int q = partition(a, l, r);
        if (k > q) {
            findK(a, q + 1, r, k);
        } else {
            findK(a, l, q, k);
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    cin >> n >> k;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    findK(a, 0, n - 1, k - 1);
    cout << a[k - 1];
    return 0;
}
