#include <iostream>
using namespace std;
int R, C, T, room[51][51], air, move_y[4] = { 0,0,-1,1 }, move_x[4] = { 1,-1,0,0 }, summ;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> room[i][j]; //미세먼지 정보 저장
			if (room[i][j] == -1) //공기청정기 위치 저장 (air, air-1)
				air = i;
		}
	}

	for (int t = 1; t <= T; t++) {//시간 만큼 반복문
		int tmp_room[51][51] = { 0 }; //미세먼지 분산을 위한 임시 배열
		for (int y = 1; y <= R; y++) 
			for (int x = 1; x <= C; x++) {		
				if (room[y][x] < 1) continue; 
				int tmp = room[y][x] / 5; 
				for (int j = 0; j < 4; j++) {
					int tmp_y = y + move_y[j], tmp_x = x + move_x[j];
					if (tmp_y > 0 && tmp_y <= R && tmp_x > 0 && tmp_x <= C && room[tmp_y][tmp_x] != -1) {
						tmp_room[tmp_y][tmp_x] += tmp; //분산되는 먼지는 임시 배열에 저장
						room[y][x] -= tmp; //분산되는 만큼 차감
					}
				}
			}

		for (int y = 1; y <= R; y++) {
			for (int x = 1; x <= C; x++) {
				if (room[y][x] == -1)	continue;
				room[y][x] += tmp_room[y][x]; //분산되었던 먼지량과 합산
			}
		}
		//위쪽 반시계반향 먼지이동
		for (int i = air - 2; i > 1; i--) 	room[i][1] = room[i - 1][1];
		for (int i = 1; i < C; i++) 		room[1][i] = room[1][i + 1];
		for (int i = 1; i < air - 1; i++) 	room[i][C] = room[i + 1][C];
		for (int i = C; i > 2; i--)			room[air - 1][i] = room[air - 1][i - 1];
		room[air - 1][2] = 0;
		
		//아래쪽 시계방향 먼지이동
		for (int i = air + 1; i < R; i++) 	room[i][1] = room[i + 1][1];
		for (int i = 1; i < C; i++) 		room[R][i] = room[R][i + 1];
		for (int i = R; i > air; i--) 		room[i][C] = room[i - 1][C];
		for (int i = C; i > 2; i--) 		room[air][i] = room[air][i - 1];
		room[air][2] = 0;	
	}

	for (int i = 1; i <= R; i++) //최종 먼지 합산
		for (int j = 1; j <= C; j++)
			if (room[i][j] > 0) 			summ += room[i][j];

	cout << summ;

	return 0;
}
