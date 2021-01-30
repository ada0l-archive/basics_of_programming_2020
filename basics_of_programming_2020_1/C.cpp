#include <iostream>

using namespace std;

int main() {
    int a;
    cin >> a;
    if (a % 5 == 0 && a % 3 == 0) {
        cout << "FizzBuzz";
    } else {
        if (a % 5 == 0) {
            cout << "Buzz";
        } else if (a % 3 == 0) {
            cout << "Fizz";
        } else {
            cout << "\n";
        }
    }
    return 0;
}
