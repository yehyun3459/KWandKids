#include <cstdio>

using namespace std;

long long N, B, C; //시험 장 수, 총 감독관 감시수, 부 감독관 감시수
int popul[1000000];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &popul[i]);
	scanf("%d %d", &B, &C);

	long long result = 0; //int일 경우 오버플로우 나므로 long long
	long long remain;
	for (int i = 0; i < N; i++)
	{
		if (popul[i] <= 0) continue;
		remain = popul[i] - B;
		result++;
		if (remain <= 0) continue;
		result += remain / C;
		if (!(remain % C)) continue;
		result++;
	}

	printf("%lld", result); //출력시에도 그냥 %d는 int형으로 출력하여 오류, %lld를 이용하여 long long으로 출력해야함
}
