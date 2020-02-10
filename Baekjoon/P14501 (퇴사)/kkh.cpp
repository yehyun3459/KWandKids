#include <iostream>
using namespace std;
int N, nlist[16][2],isvis[16], maxx;
void dfs(int day, int money) {
	if (day > N + 1)	return;	 // 마감일 넘어가면 리턴
	if (maxx < money)	maxx = money; //dfs과정동안 가장 큰 값을 저장
	for (int i = day; i <= N; i++) 
		dfs(nlist[i][0] + i, money + nlist[i][1]);
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> nlist[i][0] >> nlist[i][1]; 

	for (int i = 1; i <= N; i++) 
		dfs(nlist[i][0] + i, nlist[i][1]); // 상담 마감 날짜 기준으로 탐색

	cout << maxx;
	return 0;
}
