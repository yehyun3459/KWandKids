#include <iostream>
using namespace std;
int N, M, Num[100], oper[4], maxx = INT32_MIN, minn = INT32_MAX;
void dfs(int num, int cnt) {
	if (cnt == N) {
		if (maxx < num)	maxx = num;
		if (minn > num)	minn = num;
		return;
	}

	for (int i = 0; i < 4; i++) 
		if (oper[i]) {
			oper[i]--;
			switch (i) {
			case 0:dfs(num + Num[cnt], cnt + 1); break;
			case 1:dfs(num - Num[cnt], cnt + 1); break;
			case 2:dfs(num * Num[cnt], cnt + 1); break;
			case 3:dfs(num / Num[cnt], cnt + 1); break;
			}
			oper[i]++;
		}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) 
		cin >> Num[i];
	for (int i = 0; i < 4; i++) 
		cin >> oper[i];	
	dfs(Num[0], 1);
	cout << maxx <<"\n" << minn;
	return 0;
}
