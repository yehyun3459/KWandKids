#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int R, C, M, inp, AA[101][101], my[5] = { 0, -1, 1, 0, 0 }, mx[5] = { 0, 0, 0, 1, -1 }, res;
struct shark { int y, x, speed, dir, size, die; };
vector<shark> v;

void move() { //상어 움직임
	memset(AA, 0, sizeof(AA));
	for (int i = 0; i < v.size(); i++) {
		int ndir = v[i].dir;
		int nY = v[i].y, nX = v[i].x;
		if (v[i].dir == 1 || v[i].dir == 2) {  //위 아래 방향
			int nSpeed_new = v[i].speed % ((R - 1) * 2);			
			for (int cnt = 1; cnt <= nSpeed_new; cnt++) {
				if (nY + my[ndir] == 0) {
					ndir = 2;
					nY += my[ndir];
				}
				else if (nY + my[ndir] > R) {
					ndir = 1;
					nY += my[ndir];
				}
				else
					nY += my[ndir];
			}			
		}
		else {                              // 좌우 방향
			int nSpeed_new = v[i].speed % ((C - 1) * 2);			
			for (int cnt = 1; cnt <= nSpeed_new; cnt++) {
				if (nX + mx[ndir] == 0) {
					ndir = 3;
					nX += mx[ndir];
				}
				else if (nX + mx[ndir] > C) {
					ndir = 4;
					nX += mx[ndir];
				}
				else
					nX += mx[ndir];
			}
		}

		v[i].x = nX;
		v[i].y = nY;
		v[i].dir = ndir;

		if (AA[nY][nX] == 0) 
			AA[nY][nX] = i + 1;
		else if (v[AA[nY][nX] - 1].size > v[i].size)  //중복 위치 비교 후 죽은 상어 표시
			v[i].die = 1;
		else {
			v[AA[nY][nX] - 1].die = 1;
			AA[nY][nX] = i + 1;
		}
	}	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		shark s;
		cin >> s.y >> s.x >> s.speed >> s.dir >> s.size;
		v.push_back(s);
	}

	for (int cnt = 1; cnt <= C; cnt++) {  //상어 낚시 하기
		int minn = 101, idx = -1;
		for (int ii = 0; ii < v.size(); ii++) {
			if (v[ii].x == cnt) {
				if (minn > v[ii].y) {
					minn = v[ii].y;
					idx = ii;
				}
			}
		}

		if (idx != -1) { //잡은 상어 백터에서 삭제
			res += v[idx].size;
			v.erase(v.begin() + idx);
		}	

		move();

		for (int i = 0; i < v.size(); i++) {  //죽은 상어 백터에서 삭제
			if (v[i].die == 1) {
				v.erase(v.begin() + i);
				i--;
			}
		}
	}
  	cout << res;
	return 0;
}
