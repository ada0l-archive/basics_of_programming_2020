#include <iostream>
#include <stdio.h>

using namespace std;

void swap(int *a, int i, int j)
{
    if (a[i] != a[j])
    {
        int tmp = a[j];
        a[j] = a[i];
        a[i] = tmp;
    }
}

void bubble_sort(int *a, int *b, int n)
{
    bool flag;
    do
    {
        flag = true;
        for (int i = 1; i < n; ++i)
        {
            if (a[i - 1] < a[i])
            {
                swap(a, i - 1, i);
                swap(b, i - 1, i);
                flag = false;
            }
        }
    }
    while (!flag);
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int n;
    cin >> n;
    int *a = new int[n];
    int *b = new int[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        b[i] = i + 1;
    }

    bubble_sort(a, b, n);

    for (int i = 0; i < n; ++i)
    {
        cout << b[i] << " ";
    }

    return 0;
}
