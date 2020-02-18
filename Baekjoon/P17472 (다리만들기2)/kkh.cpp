#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, Map[11][11], isvis[11][11], Totcnt, dp[7][7], land_label, Totminn = INT32_MAX;
int my[4] = { 0,0, -1,1 }, mx[4] = { 1,-1,0,0 };

struct bridge { int nlen, nfrom, nto; }; //다리 길이, 시작점, 도착점
bool compare(bridge a, bridge b) {
	if (a.nlen < b.nlen)
		return 1;
	return 0;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= M; j++) 
			cin >> Map[i][j];		

	vector<pair<int, int> > v[7]; 
  
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (Map[i][j] && !isvis[i][j]) {
				isvis[i][j] = ++land_label; //섬마다 인덱스로 구별 및 전체 섬 갯수
				queue<pair<int, int> > q;
				q.push({ i,j });
				v[land_label].push_back({ i,j });

				while (!q.empty()) {
					pair<int, int> tmp = q.front();
					q.pop();

					for (int k = 0; k < 4; k++) {
						int tmp_y = tmp.first + my[k];
						int tmp_x = tmp.second + mx[k];
						if (tmp_y > N || tmp_y <= 0 || tmp_x > M || tmp_x <= 0)	continue;
						if (Map[tmp_y][tmp_x] && !isvis[tmp_y][tmp_x]) {
							isvis[tmp_y][tmp_x] = land_label;
							q.push({ tmp_y, tmp_x });
							v[land_label].push_back({ tmp_y,tmp_x }); //섬마다 백터로 구별하여 관리
						}
					}
				}
			}

	for (int cnt = 1; cnt <= land_label; cnt++) {
		for (int i = 0; i < (int)v[cnt].size(); i++) { //상하좌우로 연결 할수 있는 섬 있는지 확인
			pair<int, int> tmp = v[cnt][i];
			if (tmp.first + 2 < N && isvis[tmp.first + 1][tmp.second] == 0 && isvis[tmp.first + 2][tmp.second] == 0) {
				int del = 2;
				while (tmp.first + del <= N && isvis[tmp.first + del][tmp.second] == 0)
					del++;

				if (tmp.first + del <= N) {
					int landNum = isvis[tmp.first + del][tmp.second];
					if (dp[cnt][landNum] == 0) { // 시작점 : cnt , 도착점 : landNum
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
					else if (dp[cnt][landNum] > del - 1) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
				}
			}

			if (tmp.first - 2 > 1 && isvis[tmp.first - 1][tmp.second] == 0 && isvis[tmp.first - 2][tmp.second] == 0) {
				int del = 2;
				while (tmp.first - del > 0 && isvis[tmp.first - del][tmp.second] == 0)
					del++;

				if (tmp.first - del > 0) {
					int landNum = isvis[tmp.first - del][tmp.second];
					if (dp[cnt][landNum] == 0) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
					else if (dp[cnt][landNum] > del - 1) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
				}
			}

			if (tmp.second + 2 < N && isvis[tmp.first][tmp.second + 1] == 0 && isvis[tmp.first][tmp.second + 2] == 0) {
				int del = 2;
				while (tmp.second + del <= N && isvis[tmp.first][tmp.second + del] == 0)
					del++;

				if (tmp.second + del <= N) {
					int landNum = isvis[tmp.first][tmp.second + del];
					if (dp[cnt][landNum] == 0) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
					else if (dp[cnt][landNum] > del - 1) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
				}
			}

			if (tmp.second - 2 > 1 && isvis[tmp.first][tmp.second - 1] == 0 && isvis[tmp.first][tmp.second - 2] == 0) {
				int del = 2;
				while (tmp.second - del > 0 && isvis[tmp.first][tmp.second - del] == 0)
					del++;

				if (tmp.second - del > 0) {
					int landNum = isvis[tmp.first][tmp.second - del];
					if (dp[cnt][landNum] == 0) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
					else if (dp[cnt][landNum] > del - 1) {
						dp[cnt][landNum] = del - 1;
						dp[landNum][cnt] = del - 1;
					}
				}
			}
		}
	}

	vector<bridge> vBridge;

	for (int i = 1; i <= land_label; i++) 
		for (int j = 1; j <= land_label; j++) //시작점 < 도착점 값들로 정리
			if (i < j && dp[i][j] >= 2) 
				vBridge.push_back({ dp[i][j], i, j });	

	int summ = 0;
	int isvisLand[7] = { 0 };
	int parent[7] = { 0,1,2,3,4,5,6 }; // 각 섬들의 루트? 부모? 값들
	int connection[7][7] = { 0 };

	sort(vBridge.begin(), vBridge.end(), compare); //작은 다리 먼저

	for (int i = 0; i < (int)vBridge.size(); i++) {
		int tmp_parent_from = parent[vBridge[i].nfrom]; // 더 작은 인덱스를 가진 섬과 연결되 있으면 연결된 섬을 기준으로 확인(부모확인)
		int tmp_parent_to = parent[vBridge[i].nto];        
		if (tmp_parent_from == tmp_parent_to)	continue;
		if (connection[tmp_parent_from][tmp_parent_to] == 0) { 
			connection[tmp_parent_from][tmp_parent_to] = 1;
			parent[tmp_parent_to] = tmp_parent_from;  //다리 연결되면 부모값들 새로 갱신
			parent[vBridge[i].nto] = tmp_parent_from;
            
			land_label--; //연결된 섬들 개수에서 차감
			summ += vBridge[i].nlen;
		}		
	}

	if (summ && land_label == 1) //모든 섬이 연결 된 경우 (처음 시작점을 차감안해서 1이 남음)
		cout << summ;
	else
		cout << -1;
	return 0;
}
