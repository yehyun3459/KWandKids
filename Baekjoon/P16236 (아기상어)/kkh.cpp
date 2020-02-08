#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, see[20][20], my[4] = { 0,0,-1,1 }, mx[4] = { 1,-1,0,0 };
struct fish { int y, x, size, eat, sec; }; // y,x, 물고기 or 상어 size, 먹은 횟수, total time
vector<fish> v;//구조체타입의 백터 선언
fish shark;//상어 위치 저장

bool bfs() {//가장 가까운 위치의 물고기 찾기 or 위치 갱신
	int isvis[20][20] = { 0 };//방문점 초기화
	bool b = false;
	queue<fish> q;
	q.push(shark);
	isvis[shark.y][shark.x] = 1;
	while (!q.empty()) {
		fish tmp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int move_y = tmp.y + my[i];
			int move_x = tmp.x + mx[i];
			if (move_y >= N || move_y < 0 || move_x >= N || move_x < 0)	continue;
			if (!isvis[move_y][move_x] && see[move_y][move_x] <= shark.size ) {//사이즈 같거나 작은지 확인
				isvis[move_y][move_x] = isvis[tmp.y][tmp.x] + 1;//시간 구하기 위해 1씩 추가
				q.push({ move_y , move_x, 0 });
			}
		}
	}

	int idx = 0, minn = 100000;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size >= shark.size)	continue;
		if (!isvis[v[i].y][v[i].x])		continue;
		if (minn > isvis[v[i].y][v[i].x]) {//가장 적은 시간의 물고기 인덱스 구하기
			minn = isvis[v[i].y][v[i].x];
			idx = i;
			b = true; //사냥했다는 표시
		}
		else if (minn == isvis[v[i].y][v[i].x]) {
			if (v[idx].y > v[i].y) {//거리 같을 땐 y값 먼저 비교
				idx = i;
				b = true;
			}				
			else if (v[idx].y == v[i].y) {//x값 비교
				if (v[idx].x > v[i].x) {
					idx = i;
					b = true;
				}					
			}
		}
	}

	if (b) {//b == true ? 사냥성공 : 사냥실패
		shark.y = v[idx].y;//상어 위치 갱신
		shark.x = v[idx].x;
		shark.eat++; //먹은 횟수 1추가
		if (shark.eat == shark.size) { 
			shark.size++; 
			shark.eat = 0;	
		}			
		shark.sec += minn - 1; //total time 누적		
		v.erase(v.begin() + idx);//먹은 물고기 삭제
	}
	return b;
}

int main() {
	scanf_s(" %d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf_s(" %d", &see[i][j]);
			if (see[i][j] >= 1 && see[i][j] <= 6)
				v.push_back({ i,j,see[i][j], 0 });
			else if (see[i][j] == 9)
				shark = { i , j, 2, 0, 0 };
		}
	see[shark.y][shark.x] = 0; //bfs할때 거슬려서 지움
	while (bfs());	//사냥 실패할때까지 반복
	printf("%d", shark.sec); 
	return 0;
}