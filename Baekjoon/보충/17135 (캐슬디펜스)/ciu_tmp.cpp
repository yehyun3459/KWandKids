#include <cstdio>
#include <cstring>
using namespace std;

int N, M, D; //행, 열, 사정거리
int map[16][15]; //맵(맵에서 사라지는 적을 위해 한 행 더 함)
int enemys[226][2]; //적의 위치를 저장하는 배열
char dead[226]; //적이 죽었는지 나타내는 배열
int enemy_cnt = 0; //적의 수
int archers[3]; //궁수 배치
int max_kill=0; //최대 킬 수

//적을 맵에 다시 배치하고 생존여부 리셋
void enemy_init()
{
	for (int i = 1; i <= enemy_cnt; i++)
		map[enemys[i][0]][enemys[i][1]] = i;
	memset(dead, 0, sizeof(dead));
}

//배치된 궁수로 적을 죽이는 함수
void kill()
{
	int r, c, min_dist, dist, rr, cc; //궁수 위치, 최소 거리, 거리, 적 위치
	int kill_flag; //적을 죽였는지 나타내는 flag
	int remain = enemy_cnt, kill=0; //남은 적 수, kill 수
	while (remain > 0) //적이 다 사라질 때 까지
	{
		for (int i = 0; i < 3; i++) //3명의 궁수에 대해
		{
			kill_flag = 0;
			min_dist = N + M;
			r = N; c = archers[i];
			for (int j = 0; j < M; j++)
				for (int i = 0; i < N; i++)
				{
					if (map[i][j]) //맵에 적이 있으면
					{
						dist = r - i < 0 ? i - r : r - i;
						dist += c - j < 0 ? j - c : c - j;
						if (dist<=D&&dist < min_dist)
						{
							min_dist = dist;
							rr = i; cc = j; //적 위치 기억
							kill_flag = 1;
						}
					}
				}
			if(kill_flag) //죽인 적이 있을 때
				dead[map[rr][cc]] = 1; //적 죽었음을 표시
		}
		//맵에서 실제로 적 상태 갱신
		for (int i = N - 1; i >= 0; i--)
			for (int j = 0; j < M; j++)
			{
				if (map[i][j]) //맵에 적이 있으면
				{
					if (dead[map[i][j]]) //죽인 적이면 
					{
						map[i][j] = 0;
						remain--; kill++; //남은 적수 줄이고 kill수 늘림
					}
					else if (i + 1 >= N) //마지막칸을 넘어가게 되면
						remain--; //남은 적 수 줄임
					map[i + 1][j] = map[i][j]; //적을 다음 칸으로 옮기고
					map[i][j] = 0; //현재 칸은 0으로 만듦
				}
			}
	}
	if (kill > max_kill) //총 킬 수가 최대 킬 수 보다 많으면
		max_kill = kill; //최대 킬 수 갱신
}

int main()
{
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j])
			{
				enemys[++enemy_cnt][0] = i; //적 위치 기록
				enemys[enemy_cnt][1] = j;
				map[i][j] = enemy_cnt; //맵에 적을 해당 번호로 기록
			}
		}
	//궁수 위치 조합 및 적 처리
	for (int i = 0; i < M - 2; i++)
	{
		archers[0] = i;
		for (int j = i + 1; j < M - 1; j++)
		{
			archers[1] = j;
			for (int k = j + 1; k < M; k++)
			{
				archers[2] = k;
				enemy_init(); //적 위치 초기화
				kill(); //적 처리
				if (max_kill >= enemy_cnt) break; //적을 모두 죽인 경우 그대로 끝
			}
			if (max_kill >= enemy_cnt) break;
		}
		if (max_kill >= enemy_cnt) break;
	}
	printf("%d", max_kill);
}
