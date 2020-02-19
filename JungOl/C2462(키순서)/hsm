#include<stdio.h>
#include<iostream>
#include<cstring>

using namespace std;

int map[501][501];
int map2[501][501];
int visited[501];
int visited2[501];
int cnt, ans, n, m;

void dfs(int x) {
	cnt++;
	visited[x] = 1;
	for (int i = 1; i <= n; i++) {
		if (!visited[i] && map[x][i]) {
			dfs(i);
		}
	}
}

void dfs2(int x) {
	cnt++;
	visited2[x] = 1;
	for (int i = 1; i <= n; i++) {
		if (!visited2[i] && map2[x][i]) {
			dfs2(i);
		}
	}
}
int main() {
	memset(map, 0, sizeof(map));
	memset(map2, 0, sizeof(map2));

	scanf("%d", &n); scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		map[a][b] = 1;
		map2[b][a] = 1;
	}

	ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(visited, 0, sizeof(visited));
		memset(visited2, 0, sizeof(visited2));
		cnt = 0;
		dfs(i); 
		dfs2(i);
		if (cnt == n + 1) {
			ans++;
		}
	}
	printf("%d\n", ans);
	//system("pause");
	return 0;
}
