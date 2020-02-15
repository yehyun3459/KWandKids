#include <cstdio>
//Baekjoon - 14500(테트로미노)
using namespace std;

int N, M;
int map[500][500];
char visited[500][500];
int dR[4] = { -1, 0, 1, 0 };
int dC[4] = { 0, 1, 0, -1 };
int selected[4][2];
int max_sum;

//selected에 k까지 쌓인 블록들 각각 주변 블록들을 다 집어 넣음
void find(int n, int k, int r, int c)
{
	if (n == k) //4개 다 쌓이면
	{
		int result = 0;
		for (int i = 0; i < 4; i++) //쌓인 selected에 대해 값 다 더해봄
			result += map[selected[i][0]][selected[i][1]];
		if (result > max_sum)
			max_sum = result;
	}
	else
	{
		int rr, cc;
		for (int t = 0; t < k; t++) //k까지 쌓인 selected에 대해
		{
			r = selected[t][0]; c = selected[t][1]; //r,c 값 받고
			for (int i = 0; i < 4; i++) //4방향에 대해
			{
				rr = r + dR[i]; cc = c + dC[i]; //rr, cc 만들고
				if (rr < 0 || rr >= N || cc < 0 || cc >= M) continue;
				if (!visited[rr][cc]) //방문하지 않았으면 selected에 쌓음
				{
					visited[rr][cc] = 1;
					selected[k][0] = rr; selected[k][1] = cc;
					find(n, k + 1, rr, cc);
					selected[k][0] = -1; selected[k][1] = -1;
					visited[rr][cc] = 0;
				}
			}
		}
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			visited[i][j] = 1;
			selected[0][0] = i; selected[0][1] = j;
			find(4, 1, i, j); //하나 넣어서 돌려봄
			selected[0][0] = -1; selected[0][1] = -1;
			visited[i][j] = 0;
		}
	printf("%d", max_sum);
	return 0;
}
