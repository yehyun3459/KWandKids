#include <iostream>
#include <cstring>

using namespace std;

int N; //크기
int map[20][20]; //맵
int visited[20][20]; //방문 표시 맵
int queue[10000]; //큐
int feed_time; //상어가 물고기 먹는데 걸린 총 시간
int dR[4] = { -1, 0, 0, 1 }; //행 델타 배열
int dC[4] = { 0, -1, 1, 0 }; //열 델타 배열

//가장 가까운 거리의 물고기 중 가장 우선순위 물고기의 위치를 반환하는 함수
int findPrey(int p, int s_size) //매개변수: 물고기와의 거리, 상어 크기
{
	//위에서 부터 탐색하여 물고기를 찾은 거리와 같고 
	//실제로 빈 칸이나 못 먹는 물고기가 아닌 것을 찾았을 때
	//(i=0부터 j도 0부터 탐색하므로 거리가 같은 물고기 중 
	//가장 상단에 위치한 것중 가장 좌측에 있는 물고기를 반환)
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (visited[i][j] == p&&0<map[i][j]&&map[i][j]<s_size)
				return i * N + j;
}

//해당 위치가 맵에 속하는 지 반환
int isMap(int r, int c)
{
	return 0 <= r && r < N && 0 <= c && c < N;
}

//상어 물고기 식사 시작
void bfs(int r, int c)
{
	memset(visited, -1, sizeof(visited)); //방문 맵을 모두 -1로 세팅
	int f = -1, t = -1; //큐의 첫 원소 자리, 마지막 다음 자리(다음 원소 들어갈 자리)
	int pos, rr, cc; //1차원으로 변환된 위치, 다음 행 위치, 다음 열 위치
	int s_size = 2; //상어 크기
	int qsize = 0; //큐 사이즈
	int feed_cnt = 0; //먹은 물고기 수
	int flag = 0; //먹을 물고기 있는지 나타내는 flag
	int limit = 0; //각 단계(거리)마다 큐 사이즈를 나타내기 위한 변수
	int prey = 0; //가장 가까운 물고기와의 거리
	queue[++t] = r * N + c; //큐에 현재 상어 위치 넣음(1차원으로 축약하여 삽입)
	qsize++; //큐 사이즈+1
	visited[r][c] = 0; //첫 방문점임을 표시
	while (f != t) //큐 사이즈 0이상일 때(큐의 첫 원소 자리가 큐 마지막 원소 다음 자리와 같으면 큐 사이즈 = 0)
	{
		flag = 0; 
		limit = qsize; //큐 사이즈 받아옴
		for (int i = 0; i < limit; i++) //받아온 큐 사이즈 만큼 큐에서 원소 삭제하며 탐색
		{
			pos = queue[++f]; //큐 첫 번째 원소 받아옴
			qsize--; //큐 사이즈-1
			r = pos / N; //행 위치
			c = pos % N; //열 위치
			for (int j = 0; j < 4; j++) //상, 좌, 우, 하에 대해
			{
				rr = r + dR[j]; cc = c + dC[j]; //다음 위치 설정
				if (isMap(rr, cc) && visited[rr][cc] < 0 && map[rr][cc] <= s_size) //맵에 속하고 방문하지 않았고 상어가 지나갈 수 있으면
				{
					if (0 < map[rr][cc] && map[rr][cc] < s_size) //빈 칸이 아니고 상어 보다 작은 물고기면
					{
						flag = 1; //먹을 수 있는 가장 가까운 물고기 찾았음을 나타냄
						prey = visited[r][c] + 1; //가장 가까운 물고기와의 거리 기록
					}
					visited[rr][cc] = visited[r][c] + 1; //다음 방문위치는 현재 보다 1초 지났음을 기록
					queue[++t] = rr * N + cc; // 큐에 다음 위치 삽입
					qsize++; //큐 사이즈+1
				}
			}			
		}
		if (flag) //먹을 물고기가 있을 때
		{
			cc = findPrey(prey, s_size); //같은 거리 중 가장 우선순위 물고기 위치 받아옴
			rr = cc / N; //먹을 물고기 행 위치
			cc = cc % N; //먹을 물고기 열 위치
			map[rr][cc] = 0; //물고기 있던 자리 빈 칸으로 만듦
			f = -1; t = -1; //큐 초기화
			feed_time += prey; //아기상어 총 식사 시간에 현재 물고기 먹으러 간 시간(=거리) 더함
			feed_cnt++; //먹은 물고기 수+1
			if (feed_cnt == s_size) //먹은 물고기 수가 상어 사이즈와 같아지면
			{
				feed_cnt = 0; //물고기 수 초기화
				s_size++; //상어 크기+1
			}
			memset(visited, -1, sizeof(visited)); //방문 맵 모두 -1로 설정
			visited[rr][cc] = 0; //물고기 먹은 현재 위치 방문 표시
			queue[++t] = rr * N + cc; //큐에 현재 위치 삽입
			qsize = 1; //큐 사이즈 1로 설정
			flag = 0; //다시 flag 0으로 만듦
		}
	}
	//큐 사이즈가 0이 되어 더이상 탐색 할 수 없는 상황이면 엄마 상어 부름으로써 아기상어의 식사는 종료됨
}

int main()
{
	scanf("%d", &N);
	int r, c;
	for(int i=0; i<N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) //상어 있는 곳
			{
				r = i; c = j; //상어 위치 기록
			}
		}
	feed_time = 0; //아기 상어 총 식사시간 0으로 설정
	map[r][c] = 0; //편한 탐색을 위해 상어 위치 0으로 바꿈
	bfs(r, c); //상어 식사 시작
  
	cout << feed_time;

	return 0;
}
