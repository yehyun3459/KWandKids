#include <cstdio>
/*
dI[]	s	e	dir	dir_Str	rowcol	range	r		c
 1		0	N	0	up		col		0~N-1	i		rowcol
-1	   N-1	-1	2	down	col		N-1~0	i		rowcol
 1		0	N	1	left	row		0~N-1	rowcol	i
-1	   N-1	-1	3	right	row		N-1~0	rowcol	i
*/

using namespace std;

int N;
int raw_map[20][20];
int dR[4] = { -1, 0, 1, 0 };
int dC[4] = { 0, -1, 0, 1 };
int dI[2] = { 1, -1 };
int max_num = 0;


int isMap(int r, int c)
{
	return 0 <= r && r < N && 0 <= c && c < N;
}

//상,하,좌,우에 따라 움직이기
void move(int rowcol, int map[20][20], int dir)
{
	int r, rr, c, cc;
	int di = dir / 2;	//방향에 따른 i에 대한 델타배열 인덱스 정하기(상단 표)
	int merged = 0;		//직전에 합쳐졌는지 확인하는 flag
	int start, end;		//시작점, 끝점
	//방향에 따른 시작점, 끝점 정하기(상단 표)
	if (dir < 2)
	{
		start = 0, end = N;
	}
	else
	{
		start = N - 1, end = -1;
	}
	int i = start;

	while (i != end)	//각 행이나 각 열의 시작점부터 끝에 도달 할 때 까지
	{
		if (dir % 2 == 0)
		{
			r = i; c = rowcol;
		}
		else
		{
			r = rowcol; c = i;
		}
		//0이 아닌 경우만
		if (map[r][c])
		{
			rr = r + dR[dir]; cc = c + dC[dir];
			while (isMap(rr, cc)) //다음 칸이 맵에 속할 때
			{
				if (!map[rr][cc]) //0인 경우엔
				{
					//다음 칸으로 넘어가고 현재 칸은 0으로 만들기
					map[rr][cc] = map[r][c];
					map[r][c] = 0;
					r = rr; c = cc;
					rr = r + dR[dir]; cc = c + dC[dir];
				}
				else if (!merged && map[r][c] == map[rr][cc]) //직전에 합쳐지지 않았고 같은 숫자면
				{
					//합쳐짐을 표시하고 다음칸과 합치기
					merged = 1;
					map[r][c] = 0;
					map[rr][cc] *= 2;
					break;
				}
				else //직전이 합쳐졌던 경우엔 그자리에 머물고 합쳐지지 않음을 표시
				{
					merged = 0;
					break;
				}
			}
		}
		i += dI[di]; //그 다음 수 처리위해 i늘림(실제로는 줄어드는 방향일 수 있음)
	}
}

void dfs(int n, int k, int map[20][20], int dir)
{
	int new_map[20][20]; //맵 복사하고
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			new_map[i][j] = map[i][j];
	//방향에 따라 숫자 이동 및 합치기
	int start, end;
	int di = dir / 2;
	if (dir < 2)
	{
		start = 0; end = N;
	}
	else
	{
		start = N - 1; end = -1;
	}
	int i = start;
	while (i != end)
	{
		move(i, new_map, dir);
		i += dI[di];
	}
	if (n == k) //마지막 시도 일 때
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (new_map[i][j] > max_num)
					max_num = new_map[i][j]; //최대 값 찾기
	}
	else
	{
		for (int i = 0; i < 4; i++) //4방향에 대해 탐색 진행
			dfs(n, k + 1, new_map, i);
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &raw_map[i][j]);
	for (int i = 0; i < 4; i++)
		dfs(5, 1, raw_map, i);

	printf("%d\n", max_num);
}
