#include <iostream>

using namespace std;

int n, m;
char **maze;
const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

bool bad(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= m;
}

void dfs(int x, int y) {
    if (maze[x][y] == '.')
        return;
    for (int i = 0; i < 4; ++i) {
        int xx = x + dx[i],
            yy = y + dy[i];
        if (bad(xx, yy))
            continue;
        if (maze[xx][yy] == '.')
            return;
    }
    maze[x][y] = '*';
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    maze = new char*[n];
    for (int i = 0; i < n; ++i)
        maze[i] = new char[m];
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j)
            maze[i][j] = s[j];
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dfs(i, j);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (maze[i][j] == '*')
                maze[i][j] = '.';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << maze[i][j];
        cout << "\n";
    }
    return 0;
}
