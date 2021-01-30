#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;


int main()
{
    float f;
    cin >> f;
    int f_int = *(int *) &f;

    f_int >>= 23;
    f_int &= ((1 << 8) - 1);

    if (f_int == 0) {
        cout << -126;
        return 0;
    }

    cout << f_int - 127;

    return 0;
}

