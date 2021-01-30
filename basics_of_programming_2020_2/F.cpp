#include <iostream>
#include <vector>

#define CATS

using namespace std;

struct Soldier
{
    float height;
    string name;
};

long long int merge(Soldier *a, Soldier *b, int low, int high, int mid)
{
    long long int answer = 0;
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (a[i].height >= a[j].height)
            b[k++] = a[i++];
        else {
            b[k++] = a[j++];
            answer += mid - i + 1;
        }
    }
    while (i <= mid)    b[k++] = a[i++];
    while (j <= high)   b[k++] = a[j++];
    for (i = low; i < k; i++) a[i] = b[i];
    return answer;
}

long long int merge_sort(Soldier *a, Soldier* b, int low, int high)
{
    long long int answer = 0;
    if (low >= high)
    {
        return 0;
    }
    int mid = (low+high)/2;
    answer += merge_sort(a, b, low, mid);
    answer += merge_sort(a, b, mid+1, high);
    answer += merge(a, b, low, high, mid);
    return answer;
}

int main() {
    freopen("input.txt", "r", stdin);
#ifdef CATS
    freopen("output.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    Soldier *army = new Soldier[n];
    Soldier *buffer = new Soldier[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> army[i].height;
        cin >> army[i].name;
    }
    cout << merge_sort(army, buffer, 0, n - 1);
    return 0;
}
