#include <iostream>

using namespace std;

int status[10000][5]; //각 상어의 상태 배열 => r(행), c(열), s(속), d(방), z(크)가 M(상어 수)개
char map[100][100]; //낚시 풀(격자판) (각 자리에 있는 상어 수 나타냄)
int R, C, M; //낚시 풀의 행 크기, 열 크기, 상어 수
char dead[10000]; //상어가 낚였거나 먹혔음을 표시할 배열

//1,2,3,4에 따라 방향을 0(인덱스가 줄어듦을 의미), 1(늘어남을 의미)로 변환
int getDir(int d)
{
	if (d == 1 || d == 4) return 0; //상어 방향이 1 혹은 4면 인덱스가 줄어드는 방향이므로 0으로 치환
	return 1; //반대로 2 혹은 3이면 늘어나는 방향이므로 1로 치환
}

//상어 이동
void moveShark(int m)
{
	int r = status[m][0]; int c = status[m][1]; //현재 r, c 반환 받음
	int remain = status[m][2]; int d = getDir(status[m][3]); //속도(=남은 거리)와 방향을 받아옴
	int curr, max; //1차원으로 변환하기 위한 변수
	if (status[m][3] < 3) //위, 아래로 움직이는 경우 행에 대한 이동
	{
		curr = r; max = R; //현재 위치로 r을 받음, 최대 크기는 행의 크기.
	}
	else //좌,우로 움직이는 경우 열에 대한 이동
	{
		curr = c; max = C; //현재 위치로 c를 받음, 최대 크기는 열의 크기.
	}
	remain %= (max - 1) * 2; //(max-1)*2 만큼 이동하면 항상 제자리로 옴. 따라서 모듈러 연산을 하면 남은 거리 쉽게 줄임.
	while (remain > 0) //남은 거리 0 될 때 까지
	{
		if (d == 0) //줄어드는 방향일 때
		{
			if (remain > curr) //남은 거리가 현재 위치에서 경계선까지의 거리 보다 크면
			{
				remain -= curr; //남은 거리를 빼주고(curr-0이 현재 위치에서 왼쪽 혹은 위쪽 끝까지의 거리)
				curr = 0; d = 1; // 위 혹은 왼쪽 끝부분에 현재 위치 설정, 방향 전환
			}
			else //남은 거리가 현재 위치에서 경계선까지의 거리 보다 작으면
			{
				curr -= remain; //현재위치에서 남은거리 빼면 목적지 도착.
				remain = 0; //남은거리는 0
			}
		}
		else //늘어나는 방향일 때
		{
			if (remain > (max-1)-curr) //남은 거리가 현재위치에서 경계선까지의 거리 보다 크면
			{
				remain -= (max - 1) - curr; //남은 거리 빼줌((max-1)-curr이 현재 위치에서 오른쪽 혹은 아래쪽 끝까지의 거리)
				curr = max-1; d = 0; //아래 혹은 오른쪽 끝부분에 현재 위치 설정, 방향 전환
			}
			else //남은 거리가 현재위치에서 경계선까지의 거리보다 작으면
			{
				curr += remain; //현재위치에서 남은거리 더하면 목적지 도착.
				remain = 0; //남은 거리는 0
			}
		}
	}
	//도착지 계산 후 갱신
	if (status[m][3] < 3) //위, 아래로 움직이는 경우였을 때
	{
		map[curr][c]++; map[r][c]--; status[m][0] = curr; //맵에서 이전 위치는--, 옮길 위치는 ++, 상어의 상태 배열위치도 갱신
		if (d == 0) status[m][3] = 1; //방향 갱신
		else status[m][3] = 2;
	}
	else //좌, 우로 움직이는 경우였을 때
	{
		map[r][curr]++; map[r][c]--; status[m][1] = curr;
		if (d == 0) status[m][3] = 4;
		else status[m][3] = 3;
	}
}

//겹치는 상어 처리
void killShark(int r, int c)
{
	int prev=-1;
	for (int i = 0; i < M; i++) //전체 상어에 대해
		if (!dead[i] && status[i][0] == r && status[i][1] == c) //죽지 않았고, r,c에 해당하는 위치에 있는 상어의 경우
		{
			if (prev == -1) //이전에 찾은 상어 없으면 현재 인덱스 기억
				prev = i;
			else if (status[i][4] > status[prev][4]) //이전에 찾은 상어와 크기 비교
			{
				dead[prev] = 1; prev = i; map[r][c]--; //이전 상어가 더 작은 경우 이전 상어 죽이고 현재 인덱스를 prev로 만듦, 맵 갱신
			}
			else
			{
				dead[i] = 1; map[r][c]--; //지금 찾은 상어가 더 작은 경우 현재 상어 죽이고 맵 갱신
			}
		}
}

int main()
{
	scanf("%d %d %d", &R, &C, &M);
	int tmp;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			scanf("%d", &status[i][j]);
		}
		map[--status[i][0]][--status[i][1]]++; //인덱스가 1부터 시작하는 것을 0부터 시작하는 것을 변환하고 그 자리 +1(그 자리의 상어 수)
	}
	int king = 0; //낚시왕의 위치
	int sum = 0; //낚은 상어 크기 총합
	while (king < C)
	{
		//상어잡기
		for (int i = 0; i < R; i++) //행 늘려가며
		{
			if (map[i][king]) //상어가 있으면 
			{
				for (int j = 0; j < M; j++)
					if (!dead[j]&&status[j][0] == i && status[j][1] == king) //죽지 않고 그 자리에 있는 상어 찾기
					{
						sum += status[j][4]; //낚은 상어 크기 총합 업데이트
						dead[j] = 1; break; //상어가 잡혀서 죽었음을 표시
					}
				map[i][king] = 0;
				break; //그 다음 상어 잡지 않도록 break
			}
		}
		//상어 이동
		for (int i = 0; i < M; i++)
			if (!dead[i]) //살아있는 상어에 한해 이동
				moveShark(i);
		//상어 이동 후 겹치는 상어 처리
		for(int i=0; i<R; i++)
			for(int j=0; j<C; j++)
				if (map[i][j]>1) //2마리 이상 있는 곳을 처리
				{
					killShark(i, j);
				}

		king++; //낚시왕 이동
	}

	cout << sum;
}