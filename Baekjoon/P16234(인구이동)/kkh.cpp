#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int N, L, R, idx, summ[2500], cnt[2500], map[50][50], isvis[50][50], my[4] = { 0,0,-1,1 }, mx[4] = { 1,-1,0,0 }, tmp2, ans;
queue<pair<int, int> > q;

bool bfs() {
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) {
			if (isvis[i][j])	continue;
			q.push({ i, j });
			idx++;
			summ[idx] = map[i][j], cnt[idx] = 1;
			while (!q.empty()) {
				pair<int, int> tmp = q.front();
				isvis[i][j] = idx;
				q.pop();

				for (int k = 0; k < 4; k++) {
					if (tmp.first + my[k] >= N || tmp.first + my[k] < 0)		continue;
					if (tmp.second + mx[k] >= N || tmp.second + mx[k] < 0)	continue;
					if (isvis[tmp.first + my[k]][tmp.second + mx[k]])		continue;
					if (map[tmp.first + my[k]][tmp.second + mx[k]] > map[tmp.first][tmp.second])
						tmp2 = map[tmp.first + my[k]][tmp.second + mx[k]] - map[tmp.first][tmp.second];
					else
						tmp2 = map[tmp.first][tmp.second] - map[tmp.first + my[k]][tmp.second + mx[k]];
					if (tmp2 >= L && tmp2 <= R) {
						isvis[tmp.first + my[k]][tmp.second + mx[k]] = idx;
						summ[idx] += map[tmp.first + my[k]][tmp.second + mx[k]];
						cnt[idx]++;
						q.push({ tmp.first + my[k], tmp.second + mx[k] });
					}
				}
			}
		}

	int maxx = 0;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) {
			maxx = maxx < cnt[isvis[i][j]] ? cnt[isvis[i][j]] : maxx;
			map[i][j] = summ[isvis[i][j]] / cnt[isvis[i][j]];
		}

	if (maxx > 1)	return true;
	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			cin >> map[i][j];
		
	while (bfs()) {
		memset(isvis, 0, sizeof(isvis));
		ans++;
		idx = 0;
	}
	
	cout << ans;
	return 0;
}
