#include <iostream>

#define DEBUG 0

using namespace std;

unsigned long long int
f(unsigned long long int a,
  unsigned long long int w,
  unsigned long long int h)
{
    return (a / h) * (a / w);
}

int
main()
{
    int w, h, n;
    if ( DEBUG ) {
        w = 1; h = 1; n = 1000000000;
    }
    else
    {
        freopen("diploma.in", "r" , stdin);
        freopen("diploma.out", "w" , stdout);
        cin >> w >> h >> n;
    }

    unsigned long long int left = 0,
                  right = 1e18,
                  mid = -1;

    while ( left < right - 1 )
    {
        unsigned long long int mid = (left + right) / 2;

        unsigned long long int f_mid = f(mid, w, h);
        //cout << f_mid << "\n";
        if ( f_mid >= n)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }

        if ( DEBUG )
            cout << left << "\t" << right << "\n";
    }

    cout << right;

    return 0;
}
