#include <iostream>
using namespace std;
int R, C, M, shark[10001][6], move_y[5] = { 0, -1, 1, 0, 0 }, move_x[5] = { 0, 0, 0, 1, -1 }, res;
int AA[101][101];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 5; j++)
			cin >> shark[i][j]; // y,x,속력, 이동방향, 크기
		AA[shark[i][0]][shark[i][1]] = i;//상어 위치 좌표 인덱스로 표시
	}

	for (int cnt = 1; cnt <= C; cnt++) {
		int minn = 101, idx = 0;
		for (int j = 1; j <= M; j++) {
			if (shark[j][1] == cnt) {//현재 낚시왕 위치중 최소 y값 구하기
				if (minn > shark[j][0]) {
					minn = shark[j][0];
					idx = j;
				}
			}
		}

		if (minn < 101) {
			AA[shark[idx][0]][shark[idx][1]] = 0; //잡 상어 맵에서 제거
			shark[idx][0] = 0; //잡은 상어 x, y값 0으로 표시
			shark[idx][1] = 0;
			res += shark[idx][4]; //잡은 상어 크기 추가
		}

		for (int i = 1; i <= M; i++) {
			int tmp_y = shark[i][0], tmp_x = shark[i][1];
			if (!tmp_y)	continue; //잡거나 죽은 상어일경우 넘기기
			AA[tmp_y][tmp_x] = 0; //현재 상어 위치 임시로 없앰
			if (shark[i][3] == 1) { //위로 움직일때
				shark[i][0] += (move_y[shark[i][3]] * shark[i][2]);
				if (shark[i][0] < 1) {
					shark[i][0]--;
					int tmp_div = abs(shark[i][0]) / (R - 1);
					int tmp_mod = abs(shark[i][0]) % (R - 1);
					if (tmp_div & 1) {
						shark[i][0] = R - tmp_mod;
						if (!tmp_mod) //마지막 칸에 있는 경우 방향이 다름
							shark[i][3] = 2;
					}
					else {
						shark[i][0] = 1 + tmp_mod;
						if (tmp_mod) //첫번째 칸에 있는 경우 방향이 다름
							shark[i][3] = 2;
					}
				}
			}
			else if (shark[i][3] == 2) {//아래로 움직일때
				shark[i][0] += (move_y[shark[i][3]] * shark[i][2]);
				if (shark[i][0] > R) {
					shark[i][0] -= R;
					int tmp_div = shark[i][0] / (R - 1);
					int tmp_mod = shark[i][0] % (R - 1);
					if (tmp_div & 1) {
						shark[i][0] = 1 + tmp_mod;
						if (!tmp_mod)
							shark[i][3] = 1;
					}
					else {
						shark[i][0] = R - tmp_mod;
						if (tmp_mod)
							shark[i][3] = 1;
					}


				}
			}
			else if (shark[i][3] == 3) { //오른쪽으로 움직일때
				shark[i][1] += (move_x[shark[i][3]] * shark[i][2]);
				if (shark[i][1] > C) {
					shark[i][1] -= C;
					int tmp_div = shark[i][1] / (C - 1);
					int tmp_mod = shark[i][1] % (C - 1);
					if (tmp_div & 1) {
						shark[i][1] = 1 + tmp_mod;
						if (!tmp_mod)
							shark[i][3] = 4;
					}
					else {
						shark[i][1] = C - tmp_mod;
						if (tmp_mod)
							shark[i][3] = 4;
					}

				}
			}
			else if (shark[i][3] == 4) {//왼쪽으로 움직일때
				shark[i][1] += (move_x[shark[i][3]] * shark[i][2]);
				if (shark[i][1] < 1) {
					shark[i][1]--;
					int tmp_div = abs(shark[i][1]) / (C - 1);
					int tmp_mod = abs(shark[i][1]) % (C - 1);
					if (tmp_div & 1) {
						shark[i][1] = C - tmp_mod;
						if (!tmp_mod)
							shark[i][3] = 3;
					}
					else {
						shark[i][1] = 1 + tmp_mod;
						if (tmp_mod)
							shark[i][3] = 3;
					}

				}
			}

			if (AA[shark[i][0]][shark[i][1]] < i) { //이동한 위치에 이미 이동한 상어 있는지 확인
				int tmp_idx = AA[shark[i][0]][shark[i][1]];
				if (shark[tmp_idx][4] > shark[i][4]) {//크기 비교후 죽은상어 좌표 0으로 설정
					shark[i][0] = 0;
					shark[i][1] = 0;
				}
				else {
					shark[tmp_idx][0] = 0;
					shark[tmp_idx][1] = 0;
					AA[shark[i][0]][shark[i][1]] = i;
				}
			}
		}
		
	}

	cout << res;
	return 0;
}
