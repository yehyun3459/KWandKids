#include <cstdio>
//Baekjoon - 3190(뱀,zmija)
using namespace std;

int N, K, L; //맵 크기, 사과 개수, 방향 전환 횟수
int S = 10000; //큐의 크기
int map[100][100];
int que[10000]; //뱀 위치 들어가는 원형 큐
int f, rear; //원형 큐의 앞과 뒤
int dR[4] = { -1, 0, 1, 0 }; //방향에 따른 뱀 머리의 다음 위치 델타 배열(상,우,하,좌)
int dC[4] = { 0, 1, 0, -1 };
int cmdT[100]; // 방향 전환 시간 배열
char cmdC[100]; //방향 전환 시 전환방향 배열
int result_time=1; //종료 시간

int main()
{
	scanf("%d", &N);
	scanf("%d", &K);
	int r, c;
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d", &r, &c);
		map[r-1][c-1] = 1; //사과의 위치를 맵에서 1로 표현
	}
	scanf("%d", &L);
	int time;
	char dirC;
	f = rear = -1;
	que[++rear] = 0; //큐 처음에 (0, 0) 1차원으로 변환하여 삽입
	for (int i = 0; i < L; i++)
	{
		scanf("%d %c", &time, &dirC);
		cmdT[i] = time;
		cmdC[i] = dirC;
	}
	int stop_flag = 0;
	int cmd_cnt = 0; //방향 전환 명령 인덱스
	int dir = 1; //현재 뱀 머리 방향(처음엔 오른쪽)
	r = 0, c = 0;
	map[r][c] = 3; //뱀이 존재하는 곳을 3으로 표현
	int rr, cc;
	while (!stop_flag)
	{
		rr = r + dR[dir]; cc = c + dC[dir]; //뱀의 다음 위치
		if (rr < 0 || rr >= N || cc < 0 || cc >= N) break; //맵 벗어나면 끝
		if (map[rr][cc] > 1) break; //해당 위치에 뱀 존재하면 끝
		r = rr; c = cc; //현재 뱀 머리 위치 갱신
		rear = (rear + 1) % S;
		que[rear] = r * N + c; //원형 큐 뒤에 현재 뱀 머리 위치 삽입
		if (!map[r][c]) //머리 부분에 사과가 없으면
		{
			f = (f + 1) % S; //큐 pop 하면서
			map[que[f] / N][que[f] % N] = 0; // 꼬리가 있던 부분을 맵에서 0으로 설정
		}
		map[r][c] = 3; //현재 뱀 머리 위치 맵에서 3으로 표현
		if (cmdT[cmd_cnt] == result_time) //방향 전환 할 시간이 되면
		{
			switch (cmdC[cmd_cnt])
			{
			case 'D': dir = (dir + 1) % 4; break;
			case 'L': dir = (dir + 3) % 4; break;
			}
			cmd_cnt++; //방향 바꿔준 뒤 다음 명령을 가리킴
		}
		/*printf("-----%d------\n", result_time); //디버깅 용
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				printf("%d ", map[i][j]);
			printf("\n");
		}*/
		result_time++;
	}

	printf("%d", result_time);
}
