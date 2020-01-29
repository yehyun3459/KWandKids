#include "iostream"
using namespace std;
int N, M, T, summ, zeroCnt, tmp, res, nPtr[52], circle[52][52], xdk[52][3];
bool b_flg;
void dfs(int n, int m, int num) {
	int ri = m + 1 > M ? m + 1 - M : m + 1; //오른쪽 좌표
	int le = m - 1 < 1 ? M + (m - 1) : m - 1; //왼쪽 좌표
	int sub = nPtr[n] - nPtr[n + 1]; //바깥쪽 원판 인접 좌표
	int next_c = m - sub;
	if (next_c < 1)	next_c = M + next_c;
	else if (next_c > M)	next_c = next_c - M;
	
	int sub1 = nPtr[n] - nPtr[n - 1];//안쪽 원판 인접 
	int post_c = m - sub1;
	if (post_c < 1)	post_c = M + post_c;
	else if (post_c > M)	post_c = post_c - M;

	if (circle[n][ri] == num) {
		circle[n][ri] = 0, circle[n][m] = 0, b_flg = false;
		dfs(n, ri, num);
	}
	if (circle[n][le] == num) {
		circle[n][le] = 0, circle[n][m] = 0, b_flg = false;
		dfs(n, le, num);
	}
	if (n < N && circle[n + 1][next_c] == num) {//마지막 원판일때는 실행안함
		circle[n + 1][next_c] = 0, circle[n][m] = 0, b_flg = false;
		dfs(n + 1, next_c, num);
	}
	
	if (n > 1 && circle[n - 1][post_c] == num) {//첫번째 원판 실행안함
		circle[n - 1][post_c] = 0, circle[n][m] = 0, b_flg = false;
		dfs(n - 1, post_c, num);
	}
}

void fu(int Tcnt) {
	int n_cnt = xdk[Tcnt][0], dir = xdk[Tcnt][1], rotcnt = xdk[Tcnt][2];
	for (int i = n_cnt; i <= N; i += n_cnt) {//스타트 포인터 조정
		if (dir) {
			nPtr[i] += rotcnt;
			if (nPtr[i] > M)	nPtr[i] = nPtr[i] % M > 0 ? nPtr[i] % M : M;
		}
		else {
			nPtr[i] -= rotcnt;
			if (nPtr[i] < 1) 	nPtr[i] = M + (nPtr[i] % M) ;
		}
	}

	b_flg = true;//원판 숫자 삭제여부 확인
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++)
			if (circle[i][j]) 	dfs(i, j, circle[i][j]);
	}

	summ = 0, zeroCnt = M * N;
	if (b_flg) {//평균계산 및 조정
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (circle[i][j])	summ += circle[i][j];
				else
					zeroCnt--;
			}
		}

		double tmp = (double)summ / (double)zeroCnt;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (!circle[i][j])	continue;
				if (tmp > circle[i][j])
					circle[i][j]++;
				else if (tmp < circle[i][j])
					circle[i][j]--;
			}
		}
	}
}

int main() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		nPtr[i]++;
		for (int j = 1; j <= M; j++)	cin >> circle[i][j];
	}

	for (int i = 1; i <= T; i++) {
		cin >> xdk[i][0] >> xdk[i][1] >> xdk[i][2];
		fu(i);
	}

	for (int i = 1; i <= N; i++) {//전체 원판 값 
		for (int j = 1; j <= M; j++) {
			if (circle[i][j])	res += circle[i][j];
		}
	}

	cout << res;
	return 0;
}
