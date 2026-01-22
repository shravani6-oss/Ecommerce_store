#include <stdio.h>
#include <stdbool.h>

#define MAXQ 10000

int min(int x, int y) {
    return (x < y) ? x : y;
}

int Steps(int m, int n, int o, int d) {

    int q[MAXQ][4];      // jug1, jug2, jug3, steps
    int parent[MAXQ];   // parent index

    bool visited[m+1][n+1][o+1];

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= o; k++)
                visited[i][j][k] = false;

    int front = 0, rear = 0;

    // Initial state (8,0,0)
    q[rear][0] = m;
    q[rear][1] = 0;
    q[rear][2] = 0;
    q[rear][3] = 0;
    parent[rear] = -1;
    visited[m][0][0] = true;
    rear++;

    int goalIndex = -1;

    while (front < rear) {

        int jug1 = q[front][0];
        int jug2 = q[front][1];
        int jug3 = q[front][2];
        int steps = q[front][3];

        // Goal check
        if (jug1 == d || jug2 == d || jug3 == d) {
            goalIndex = front;
            break;
        }

        // ---------- ALL POSSIBLE MOVES ----------

        int t, nj1, nj2, nj3;

        // jug1 -> jug2
        t = min(jug1, n - jug2);
        nj1 = jug1 - t; nj2 = jug2 + t; nj3 = jug3;
        if (!visited[nj1][nj2][nj3]) {
            visited[nj1][nj2][nj3] = true;
            q[rear][0] = nj1; q[rear][1] = nj2; q[rear][2] = nj3;
            q[rear][3] = steps + 1;
            parent[rear] = front;
            rear++;
        }

        // jug2 -> jug3
        t = min(jug2, o - jug3);
        nj1 = jug1; nj2 = jug2 - t; nj3 = jug3 + t;
        if (!visited[nj1][nj2][nj3]) {
            visited[nj1][nj2][nj3] = true;
            q[rear][0] = nj1; q[rear][1] = nj2; q[rear][2] = nj3;
            q[rear][3] = steps + 1;
            parent[rear] = front;
            rear++;
        }

        // jug3 -> jug1
        t = min(jug3, m - jug1);
        nj1 = jug1 + t; nj2 = jug2; nj3 = jug3 - t;
        if (!visited[nj1][nj2][nj3]) {
            visited[nj1][nj2][nj3] = true;
            q[rear][0] = nj1; q[rear][1] = nj2; q[rear][2] = nj3;
            q[rear][3] = steps + 1;
            parent[rear] = front;
            rear++;
        }

        // Fill jug2
        if (!visited[jug1][n][jug3]) {
            visited[jug1][n][jug3] = true;
            q[rear][0] = jug1; q[rear][1] = n; q[rear][2] = jug3;
            q[rear][3] = steps + 1;
            parent[rear] = front;
            rear++;
        }

        // Empty jug2
        if (!visited[jug1][0][jug3]) {
            visited[jug1][0][jug3] = true;
            q[rear][0] = jug1; q[rear][1] = 0; q[rear][2] = jug3;
            q[rear][3] = steps + 1;
            parent[rear] = front;
            rear++;
        }

        front++;
    }

    // ---------- PRINT PATH ----------
    if (goalIndex == -1)
        return -1;

    int path[50], len = 0;
    int idx = goalIndex;

    while (idx != -1) {
        path[len++] = idx;
        idx = parent[idx];
    }

    printf("(%d, %d, %d)\n", q[path[len-1]][0], q[path[len-1]][1], q[path[len-1]][2]);

    for (int i = len-2, step = 1; i >= 0; i--, step++) {
        printf("%d\t(%d, %d, %d)\n",
               step,
               q[path[i]][0],
               q[path[i]][1],
               q[path[i]][2]);
    }

    return q[goalIndex][3];
}

int main() {

    int m = 8, n = 5, o = 3, d = 4;

    int result = Steps(m, n, o, d);

    printf("\nMinimum steps = %d\n", result);

    return 0;
}
