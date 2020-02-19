#include <cstdio>
//Baekjoon - 17472(다리만들기2)
using namespace std;

int N, M; //맵 크기(행, 열)
int map[10][10]; //맵
char map_visit[10][10]; //섬 구별하기 위한 dfs를 위한 visited배열
int g[7][7]; //섬 연결 그래프

int visited[7]; //섬 연결 되었는지 나타내는 visited 배열
int island_cnt; //섬 개수
int dR[4] = { -1, 0, 1, 0 };
int dC[4] = { 0, 1, 0, -1 };

//섬을 찾고 섬을 구별할 숫자(1~6사이)로 표현하는 함수
void findIsland(int r, int c, int isl_cnt)
{
	map_visit[r][c] = 1;
	map[r][c] = isl_cnt + 1; //맵에 섬 넘버링
	int rr, cc;
	for (int i = 0; i < 4; i++)
	{
		rr = r + dR[i]; cc = c + dC[i];
		if (rr < 0 || rr >= N || cc < 0 || cc >= M) continue;
		if (!map_visit[rr][cc]&&map[rr][cc]>0) //방문한 적 없고 섬에 해당하면 dfs 계속 진행
		{
			findIsland(rr, cc, isl_cnt);
		}
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
		}
	for(int i=0; i<N; i++)
		for (int j = 0; j < M; j++)
		{
			if (!map_visit[i][j]&&map[i][j]>0) //방문한 적 없고 섬에 해당하면
			{
				findIsland(i, j, island_cnt); //섬 넘버링
				island_cnt++; //섬 개수 증가
			}
		}
	int k;
	//가로 다리를 찾아 그래프로 기록
	for(int i=0; i<N; i++)
		for(int j=0; j<M; j++)
			if (!map[i][j]) //0일 때
			{
				k = j;
				int weight=0;
				while (!map[i][k]&&k<M) //0아닐 때까지 길이 증가
				{
					weight++;
					k++;
				}
				if (j == 0 || k == M) { j = k; continue; } //그 전이나 후가 섬이 아니면 컨티뉴
				if (weight > 1) //다리 길이 1보다 클 때 그 전 섬(map[i][j-1])과 그 다음 섬(map[i][k]) 연결
				{
					if (!g[map[i][j-1]][map[i][k]] || g[map[i][j-1]][map[i][k]] > weight)
					{
						g[map[i][j-1]][map[i][k]] = weight;
						g[map[i][k]][map[i][j-1]] = weight;
					}
				}
				j = k;
			}
	//세로 다리를 찾아 그래프로 기록
	for (int j = 0; j < M; j++)
		for (int i = 0; i < N; i++)
			if (!map[i][j])
			{
				k = i;
				int weight = 0;
				while (!map[k][j]&&k<N)
				{
					weight++;
					k++;
				}
				if(i==0||k==N) { i = k; continue; }
				if (weight > 1)
				{
					if (!g[map[i-1][j]][map[k][j]] || g[map[i-1][j]][map[k][j]] > weight)
					{
						g[map[i-1][j]][map[k][j]] = weight;
						g[map[k][j]][map[i-1][j]] = weight;
					}
				}
				i = k;
			}
	int result = 0, remain = island_cnt-1; //결과, 연결 안 된 섬 수
	int invalid = 0; //연결되지 않는 섬이 있는지 나타내는 flag
	visited[1] = 1; //첫번째 섬을 연결된 상태로 둠
	int short_path = 0, v = 0; //연결됭 섬들과의 최소 거리, 그 때의 해당 섬
	//프림 알고리즘을 이용하여 최소신장트리, 즉 최소거리로 모든 섬 연결 시키기
	while (remain > 0)
	{
		short_path = N * M; v = -1;
		for (int i = 1; i <= island_cnt; i++)
		{
			if (visited[i])
			{
				for (int j = 1; j <= island_cnt; j++)
					if (g[i][j] && !visited[j] && g[i][j] < short_path)
					{
						short_path = g[i][j]; v = j;
					}
			}
		}
		if (short_path >= N * M) //최소거리가 변경 되지 않았으면(섬이 연결되지 않으면)
			invalid = 1; //섬 연결되지 않는 것을 표현
		result += short_path;
		visited[v] = 1;
		remain--;
	}
	if (invalid)
		result = -1;
	printf("%d", result);
}
