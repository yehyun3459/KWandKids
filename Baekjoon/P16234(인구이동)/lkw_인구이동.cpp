#include <iostream>
using namespace std;

//국경선을 공유하는 두 나라의 인구 차이가 L명 이상, R명 이하라면,
//두 나라가 공유하는 국경선을 오늘 하루동안 연다.

//위의 조건에 의해 열어야하는 국경선이 모두 열렸다면, 인구 이동을 시작한다.

//국경선이 열려있어 인접한 칸만을 이용해 이동할 수 있으면,
//그 나라를 오늘 하루 동안은 연합이라고 한다.

//연합을 이루고 있는 각 칸의 인구수는(연합의 인구수) / (연합을 이루고 있는 칸의 개수)가 된다.
//편의상 소수점은 버린다.

//연합을 해체하고, 모든 국경선을 닫는다.

int map[50][50]; // 인구 저장
bool v[50][50]; // 방문 표시
int lab[50][50]; // 연합 번호
int label = 0; // 연합 번호를 나타내
bool f = 0; // 인구 이동 종료

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


void set() { // 방문, 연합 번호 초기화
	for (int j = 0; j < 50; j++)
		for (int i = 0; i < 50; i++) {
			v[j][i] = 0;
			lab[j][i] = 0;
		}

}
void dfs(int y, int x, int n, int L, int R) { // 같은 연합인지 탐색하기 위해
	lab[y][x] = label; // lab 값이 같으면 같은 연합이다.

	for (int i = 0; i < 4; i++) {
		int yt = y + dy[i]; 
		int xt = x + dx[i];
		if (yt >= 0 && yt < n && xt >= 0 && xt < n && v[yt][xt] == 0
			&& abs(map[y][x] - map[yt][xt]) >= L && abs(map[y][x] - map[yt][xt]) <= R) { // 연합 조건에 맞으면
			v[yt][xt] = 1; // 방문표시하고
			dfs(yt, xt, n, L, R); // 탐색을 이어나가
			f = 1; // 연합의 크기가 2 이상인게 하나라도 있으면 인구이동은 계속된다.
		}
	}
}
void prtl(int n) { // 연합 번호 출력
	cout << "lab\n";
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++)
			cout << lab[j][i] << " ";
		cout << endl;
	}cout << endl;
}
void prtm(int n) { // 인구 출력
	cout << "map\n";
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++)
			cout << map[j][i] << " ";
		cout << endl;
	}cout << endl;
}
void movemove(int n, int end) { // 인구 이동
	int *cnt = new int[end]; // 각 번호에 해당하는 연합의 수
	int *sum = new int[end]; // 각 연합의 인구 총합

	for (int i = 0; i < end; i++) { // 초기화
		cnt[i] = 0;
		sum[i] = 0;
	}

	for (int j = 0; j < n; j++)
		for (int i = 0; i < n; i++) {
			cnt[lab[j][i]]++; // 엽합이 몇 개의 나라로 이루어 지는지.
			sum[lab[j][i]] += map[j][i]; // 그 나라들의 인구 총합
		}

	for(int i=0; i < end; i++)
		if (cnt[i] > 1) {
			sum[i] = sum[i] / cnt[i]; // 평균을 구한다.
		}

	for (int j = 0; j < n; j++)
		for (int i = 0; i < n; i++)
			map[j][i] = sum[lab[j][i]]; // 각 연합의 인구를 각 연합의 평균으로 수정

	delete [] cnt;
	delete [] sum;
	
}

int main()
{
	int N, L, R;

	cin >> N >> L >> R; // 맵 크기, 하한선, 상한선
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			cin >> map[j][i]; // 초기 인구 값
	f = 1;
	label = 0;
	
	int mcnt = 0; // 이동한 횟수
	while (1) {
		f = 0;
		label = 0;
		set(); // 초기화 해야할 것 초기화
		for (int j = 0; j < N; j++)
			for (int i = 0; i < N; i++)
				if (v[j][i] == 0) {
					label++; // 각 연합은 이 값을 lab 2차배열에 공통으로 가진다.
					dfs(j, i, N, L, R); // 같은 연합 탐색
				}
		if (f == 0) // 더 이상 이동이 안 되는 경우라면
			break;
			
		movemove(N, label + 1); // 인구 이동
		mcnt++;
	}
	cout << mcnt << endl;

	return 0;
}