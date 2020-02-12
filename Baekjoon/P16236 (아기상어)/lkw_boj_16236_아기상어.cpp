#include<iostream>
using namespace std;

int N = 0;
int sharksize = 2;
int eatcount = 0;
int sy = 0, sx = 0, fy = 0, fx = 0;
int time = 0;

int arr[20][20]; // 9 : 상어, 0 : 빈칸, 1~6 : 물고기크기
bool canmove[20][20]; // 움직일 수 있는 곳
int caneat[20][20];
bool visit[20][20];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

void findcanmove() { // 움직일 수 있는 곳 구하는 함수
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			if (sharksize >= arr[j][i] && arr[j][i] != 9)
				canmove[j][i] = 1;
			else canmove[j][i] = 0;
}
void search_init() { // visit 초기화
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			visit[j][i] = 0;
}
void search(int y, int x) {// bfs로 해야지, 입력 받은 위치를 기준으로 너비우선 탐색
	int qy[1001];
	int qx[1001];
	int dis[1001];
	int head = 0;
	int tail = 0;

	qy[tail] = y;
	qx[tail] = x;
	dis[tail] = 0;
	tail++;

	int y1, x1, d1;
	while (head < tail) {
		y1 = qy[head];
		x1 = qx[head];
		d1 = dis[head];
		head++;

		if (visit[y1][x1])
			continue;
		else
			visit[y1][x1] = 1;
		//cout << "y1 : " << y1 << ", x1 : " << x1 << endl;
		if (y1 == sy && x1 == sx) { // 자신을 먹지 말라
			caneat[y1][x1] = 0;
		}
		else if (sharksize > arr[y1][x1] && arr[y1][x1] > 0) { // 먹을 수 있는 거 거리 저장
			caneat[y1][x1] = d1;
		}
		else caneat[y1][x1] = 0;

		int y0, x0;
		for (int i = 0; i < 4; i++) {
			y0 = y1 + dy[i];
			x0 = x1 + dx[i];
			if (y0 >= 0 && y0 < N && x0 >= 0 && x0 < N && visit[y0][x0] == 0 && canmove[y0][x0]) {
				qy[tail] = y0;
				qx[tail] = x0;
				dis[tail] = d1 + 1;
				tail++;
			}
		}
	}
}
bool eatfish() { // 상어야 밥먹자
	int dis = 10000;
	bool flg = 0;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (caneat[j][i] > 0) { // 먹을 수 있는 녀석인가
				flg = 1; // 먹을 수 있는게 최소 하나 이상
				int tmp = caneat[j][i];
				if (dis > tmp) { // 가까운 녀석을 찾아보자
					dis = tmp;
					fy = j;
					fx = i;
				}
				else if (dis == tmp) { // 같은 거리면 우선순위를 따져보자
					if (j < fy) {
						fy = j;
						fx = i;
					}
					else if (j == fy && i < fx) {
						fy = j;
						fx = i;
					}
				}
			}
		}
	}
	if (!flg) return flg; // 못먹음 ㅠ

	eatcount++; // 먹은 횟수 카운트
	time += dis; // 걸린시간
	arr[sy][sx] = 0; // 상어위치 업데이트
	sy = fy;
	sx = fx;
	arr[sy][sx] = 9; // 상어위치 업데이트

	if (eatcount / sharksize > 0) { // 나이 먹음
		sharksize++;
		eatcount = 0;
	}

	return flg;
}
void prt() {
	cout << "arr" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			cout << arr[j][i];
		cout << endl;
	}
	cout << "move" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			cout << canmove[j][i];
		cout << endl;
	}
	cout << "eat" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			cout << caneat[j][i];
		cout << endl;
	}
	cout << "sharksize : " << sharksize << ", eatcount : " << eatcount << ", time : " << time << endl;
}
int main() {
	cin >> N;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++) {
			cin >> arr[j][i];
			if (arr[j][i] == 9) {
				sy = j;
				sx = i;
			}
		}
	sharksize = 2;
	time = 0;
	eatcount = 0;
	// 먹을 수 있는 물고기 파악
	// 먹으러 갈 수 있는 물고기 파악
	// 가장 가까운 물고기 먹어 (우선순위 : 1. y 좌표 작은거 2. x좌표 작은거)
	//prt();
	while (1) {

		findcanmove(); // 움직일 수 있는 곳 체크
		search_init(); // visit 초기화
		search(sy, sx); // 먹이 탐색
		//prt();
		if (!eatfish()) // 먹을 수 없을 때 까지
			break;
	}
	cout << time;

	return 0;
}