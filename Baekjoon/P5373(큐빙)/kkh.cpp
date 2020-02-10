#include <iostream>
using namespace std;
int T, N, M;
char cr[6] = { 'w', 'y','r','o','g','b' };// 위 아래 앞 뒷 왼 오
char qu[6][3][3], tmp[3];

void cur(int idx) { //  선택 면에서 시계방향 90도 회전
	for (int i = 0; i < 2; i++) {
		char tmp = qu[idx][0][0];
		qu[idx][0][0] = qu[idx][1][0];
		qu[idx][1][0] = qu[idx][2][0];
		qu[idx][2][0] = qu[idx][2][1];
		qu[idx][2][1] = qu[idx][2][2];
		qu[idx][2][2] = qu[idx][1][2];
		qu[idx][1][2] = qu[idx][0][2];
		qu[idx][0][2] = qu[idx][0][1];
		qu[idx][0][1] = tmp;
	}
}
 
void cur_L() { //왼쪽면 시계방향 90도 회전
	for (int zz = 0; zz < 3; zz++)
		tmp[zz] = qu[0][zz][0];

	qu[0][0][0] = qu[3][2][0];
	qu[0][1][0] = qu[3][1][0];
	qu[0][2][0] = qu[3][0][0];

	qu[3][2][0] = qu[1][0][0];
	qu[3][1][0] = qu[1][1][0];
	qu[3][0][0] = qu[1][2][0];

	qu[1][0][0] = qu[2][0][0];
	qu[1][1][0] = qu[2][1][0];
	qu[1][2][0] = qu[2][2][0];

	qu[2][0][0] = tmp[0];
	qu[2][1][0] = tmp[1];
	qu[2][2][0] = tmp[2];
}

void cur_R() { //오른쪽면 시계방향 90도 회전
	for (int zz = 0; zz < 3; zz++)
		tmp[zz] = qu[0][zz][2];

	qu[0][0][2] = qu[2][0][2];
	qu[0][1][2] = qu[2][1][2];
	qu[0][2][2] = qu[2][2][2];

	qu[2][0][2] = qu[1][0][2];
	qu[2][1][2] = qu[1][1][2];
	qu[2][2][2] = qu[1][2][2];

	qu[1][0][2] = qu[3][2][2];
	qu[1][1][2] = qu[3][1][2];
	qu[1][2][2] = qu[3][0][2];

	qu[3][0][2] = tmp[2];
	qu[3][1][2] = tmp[1];
	qu[3][2][2] = tmp[0];
}

void cur_U() { //위쪽면 시계방향 90도 회전
	for (int zz = 0; zz < 3; zz++)
		tmp[zz] = qu[2][0][zz];

	qu[2][0][0] = qu[5][0][0];
	qu[2][0][1] = qu[5][0][1];
	qu[2][0][2] = qu[5][0][2];

	qu[5][0][0] = qu[3][0][2];
	qu[5][0][1] = qu[3][0][1];
	qu[5][0][2] = qu[3][0][0];

	qu[3][0][0] = qu[4][0][2];
	qu[3][0][1] = qu[4][0][1];
	qu[3][0][2] = qu[4][0][0];

	qu[4][0][0] = tmp[0];
	qu[4][0][1] = tmp[1];
	qu[4][0][2] = tmp[2];
}

void cur_D() { //아래쪽면 시계방향 90도 회전
	for (int zz = 0; zz < 3; zz++)
		tmp[zz] = qu[2][2][zz];

	qu[2][2][0] = qu[4][2][0];
	qu[2][2][1] = qu[4][2][1];
	qu[2][2][2] = qu[4][2][2];

	qu[4][2][0] = qu[3][2][2];
	qu[4][2][1] = qu[3][2][1];
	qu[4][2][2] = qu[3][2][0];

	qu[3][2][0] = qu[5][2][2];
	qu[3][2][1] = qu[5][2][1];
	qu[3][2][2] = qu[5][2][0];

	qu[5][2][0] = tmp[0];
	qu[5][2][1] = tmp[1];
	qu[5][2][2] = tmp[2];
}

