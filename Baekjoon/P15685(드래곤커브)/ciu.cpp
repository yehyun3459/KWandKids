#include <iostream>
//Baekjoon - 15685
using namespace std;

int dR[4] = { 0, -1, 0, 1 };
int dC[4] = { 1, 0, -1, 0 };
int incres[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 }; //g 증가에 따른 방향 배열 길이
int N;
int dirs[1025]; //방향 배열(0:우, 1:상, 2:좌, 3:하)
int map[101][101]; //드래곤 커브가 그려지는 맵

//드래곤 커브 그리는 함수
void draw_curve(int r, int c, int d, int g)
{
	int rr = r, cc = c; //다음 행, 열 변수
	int gen = 0; // i 증가에 따른 세대
	dirs[0] = d; //방향 배열의 첫 방향 넣기
	map[r][c] = 1; //현재 좌표에 점 찍기
	for (int i = 0; i < incres[g]; i++)
	{
		rr = r + dR[dirs[i]]; cc = c + dC[dirs[i]]; //방향에 따른 다음 행, 열
		map[rr][cc] = 1; //점을 찍음으로써 선 그리기
		r = rr; c = cc; //r,c 갱신

		//방향 배열에 드래곤 커브를 그리기 위한 방향 삽입하는 부분
		if (i < incres[g] / 2) //현재 인덱스가 필요한 방향의 총 길이의 1/2 전이라면 방향 만들어 방향 배열에 넣기
		{
			for (int j = gen + 1; j <= g; j++) //현재 세대+1 ~ 주어진 세대까지
			{
				//2^j - (1+현재 인덱스)의 자리에 현재 인덱스 방향의 다음 방향을 넣으면
				//한 번에 필요한 모든 부분에 현재 인덱스에 대응해야 하는 모든 자리에 방향 넣을 수 있다.
				//ex) 3세대 커브 그릴 때 처음 주어진 방향의 경우 1, 3, 7, 15... 자리에 (주어진 방향+1)%4 값을 넣으면 된다.
				dirs[incres[j] - (1+i)] = (dirs[i] + 1) % 4; 
			}
		}


		if (i >= incres[gen] - 1)
			gen++;
	}
}

int main()
{
	scanf("%d", &N);
	int x, y, d, g;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d %d", &x, &y, &d, &g);
		draw_curve(y, x, d, g); //x,y가 맵상 좌표이므로 배열 상의 좌표로 바꾸기 위해 순서 바꿔서 넣음
	}
	int result=0;
	for(int i=0; i<100; i++)
		for (int j = 0; j < 100; j++)
		{
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
				result++;
		}
	printf("%d", result);
	return 0;
}
