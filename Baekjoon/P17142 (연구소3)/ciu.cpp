#include <iostream>
#include <queue>
#include <cstring>
//백준 17142
using namespace std;

int N; //맵 크기
int M; //바이러스 활성화 될 개수
int posR[10] = { 0, }; //활성화 될 수 있는 바이러스 행 좌표
int posC[10] = { 0, }; //활성화 될 수 있는 바이러스 열 좌표
int chooseR[10] = { 0, }; //선택된 M개의 활성화 바이러스 행 좌표
int chooseC[10] = { 0, }; //선택된 M개의 활성화 바이러스 열 좌표
char visited[10] = { 0, }; //dfs를 위한 선택된 바이러스 표현하는 배열
int dR[4] = { 0, 1, 0, -1 }; //행에 대한 델타 배열
int dC[4] = { 1, 0, -1, 0 }; //열에 대한 델타 배열
int V = 0; //활성화 될 수 있는 총 바이러스 개수
int map[50][50] = { {0,} }; //바이러스, 벽, 빈칸 등을 나타낼 맵
int map_visit[50][50]; //bfs에서 방문했는지 확인할 배열
int min_time = 0; //최소 시간

//r,c가 맵 범위 안에 드는지 확인하는 함수
int isMap(int r, int c)
{
	return (0 <= r && r < N && 0 <= c && c < N);
}

//선택된 바이러스들에 대해 시간이 얼마나 걸릴지 확인하는 함수
int bfs()
{
	memset(map_visit, 0, sizeof(map_visit)); //방문확인 배열 초기화
	int r, c, nextR, nextC, size; //행, 열, 다음행, 다음열, 큐 사이즈
	int time = 0; //걸린 시간
	int tmp_time = 0; //잠시 시간 저장할 변수(빈 칸이 아니라 비활성 바이러스 일 때)
	int flag = 0; //빈 칸을 찾았는지 확인하는 flag
	queue<int> q; //다음 탐색해야 할 칸 들을 담을 큐
	//먼저 선택한 바이러스의 행,열을 큐에 담음(행, 열을 하나로 합침)
	for (int i = 0; i < M; i++)
		q.push(chooseR[i] * N + chooseC[i]);
	size = q.size(); //큐 사이즈 기록
	//더 이상 탐색할 지점이 없을 때 까지
	while (!q.empty())
	{
		//큐 사이즈 만큼
		for (int i = 0; i < size; i++)
		{
			r = q.front() / N; //큐에 담긴 첫 항목을 행으로 변환
			c = q.front() % N; //큐에 담긴 첫 항목을 열로 변환
			map_visit[r][c] = 1; //현재 지점에 방문했음을 표시
			q.pop(); //큐의 첫 항목 삭제
			//전후좌우 4방향에 대해 탐색
			for (int j = 0; j < 4; j++)
			{
				nextR = r + dR[j];
				nextC = c + dC[j];
				//다음 탐색 지점이 맵안에 있고 방문하지 않았으며 빈칸이거나 비활성 바이러스 일 때
				if (isMap(nextR, nextC) && (map[nextR][nextC] == 0 || map[nextR][nextC] == 2) && !map_visit[nextR][nextC])
				{
					if (map[nextR][nextC] == 0) //빈칸이면 빈칸을 찾았음을 표시
						flag = 1;
					map_visit[nextR][nextC] = 1; //방문했음을 표시
					q.push(nextR * N + nextC); //다음 탐색지점으로 큐에 넣음
				}
			}
		}
		size = q.size(); //큐 사이즈 기록
		if (!flag) //비활성 바이러스였으면 임시 시간을 더 함
			tmp_time++;
		else //빈 칸이었으면
		{
			time += tmp_time + 1; //시간을 1 늘리며 이전의 임시 시간을 더 함
			tmp_time = 0; //임시 시간 초기화
		}
		flag = 0; //flag 초기화
		if (size == 0) 
			break;
	}
	//탐색이 끝났는데 방문하지 않은 빈칸이 있는지 탐색
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] == 0 && map_visit[i][j] == 0)
				return N * N; //방문하지 않은 빈칸이 있었으면 전체 감염 불가함을 표현
	return time; //방문하지 않은 빈칸 없으면 시간 
	
}

//바이러스 M개 선택하는 함수
void dfs(int K, int k, int idx)
{
	if (K == k)
	{
		int time = bfs();
		if (time < min_time)
			min_time = time;
	}
	else {
		for (int i = idx; i < V; i++)
		{
			if (!visited[i])
			{
				visited[i] = 1;
				chooseR[k] = posR[i];
				chooseC[k] = posC[i];
				dfs(K, k + 1, i + 1);
				chooseR[k] = -1;
				chooseC[k] = -1;
				visited[i] = 0;
			}
		}
	}
}

int main(int argc, char** argv)
{
	memset(chooseR, -1, sizeof(chooseR));
	memset(chooseC, -1, sizeof(chooseC));
	memset(map, -1, sizeof(map));
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)
			{
				posR[V] = i;
				posC[V] = j;
				V++;
			}
		}
	min_time = N * N;
	dfs(M, 0, 0);
	min_time = (min_time < (N * N)) ? min_time : -1;
	cout << min_time;

	return 0;
}
