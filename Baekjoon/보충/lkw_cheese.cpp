#include<iostream>
using namespace std;

bool visited[100][100];
int map_t[100][100]; // 공기를 표시하기 위해
int map[100][100]; // 치즈
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int savelast;

void set() {
	for (int j = 0; j < 100; j++)
		for (int i = 0; i < 100; i++) {
			visited[j][i] = 0;
			map_t[j][i] = 0;
		}
}
void dfs(int y, int x, int n, int m) {
	visited[y][x] = 1;
	map_t[y][x] = 1;

	for (int i = 0; i < 4; i++) {
		int yt = y + dy[i];
		int xt = x + dx[i];

		if (yt >= 0 && yt < n && xt >= 0 && xt < m && visited[yt][xt] == 0 && map[yt][xt] == 0)
			dfs(yt, xt, n, m);
	}
}
void prtm(int n, int m) {
	cout << "cheese~\n";
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++)
			cout << map[j][i] << " ";
		cout << endl;
	}cout << endl;
}
bool cheeseMelt(int n, int m) {
	set();
	dfs(0, 0, n, m);
	//prtm(n, m);
	int count = 0;
	savelast = 0;
	for (int j = 1; j < n - 1; j++) 
		for (int i = 1; i < m - 1; i++) 
			if (map[j][i]) {
				count++;
				savelast++;
				for (int k = 0; k < 4; k++) {
					int jt = j + dy[k];
					int it = i + dx[k];
					if (map_t[jt][it]) {
						map[j][i] = 0;
						count--;
						break;
					}
				}
			}
	//prtm(n, m);

	if (count > 0)
		return 0;
	else return 1;

}

int main() {
	int N, M;


	cin >> N >> M;
	int time = 1; //
	int zeroflag = 1;
	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++) {
			cin >> map[j][i];
			if (map[j][i])
				zeroflag = 0;
		}
	if (zeroflag)
		cout << 0 << endl << 0 << endl;

	while(!cheeseMelt(N, M))
		time++;
	cout << time << endl << savelast << endl;

	return 0;
}