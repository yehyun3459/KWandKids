#include <iostream>
using namespace std;
int N, M, robot[3], Map[51][51], isvis[51][51], cnt;
int change_dir[4] = { 3,0,1,2 }, my[4] = { -1,0,1,0 }, mx[4] = { 0,1,0,-1 };
int main() {
	cin >> N >> M;
	cin >> robot[0] >> robot[1] >> robot[2];
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++)
			cin >> Map[i][j];		
	
	while (1) {
		isvis[robot[0]][robot[1]] = 1; //청소한곳 체크
		int search_left = change_dir[robot[2]]; //왼쪽으로 회전
		int next_y = robot[0] + my[search_left];
		int next_x = robot[1] + mx[search_left];
		if (!Map[next_y][next_x] && !isvis[next_y][next_x]) 
			robot[0] = next_y, robot[1] = next_x, robot[2] = search_left;
		else {
			bool b_flag = true;
			for (int i = 0; i < 3; i++) { //다른 방향 체크, 돌면서 3방향 다
				search_left = change_dir[search_left];
				next_y = robot[0] + my[search_left];
				next_x = robot[1] + mx[search_left];
				if (!Map[next_y][next_x] && !isvis[next_y][next_x]) { //청소할곳 체크
					robot[0] = next_y, robot[1] = next_x, robot[2] = search_left;
					b_flag = false;
					break;
				}
			}

			if (b_flag) { //청소할곳이 없을때 왼쪽으로 두번 돌아서 후진
				search_left = change_dir[search_left];
				search_left = change_dir[search_left];
				next_y = robot[0] + my[search_left];
				next_x = robot[1] + mx[search_left];

				if (!Map[next_y][next_x]) //후진 못하면 루프 탈출
					robot[0] = next_y, robot[1] = next_x;
				else 
					break;
			}	
		}
	}	
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			if (isvis[i][j]) 
				cnt++;	
    
	cout << cnt;
	return 0;
}
