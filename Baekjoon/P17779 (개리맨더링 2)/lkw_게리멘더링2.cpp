#include<iostream>
using namespace std;

int map[21][21];
int idx[21][21];
int N;

void setWard(int r, int c, int d1, int d2) { // 기준점과 두 길이를 입력받아 구역을 나눠주는 함수
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			if (j < r + d1 && i <= c && j + i < r+c) // 1번 구역
				idx[j][i] = 1;
			else if (j <= r + d2 && i > c && j + (N-i+1) < r + (N-c+1)) // 2번 구역
				idx[j][i] = 2;
			else if (r + d1 <= j && i < c - d1 + d2 && (N-j+1) + i < c - d1 + (N- r - d1+1) ) // 3번 구역
				idx[j][i] = 3;
			else if (r + d2 < j && c - d1 + d2 <= i && (N-j+1)+(N-i+1) < (N - c - d2+1) + (N-r - d2 + 1)) // 4번 구역
				idx[j][i] = 4;
			else idx[j][i] = 5; // 나머지가 5번 구역
		}
	}
}
int getDiff(int n) { // 최대와 최소의 차이를 구해주는 함수
	int sum[6] = { 0, };
	for (int j = 1; j <= n; j++)
		for (int i = 1; i <= n; i++)
			sum[idx[j][i]] += map[j][i]; // 각 구역의 인구를 합한다.
	int max0 = 0;
	int min0 = 987654321;
	for (int i = 1; i <= 5; i++) {
		if (sum[i] > max0)
			max0 = sum[i];
		if (sum[i] < min0)
			min0 = sum[i];
	}

	return max0 - min0;
		

}
void prtI(int n) {
	cout << "idx\n";
	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++)
			cout << idx[j][i] << " ";
		cout << endl;
	}cout << endl;
}
void prtM(int n, int r, int c, int d1, int d2) {
	cout << "r : " << r << ", c : " << c << ", d1 : " << d1 << ", d2 : " << d2 << endl;
	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++)
			cout << map[j][i] << " ";
		cout << endl;
	}cout << endl;
}
int main() {
	//int d1, d2;

	cin >> N;

	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++) {
			cin >> map[j][i];
			//idx[j][i] = 5;
		}

	int minDiff = 987654321;
	int tmp;
	for (int r = 1; r <= N - 2; r++) {
		for (int c = 2; c <= N - 1; c++) {
			for (int d1 = 1; d1 <= N - 2; d1++) {
				for (int d2 = 1; d2 <= N - 2; d2++) {
					if ((r + d1 + d2 <= N) && (1 <= c - d1 && c + d2 <= N)) { // 기준점과 d1, d2가 가능한 상태이면
						setWard(r, c, d1, d2);	// 선거구를 나누고	
						//prtM(N, r, c, d1, d2);
						//prtI(N);
						tmp = getDiff(N); // 최대와 최소의 차이를 구한다
						//cout << "DIFF : " << tmp << endl << endl;
						if (tmp < minDiff)
							minDiff = tmp;
					}
				}
			}
		}
	}
	cout << minDiff;

	return 0;
}