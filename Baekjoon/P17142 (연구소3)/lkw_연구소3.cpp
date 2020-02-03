#include<iostream>
using namespace std;

int arr[50][50];
int N, M, ans = 10000;
bool cant = 0;

bool visit[2500] = { 0, };

int ylist[2500];
int xlist[2500];
int ldx = 0;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void prt(char a[][50], int n) {
	cout << "prt:" << endl;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++)
			cout << a[j][i];
		cout << endl;
	}
}

int bfs() {
	char tmp[50][50];
	char tmp2[50][50];
	bool vis[50][50];
	int count = 0;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++) {
			if (arr[j][i] == 1)
				tmp[j][i] = '-';
			else if (arr[j][i] == 2)
				tmp[j][i] = '*';
			else {
				tmp[j][i] = '@';
				count++;
			}
			tmp2[j][i] = tmp[j][i];
			vis[j][i] = 0;
		}

	int qy[2505];
	int qx[2505];
	int qs[2505];
	int head = 0, tail = 0;

	for(int j=0; j < ldx; j++)
		if (visit[j]) {
			tmp[ylist[j]][xlist[j]] = '0';
			tmp2[ylist[j]][xlist[j]] = '0';
			vis[ylist[j]][xlist[j]] = 1;
			qy[tail] = ylist[j];
			qx[tail] = xlist[j];
			qs[tail] = 0;
			tail++;
		}
	int sec = 0;
	bool fg = 0;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (tmp[j][i] == '@') {
				fg = 1; break;
			}
		}
	}
	if (fg == 0)
		return 0;
	while (head < tail) {
		int y0 = qy[head];
		int x0 = qx[head];
		sec = qs[head];
		head++;

		if (tmp2[y0][x0] == '@')
			count--;

		for (int i = 0; i < 4; i++) {
			int yt = y0 + dy[i];
			int xt = x0 + dx[i];
			if (yt >= 0 && yt < N && xt >= 0 && xt < N && vis[yt][xt] == 0 && tmp[yt][xt] != '-') {
				if (tmp[yt][xt] == '@') {
					vis[yt][xt] = 1;
					tmp[yt][xt] = '*';
					qy[tail] = yt;
					qx[tail] = xt;
					qs[tail] = sec + 1;
					tail++;
				}
				else if (tmp[yt][xt] == '*') {
					vis[yt][xt] = 1;
					tmp[yt][xt] = '*';
					qy[tail] = yt;
					qx[tail] = xt;
					qs[tail] = sec+1;
					tail++;
				}
			}
		}
		if (count == 0)
			break;
		//prt(tmp, N);
	}

	//prt(tmp, N);
	//int Min = 1000;
	int tm = sec;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (tmp[j][i] == '@')
				return -1;
		}
	}
	return sec;
}

void choosev(int s, int e, int cnt, int m) {
	if (cnt == m) {
		//cout << "v : ";
		//for (int i = 0; i < e; i++)
	//		cout << visit[i];
		//cout << endl;
		int tmp = bfs();
		if (tmp == -1)
			cant = 1;
		else if (tmp < ans)
			ans = tmp;
		//cout << "res : " << bfs() << endl;
	}
	else if (s < e && cnt < m) {
		visit[s] = 1;
		cnt++;
		choosev(s + 1, e, cnt, m);
		visit[s] = 0;
		cnt--;
		choosev(s + 1, e, cnt, m);
		
	}
}

int main() {
	cin >> N >> M;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++) {
			cin >> arr[j][i]; //0:빈칸, 1:벽, 2:비활성바이러스
			if (arr[j][i] == 2) {
				ylist[ldx] = j;
				xlist[ldx] = i;
				ldx++;
			}
		}

	choosev(0, ldx, 0, M);

	if (cant && ans == 10000)
		cout << -1;
	else 
		cout << ans;

	return 0;
}