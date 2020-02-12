#include<iostream>
#include<queue>
using namespace std;

int N, tmp, Max = 0;
int T[16] = { 0, };
int P[16] = { 0, };
int M[16] = { 0, };

struct psb {
	bool flag[16];
	int index=1;
};

queue<psb> Q;
//queue<int> index;

int max(int a, int b) {
	if (a > b)
		return a;
	else return b;
}
psb choose(psb B, int n) {
	psb A = B;
	int tmp = min(n + T[n] - 1, N);
	for (int k = n+1; k <= tmp; k++)
		A.flag[k] = 0;
	A.index = tmp + 1;

	return A;
}
int total(psb A) {
	int sum = 0;
	for (int i = 1; i <= N; i++)
		sum = sum + A.flag[i] * P[i];
	return sum;
}
void printM(psb A){
	cout << "index : " << A.index << "// ";
	cout << "psb : ";
	for (int i = 1; i <= N; i++)
		cout << A.flag[i] << " ";

	cout << "// total: " << total(A) << endl;

}

int main() {
	psb init;
	init.index = 1;

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> T[i] >> P[i];
		init.flag[i] = 1;
	}
	init.flag[N] = 1;
	for (int i = N; i >= 1; i--)
		if (i + T[i] - 1 > N)
			init.flag[i] = 0;

	Q.push(init);
	//cout << "init :";
	//printM(init);
	//int cnt=0;
	while (!Q.empty()) {
		//cnt++;
		psb tmp, tmp2;
		tmp = Q.front();
		//cout << "POP-";
		//printM(tmp);		
		Q.pop();
		if (tmp.index > N) {
			int m = total(tmp);
			if (Max < m)
				Max = m;
			
		}

		
		if (tmp.index <= N) {
			if (tmp.flag[tmp.index]) {
				tmp2 = choose(tmp, tmp.index);
				Q.push(tmp2);
				//cout << "PUSH-";
				//printM(tmp2);
			}
			tmp.flag[tmp.index] = 0;
			tmp.index = tmp.index + 1;
			Q.push(tmp);
			//cout << "PUSH-";
			//printM(tmp);
		}
	}

	//printM();
	cout << Max;
	//choose(1);
	//printM();
	//cout << total();
}