#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<vector>

#define MAX 50
using namespace std;

int n, l, r;
int map[MAX][MAX]; //ÀÎ±¸¼ö
int visited[MAX][MAX];

int cnt, sum;
int dx[] = { 0,0,-1,1 };
int dy[] = { 1,-1,0,0 };

vector<pair<int, int>> v;

bool condition(int nx, int ny, int x, int y) {
	int t = map[nx][ny] - map[x][y];
	if (t < 0) t *= -1;
	if (t >= l && t <= r) {
		return true;
	}
	else {
		return false;
	}
}

void find_people(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
			if (visited[nx][ny] == 0) {
				if (condition(nx, ny, x, y)) {
					visited[nx][ny] = 1;
					v.push_back(make_pair(nx, ny));
					sum += map[nx][ny];
					cnt++;
					//printf("sum: %d, cnt: %d\n", sum, cnt);
					find_people(nx, ny);
				}
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &n, &l, &r);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}


	int ans = 0;

	while (1){

		/*
		printf("------------%d-------------\n",ans);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		*/

		for (int i = 0; i < n; i++) {
			memset(visited[i], 0, sizeof(int)*n);
		}
		bool change = false;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j] == 0) {
					visited[i][j] = 1;
					sum = map[i][j];
					cnt = 1;
					v.clear();
					//printf("sum: %d, cnt: %d\n", sum, cnt);
					v.push_back(make_pair(i, j));
					
					find_people(i, j);
					
					if (cnt >= 2) {
						change = true;
						for (int k = 0; k < v.size(); k++) {
							map[v[k].first][v[k].second] = int(sum / cnt);
						}
					}
				}
			}
		}
		if (change) {
			ans++;
		}
		else {
			break;
		}
	}

	printf("%d\n", ans);
	//system("pause");
	return 0;
}