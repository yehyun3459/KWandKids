#include<stdio.h>
#include<vector>
#include<iostream>

#define MAX 12
#define CHESS_MAX 10
using namespace std;

struct circle
{
	int x, y, dir;
};

int n, k;
int map[MAX][MAX];				//입력받을 맵을 저장
vector<int> map_state[MAX][MAX]; //좌표에 들어있는 맵의 상태 ex)map_state[0][0]={1,2,}; ->0index가 가장 아래
circle cir[CHESS_MAX];

int dx[] = { 0,0,-1,1 }; //right left up down
int dy[] = { 1,-1,0,0 };

int find_delete_num(int x, int y, int num) {
	int cnt = 0;
	for (int i = map_state[x][y].size() - 1; i >= 0; i--) {
		if (map_state[x][y][i] == num)
			break;
		cnt++;
	}
	return cnt + 1;
}

void move_circle(int x, int y, int nx, int ny, int num, int pos, int status) {

	//printf("\n%d %d %d %d %d %d %d\n", x, y, nx, ny, num, pos, status);
	//4.조건에 맞춰 원판말 이동
	if (status == 0) {
		for (int i = pos; i < map_state[x][y].size(); i++) {
			map_state[nx][ny].push_back(map_state[x][y][i]);
			int temp = map_state[x][y][i];
			cir[temp].x = nx;
			cir[temp].y = ny;
		}
		int del = find_delete_num(x, y, num);
		for (int i = 0; i < del; i++) {
			map_state[x][y].pop_back();
		}
	}
	else if (status == 1) {
		for (int i = map_state[x][y].size() - 1; i >= pos; i--) {
			map_state[nx][ny].push_back(map_state[x][y][i]);
			int temp = map_state[x][y][i];
			cir[temp].x = nx;
			cir[temp].y = ny;
		}
		int del = find_delete_num(x, y, num);
		for (int i = 0; i < del; i++) {
			map_state[x][y].pop_back();
		}
	}
	else if (status == 2) {
		int dir = cir[num].dir;
		if (dir == 0) dir = 1;
		else if (dir == 1) dir = 0;
		else if (dir == 2) dir = 3;
		else if (dir == 3) dir = 2;

		cir[num].dir = dir;
		int nnx = x + dx[dir];
		int nny = y + dy[dir];

		if (nnx >= 0 && nny >= 0 && nnx < n&&nny < n) {
			if (map[nnx][nny] != 2) move_circle(x, y, nnx, nny, num, pos, map[nnx][nny]);
		}

	}
}

int find_position(int x, int y, int id) {
	//3. 해당 말이 몇 번째에 위치하는지 return
	for (int i = 0; i < map_state[x][y].size(); i++) {
		if (map_state[x][y][i] == id)
			return i;
	}
}

int main() {
	//1.입력 받기
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 0; i < k; i++) {
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);
		x--; y--; d--;
		cir[i] = { x,y,d };
		map_state[x][y].push_back(i);
	}

	//2. 원판 조건성립할 때까지 이동
	bool flag = false;
	int round = 0;
	while (true) {
		if (round > 1000) break;
		//printf("%d\n", round);
		for (int i = 0; i < k; i++) {
			int x = cir[i].x;
			int y = cir[i].y;
			int dir = cir[i].dir;

			int nx = x + dx[dir];
			int ny = y + dy[dir];

			int pos = find_position(x, y, i);

			if (nx >= 0 && ny >= 0 && nx < n&&ny < n) {
				move_circle(x, y, nx, ny, i, pos, map[nx][ny]);
			}
			else {
				move_circle(x, y, nx, ny, i, pos, 2);
			}

			//5. 상태 확인후 종료할 수 있으면 종료
			bool check = false;
			for (int i = 0; i < k; i++) {
				int x = cir[i].x;
				int y = cir[i].y;
				if (map_state[x][y].size() >= 4) check = true;
			}
			if (check == true) {
				flag = true;
				break;
			}
		}
		if (flag == true)
			break;
		round++;
		//printf("===========================================\n");
	}

	//6. 출력
	if (flag == true) {
		printf("%d", round + 1);
	}
	else {
		printf("%d", -1);
	}

	//system("pause");
	return 0;
}