void cur_F() { //앞쪽면 시계방향 90도 회전
	for (int zz = 0; zz < 3; zz++)
		tmp[zz] = qu[0][2][zz];

	qu[0][2][0] = qu[4][2][2];
	qu[0][2][1] = qu[4][1][2];
	qu[0][2][2] = qu[4][0][2];

	qu[4][0][2] = qu[1][0][0];
	qu[4][1][2] = qu[1][0][1];
	qu[4][2][2] = qu[1][0][2];

	qu[1][0][0] = qu[5][2][0];
	qu[1][0][1] = qu[5][1][0];
	qu[1][0][2] = qu[5][0][0];

	qu[5][2][0] = tmp[2];
	qu[5][1][0] = tmp[1];
	qu[5][0][0] = tmp[0];
}

void cur_B() { //뒤쪽면 시계방향 90도 회전 (인덱스 반대로 함)
	for (int zz = 0; zz < 3; zz++)
		tmp[zz] = qu[0][0][zz];

	qu[0][0][0] = qu[5][0][2];
	qu[0][0][1] = qu[5][1][2];
	qu[0][0][2] = qu[5][2][2];

	qu[5][0][2] = qu[1][2][2];
	qu[5][1][2] = qu[1][2][1];
	qu[5][2][2] = qu[1][2][0];

	qu[1][2][0] = qu[4][0][0];
	qu[1][2][1] = qu[4][1][0];
	qu[1][2][2] = qu[4][2][0];

	qu[4][0][0] = tmp[2];
	qu[4][1][0] = tmp[1];
	qu[4][2][0] = tmp[0];
}


int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		for (int c = 0; c < 6; c++)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					qu[c][i][j] = cr[c]; //면마다 칼라 지정 (0:위w, 1:아래y, 2:앞r, 3:뒤o, 4:왼g, 5:오b)

		cin >> N;
		for (int i = 0; i < N; i++) {
			char tx[3];
			cin >> tx;
			if (tx[0] == 'L') {
				if (tx[1] == '+') {
					cur(4);
					cur_L();
				}
				else {
					for (int k = 0; k < 3; k++) { //반시계 방향은 시계방향으로 3번한 것과 같음
						cur(4);
						cur_L();
					}
				}
			}
			else if (tx[0] == 'R') {
				if (tx[1] == '+') {
					cur(5);
					cur_R();
				}
				else {
					for (int k = 0; k < 3; k++) {
						cur(5);
						cur_R();
					}
				}
			}
			else if (tx[0] == 'U') {
				if (tx[1] == '+') {
					cur(0);
					cur_U();
				}
				else {
					for (int k = 0; k < 3; k++) {
						cur(0);
						cur_U();
					}
				}
			}
			else if (tx[0] == 'D') {
				if (tx[1] == '+') {
					cur(1);
					cur_D();
				}
				else {
					for (int k = 0; k < 3; k++) {
						cur(1);
						cur_D();
					}
				}
			}
			else if (tx[0] == 'F') {
				if (tx[1] == '+') {
					cur(2);
					cur_F();
				}
				else {
					for (int k = 0; k < 3; k++) {
						cur(2);
						cur_F();
					}
				}
			}
			else if (tx[0] == 'B') { //뒷면 인덱스 뒤집어서 해서 조금 다름
				if (tx[1] == '+') {
					for (int k = 0; k < 3; k++) 
						cur(3);

					cur_B();
				}
				else {
					cur(3);
					for (int k = 0; k < 3; k++)
						cur_B();
				}
			}		
		}
		for (int i = 0; i < 3; i++) { //최종 윗면 출력
			for (int j = 0; j < 3; j++) 
				cout << qu[0][i][j];
			cout << "\n";
		}
	}
	return 0;
}
