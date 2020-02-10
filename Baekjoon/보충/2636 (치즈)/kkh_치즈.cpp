#include <iostream>
#include <cstring>
using namespace std;
int Y, X, summ, cheeze[100][100], isvisit[100][100], xx[4] = { 1, -1, 0, 0 }, yy[4] = { 0, 0, 1, -1 };
void dfs(int y, int x) {
    isvisit[y][x] = 1;
    if (cheeze[y][x] == 1) {
        cheeze[y][x] = 0;
        summ--;
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (!isvisit[y + yy[i]][x + xx[i]] && y + yy[i] >= 0 && y + yy[i] < Y && x + xx[i] >= 0 && x + xx[i] < X)
            dfs(y + yy[i], x + xx[i]);
    }
 }
 
int main() {
    cin >> Y >> X;
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++) {
            cin >> cheeze[i][j];
            summ += cheeze[i][j];
        }
    for (int i = 1; ; i++) {
        int tmp_sum = summ;
        dfs(0, 0);
        memset(isvisit, 0, sizeof(isvisit));
        if (!summ) {
            cout << i << "\n" << tmp_sum;
            exit(0);
        }
    }
    return 0;
}
