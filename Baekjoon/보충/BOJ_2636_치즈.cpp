#include<stdio.h>
#include<iostream>
#include<vector>
#include<string.h>

#define MAX 100
using namespace std;

int n, m;
int map[MAX][MAX];
int map_air[MAX][MAX];
int visited[MAX][MAX];
int cheeze_num=0;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

void delete_cheeze(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < n&&ny >= 0 && ny < m) {
			if (map_air[nx][ny] == 1) {
				map[x][y] = 0;
				//cheeze_num--;
			}
		}

	}
}

void make_air(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
			if (visited[nx][ny] == 0 && map[nx][ny] == 0) {
				map_air[nx][ny] = 1;
				visited[nx][ny] = 1;
				make_air(nx, ny);
			}
		}
		
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				cheeze_num++;
			}
		}
	}

	int time = 0;
	int cnt = 0;
	//for(int i=0;i<5;i++)
	while (cheeze_num > 0){
		//printf("\n-------------%d----------------\n",cheeze_num);
		for (int i = 0; i < n; i++) {
			memset(map_air[i], 0, sizeof(int)*m);
			memset(visited[i], 0, sizeof(int)*m);
		}
		
		map_air[0][0] = 1;
		visited[0][0] = 1;
		
		make_air(0, 0);
		
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", map_air[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
		*/
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 1) {
					delete_cheeze(i, j);
				}
			}
		}
		
		int temp=0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if(map[i][j]==1) temp++;
			}
		}
		cheeze_num = temp;

		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
		*/
		time++;
		if (temp > 0) {
			cnt = temp;
		}
	}
	
	printf("%d\n%d\n", time, cnt);
	//system("pause");
	return 0;
}
