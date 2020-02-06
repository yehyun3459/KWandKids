#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>

#define MAX 50
using namespace std;

int n, m, ans=-1;
int map[MAX][MAX]; //¹Ù´Ù:0, À°Áö:1
//int map2[MAX][MAX];
int visited[MAX][MAX];

int dx[] = { 0,0,-1,1 };
int dy[] = { 1,-1,0,0 };

int main() {
	scanf("%d %d", &n, &m);
	queue<pair<int, int>> start;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char t;
			scanf(" %c", &t);
			if (t == 'W') {
				map[i][j] = 0; //¹Ù´Ù
			}
			else if (t == 'L') {
				map[i][j] = 1; //À°Áö
				start.push(make_pair(i, j));
			}
		}
	}

	while (!start.empty()) {
		int x = start.front().first;
		int y = start.front().second;
		start.pop();

		for (int i = 0; i < n; i++) {
			memset(visited[i], 0, sizeof(int)*m);
		}

		visited[x][y] = 1;
		queue<pair<int, int>> q;
		q.push(make_pair(x, y));

		/*
		printf("------------(%d,%d)---------------\n",x,y);
		printf("before\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", visited[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		*/

		while (!q.empty()) {
			int xx = q.front().first;
			int yy = q.front().second;
			q.pop();
			if (visited[xx][yy] == 0) {
				visited[xx][yy] = 1;
			}
			for (int i = 0; i < 4; i++) {
				int nx = xx + dx[i];
				int ny = yy + dy[i];

				if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
					if (map[nx][ny] == 0) {
						continue;
					}
					if (visited[nx][ny] == 0 || visited[nx][ny] > visited[xx][yy] + 1) {
						visited[nx][ny] = visited[xx][yy] + 1;
						q.push(make_pair(nx, ny));
					}
				}
			}
		}

		/*
		printf("after\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", visited[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		*/


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (visited[i][j] != 0) {
					ans = (ans < visited[i][j]) ? visited[i][j] : ans;
				}
			}
		}
	}
	

	printf("%d\n", ans-1);

	//system("pause");
	return 0;
}