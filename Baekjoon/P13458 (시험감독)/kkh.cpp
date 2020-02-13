#include <iostream>
using namespace std;
int N, list[1000001], B, C, tmp;
long long cnt; // 이게 포인트
int main() {
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> list[i];
	cin >> B >> C;
	for (int i = 1; i <= N; i++) {
		tmp = list[i] - B;
		if (tmp <= 0)	continue;
		if (tmp % C) 
			cnt += tmp / C + 1;
		else
			cnt += tmp / C;
	}

	cout << cnt + N;

	return 0;
}
