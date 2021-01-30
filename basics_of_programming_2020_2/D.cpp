#include <iostream>

using namespace std;

struct Soldier
{
    float height;
    string name;
};

int n = 0;

void merge(Soldier *a, Soldier *b, int low, int high, int mid)
{
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (a[i].height >= a[j].height) {
            b[k++] = a[i++];
        }
        else {
            b[k++] = a[j++];
            ++n;
        }
    }
    while (i <= mid)    b[k++] = a[i++];
    while (j <= high)   b[k++] = a[j++];
    for (i = low; i < k; i++) a[i] = b[i];
}

void merge_sort(Soldier *a, Soldier* b, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(a, b, low, mid);
        merge_sort(a, b, mid + 1, high);
        merge(a, b, low, high, mid);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    Soldier *army = new Soldier[n];
    Soldier *buffer = new Soldier[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> army[i].height;
        cin >> army[i].name;
    }
    merge_sort(army, buffer, 0, n - 1);
    cout << n;
    return 0;
}
