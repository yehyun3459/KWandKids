#include <iostream>
using namespace std;
int N, Arr[21][21], Team[21], minn = INT32_MAX;
void dfs(int idx, int cnt) {
	if (cnt == N / 2) {
		int sum1 = 0, sum2 = 0;
		for (int i = 1; i <= N; i++) 
			for (int j = 1; j <= N; j++) {
				if (Team[i] && Team[j])
					sum1 += Arr[i][j];
				else if (!Team[i] && !Team[j]) 
					sum2 += Arr[i][j];
			}

		if (minn > abs(sum1 - sum2))
			minn = abs(sum1 - sum2);
	}
	for (int n = idx + 1; n <= N; n++) {
		Team[n] = 1;
		dfs(n, cnt + 1);
		Team[n] = 0;
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= N; j++) 
			cin >> Arr[i][j];

	for (int i = 1; i <= N / 2; i++) {
		Team[i] = 1;
		dfs(i, 1);
		Team[i] = 0;
	}		
	cout << minn;
	return 0;
}
