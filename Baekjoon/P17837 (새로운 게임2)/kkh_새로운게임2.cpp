#include "iostream"
using namespace std;
int N, K, num, board[14][14], order[14];//각 말의 높이
pair<pair<int, int>, int > phorse[13];//(y,x),d

void white(int num, int y, int x) {//흰색 칸
	int n_horse_cnt = 0;
	for (int n = 1; n <= K; n++) { 
		if (y == phorse[n].first.first && x == phorse[n].first.second)
			n_horse_cnt++;	//이동 하려는 칸의 말의 개수
	}
	int past_y = phorse[num].first.first;
	int past_x = phorse[num].first.second;
	int past_order = order[num];
	for (int n = 1; n <= K; n++) { //이전 칸 말 중 올라타고 있는 말만 선정
		if (past_y == phorse[n].first.first && past_x == phorse[n].first.second && order[n] >= past_order) {
			order[n] = n_horse_cnt + order[n] - past_order + 1;
			phorse[n].first.first = y;
			phorse[n].first.second = x;
		}
	}
}

void red(int num, int y, int x) {//빨간색 칸
	int tmp_y = y, tmp_x = x;
	int n_horse_cnt = 0;
	for (int n = 1; n <= K; n++) {
		if (tmp_y == phorse[n].first.first && tmp_x == phorse[n].first.second)
			n_horse_cnt++;//이동하려는 칸의 말 개수
	}
	int past_y = phorse[num].first.first;
	int past_x = phorse[num].first.second;
	int upcnt = 0, past_order = order[num];
	for (int n = 1; n <= K; n++) { //이전 칸 중 올라타고 있는 말의 개수
		if (past_y == phorse[n].first.first && past_x == phorse[n].first.second && order[n] >= past_order)
			upcnt++;
	}
	for (int n = 1; n <= K; n++) { //이전 칸 중 올라타고 있는 말들 높이 변경
		if (past_y == phorse[n].first.first && past_x == phorse[n].first.second && order[n] >= past_order) {
			order[n] = n_horse_cnt + upcnt + past_order - order[n];
			phorse[n].first.first = tmp_y;
			phorse[n].first.second = tmp_x;
		}
	}
}

void blue(int num, int y, int x, int dir) {//파란색 칸
	int tmp_y = y, tmp_x = x, del_x[5] = { 0, -2, 2, 0, 0 }, del_y[5] = { 0, 0, 0, 2, -2 }, change_dir[5] = { 0, 2,1,4,3 };
	phorse[num].second = change_dir[dir];//반대반향으로 변환
	if (board[tmp_y + del_y[dir]][tmp_x + del_x[dir]] == 1)// 이동한 칸이 빨간색일 경우
		red(num, tmp_y + del_y[dir], tmp_x + del_x[dir]);
	else if (board[tmp_y + del_y[dir]][tmp_x + del_x[dir]] != 2 && //이동한 칸이 흰색인 경우
		tmp_y + del_y[dir] <= N && tmp_y + del_y[dir] > 0 && tmp_x + del_x[dir] <= N && tmp_x + del_x[dir] > 0)
		white(num, tmp_y + del_y[dir], tmp_x + del_x[dir]);
}

int main() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> board[i][j];

	for (int i = 1; i <= K; i++) {
		cin >> phorse[i].first.first >> phorse[i].first.second >> phorse[i].second;
		order[i] = 1;
	}

	for (int cnt = 1; ; cnt++) {
		for (int num = 1; num <= K; num++) {
			int tmp_y = phorse[num].first.first;
			int tmp_x = phorse[num].first.second;
			int dir = phorse[num].second;

			if (dir == 1)		tmp_x++;
			else if (dir == 2)	tmp_x--;
			else if (dir == 3)	tmp_y--;
			else if (dir == 4)	tmp_y++;

			if (board[tmp_y][tmp_x] == 2) //이동할 칸이 파란색
				blue(num, tmp_y, tmp_x, dir);
			else if (board[tmp_y][tmp_x] == 1) //이동할 칸이 빨간색
				red(num, tmp_y, tmp_x);
			else if (tmp_y > N || tmp_y < 1) { //y값이 넘어갈경우
				dir == 3 ? tmp_y += 2 : tmp_y -= 2;
				dir == 3 ? phorse[num].second = 4 : phorse[num].second = 3;
				if (board[tmp_y][tmp_x] == 1) //반대로 이동한 칸이 빨간색
					red(num, tmp_y, tmp_x);
				else if (board[tmp_y][tmp_x] != 2) //반대로 이동한 칸이 빨간색
					white(num, tmp_y, tmp_x);
			}
			else if (tmp_x > N || tmp_x < 1) { //x값이 넘어갈 경우
				dir == 2 ? tmp_x += 2, phorse[num].second = 1 : tmp_x -= 2, phorse[num].second = 2;
				dir == 2 ? phorse[num].second = 1 : phorse[num].second = 2;
				if (board[tmp_y][tmp_x] == 1) //반대로 이동한 칸이 빨간색
					red(num, tmp_y, tmp_x);
				else if (board[tmp_y][tmp_x] != 2) //반대로 이동한 칸이 흰색
					white(num, tmp_y, tmp_x);
			}
			else
				white(num, tmp_y, tmp_x);

			for (int i = 1; i <= K; i++) {
				if (order[i] >= 4) {//말의 높이가 4층 이상 존재하는 경우 출력
					cout << cnt;
					exit(0);
				}
			}
			if (cnt > 1000) {
				cout << -1;
				exit(0);
			}
		}
	}
	return 0;
}