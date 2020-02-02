#include <iostream>

using namespace std;

static int map[20][20] = { { 0, }, }; //최대 20x20 맵
static int N; //격자맵 크기
static int diff_min = 0; //최소 차
static int sum_all = 0; //모든 인구수 합 

//x,y,d1,d2에 따라 선거구를 나눠 최소 차를 구하는 함수
void search(int x, int y, int d1, int d2)
{
	int max = 0; //인구 합이 가장 큰 선거구의 인구 수
	int min = sum_all; //인구 합이 가장 작은 선거구의 인구 수
	int sum = 0; //한 선거구의 인구 수
	int sum_sum = 0; //5번 선거구 계산 위해 1~4번 선거구 인구 합

	//1번 선거구 인구 합
	for (int i = 0, k = 0; i < x + d1; i++)
	{
		k += i < x ? 0 : 1;
		for (int j = 0; j <= y - k; j++)
			sum += map[i][j];
	}
	sum_sum += sum;
	min = min > sum ? sum : min; //최소 인구 수 보다 작으면 최소 인구 수 갱신
	max = max < sum ? sum : max; //최대 인구 수 보다 크면 최대 인구 수 갱신
	sum = 0;
	//2번 선거구 인구 합
	for (int i = 0, k=0; i <= x + d2; i++)
	{
		if (i > x)
			k++;
		for (int j = y + 1 + k; j < N; j++)
			sum += map[i][j];
	}
	sum_sum += sum;
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	sum = 0;
	//3번 선거구 인구 합
	for (int i = x + d1, k = y-d1-1; i < N; i++)
	{
		if (i <= x + d1 + d2)
			k++;
		for (int j = 0; j < k; j++)
			sum += map[i][j];
		
	}
	sum_sum += sum;
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	sum = 0;
	//4번 선거구 인구 합
	for (int i = x + d2 + 1, k = 0; i < N; i++)
	{
		for (int j = y + d2 - k; j < N; j++)
			sum += map[i][j];
		k += i < x + d1 + d2 + 1 ? 1 : 0;
	}
	sum_sum += sum;
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	sum = 0;

	sum = sum_all - sum_sum; // 5번 선거구 인구 합
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	//최대 인구 선거구와 최소 인구 선거구 차가 이전의 최소 차 보다 작으면 갱신
	if (max - min < diff_min)
		diff_min = max - min;
}

int main() 
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &map[i][j]);
			diff_min += map[i][j]; //최소 차의 값을 일단 총 인구수로 설정
		}
	sum_all = diff_min; //총 인구수 기록

	//0<x<N, 1<y<N-1, 1<d1<=y, 1<d2<N-y 에 대해 완전 탐색
	for (int x = 0; x < N; x++)
		for (int y = 1; y < N-1; y++)
			for (int d1 = 1; d1 <= y; d1++)
				for (int d2 = 1; d2 < N - y; d2++)
					search(x, y, d1, d2);
	cout << diff_min;
}