#include <iostream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, max = 0, x, sum = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        if (x > max)
        {
            max = x;
        }
        sum += x;
    }
    cout << sum - max;
    return 0;
}
