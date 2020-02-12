#include<iostream>
using namespace std;

int arr[10][10];
int N, M;
int MIN;

int dy[4] = { -1,0,1,0 }; // u r d l
int dx[4] = { 0,1,0,-1 };

struct cam { 
	int y, x;
	int type;
	bool dir[4];
	cam() {};
	void makecam(int Y, int X, int T) { // 카메라의 좌표 및 감시 방향을 정한다.
		y = Y;
		x = X;
		type = T;
		if (T == 1) {
			dir[0] = 1;
			dir[1] = 0;
			dir[2] = 0;
			dir[3] = 0;
		}
		else if (T == 2) {
			dir[0] = 0;
			dir[1] = 1;
			dir[2] = 0;
			dir[3] = 1;
		}
		else if (T == 3) {
			dir[0] = 1;
			dir[1] = 1;
			dir[2] = 0;
			dir[3] = 0;
		}
		else if (T == 4) {
			dir[0] = 1;
			dir[1] = 1;
			dir[2] = 1;
			dir[3] = 0;
		}
		else if (T == 5) {
			dir[0] = 1;
			dir[1] = 1;
			dir[2] = 1;
			dir[3] = 1;
		}
	}
};

void shiftcamdir(cam &a) { // 반시계 회전
	bool tmp = a.dir[0];
	for (int i = 0; i < 3; i++)
		a.dir[i] = a.dir[i + 1];
	a.dir[3] = tmp;
}
void revshiftcamdir(cam a) { // 시계 회전
	bool tmp = a.dir[3];
	for (int i = 3; i > 0; i--)
		a.dir[i] = a.dir[i - 1];
	a.dir[0] = tmp;
}

int cbs(cam c[], int cdx) {
	int tmp[10][10];
	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++)
			tmp[j][i] = arr[j][i];

	for (int j = 0; j < cdx; j++) {
		for (int i = 0; i < 4; i++) {
			if (c[j].dir[i]) {
				int y0 = c[j].y + dy[i];
				int x0 = c[j].x + dx[i];

				while (1) {
					if (y0 < N && y0 >= 0 && x0 < M && x0 >= 0) {
						if (tmp[y0][x0] == 6)
							break;
						if (tmp[y0][x0] == 0)
							tmp[y0][x0] = 7; // 사각지대가 아니야. 사각지대는 0
						y0 = y0 + dy[i];
						x0 = x0 + dx[i];
					}
					else break;
				}
			}
		}
	}

	//cout << "tmp :" << endl;
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++)
	//		cout << tmp[i][j] << " ";
	//	cout << endl;
	//}cout << endl;

	int cnt = 0;
	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++)
			if (tmp[j][i] == 0)
				cnt++;

	return cnt;
}
int many = 0;
void search(cam c[], int cdx, int k) {// 카메라 돌려돌려 돌림판. 재 귀
	if (k == cdx) {
		int tmp = cbs(c, cdx);
		if (tmp < MIN)
			MIN = tmp;

		//for (int i = 0; i < cdx; i++) {
		//	for (int j = 0; j < 4; j++)
		//		cout << c[i].dir[j];
		//	cout << " ";
		//}cout << endl;


		//cout << "tmp : " << tmp << endl;
		//many++;
	}
	else {
		int p;
		if (c[k].type == 1 || c[k].type == 3 || c[k].type == 4) // 카메라마다 달라.
			p = 4;
		else if (c[k].type == 2)
			p = 2;
		else if (c[k].type == 5)
			p = 1;

		for (int i = 0; i < p; i++) {
			search(c, cdx, k + 1);
			shiftcamdir(c[k]);
		}
	}
}

int main() {
	cam Cam[8];
	int ccnt = 0;
	MIN = 1000;

	cin >> N >> M;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++) {
			cin >> arr[j][i];
			if (arr[j][i] >= 1 && arr[j][i] <= 5) {
				Cam[ccnt].makecam(j, i, arr[j][i]);
				ccnt++;
			}
		}

	search(Cam, ccnt, 0);

	cout << MIN;// << endl << many;

	return 0;
}