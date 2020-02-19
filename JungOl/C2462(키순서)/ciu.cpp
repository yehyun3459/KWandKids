#include <cstdio>
#include <cstring>
//Jungol - 2462(키 순서)

#define IN 0 //그래프에서 진입 차수 인덱스
#define OUT 1 //진출 차수 인덱스
#define IIDX 2 //첫 진입 정점 인덱스
#define OIDX 502 //첫 진출 정점 인덱스

using namespace std;

int N, M; //학생 수, 비교 횟수
int g[501][1003]; //키 비교 그래프(더 키 큰 사람이 진출 정점으로, 더 작은 사람은 진입 정점으로 삽입)
int visited[501]; //방문 확인 배열

//진출 방향으로 dfs 탐색
void dfs(int v)
{
	visited[v] = 1;
	for (int i = 0; i < g[v][OUT]; i++) //0부터 진출 정점 갯수 만큼
	{
		if (!visited[g[v][OIDX + i]]) //i번째 진출 정점이 방문하지 않았던 정점이면
			dfs(g[v][OIDX + i]); //dfs 탐색 진행
	}
}

//진입 방향으로 dfs 탐색
void dfsRev(int v)
{
	visited[v] = 1;
	for (int i = 0; i < g[v][IN]; i++)
	{
		if (!visited[g[v][IIDX + i]])
			dfsRev(g[v][IIDX + i]);
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	int a, b;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &a, &b);
		g[a][OIDX+g[a][OUT]++] = b; //키 큰 사람을 진출 정점으로 삽입
		g[b][IIDX+g[b][IN]++] = a; //키 작은 사람을 진입 정점으로 삽입
	}
	int result=0; //결과
	int possible = 1; //키 순서 확인할 수 있는지 확인하는 flag
	for (int i = 1; i <= N; i++) //모든 학생들에 대해
	{
		possible = 1;
		memset(visited, 0, sizeof(visited));
		dfs(i); //키 더 큰 사람들 쪽으로 dfs
		dfsRev(i); //키 더 작은 사람들 쪽으로 dfs
		for (int j = 1; j <= N; j++)
		{
			if (!visited[j]) //방문한 적 없는 정점 있으면
			{
				possible = 0; //키 순서 확인 불가
				break;
			}
		}
		if (possible) result++; //키 순서 확인가능하면 result+1
	}
	printf("%d", result);
}
