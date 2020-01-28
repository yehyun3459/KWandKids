#include<iostream>
using namespace std;

int circle[51][51]; // 1 ~ 1000
int dy[4] = { -1, 1, 0, 0 }; 
int dx[4] = { 0, 0, -1, 1 };

void shift(int idx, int d, int k, int M) { // idx 번 원판을, d 방향으로, k 만큼 회전. M은 한 원판의 숫자 갯수
	// d:0 clock, d : 1 anticlock
	int c_t[51];	// 바로 돌리면 덮어쓰다가 값 지워지니까 돌리기 전꺼 저장해놓기
	for (int i = 1; i <= M; i++)
		c_t[i] = circle[idx][i];

	if (d == 0) { // 시계방향이면
		for (int i = M; i > k; i--)
			circle[idx][i] = c_t[i - k];
		for (int i = k; i >= 1; i--)
			circle[idx][i] = c_t[i + (M - k)];
	}
	else if (d == 1) { // 반시계방향이면
		for (int i = 1; i <= M-k; i++)
			circle[idx][i] = c_t[i + k];
		for (int i = M-k+1; i <= M; i++)
			circle[idx][i] = c_t[i - (M - k)];
	}
}

void rotate(int x, int d, int k, int N, int M) { // x의 배수에 해당하는 원판을 회전시키는 함수
	for(int i=1; i <= N; i++)
		if (i % x == 0) {
			shift(i, d, k, M);
		}
}
bool BFS(int y, int x, int N, int M, int value, bool& f) { // 같은 숫자면 1 리턴 아니면 0
	if (circle[y][x] == value) { // 같은 곳이면
		f = 1;		
		int yt, xt, v;
		v = circle[y][x];
		circle[y][x] = 0; // 지우고

		for (int i = 0; i < 4; i++) {
			yt = y + dy[i];
			xt = x + dx[i];
			if (yt > 0 && yt <= N) {
				if (xt == 0) xt = M;
				if (xt == M + 1) xt = 1;

				if (circle[yt][xt] == v) {	// 더 붙어 있는게 있는지
					BFS(yt, xt, N, M, v, f);
				}
			}
		}
	}
	return f;
}
bool BFS_init(int y, int x, int N, int M) {
	int yt, xt;
	bool f = 0;

	for (int i = 0; i < 4; i++) { // 나랑 같은 숫자가 있는지 주변 4방향을 볼까?
		yt = y + dy[i];
		xt = x + dx[i];
		if (yt > 0 && yt <= N) {
			if (xt == 0) xt = M; // 원이라서 해줘야해
			if (xt == M + 1) xt = 1;
			
			if (circle[yt][xt] != 0) { // 사라진 곳이 아니라면
				f = BFS(yt, xt, N, M, circle[y][x], f);		// 찾아보자		
			}
		}
	}
	return f;
	
}

void erase(int N, int M) { // 붙어 있는 숫자 지우고, 붙어 있는 숫자가 없을 땐 더하기빼기
	bool flag = 0;
	for (int j = 1; j <= N; j++) { 
		for (int i = 1; i <= M; i++) {
			if(BFS_init(j, i, N, M)) // j, i 에 해당하는 숫자 주변에 같은 게 있나?
				flag=1; // 있으면 1
		}
	}
	if (!flag) { // 없으면 이상한연산 해야해
		int sum = 0, cnt=0;
		for (int j = 1; j <= N; j++)
			for (int i = 1; i <= M; i++)
				if (circle[j][i] > 0) {
					sum += circle[j][i];
					cnt++;
				}
		double avg = sum / (double)cnt;

		for (int j = 1; j <= N; j++)
			for (int i = 1; i <= M; i++)
				if (circle[j][i] > 0) 
					if (circle[j][i] > avg)
						circle[j][i] -= 1;
					else if (circle[j][i] < avg)
						circle[j][i] += 1;
	}
}

void prtC(int N, int M) {
	cout << "circle\n";
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++)
			cout << circle[j][i] << " ";
		cout << endl;
	}cout << endl;
}

int main() {
	int N=0, M=0, T=0; // 
	int x, d, k;
	
	cin >> N >> M >> T;
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= M; i++)
			cin >> circle[j][i];
	//cout << "default : ";
	//prtC(N, M);
	for (int i = 1; i <= T; i++) {
		cin >> x >> d >> k;
		rotate(x, d, k, N, M);
		//cout << "after rotate : ";
		//prtC(N, M);
		erase(N, M);
		//cout << "after erase: ";
		//prtC(N, M);
	}

	int sum = 0;
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= M; i++)
			sum += circle[j][i];

	cout << sum;
	/*prtC(N, M);
	shift(1, 0, 2, M);
	prtC(N, M);
	shift(1, 1, 2, M);
	prtC(N, M);
	shift(2, 1, 1, M);
	prtC(N, M);*/
	return 0;
}