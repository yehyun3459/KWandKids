#include<iostream>
using namespace std;

bool key[501][501] = { {0, }, }; // j 가 i q보다 작아
bool v[501] = { 0, }; // 탐색 시 방문 확인용

void dfs(int idx, int N, int& cnt) { // 나보다 큰 사람 탐색
	v[idx] = 1;
	cnt++;
	for (int i = 1; i <= N; i++)
		if (key[idx][i] && !v[i])
			dfs(i, N, cnt);
}
void dfs_back(int idx, int N, int & cnt) { // 나보다 작은 사람 탐색
	v[idx] = 1;
	cnt++;
	for (int i = 1; i <= N; i++)
		if (key[i][idx] && !v[i])
			dfs_back(i, N, cnt);
}
bool search(int idx, int N) { // 키 순서 확정 가능하면 1, 아니면 0
	int cnt = 0;
	v[idx] = 1;
	for (int i = 1; i <= N; i++)
		if (key[idx][i] && !v[i]) // 나보다 큰 사람이면 그 사람보다 큰 사람도 나보다 커
			dfs(i, N, cnt);
	
	for (int i = 1; i <= N; i++)
		if (key[i][idx] && !v[i]) // 나보다 작은 사람이면 그 사람보다 작은 사람도 나보다 작아
			dfs_back(i, N, cnt);

	//cout << "idx : " << idx << ", cnt : " << cnt << endl;
	if (cnt == N - 1) // 나보다 크거나 작은 사람이 N-1이면 나의 키 순서를 확정할 수 있다.
		return 1;
	else 
		return 0;
}


int main() {
	int N, M;
	cin >> N;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int s, l;
		cin >> s >> l;
		key[s][l] = 1;
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) { // 각 사람에 대해
		for (int i = 0; i <= N; i++)
			v[i] = 0;
		if(search(i, N)) // 키 순서 확정 가능하지 검사
			ans++;
	}

	cout << ans;

	return 0;
}