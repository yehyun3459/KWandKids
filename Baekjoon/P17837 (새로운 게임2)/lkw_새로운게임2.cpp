#include<iostream>
using namespace std;

int dy[5] = { 0, 0, 0, -1, 1 };
int dx[5] = { 0, 1, -1, 0, 0 }; //  우 좌 상 하

struct horse {
	int y, x, d;
};
horse h[11];

struct map {
	int list[10]; // 말이 4개가 쌓이면 종료( 딱 4개!)
	int color = 0;
	int cnt = 0;
	void reset() {
		cnt = 0;
		for (int i = 0; i < 10; i++)
			list[i] = 0;
	}
};
map m[14][14];

void move(int n, int i, int &after_y, int &after_x, int& clr) { // i 번째 말 움직여
	int yt = h[i].y + dy[h[i].d];
	int xt = h[i].x + dx[h[i].d];

	if (yt > n || yt < 1 || xt > n || xt < 1 || m[yt][xt].color == 2) { // blue
		if (h[i].d == 1)
			h[i].d = 2;
		else if (h[i].d == 2)
			h[i].d = 1;
		else if (h[i].d == 3)
			h[i].d = 4;
		else if (h[i].d == 4)
			h[i].d = 3;

		yt = yt + dy[h[i].d];
		xt = xt + dx[h[i].d];

		if (yt + dy[h[i].d] > n || yt + dy[h[i].d] < 1 || xt + dx[h[i].d]> n || xt + dx[h[i].d] < 1 || m[yt+dy[h[i].d]][xt + dx[h[i].d]].color == 2)
			;
		else {
			yt = yt + dy[h[i].d];
			xt = xt + dx[h[i].d];
		}
	}

	clr = m[yt][xt].color;
	after_y = yt;
	after_x = xt;
}
bool action(int b_y, int b_x, int a_y, int a_x, int hi, int color) {
	if (b_y == a_y && b_x == a_x)
		return 0;
	int bcnt = m[b_y][b_x].cnt;
	int acnt = m[a_y][a_x].cnt;
	int startidx;

	if (color == 0) { // to white
		for (int i = 0; i < bcnt; i++)
			if (m[b_y][b_x].list[i] == hi) {
				startidx = i; // 얘부터 옮겨
				break;
			}

		for (int i = startidx; i < bcnt; i++) {
			m[a_y][a_x].list[acnt + i - startidx] = m[b_y][b_x].list[i];
			h[m[b_y][b_x].list[i]].y = a_y;
			h[m[b_y][b_x].list[i]].x = a_x;
			m[b_y][b_x].list[i] = 0;
		}
		m[a_y][a_x].cnt = acnt + bcnt - startidx;
		m[b_y][b_x].cnt = startidx;

	}
	else if (color == 1) { // to red
		for (int i = 0; i < bcnt; i++)
			if (m[b_y][b_x].list[i] == hi)
				startidx = i; // 얘부터 옮겨

		for (int i = startidx; i < bcnt; i++) {
			m[a_y][a_x].list[acnt + i - startidx] = m[b_y][b_x].list[bcnt - 1 - (i - startidx)];
			h[m[b_y][b_x].list[bcnt - 1 - (i - startidx)]].y = a_y;
			h[m[b_y][b_x].list[bcnt - 1 - (i - startidx)]].x = a_x;
			m[b_y][b_x].list[bcnt - 1 - (i - startidx)] = 0;
		}
		m[a_y][a_x].cnt = acnt + bcnt - startidx;
		m[b_y][b_x].cnt = startidx;
	}
	if (m[a_y][a_x].cnt >= 4 || m[b_y][b_x].cnt >= 4)
		return 1;
	return 0;
}

void prt(int a) {
	cout << "map :\n";
	for (int j = 1; j <= a; j++) {
		for (int i = 1; i <= a; i++)
			cout << m[j][i].cnt << " ";
		cout << endl;
	}cout << endl;
}

int main() {
	int N = 0, K = 0; // 체스판 크기:4~12 , 말의 수 : 4 ~ 10

	cin >> N >> K;

	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			cin >> m[j][i].color;

	for (int i = 1; i <= K; i++) {
		cin >> h[i].y >> h[i].x >> h[i].d;
		m[h[i].y][h[i].x].cnt = 1;
		m[h[i].y][h[i].x].list[0] = i; // 초기 말의 위치
	}
	//
	//cout << " init \n";
	//prt(N);
	
	for (int i = 1; i <= 1000; i++) {
		//cout << "/ / /   i : " << i << endl;
		int after_y, after_x, color;
		for (int j = 1; j <= K; j++) {
			//cout << " before move\n";
			//prt(N);
			move(N, j, after_y, after_x, color);// i 번쩨가 이동할 좌표.
			if (action(h[j].y, h[j].x, after_y, after_x, j, color)) {
				cout << i << endl;
				//cout << " after move\n";
				//prt(N);
				return 0;
			}
			//cout << " after move\n";
			
		}
		//prt(N);
	}
	cout << -1 << endl;

	return 0;
}