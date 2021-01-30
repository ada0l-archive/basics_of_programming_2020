#include <iostream>
#include <cmath>

using namespace std;

struct Point{
    long double x, y;
};

int get_a_quarter_plane(Point A) {
    if (A.x > 0 && A.y > 0) {
        return 1;
    } else if (A.x < 0 && A.y > 0) {
        return 2;
    } else if (A.x < 0 && A.y < 0) {
        return 3;
    } else if (A.x > 0 && A.y < 0) {
        return 4;
    }
    return 0;
}

int main() {
    Point A;

    cin >> A.x >> A.y;

    long double e = 1e-16;

    if (abs(A.x) < e) {
        A.x = 0;
    }

    if (abs(A.y) < e) {
        A.y = 0;
    }

    cout << get_a_quarter_plane(A);

    return 0;
}
