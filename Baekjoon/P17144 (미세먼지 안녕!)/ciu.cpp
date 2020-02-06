#include <iostream>
//Baekjoon 17144
using namespace std;

int map[50][50]; //맵
int R, C, T; //행, 열, 초
int puri[2]; //공기청정기 아래부분 위치 0이 행, 1이 열
int dRU[4] = { -1, 0, 1, 0 }; //공기청정기 위쪽 순환 행 델타 배열
int dCU[4] = { 0, 1, 0, -1 }; //공기청정기 위쪽 순환 열 델타 배열
int dRD[4] = { 1, 0, -1, 0 }; //공기청정기 아래쪽 순환 행 델타 배열
int dCD[4] = { 0, 1, 0, -1 }; //공기청정기 아래쪽 순환 행 델타 배열

//맵 안에 있고 공기청정기가 아닌 지역인지 검사
int isMap(int r, int c)
{
	return 0 <= r && r < R && 0 <= c && c < C&&map[r][c] >= 0;
}

//먼지 확산
void spread()
{
	int tmp_map[50][50] = { {0} }; //임시 맵
	int spread_cnt = 0; //한 칸이 얼마나 확산되었는지 카운트
	int rr, cc; //주변 칸
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			spread_cnt = 0;
			for (int d = 0; d < 4; d++) //전,후,좌,우 네 방향에 대해
			{
				rr = i + dRU[d]; cc = j + dCU[d]; //다음 위치 세팅
				if (isMap(rr, cc)) //맵 안이고 공기청정기가 아닌 칸일 때
				{
					spread_cnt++; //확산 된 수 +1
					tmp_map[rr][cc] += map[i][j] / 5; //해당 칸 확산량을 임시 맵에 업데이트
				}
			}
			tmp_map[i][j] += map[i][j]-(map[i][j] / 5)*spread_cnt; //현재 칸에 남을 먼지 임시 맵에 업데이트
		}
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			map[i][j] = tmp_map[i][j]; //임시 맵에 들어가 있는 정보 본 맵에 옮김
	map[puri[0]][puri[1]] = -1; //공기청정기 아래 부분 적용
	map[puri[0] - 1][puri[1]] = -1; //공기청정기 위 부분 적용
}

//공기 순환 
//처음에서 끝으로 밀어준다는 느낌보다 끝에서 처음으로 당긴다는 느낌으로 구현
//예를들어 공기청정기 윗부분은 공기청정기 오른편에서 시작해서 공기 방향이 오른쪽, 위쪽, 왼쪽, 아래쪽으로 현재칸 것을 다음 칸으로 밀면서 순환되지만
//구현 할 때는 공기청정기 위에서 부터 위쪽, 오른쪽, 아래쪽, 왼쪽으로 진행하며 다음칸 것을 현재칸으로 당김으로써 공기를 순환 시킴.
void circulate()
{
	int r = puri[0] - 2; //위쪽을 순환하기 위해 공기청정기 윗부분을 처음 시작점으로 지정
	int c = puri[1];
	int d = 0; //방향 나타낼 변수
	int rr, cc; //다음 행, 열 나타낼 변수
	while (d<4) //방향이 3이하 일 때
	{
		rr = r + dRU[d]; cc = c + dCU[d]; //다음 칸 세팅
		if (isMap(rr, cc)&&rr<puri[0]) //맵 안의 공기청정기 윗 지역일 때
		{
			map[r][c] = map[rr][cc]; //그 다음에 있는것을 현재 칸으로 가져옴
			r = rr; c = cc; //r을 다음칸으로 세팅
		}
		else //바깥으로 나가는 방향이면 방향 전환
		{
			if (d==3) //공기청정기 직전 칸이면 해당 칸은 -1이 아니라 0으로 세팅
				map[r][c] = 0;
			d++; //방향 전환
		}
	}
	//공기 청정기 아래 부분 진행
	r = puri[0] + 1; //공기청정기 아래를 시작점으로 지정
	c = puri[1];
	d = 0;
	while (d < 4)
	{
		rr = r + dRD[d]; cc = c + dCD[d];
		if (isMap(rr, cc)&&rr>(puri[0]-1))
		{
			map[r][c] = map[rr][cc];
			r = rr; c = cc;
		}
		else
		{
			if (d==3)
				map[r][c] = 0;
			d++;
		}
	}
}

int main()
{
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1) 
			{
				//최종적으로 공기청정기 아래부분 저장
				puri[0] = i;
				puri[1] = j;
			}
		}
	for (int t = 0; t < T; t++)
	{
		spread(); //먼지 확산
		circulate(); //공기 순환
	}
	int sum = 0;
	for(int i=0; i<R; i++)
		for (int j = 0; j < C; j++)
		{
			sum += map[i][j]; //맵에 남아있는 먼지 전부 더하기
		}
	cout << sum+2; //맵에서 미세먼지가 -1로 2개씩 있으므로 다시 2를 더한 후 출력

	return 0;
}