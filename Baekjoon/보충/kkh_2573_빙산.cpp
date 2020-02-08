#include <iostream>
#include <cstring>
using namespace std;
int N, M, Arr[300][300], ice[10000][3], isvis[300][300], idx, year, summ, cnt, move_y[4] = { 0,0,-1,1 }, move_x[4] = { 1,-1,0, 0 };

void dfs(int y, int x) {
	for (int i = 0; i < 4; i++) {
		if (Arr[y + move_y[i]][x + move_x[i]] && !isvis[y + move_y[i]][x + move_x[i]]) {
			isvis[y + move_y[i]][x + move_x[i]] = 1;
			summ--;
			dfs(y + move_y[i], x + move_x[i]);
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) {
			cin >> Arr[i][j];
			if (Arr[i][j]) {
				ice[idx][0] = i;
				ice[idx][1] = j;
				ice[idx++][2] = Arr[i][j];
			}
		}					

	for (year = 1; ; year++) {
		for (int i = 0; i < idx; i++) {
			if (ice[i][2] == 0) continue;
			for (int k = 0; k < 4; k++) {
				if (ice[i][0] + move_y[k] >= 0 && ice[i][0] + move_y[k] < N
					&& ice[i][1] + move_x[k] >= 0 && ice[i][1] + move_x[k] < M
					&& !Arr[ice[i][0] + move_y[k]][ice[i][1] + move_x[k]]) {
					ice[i][2]--;
				}
			}
		}

		summ = 0;

		for (int i = 0; i < idx; i++) {
			if (ice[i][2] <= 0) {
				Arr[ice[i][0]][ice[i][1]] = 0;
				ice[i][2] = 0;
			}			
			else {
				Arr[ice[i][0]][ice[i][1]] = ice[i][2];
				summ++;
			}
		}

		if (!summ) {
			year = 0;
			break;
		}

		cnt = 0;
		memset(isvis, 0, sizeof(isvis));
	
		for (int i = 0; i < idx; i++) {
			if (ice[i][2] && !isvis[ice[i][0]][ice[i][1]]) {
				isvis[ice[i][0]][ice[i][1]] = 1;
				summ--;
				cnt++;
				dfs(ice[i][0], ice[i][1]);
			}
			if (summ <= 0)	break;
		}
    
		if (cnt >= 2) 		break;
	}

	cout << year;
	return 0;
}
