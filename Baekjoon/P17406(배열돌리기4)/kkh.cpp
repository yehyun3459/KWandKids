#include "iostream"
using namespace std;
int N, M, K, W[51][51], arr[51][51], minn = INT32_MAX;
int cul[7][3], order[7], vis[7];
void dfs(int a);
int summ();
void change();

int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> W[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		cin >> cul[i][0] >> cul[i][1] >> cul[i][2];
	}

	dfs(1);

	cout << minn;

	return 0;
}

void dfs(int a) {
	if (a > K) {

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				arr[i][j] = W[i][j];
			}
		}

		change();

		int cnt = summ();
		if (minn > cnt)
			minn = cnt;

		return;
	}

	for (int i = 1; i <= K; i++) {
		if (vis[i] == 0) {
			vis[i] = 1;
			order[a] = i;

			dfs(a + 1);

			vis[i] = 0;
		}
	}

}

int summ() {
	int anss = INT32_MAX;
	for (int i = 1; i <= N; i++) {
		int ss = 0;
		for (int j = 1; j <= M; j++) {
			ss += arr[i][j];
		}

		if (anss > ss)
			anss = ss;
	}

	return anss;
}

void change() {
	for (int i = 1; i <= K; i++) {
		int a = order[i];
		int r = cul[a][0];
		int c = cul[a][1];
		int s = cul[a][2];

		for (int j = 1; j <= s; j++) {
			int tmp = arr[r - j][c - j];

			for (int z = r - j; z < r + j; z++) {
				arr[z][c - j] = arr[z + 1][c - j];
			}

			for (int z = c - j; z < c + j; z++) {
				arr[r + j][z] = arr[r + j][z + 1];
			}

			for (int z = r + j; z > r - j; z--) {
				arr[z][c + j] = arr[z - 1][c + j];
			}

			for (int z = c + j; z > c - j; z--) {
				arr[r - j][z] = arr[r - j][z - 1];
			}

			arr[r - j][c - j + 1] = tmp;
		}
	}
}
