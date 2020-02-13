#include <iostream>
#include <deque>
using namespace std;
int N, K, L, map[101][101], snake[101][101], sec, dir;
int my[4] = { 0,1,0,-1 }, mx[4] = { 1,0, -1,0 };
deque<pair<int, char> > d; //방향 회전
deque<pair<int, char> > d_snake; //뱀

int main() {
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		int a, b;
		cin >> a >> b;
		map[a][b] = 1;
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		int x;
		char c;
		cin >> x >> c;
		d.push_back({ x,c }); // 회전 타이밍 저장
	}

	d_snake.push_back({ 1,1 }); //뱀 시작
	for (sec = 1; ; sec++) {	
		pair<int, int> head = d_snake.front();
		d_snake.push_front({ head.first + my[dir], head.second + mx[dir] }); //머리 부터 이동
		head = d_snake.front();
		if (head.first > N || head.first <= 0 || head.second > N || head.second <= 0)	break; //밖으로 나가는지 확인
		
		for (int idx = 1; idx < d_snake.size(); idx++) {  //몸이랑 닿는지 확인
			if (head.first == d_snake[idx].first && head.second == d_snake[idx].second)
				goto Exit;		
		}
		
		if (!map[head.first][head.second]) //사과 확인
			d_snake.pop_back(); 
		else
			map[head.first][head.second] = 0;		

		if (!d.empty() && d.front().first == sec) { //방향에 따라 회전
			if (d.front().second == 'D') {
				dir++;
				if (dir >= 4)
					dir = 0;
			}
			else {
				dir--;
				if (dir < 0)
					dir = 3;
			}

			d.pop_front();
		}
	}

Exit : 
	cout << sec;

	return 0;
}
