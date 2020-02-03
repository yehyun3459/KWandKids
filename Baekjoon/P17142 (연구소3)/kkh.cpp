#include "iostream"
#include "cstring"
#include "queue"
using namespace std;
int N, M, nCnt_vir, Arr[50][50], isvis[50][50], virus[10][2], activeVir[10], move_x[4] = { 1, -1, 0 ,0 }, move_y[4] = { 0, 0, 1, -1 }, minn = INT32_MAX;
void dfs() {
	memset(isvis, 0, sizeof(isvis));
	queue<pair<int, int> > q;
	for (int i = 0; i < nCnt_vir; i++) {
		if (activeVir[i]) {
			q.push({ virus[i][0], virus[i][1] });
			isvis[virus[i][0]][virus[i][1]] = 1;
		}
	}

	while (!q.empty()) {
		int yy = q.front().first, xx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			if (yy + move_y[i] >= N || yy + move_y[i] < 0 || xx + move_x[i] >= N || xx + move_x[i] < 0)
				continue;
			if (Arr[yy + move_y[i]][xx + move_x[i]] == 1 || isvis[yy + move_y[i]][xx + move_x[i]])
				continue;
			isvis[yy + move_y[i]][xx + move_x[i]] = isvis[yy][xx] + 1;
			q.push({ yy + move_y[i] , xx + move_x[i] });
		}
	}
	int maxx = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (!Arr[i][j]) {
				if (isvis[i][j])
					maxx = maxx < isvis[i][j] ? isvis[i][j] : maxx;
				else
					return;
			}

	if (minn > maxx - 1)
		minn = maxx - 1;
}

void activeVirus(int past, int cnt) {
	if (cnt >= M) {
		dfs();
		return;
	}
	for (int i = past + 1; i <= nCnt_vir - M + cnt; i++) {
		activeVir[i] = 1;
		activeVirus(i, cnt + 1);
		activeVir[i] = 0;
	}
}

int main() {
	iostream::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> Arr[i][j];
			if (Arr[i][j] == 2) {
				virus[nCnt_vir][0] = i;
				virus[nCnt_vir++][1] = j;
			}
		}

	for (int i = 0; i <= nCnt_vir - M; i++) {
		activeVir[i] = 1;
		activeVirus(i, 1);
		activeVir[i] = 0;
	}

	if (minn == INT32_MAX)
		cout << -1;
	else if (minn == -1)
		cout << 0;
	else
		cout << minn;
	return 0;
}