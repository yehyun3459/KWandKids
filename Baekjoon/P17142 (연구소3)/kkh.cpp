#include "iostream"
#include "cstring"
#include "queue"
using namespace std;
int N, M, nCnt_vir, Arr[50][50], isvis[50][50], virus[10][2], activeVir[10], move_x[4] = { 1, -1, 0 ,0 }, move_y[4] = { 0, 0, 1, -1 }, minn = INT32_MAX;
void dfs() {
	memset(isvis, 0, sizeof(isvis));//방문표기 초기화
	queue<pair<int, int> > q;
	for (int i = 0; i < nCnt_vir; i++) {
		if (activeVir[i]) {//활성된 바이러스 인덱스
			q.push({ virus[i][0], virus[i][1] }); //활성바이러스 큐에 추가
			isvis[virus[i][0]][virus[i][1]] = 1; //활성바이러스 좌표는 방문으로 표시
		}
	}

	while (!q.empty()) {
		int yy = q.front().first, xx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			if (yy + move_y[i] >= N || yy + move_y[i] < 0 || xx + move_x[i] >= N || xx + move_x[i] < 0)
				continue;//이동할 좌표 확인
			if (Arr[yy + move_y[i]][xx + move_x[i]] == 1 || isvis[yy + move_y[i]][xx + move_x[i]])
				continue;//이동할 좌표가 벽인지 방문했었는지 확인
			isvis[yy + move_y[i]][xx + move_x[i]] = isvis[yy][xx] + 1; //방문점에 1씩 추가하여 시간표시
			q.push({ yy + move_y[i] , xx + move_x[i] });
		}
	}
	int maxx = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (!Arr[i][j]) {
				if (isvis[i][j])
					maxx = maxx < isvis[i][j] ? isvis[i][j] : maxx; //젤 오래거린 시간 표시
				else
					return; //전부 탐색 못했을경우 리턴
			}

	if (minn > maxx - 1)
		minn = maxx - 1;
}

void activeVirus(int past, int cnt) {//활성바이러스 선택하기
	if (cnt >= M) {
		dfs();
		return;
	}
	for (int i = past + 1; i <= nCnt_vir - M + cnt; i++) {
		activeVir[i] = 1;
		activeVirus(i, cnt + 1);
		activeVir[i] = 0;
	}
}

int main() {
	iostream::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> Arr[i][j];
			if (Arr[i][j] == 2) { //바이러스 좌표 따로 저장
				virus[nCnt_vir][0] = i;
				virus[nCnt_vir++][1] = j;
			}
		}

	for (int i = 0; i <= nCnt_vir - M; i++) {
		activeVir[i] = 1;
		activeVirus(i, 1);
		activeVir[i] = 0;
	}

	if (minn == INT32_MAX)//초기값 그대로면 -1 출력
		cout << -1;
	else if (minn == -1)
		cout << 0;
	else
		cout << minn;
	return 0;
}
