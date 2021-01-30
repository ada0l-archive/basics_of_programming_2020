#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n; cin >> n;
    int a[n + 1]; a[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    int dp[n + 1]; dp[0] = 0; dp[1] = a[1];
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = max(dp[i - 2], dp[i - 1]) + a[i];
    }
    cout << dp[n];
    return 0;
}
