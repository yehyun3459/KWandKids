#include <iostream>
using namespace std;
int N, is[20], num[20], maxx = INT32_MIN; //마이너스 일수 있어서 젤 작은값에서 시작

void dfs(int n) { //연산자 위치 기준으로 괄호 여부 전체 탐색
	int idx_tmp = 0;
	int num_tmp[20] = { 0 };
	for (int i = 0; i < N; i ++) { //dfs 할때마다 계산 후 최대값 구하기
		if (is[i]) {
			if (num[i] == 100) { //괄호 부분만 미리 계산
				num_tmp[i] = num[i - 1] + num[i + 1];
				num_tmp[i - 1] = 104;
				num_tmp[i + 1] = 104;
				i++;
			}
			else if (num[i] == 101) {
				num_tmp[i] = num[i - 1] - num[i + 1];
				num_tmp[i - 1] = 104;
				num_tmp[i + 1] = 104;
				i++;
			}
			else if (num[i] == 102) {
				num_tmp[i] = num[i - 1] * num[i + 1];
				num_tmp[i - 1] = 104;
				num_tmp[i + 1] = 104;
				i++;
			}
		}
		else {
			num_tmp[i] = num[i];
		}
			
	}

	int summ = 0, tmp = 1;
	for (int i = 0; i < N; i++) { //전부 계산 
		if (num_tmp[i] == 104)	continue;
	
		if (num_tmp[i] >= 100)
			tmp = num_tmp[i];
		else if (tmp == 1)
			summ = num_tmp[i];
		else if (tmp == 100) 
			summ += num_tmp[i];
		else if (tmp == 101) 
			summ -= num_tmp[i];
		else if (tmp == 102) 
			summ *= num_tmp[i];

	}

	if (summ > maxx) //최대값 저장
		maxx = summ;

	if (n >= N - 2)
		return;

	for (int i = n + 2; i <= N - 2; i+=2) { 
		if (is[i] == 0 && is[i - 2] == 0) { //주변 연산자 괄호 여부 확인후 괄호 추가
			is[i] = 1;
			dfs(i);
			is[i] = 0;
		}
	}
}


int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		char cc;
		scanf(" %c", &cc);
		if (cc == '+') //연산자 숫자로 대신 저장
			num[i] = 100;
		else if (cc == '-')
			num[i] = 101;
		else if (cc == '*')
			num[i] = 102;
		else
			num[i] = cc - '0';
	}

	is[1] = 1;
	dfs(1);
	is[1] = 0;
	dfs(1);

	printf("%d", maxx);
	return 0;
}
