#include <iostream>

#define CATS

using namespace std;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };

struct Person {
    int x;
    int y;
    int dir;
};

bool bad(char **maze, int n, int x, int y) {
    return x < 0 || x >= n ||
           y < 0 || y >= n ||
           maze[y][x] != '.';
}

bool found(Person f, Person s) {
    return (f.x == s.x && f.y == s.y) ||
           (f.x == s.x - dx[s.dir] && f.y == s.y - dy[s.dir] &&
            s.x == f.x - dx[f.dir] && s.y == f.y - dy[f.dir]);
}

int get_steps(char **maze, bool **dist, int n, Person f, Person s) {
    int x1, y1, x2, y2, steps = 0;
    for (int i = 0; i < 1000; ++i) {
        x1 = f.x + dx[f.dir];
        y1 = f.y + dy[f.dir];
        x2 = s.x + dx[s.dir];
        y2 = s.y + dy[s.dir];

        if (bad(maze, n, x1, y1)) {
            f.dir += 1;
            f.dir %= 4;
        } else {
            f.x = x1;
            f.y = y1;
        }

        if (bad(maze, n, x2, y2)) {
            s.dir -= 1;
            s.dir += 4;
            s.dir %= 4;
        } else {
            s.x = x2;
            s.y = y2;
        }
        steps++;
        if (found(f, s)) {
            return steps;
        }
    }
    return -1;
}

int main() {
    freopen("input.txt", "r", stdin);
#ifdef CATS
    freopen("output.txt", "w", stdout);
#endif
    Person f, s;
    bool **dist;
    char **maze;
    int n;
    cin >> n >> f.x >> f.y >> f.dir >> s.x >> s.y >>
    s.dir;
    f.x--;
    f.y--;
    f.dir--;
    s.x--;
    s.y--;
    s.dir--;
    maze = new char *[n];
    for (int i = 0; i < n; i++) {
        maze[i] = new char[n];
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            maze[i][j] = s[j];
        }
    }

    cout << get_steps(maze, dist, n, f, s);
    return 0;
}
