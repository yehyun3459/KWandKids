#include<stdio.h>
#include<iostream>
#include<vector>
#include<deque>

using namespace std;

int n, m, t;
int sum=0, cnt=0;
const int INF_MIN = -987654321;

void find_ans(vector<deque<int>>& p) {
	vector<vector<bool>> test(n);
	for (int i = 0; i < n; i++) {
		test[i].resize(m);
	}
	bool is_change = false;

	//1. 양 옆 확인
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) {
			if (p[i][j] == p[i][j + 1] && p[i][j] != INF_MIN && p[i][j + 1] != INF_MIN) {
				test[i][j] = true;
				test[i][j + 1] = true;
				is_change = true;
			}
		}
		if (p[i][0] == p[i][m - 1] && p[i][0] != INF_MIN && p[i][m - 1] != INF_MIN) {
			test[i][0] = true;
			test[i][m - 1] = true;
			is_change = true;
		}
	}

	//2. 위 아래 확인
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n - 1; i++) {
			if (p[i][j] == p[i + 1][j] && p[i][j] != INF_MIN && p[i+1][j] != INF_MIN) {
				test[i][j] = true;
				test[i + 1][j] = true;
				is_change = true;
			}
		}
	}
	
	//3. 변경시 삭제
	if (is_change) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (test[i][j] == true && p[i][j] != INF_MIN) {
					sum -= p[i][j];
					cnt--;
					p[i][j] = INF_MIN;

				}
			}
		}
	}
	//4. 변경안될시 평균 구하고 크기 비교
	else {
		double avg = (double)sum / cnt;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (p[i][j] != INF_MIN) {
					if (p[i][j] > avg) {
						p[i][j] -= 1;
						sum--;
					}
					else if (p[i][j] < avg) {
						p[i][j] += 1;
						sum++;
					}
				}
			}
		}
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &t);

	vector<deque<int>> pan(n);

	int num;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d ", &num);
			sum += num;
			cnt++;
			pan[i].push_back(num);
		}
	}

	int x, d, k;
	while (t--) {
		scanf("%d %d %d", &x, &d, &k);
		for (int i = 1; i*x <= n; i++) {
			int xx = i * x - 1;
			for (int rot = 0; rot < k; rot++) {
				if (d == 0) {
					int tmp = pan[xx].back();
					pan[xx].pop_back();
					pan[xx].push_front(tmp);
				}
				else {
					int tmp = pan[xx].front();
					pan[xx].pop_front();
					pan[xx].push_back(tmp);
				}
			}
		}
		find_ans(pan);
	}

	printf("%d", sum);

	//system("pause");
	return 0;
}
