#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n; cin >> n; int a[n]; int dp[n + 1];
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (a[i] < a[j])
            {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
    dp[0] = 0;
    dp[1] = a[1] - a[0];
    if (n > 2)
    {
        dp[2] = a[2] - a[0];
    }
    for (int i = 3; i < n; ++i)
    {
        dp[i] = min(dp[i - 1], dp[i - 2]) + a[i] - a[i - 1];
    }
    cout << dp[n - 1];
    return 0;
}
