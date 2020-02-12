#include <iostream>
using namespace std;

int num[11];
int num_t[11];
int opcnt[4]; // + - * /
char op[10]; // 연산자 순서대로 저장

int MAX = 0x80000000;
int MIN = 0x7fffffff;

void calc(int n) { // op cnt
	int ans;
	if (op[0] == '+')
		ans = num[0] + num[1];
	else if (op[0] == '-')
		ans = num[0] - num[1];
	else if (op[0] == '*')
		ans = num[0] * num[1];
	else if (op[0] == '/')
		ans = num[0] / num[1];
	num_t[1] = ans;
	for (int i = 2; i <= n; i++)
		num_t[i] = num[i];
	for (int i = 1; i < n; i++) {
		if (op[i] == '+')
			num_t[i + 1] = num_t[i] + num_t[i + 1];
		else if (op[i] == '-')
			num_t[i + 1] = num_t[i] - num_t[i + 1];
		else if (op[i] == '*')
			num_t[i + 1] = num_t[i] * num_t[i + 1];
		else if (op[i] == '/')
			num_t[i + 1] = num_t[i] / num_t[i + 1];
	}
	if (MAX < num_t[n])
		MAX = num_t[n];
	if (MIN > num_t[n])
		MIN = num_t[n];
	//cout << "MAX : " << MAX << ", MIN : " << MIN << endl;
}

void prt(int n) {
	cout << "num : ";
	for (int i = 0; i <= n; i++)
		cout << num[i];
	cout << endl << "opcode: ";
	for (int i = 0; i <= n - 1; i++)
		cout << op[i];
	cout << endl;
}

void dfs(int s, int e) { // e : last num index
	if (s == e) {
		//prt(e);
		calc(e);
		return;
	}
	else {
		for (int i = s; i < e; i++) {
			swap(op[s], op[i]);
			dfs(s + 1, e);
			swap(op[s], op[i]);
		}
	}
}

int main() {
	int N;

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> num[i];
	int odx = 0;
	for (int i = 0; i < 4; i++) {
		cin >> opcnt[i];
		for (int k = 0; k < opcnt[i]; k++)
			if (i == 0)
				op[odx++] = '+'; // 할당된 연산자를 일단 채운다. 그리고 채워진걸 섞어 경우의수를 만든다.
			else if (i == 1)     // 중복이 발생한다. 그치만 시간은 넉넉한걸
				op[odx++] = '-';
			else if (i == 2)
				op[odx++] = '*';
			else if (i == 3)
				op[odx++] = '/';
	}
	//cout << endl << "opcode: ";
	//for (int i = 0; i < N - 1; i++)
	//	cout << op[i];
	//cout << endl;
	dfs(0, N - 1);

	cout << MAX << endl << MIN;

	return 0;
}