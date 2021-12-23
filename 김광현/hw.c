#include <stdio.h>
#include <string.h>

int field[50][50], m, n;

int find(int x, int y) {
    field[x][y] = 0;

    if (x + 1 < m && field[x + 1][y] == 1) find(x + 1, y);
    if (x - 1 >= 0 && field[x - 1][y] == 1) find(x - 1, y);
    if (y + 1 < n && field[x][y + 1] == 1) find(x, y + 1);
    if (y - 1 >= 0 && field[x][y - 1] == 1) find(x, y - 1);
    return 0;
}

int main() {
    int testnum;
    int k, x, y, wcnt;
    scanf("%d", &testnum);
    while (testnum--) {
        memset(field, 0, sizeof(field));
        scanf("%d %d %d", &m, &n, &k);

        while (k--) {
            scanf("%d %d", &x, &y);
            field[x][y] = 1;
        }
        wcnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (field[i][j] == 1) {
                    find(i, j);
                    wcnt++;
                }
            }
        }
        printf("%d\n", wcnt);
    }
    return 0;
}
