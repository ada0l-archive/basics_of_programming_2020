#include <iostream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int l, d, c;
    cin >> l >> d >> c;
    if (l % d == 0)
    {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < (l / d + 2); ++i)
    {
        if (d * (l / d + 1 - i) + i * c <= l)
        {
            cout << i;
            return 0;
        }
    }
    cout << -1;
    return 0;
}
