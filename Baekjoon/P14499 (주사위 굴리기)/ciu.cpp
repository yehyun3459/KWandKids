#include <cstdio>
//#include <cstring>
using namespace std;

int N, M, r, c, K; //맵의 행, 열, 주사위 위치 행, 열, 명령 개수
int map[20][20]; //맵
int dice[4][3]; //주사위 상태
int dR[4] = { 0, 0, -1, 1 }; //동, 서, 북, 남
int dC[4] = { 1, -1, 0, 0 };

//디버깅용
//void init()
//{
//	dice[1][0] = dice[1][1] = dice[1][2] = dice[0][1] = dice[2][1] = dice[3][1] = 0;
//}

//주사위 회전 및 수 복사
void rotate(int dir)
{
	int rr, cc;
	rr = r + dR[dir]; cc = c + dC[dir]; //다음 칸 구하기
	if (rr < 0 || rr >= N || cc < 0 || cc >= M) return; //맵 넘어갈 시 함수 종료
	int tmp;
	//동, 서, 북, 남 회전에 따른 주사위 회전
	switch (dir) 
	{
	case 0: tmp = dice[1][1]; dice[1][1] = dice[1][0]; dice[1][0] = dice[3][1];
		dice[3][1] = dice[1][2]; dice[1][2] = tmp; break;
	case 1: tmp = dice[1][1]; dice[1][1] = dice[1][2]; dice[1][2] = dice[3][1];
		dice[3][1] = dice[1][0]; dice[1][0] = tmp; break;
	case 2: tmp = dice[0][1]; dice[0][1] = dice[1][1]; dice[1][1] = dice[2][1];
		dice[2][1] = dice[3][1]; dice[3][1] = tmp; break;
	case 3: tmp = dice[3][1]; dice[3][1] = dice[2][1]; dice[2][1] = dice[1][1];
		dice[1][1] = dice[0][1]; dice[0][1] = tmp; break;
	}
	if (map[rr][cc]) { dice[3][1] = map[rr][cc]; map[rr][cc] = 0; } //칸이 0이 아니면 주사위 밑에 복사, 0으로 만들기
	else map[rr][cc] = dice[3][1]; //칸이 0이면 주사위 밑 수를 칸에 복사
	//디버깅용
	/*printf("%d %d\n", r, c);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (dice[i][j] >= 0)
				printf("%d ", dice[i][j]);
			else
				printf("  ");
		}
		printf("\n");
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}*/

	printf("%d\n", dice[1][1]); //주사위 윗 면 출력
	r = rr; c = cc; //주사위 위치 갱신
}

int main()
{
	//memset(dice, -1, sizeof(dice)); //디버깅 용
	//init(); //디버깅 
	scanf("%d %d %d %d %d", &N, &M, &r, &c, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	int cmd;
	for (int i = 0; i < K; i++)
	{
		scanf("%d", &cmd);
		rotate(cmd - 1);
	}
}
