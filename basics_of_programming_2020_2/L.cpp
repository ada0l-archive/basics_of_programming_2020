#include <iostream>

#define CATS

using namespace std;

int n;
int **dist;
char **maze;
const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

struct Point {
    int x, y;
};

struct Queue {
    Point *q;
    int head;
    int tail;
};

void push(Queue &queue, Point p) {
    queue.q[queue.tail++] = p;
}

Point pop(Queue &queue) {
    return queue.q[queue.head++];
}

bool empty(Queue &queue) {
    return queue.head == queue.tail;
}

static int bad(int x, int y) {
    return x < 0                ||
           x >= n               ||
           y < 0                ||
           y >= n               ||
           maze[y][x] != '.'    ||
           dist[y][x] != -1;
}

int bfs(int x0, int y0, int x1, int y1) {
    Queue q = { new Point[n * n], 0, 0 };
    push(q, Point{ x0, y0 });
    dist[y0][x0] = 0;
    while (!empty(q)) {
        Point p = pop(q);
        if (p.x == x1 && p.y == y1)
            return dist[p.y][p.x];
        for (int i = 0; i < 4; ++i) {
            int xx = p.x + dx[i],
                yy = p.y + dy[i];
            if (bad(xx, yy))
                continue;
            dist[yy][xx] = dist[p.y][p.x] + 1;
            push(q, Point{ xx, yy });
        }
    }
    return -1;
}


int main() {
    freopen("input.txt", "r", stdin);
#ifdef CATS
    freopen("output.txt", "w", stdout);
#endif
    int x0, y0, x1, y1;
    cin >> n >> x0 >> y0 >> x1 >> y1;
    x0--; y0--; x1--; y1--;
    maze = new char*[n];
    dist = new int*[n];
    for (int i = 0; i < n; ++i) {
        maze[i] = new char[n];
        dist[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            dist[i][j] = -1;
            maze[i][j] = s[j];
        }
    }

    cout << bfs(x0, y0, x1, y1);
    return 0;
}
