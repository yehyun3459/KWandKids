#include <iostream>
#include <cstring>
//백준 17140
using namespace std;

int R, des_r; //행 크기, 찾으려는 행
int C, des_c; //열 크기, 찾으려는 열
int k; //찾으려는 값
int nums[101] = { 0 }; //수의 개수를 담는 배열
int map[100][100] = { {0}, }; //전체 맵

//R연산
void operateR()
{
	int minIdx, min; //최소 값의 인덱스와 최솟값
	int lim; //정렬할 때 다음 원소가 들어올 인덱스
	int newC = C; //열 크기가 커질 경우를 위한 newC
	for (int i = 0; i < R; i++) //모든 행에 대해
	{
		memset(nums, 0, sizeof(nums)); //nums 배열 0으로 초기화
		for (int j = 0; j < C; j++) //한 행에 대해 
			nums[map[i][j]]++; //각 수의 개수 카운트
		min = 101;
		lim = 0;
		while (lim < 100) //100을 넘지 않을 동안
		{
			minIdx = -1;
			min = 101;
			//nums배열에서 가장 최소 빈도의 수 찾기(0은 제외)
			for (int j = 1; j < 101; j++)
			{
				if (nums[j] > 0 && nums[j] < min)
				{
					minIdx = j;
					min = nums[j];
				}
			}
			if (minIdx < 0) //빈도수가 0보다 큰 수 못찾으면 정렬 완료
				break;
			map[i][lim] = minIdx; lim++; //최소 빈도의 수 입력, 다음 원소 들어갈 자리+1
			map[i][lim] = nums[minIdx]; lim++; //빈도수 입력, 다음 원소 들어가 자리 +1
			nums[minIdx] = 0; //정렬 된 수는 빈도수를 0으로 설정
		}
		if (lim > newC) //열 크기가 더 커졌으면 임의로 newC 갱신(실제 현재 R은 아직 안바뀌도록 함)
			newC = lim;
		for (int j = lim; j < 100; j++) //그 이후는 0으로 설정
			map[i][j] = 0;
	}
	C = newC; //열 크기 갱신
}

//C연산(R연산과 행,열만 바꿈)
void operateC()
{
	int minIdx, min;
	int lim;
	int newR = R;
	for (int i = 0; i < C; i++)
	{
		memset(nums, 0, sizeof(nums));
		for (int j = 0; j < R; j++)
			nums[map[j][i]]++;
		min = 101;
		lim = 0;
		while (lim < 100)
		{
			min = 101;
			minIdx = -1;
			for (int j = 1; j < 101; j++)
			{
				if (nums[j] > 0 && nums[j] < min)
				{
					minIdx = j;
					min = nums[j];
				}
			}
			if (minIdx < 0)
				break;
			map[lim][i] = minIdx; lim++;
			map[lim][i] = nums[minIdx]; lim++;
			nums[minIdx] = 0;
		}
		if (lim > newR)
			newR = lim;
		for (int j = lim; j < 100; j++)
			map[j][i] = 0;
	}
	R = newR;
}

int main(int argc, char** argv)
{
	scanf("%d %d %d", &des_r, &des_c, &k);
	R = 3; C = 3;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			scanf("%d", &map[i][j]);
	int count = 0;
	while (count < 101) //연산 횟수 100넘으면 종료
	{
		if (map[des_r - 1][des_c - 1] == k) //목표값을 목표 위치에서 찾으면 종료
			break;
		if (R >= C)
			operateR();
		else
			operateC();
		count++;
	}
	count = count < 101 ? count : -1;
	cout << count;

	return 0;
}
