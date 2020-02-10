#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int N, M, isvis[50][50], my[4] = { 0,0,-1,1 }, mx[4] = { 1,-1,0,0 }, maxx;
char map[50][50];
struct ss{ int y, x, cnt; };
queue<ss> q;
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'L') 
				q.push({ i,j,0 });	
		}	

	while (!q.empty()) {
		memset(isvis, 0, sizeof(isvis));		
		ss tmp = q.front();
		q.pop();
		queue<ss> tmp_qq;
		tmp_qq.push(tmp);		
		while (!tmp_qq.empty()) {
			ss tmp_tmp = tmp_qq.front();
			isvis[tmp_tmp.y][tmp_tmp.x] = 1;
			tmp_qq.pop();
			
			if (tmp_tmp.cnt > maxx) maxx = tmp_tmp.cnt;		

			for (int i = 0; i < 4; i++) {
				if (tmp_tmp.y + my[i] > N || tmp_tmp.y + my[i] < 0)	continue;
				if (tmp_tmp.x + mx[i] > M || tmp_tmp.x + mx[i] < 0)	continue;

				if (map[tmp_tmp.y + my[i]][tmp_tmp.x + mx[i]] == 'L' && !isvis[tmp_tmp.y + my[i]][tmp_tmp.x + mx[i]]) {
					isvis[tmp_tmp.y + my[i]][tmp_tmp.x + mx[i]] = 1;				
					tmp_qq.push({ tmp_tmp.y + my[i] , tmp_tmp.x + mx[i] , tmp_tmp.cnt + 1 });
				}
			}
		}
	}
	cout << maxx;
	return 0;
}
