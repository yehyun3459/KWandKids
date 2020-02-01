#include <iostream>
#include <cstring>
using namespace std;
int N, Array[102][102], election[102][102], num_sum[6], minn = INT32_MAX;
void fu(int x, int y) {
	for (int d1 = 1; d1 < N; d1++) {
		for (int d2 = 1; d2 < N; d2++) {
			if (x + d1 + d2 > N)	continue; //좌표 범위 여부 확인
			if (y - d1 < 1)			continue; 
			if (y + d2 > N)			continue; 
			memset(election, 0, sizeof(election));
			memset(num_sum, 0, sizeof(num_sum));

			//5 지역구 표시 
			for (int i = 0; i <= d1; i++) {
				for (int j = 0; j < d2; j++) {
					election[x + j + i][y + j - i] = 5;
					num_sum[5] += Array[x + j + i][y + j - i];
					if (i != d1) {
						election[x + j + i + 1][y + j - i] = 5; //지역구 구별 위해 임시 표시
						num_sum[5] += Array[x + j + i + 1][y + j - i];
					}
				}
				election[x + d2 + i][y + d2 - i] = 5;
				num_sum[5] += Array[x + d2 + i][y + d2 - i];
			}
			//1 지역구 인구 합산
			for (int i = 1; i < x + d1; i++)
				for (int j = 1; j <= y; j++)
					if (!election[i][j])
						num_sum[1] += Array[i][j];

			//2 지역구 인구 합산
			for (int i = 1; i <= x + d2; i++)
				for (int j = y + 1; j <= N; j++)
					if (!election[i][j])
						num_sum[2] += Array[i][j];

			//3 지역구 인구 합산
			for (int i = x + d1; i <= N; i++)
				for (int j = 1; j < y - d1 + d2; j++)
					if (!election[i][j])
						num_sum[3] += Array[i][j];

			//4 지역구 인구 합산
			for (int i = x + d2 + 1; i <= N; i++)
				for (int j = y - d1 + d2; j <= N; j++)
					if (!election[i][j])
						num_sum[4] += Array[i][j];

			int tmp_min = INT32_MAX, tmp_max = 0;
			for (int i = 1; i <= 5; i++) {
				if (tmp_min > num_sum[i])	tmp_min = num_sum[i];
				if (tmp_max < num_sum[i])	tmp_max = num_sum[i];
			}
			if (minn > tmp_max - tmp_min)	minn = tmp_max - tmp_min;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> Array[i][j];

	for (int i = 1; i < N; i++)
		for (int j = 2; j < N; j++)
			fu(i, j);

	cout << minn;
	return 0;
}