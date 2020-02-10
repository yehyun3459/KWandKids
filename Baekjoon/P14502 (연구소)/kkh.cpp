#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, M, Map[9][9], zero_cnt, wall[3][2], my[4] = { 0,0,1,-1 }, mx[4] = { 1,-1,0,0 }, maxx;
vector<pair<int, int> > v;
void bfs() {    //바이러스 확산
	for (int i = 0; i < 3; i++)
		Map[wall[i][0]][wall[i][1]] = 1; //설치한 문의 좌표 설정

	int isvis[9][9] = { 0 }, tmp_cnt = zero_cnt - 3; //빈 칸 갯수
	queue < pair<int, int> > q;
	for (int i = 0; i < (int)v.size(); i++)
		q.push(v[i]);   //바이러스 좌표 설정

	while (!q.empty()) { //bfs 탐색
		pair<int, int> tmp = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			int yy = tmp.first + my[k];
			int xx = tmp.second + mx[k];
			if (yy > 0 && yy <= N && xx > 0 && xx <= M && !Map[yy][xx] && !isvis[yy][xx]) {
				isvis[yy][xx] = 1;
				tmp_cnt--; // 빈칸 카운트 다운
				q.push({ yy,xx });
			}
		}
	}
	if (maxx < tmp_cnt) //최대값 저장
		maxx = tmp_cnt;
	for (int i = 0; i < 3; i++) //설치한 문 위치 복귀
		Map[wall[i][0]][wall[i][1]] = 0;
}

void dfs(int y, int x, int cnt) {   //문 위치 선택
	wall[cnt][0] = y, wall[cnt][1] = x; 
	if (cnt == 2) { //3개 선택 될때까지 반복
		bfs();
		return;
	}
	int st = x + 1;
	for (int i = y; i <= N; i++) {
		for (int j = st; j <= M; j++)
			if (!Map[i][j])
				dfs(i, j, cnt + 1);
        st = 1;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 2)
				v.push_back({ i,j }); //바이러스 위치 백터 저장
			else if (Map[i][j] == 0) //빈칸 갯수
				zero_cnt++;
		}
	}
	   	  
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (!Map[i][j])
				dfs(i, j, 0);
    
	cout << maxx;
	return 0;
}
