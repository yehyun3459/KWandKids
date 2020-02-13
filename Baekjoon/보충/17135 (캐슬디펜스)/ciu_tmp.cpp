#include <cstdio>

using namespace std;

int N, M, D;
int map[16][15];
int enemys[226][3];
int enemy_cnt=1;

int main()
{
	scanf("%d %d %d", &N, &M, &D);
	for(int i=0; i<N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j])
			{
				enemys[enemy_cnt][0] = i;
				enemys[enemy_cnt][1] = j;
				map[i][j] = enemy_cnt++;
			}
		}
	for(int i=0; i<3; i++)
}
