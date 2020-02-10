#include <iostream>
#include <vector>
using namespace std;
int N, M, summ, tmp_min, map[51][51], isvis[13], minn = INT32_MAX;
vector < pair<int, int> > v_home;
vector < pair<int, int> > v_chicken;

void dfs(int idx, int cnt) {
	if (cnt == M) {     //치킨집 선택
		summ = 0;
		for (int i = 0; i < v_home.size(); i++) {
			tmp_min = 250;
			for (int j = 0; j < v_chicken.size(); j++) {
				if (isvis[j]) {  
					int yy = abs(v_home[i].first - v_chicken[j].first);
					int xx = abs(v_home[i].second - v_chicken[j].second);
					if (tmp_min > yy + xx)    //집마다 젤 짧은거리 선택
						tmp_min = yy + xx;
				}
			}
			summ += tmp_min;
		}
		if (minn > summ)    
            minn = summ;				
	}

	for (int i = idx + 1; i < v_chicken.size(); i++) {
		isvis[i] = 1;
		dfs(i, cnt + 1);
		isvis[i] = 0;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				v_home.push_back({ i, j }); //집 위치
			else if (map[i][j] == 2)
				v_chicken.push_back({ i,j }); //치킨집 위치
		}
			
	for (int idx = 0; idx <= v_chicken.size() - M; idx++) {
		isvis[idx] = 1;
		dfs(idx, 1);
		isvis[idx] = 0;
	}

	cout << minn;
	return 0;
}
