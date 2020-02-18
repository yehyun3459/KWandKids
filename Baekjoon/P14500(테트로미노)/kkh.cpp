#include <iostream>
using namespace std;
int N, M, paper[501][501], isvis[501][501], my[4] = { 0,0,1,-1 }, mx[4] = { 1,-1, 0,0 }, maxx;

void dfs(int y, int x, int cnt, int summ) { //4개 짜리 탐색
	if (cnt == 4) {
		if (maxx < summ)
			maxx = summ;
		return;
	}
	for (int k = 0; k < 4; k++) {
		int next_y = y + my[k];
		int next_x = x + mx[k];
		if (!isvis[next_y][next_x] && next_y > 0 && next_y <= N && next_x > 0 && next_x <= M) {
			isvis[next_y][next_x] = 1;
			dfs(next_y, next_x, cnt + 1, summ + paper[next_y][next_x]);
			isvis[next_y][next_x] = 0;
		}
	}	
}
int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= M; j++) 
			cin >> paper[i][j];
		
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			isvis[i][j] = 1;
			dfs(i, j, 1, paper[i][j]);
			isvis[i][j] = 0;

			int tmp_summ[4] = { 0 };
			if (i + 2 <= N && j + 1 <= M)  //dfs로 탐색 못한 ㅗ 모양(ㅈㅅ) 따로 탐색
				tmp_summ[0] = paper[i][j] + paper[i + 1][j] + paper[i + 2][j] + paper[i + 1][j + 1];
			if (i + 2 <= N && j - 1 > 0) 
				tmp_summ[1] = paper[i][j] + paper[i + 1][j] + paper[i + 2][j] + paper[i + 1][j - 1];
			if (i + 1 <= N && j + 2 <= M) 
				tmp_summ[2] = paper[i][j] + paper[i][j + 1] + paper[i][j + 2] + paper[i + 1][j + 1];
			if (i - 1 > 0 && j + 2 <= M) 
				tmp_summ[3] = paper[i][j] + paper[i][j + 1] + paper[i][j + 2] + paper[i - 1][j + 1];
				
			for (int k = 0; k < 4; k++) 
				if (tmp_summ[k] > maxx)
					maxx = tmp_summ[k];			
		}
	}
	cout << maxx;
	return 0;
}
