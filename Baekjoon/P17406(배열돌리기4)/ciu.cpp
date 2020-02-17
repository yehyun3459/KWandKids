#include <cstdio>
//Baekjoon - 17406(배열돌리기4)
using namespace std;

int N, M, K; //행, 열, 회전 연산 수
int map[50][50]; //맵
int dR[4] = { 1, 0, -1, 0 }; //회전 시 사용할 델타 배열
int dC[4] = { 0, 1, 0, -1 };
int cmds[6][3]; //회전 연산 (**이 부분 행,열을 반대로 적어 크게 헤맴)
char visited[6]; //순열 생성 시 사용할 배열, 해당 연산 줄 세웠는지 나타냄
int min_result; //최소값

//회전 연산
void rotate(int m_r, int m_c, int s, int map[50][50])
{
	for (int k = 1; k <= s; k++) //거리 1~s까지
	{
		int r = m_r - k, c = m_c - k; //위치를 왼쪽 상단에 둠
		int rr = r, cc = c;
		int tmp = map[r][c]; //첫 번째 자리 기억
		for (int i = 0; i < 4; i++) //하, 우, 상, 좌에 대해
		{
			for (int j = 0; j < 2 * k; j++) //길이 만큼 가면서
			{
				r = rr; c = cc;
				rr = r + dR[i]; cc = c + dC[i]; //다음 위치 잡고
				map[r][c] = map[rr][cc]; //다음 위치의 수를 현재 위치에 옮겨둠
			}
		}
		map[r][c] = tmp; //마지막 자리에 기억해둔 첫번째 수 기록
	}
}

//순열, 회전 연산 순서 정하기
void dfs(int n, int k, int map[50][50])
{
	if (n == k) //회전 연산 끝났으면 최대값 구함
	{
		int sum = 0;
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
		for (int i = 0; i < K; i++) //K개 연산중에
		{
			if (!visited[i]) //아직 줄세우지 않은것
			{
				visited[i] = 1;
				int newMap[50][50];
				for (int x = 0; x < N; x++)
					for (int y = 0; y < M; y++)
						newMap[x][y] = map[x][y];
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
