#include<stdio.h>
#include<iostream>
#include<string.h>

#define MAX 300
using namespace std;

int n, m;
int ice_num = 0;
int ans = 0;
int map[MAX][MAX];
int map2[MAX][MAX];
int visited[MAX][MAX];

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

void check_island(int x, int y) {
	map2[x][y] = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
			if (map2[nx][ny] != 0) {
				check_island(nx, ny);
			}
		}
	}
}

void melt_ice(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
			if (map[nx][ny] == 0) {
				map2[x][y]++;
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] != 0) {
				ice_num++;
			}
		}
	}

	int year = 0;
	while (ice_num > 0) {
		//printf("---------------%d---------------\n", ice_num);
		for (int i = 0; i < n; i++) {
			memset(visited[i], 0, sizeof(int)*m);
			memset(map2[i], 0, sizeof(int)*m);
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != 0) {
					melt_ice(i, j);
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				map[i][j] -= map2[i][j];
				if (map[i][j] < 0) {
					map[i][j] = 0;
				}
				map2[i][j] = map[i][j];
			}
		}

		int cnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map2[i][j] != 0) {
					check_island(i, j);
					cnt++;
				}
			}
		}
		year++;

		if (cnt >= 2) {
			ans = year;
			break;
		}

		int tmp = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != 0) {
					tmp++;
				}
			}
		}
		ice_num = tmp;
		
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
		*/
		//break;
	}

	printf("%d\n", ans);
	system("pause");
	return 0;
}