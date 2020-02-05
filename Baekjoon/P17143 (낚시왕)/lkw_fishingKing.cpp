#include<iostream>
using namespace std;

int arr[101][101]; // mark shark
int tarr[101][101];

struct shark {
	int y, x, d, v; // row, coloum, direction, velocity
	int size; // size
};
shark s[10001];
bool live[10001]; // 1: alive, 0: dead

int dy[5] = { 0, -1, 1, 0, 0 }; // up down right left
int dx[5] = { 0, 0, 0, 1, -1 };

int N, M, S; // max row, max coloum, sharks
int score = 0;

void hunting(int x) { // hunt shark
	for (int i = 1; i <= N; i++)
		if (arr[i][x] > 0 && live[arr[i][x]]) { // if first shark and alive, hunt only one shark
			live[arr[i][x]] = 0; // denote dead
			score += s[arr[i][x]].size; // get score
			arr[i][x] = 0; // denote dead
			//cout << "Hunt num: " << arr[i][x] << ", size : " << s[arr[i][x]].size <<endl;
			break;
		}
}
void dchange(int& d) { // change shark's dir
	if (d == 1)
		d = 2;
	else if (d == 2)
		d = 1;
	else if (d == 3)
		d = 4;
	else if (d == 4)
		d = 3;
}
void moveone(int idx) { // move one shark who number is idx
	int m; // moving has a cycle. To minimalize move, do % calc
	if (s[idx].d <= 2)
		m = s[idx].v % (2 * N - 2);
	else m = s[idx].v % (2 * M - 2);

	int y0, x0;
	for (int i = 0; i < m; i++) {
		y0 = s[idx].y + dy[s[idx].d];
		x0 = s[idx].x + dx[s[idx].d];
		if (y0 < 1 || y0 > N || x0 < 1 || x0 > M) { // if wall, change dir
			dchange(s[idx].d);
			y0 = s[idx].y + dy[s[idx].d];
			x0 = s[idx].x + dx[s[idx].d];
		}
		s[idx].y = y0;
		s[idx].x = x0;
	}
}
void moveall() { // move all shark
	for (int j = 0; j <= N; j++)
		for (int i = 0; i <= M; i++)
			tarr[j][i] = 0; // one place, one shark. if over 2, bigger eats smaller

	for (int i = 1; i <= S; i++) {
		if (live[i]) {
			moveone(i); // move other place
			if (tarr[s[i].y][s[i].x] == 0) //if no shark
				tarr[s[i].y][s[i].x] = i; // occupy the place
			else { // if yes shark
				int f = tarr[s[i].y][s[i].x];
				if (s[f].size > s[i].size) { // bigger eats smaller
					live[i] = 0;
					//cout << "eat1\n";
				}
				else {
					live[f] = 0;
					tarr[s[i].y][s[i].x] = i;
					//cout << "eat2\n";
				}
				//cout << "eat " << f << ", " << i << endl;
			}
		}
	}

	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= M; i++)
			arr[j][i] = tarr[j][i]; // update shark's position
}
void prtA() { // print shark's number
	cout << "Arr \n";
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++)
			printf("%4d", arr[j][i]);
		cout << endl;
	}cout << endl;
}
void prtS() { // print shark's size
	cout << "size \n";
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++) {
			if (arr[j][i] > 0)
				printf("%4d", s[arr[j][i]].size);
			else  printf("%4d", 0);
		}
		cout << endl;
	}cout << endl;
}
int main() {
	cin >> N >> M >> S; // map height, map width, how many sharks
	score = 0; // save score
	for (int j = 0; j <= N; j++)
		for (int i = 0; i <= M; i++)
			arr[j][i] = 0; // init arr(map)

	for (int i = 1; i <= S; i++) {
		cin >> s[i].y >> s[i].x >> s[i].v >> s[i].d >> s[i].size; // get shark's info
		live[i] = 1; // at init, all alive
		arr[s[i].y][s[i].x] = i; // arr denote shark's number
	}

	for (int i = 1; i <= M; i++) { // fisherman will hunt every coloum Sequentially
		//prtA();
		//prtS();
		hunting(i); // hunt at i col
		moveall(); // shark move themselves
	}
	cout << score;

	return 0;
}