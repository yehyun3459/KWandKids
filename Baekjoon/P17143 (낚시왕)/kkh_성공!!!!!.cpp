#include <iostream>
#include <cstring>
using namespace std;
int R, C, M, AA[101][101], shark[10001][5], move_y[5] = { 0, -1, 1, 0, 0 }, move_x[5] = { 0, 0, 0, 1, -1 }, res;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) 
		for (int j = 0; j < 5; j++)
			cin >> shark[i][j]; // y,x,속력, 이동방향, 크기

	for (int cnt = 1; cnt <= C; cnt++) { //열 옮기면서 낚시
		memset(AA, 0, sizeof(AA)); // 상어 위치 비교할때 사용

		int minn = 101, idx = 0;
		for (int j = 1; j <= M; j++) 
			if (shark[j][1] == cnt) //현재 낚시왕 위치중 최소 y값 구하기
				if (shark[j][0] && minn > shark[j][0]) { //0이 아니면서 최소값 구하기
					minn = shark[j][0];
					idx = j;
				}

		if (minn < 101) {
			shark[idx][0] = 0; //잡은 상어 y값 0으로 표시
			res += shark[idx][4]; //잡은 상어 크기 추가
		}

		for (int i = 1; i <= M; i++) {
			int tmp_y = shark[i][0], tmp_x = shark[i][1];
			if (!tmp_y)	continue; //잡거나 죽은 상어일경우 넘기기
			if (shark[i][3] == 1) { //위로 움직일때
				shark[i][0] += (move_y[shark[i][3]] * shark[i][2]);
				if (shark[i][0] < 1) {
					shark[i][0]--;
					int tmp_div = abs(shark[i][0]) / (R - 1); //방향 구하기
					int tmp_mod = abs(shark[i][0]) % (R - 1); //위치 
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

			if (AA[shark[i][0]][shark[i][1]] == 0) //빈칸인 경우 현재 상어 인덱스 표시
				AA[shark[i][0]][shark[i][1]] = i;
			else if (shark[AA[shark[i][0]][shark[i][1]]][4] > shark[i][4]) // 저장되있는 인덱스 상어와 크기 비교
				shark[i][0] = 0; 
			else {
				shark[AA[shark[i][0]][shark[i][1]]][0] = 0; //사망했을 때는 y값 
				AA[shark[i][0]][shark[i][1]] = i;
			}				
		}
	}

	cout << res;
	return 0;
}
