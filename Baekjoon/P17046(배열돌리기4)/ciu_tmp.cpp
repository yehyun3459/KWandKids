#include <cstdio>

using namespace std;

int N, M, K;
int map[50][50];
int dR[4] = { 1, 0, -1, 0 };
int dC[4] = { 0, 1, 0, -1 };
int cmds[3][6];
char visited[6];
int min_result;

void rotate(int m_r, int m_c, int s, int map[50][50])
{
	for (int k = 1; k <= s; k++)
	{
		int r = m_r - k, c = m_c - k;
		int rr = r, cc = c;
		int tmp = map[r][c];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2 * k; j++)
			{
				r = rr; c = cc;
				rr = r + dR[i]; cc = c + dC[i];
				map[r][c] = map[rr][cc];
			}
		}
		map[r][c] = tmp;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void dfs(int n, int k, int map[50][50])
{
	if (n == k)
	{
		int sum=0;
		for (int i = 0; i < N; i++)
		{
			sum = 0;
			for (int j = 0; j < M; j++)
				sum += map[i][j];
			if (sum < min_result)
				min_result = sum;
		}
	}
	else
	{
		for (int i = 0; i < K; i++)
		{
			if (!visited[i])
			{
				visited[i] = 1;
				int newMap[50][50];
				for (int x = 0; x < N; x++)
					for (int y = 0; y < M; y++)
						newMap[x][y] = map[x][y];
				printf("%d\n", i);
				rotate(cmds[i][0], cmds[i][1], cmds[i][2], newMap);
				dfs(n, k + 1, newMap);
				visited[i] = 0;
			}
		}
	}
}

int main()
{
	min_result = 0;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
			min_result += map[i][j];
		}
	int r, c, s;
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d %d", &r, &c, &s);
		cmds[i][0] = r - 1;
		cmds[i][1] = c - 1;
		cmds[i][2] = s;
	}
	dfs(K, 0, map);
	printf("%d\n", min_result);
	return 0;
}
