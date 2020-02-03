#include <iostream>
#include <queue>
#include <cstring>
//백준 17142
using namespace std;

int N;
int M;
int posR[10] = { 0, };
int posC[10] = { 0, };
int chooseR[10] = { -1, };
int chooseC[10] = { -1, };
char visited[10] = { 0, };
int dR[4] = { 0, 1, 0, -1 };
int dC[4] = { 1, 0, -1, 0 };
int V = 0;
int map[50][50] = { {-1,} };
int map_visit[50][50];
int min_time = 0;

int isMap(int r, int c)
{
	return (0 <= r && r < N && 0 <= c && c < N);
}

int bfs()
{
	memset(map_visit, 0, sizeof(map_visit));
	int r, c, nextR, nextC, size;
	int time = 0;
	int tmp_time = 0;
	int flag = 0;
	queue<int> q;
	for (int i = 0; i < M; i++)
		q.push(chooseR[i] * N + chooseC[i]);
	size = q.size();
	while (!q.empty())
	{
		
		for (int i = 0; i < size; i++)
		{
			r = q.front() / N;
			c = q.front() % N;
			map_visit[r][c] = 1;
			q.pop();
			for (int j = 0; j < 4; j++)
			{
				nextR = r + dR[j];
				nextC = c + dC[j];
				if (isMap(nextR, nextC) && (map[nextR][nextC] == 0 || map[nextR][nextC] == 2) && !map_visit[nextR][nextC])
				{
					if (map[nextR][nextC] == 0)
						flag = 1;
					map_visit[nextR][nextC] = 1;
					q.push(nextR * N + nextC);
					//flag = 1;
				}
			}
		}
		size = q.size();
		if (!flag)
			tmp_time++;
		else
		{
			time += tmp_time + 1;
			tmp_time = 0;
		}
		flag = 0;
		if (size == 0)
			break;
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] == 0 && map_visit[i][j] == 0)
				return N * N;
	return time;
	
}

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
