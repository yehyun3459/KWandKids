#include<iostream>
#include<queue>
using namespace std;

char arr[10][10]; //. # O R B
int N, M;  //N: ¼¼·Î, M: °¡·Î
int mini = 10000;
char tmp0[5][5] = {
	{ '#','#','#','#','#' },
{ '#','.','.','B','#' },
{ '#','.','#','.','#' },
{ '#','R','O','.','#' },
{ '#','#','#','#','#' }
};
char tmp1[7][7] = {
	{ '#','#','#','#','#','#','#' },
{ '#','.','.','.','R','B','#' },
{ '#','.','#','#','#','#','#' },
{ '#','.','.','.','.','.','#' },
{ '#','#','#','#','#','.','#' },
{ '#','O','.','.','.','.','#' },
{ '#','#','#','#','#','#','#' }
};
struct marble {
	int cnt = 0; // cnt: ±â¿ïÀÎ È½¼ö
	bool flag = false;
	char arr[10][10];
	void copy(marble m) {
		cnt = m.cnt;
		flag = m.flag;
		for (int j = 0; j < N; j++)
			for (int i = 0; i < M; i++)
				arr[j][i] = m.arr[j][i];
	}
};
void swap(char &a, char &b) {
	char tmp = a;
	a = b;
	b = tmp;
}
bool cantilt(marble a, int dir);
char tilt(marble a, int dir);
void printM(marble a);

queue<marble> Q;
void BFS() {
	marble b;
	char T;	
	bool one = true;
	//int count = 0;
	while (1) {//({count < 10) {
		//count++;
		if (!Q.empty()) {
			b.copy(Q.front());
			//cout <<  count << ": " <<b.cnt << endl;
			//printM(b);
			Q.pop();
			if (b.flag) {
				cout << b.cnt;
				break;
			}
			else if (b.cnt > 10) {
				cout << -1;
				break;
			}

			//cout << "check";
			for (int i = 1; i <= 4; i++) {
				if (cantilt(b, i) && b.cnt < 10) {
					//cout << "dir: " << i << endl;
					T = tilt(b, i);

				}
			}
		}
		//if (T == 'D')
		//	cout << "¤Ç";
		if (Q.empty() && one != true) {
			cout  << -1;
			break;
		}
		one = false;
			
	}

}
void printM(marble a) {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++)
			cout << a.arr[j][i];
		cout << endl;
	}cout << endl;
}
int main() {
	cin >> N >> M;
	marble a;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++)
			cin >> a.arr[j][i];

	//cout << a.cnt << " " << a.flag;
	Q.push(a);
	BFS();
	//cout << mini;
}
bool cantilt(marble a, int dir) {
	int R_x, R_y;
	int B_x, B_y;
	bool flag = false;
	for (int j = 1; j < N - 1; j++) {
		for (int i = 1; i < M - 1; i++) {
			if (a.arr[j][i] == 'R') {
				R_y = j; R_x = i;
			}
			else if (a.arr[j][i] == 'B') {
				B_y = j; B_x = i;
			}
		}
	}
	if (dir == 1) {
		if (a.arr[R_y - 1][R_x] == '.' || a.arr[R_y - 1][R_x] == 'O')
			flag = true;
		if (a.arr[B_y - 1][B_x] == '.' || a.arr[B_y - 1][B_x] == 'O')
			flag = true;
	}
	else if (dir == 2) {
		if (a.arr[R_y + 1][R_x] == '.' || a.arr[R_y + 1][R_x] == 'O')
			flag = true;
		if (a.arr[B_y + 1][B_x] == '.' || a.arr[B_y + 1][B_x] == 'O')
			flag = true;
	}
	else if (dir == 3) {
		if (a.arr[R_y][R_x - 1] == '.' || a.arr[R_y][R_x - 1] == 'O')
			flag = true;
		if (a.arr[B_y][B_x - 1] == '.' || a.arr[B_y][B_x - 1] == 'O')
			flag = true;
	}
	else if (dir == 4) {
		if (a.arr[R_y][R_x + 1] == '.' || a.arr[R_y][R_x + 1] == 'O')
			flag = true;
		if (a.arr[B_y][B_x + 1] == '.' || a.arr[B_y][B_x + 1] == 'O')
			flag = true;
	}
	return flag;
}
char tilt(marble A, int dir) {// ±¸Á¶Ã¼¸¦ ÀÔ·ÂÇÏ¸é ¹æÇâ¿¡ ¸ÂÃç ±â¿ïÀÎ´Ù.
							  //dir 1,2,3,4 »ó ÇÏ ÁÂ ¿ì
							  //return 'B' ÆÄ¶õ°ø °ñ, 'R' »¡°£°ø °ñ, 'D' µÑ ´Ù °ñ, 'N' ¾ÆÁ÷ ³ë°ñ
	int R = 0, B = 0;
	marble a;
	a.cnt = A.cnt;
	a.flag = A.flag;
	for (int j = 0; j < N; j++)
		for (int i = 0; i < M; i++)
			a.arr[j][i] = A.arr[j][i];
	//bool flag_R=false;
	//bool flag_B=false;
	a.cnt++;
	if (dir == 1) {// »ó
		for (int j = 1; j<N - 1; j++)
			for (int i = 1; i<M - 1; i++)
				if (a.arr[j][i] == 'R') {
					int tmp = j;
					while (1) {
						if (a.arr[tmp - 1][i] == '.')//
							tmp--;
						else if (a.arr[tmp - 1][i] == 'O') {
							R = 1; break;
						}
						else break;
					}
					if (R == 1)
						a.arr[j][i] = '.';
					else swap(a.arr[tmp][i], a.arr[j][i]);
				}
				else if (a.arr[j][i] == 'B') {
					int tmp = j;
					while (1) {
						if (a.arr[tmp - 1][i] == '.')//
							tmp--;
						else if (a.arr[tmp - 1][i] == 'O') {
							B = 1; break;
						}
						else break;
					}
					swap(a.arr[tmp][i], a.arr[j][i]);
				}
	}
	else if (dir == 2) {// ÇÏ
		for (int j = N - 2; j > 0; j--)
			for (int i = 1; i<M - 1; i++)
				if (a.arr[j][i] == 'R') {
					int tmp = j;
					while (1) {
						if (a.arr[tmp + 1][i] == '.')//
							tmp++;
						else if (a.arr[tmp + 1][i] == 'O') {
							R = 1; break;
						}
						else break;
					}
					if (R == 1)
						a.arr[j][i] = '.';
					else swap(a.arr[tmp][i], a.arr[j][i]);
				}
				else if (a.arr[j][i] == 'B') {
					int tmp = j;
					while (1) {
						if (a.arr[tmp + 1][i] == '.')//
							tmp++;
						else if (a.arr[tmp + 1][i] == 'O') {
							B = 1; break;
						}
						else break;
					}
					swap(a.arr[tmp][i], a.arr[j][i]);
				}
	}
	else if (dir == 3) {// ÁÂ
		for (int j = 1; j < N - 1; j++)
			for (int i = 1; i<M - 1; i++)
				if (a.arr[j][i] == 'R') {
					int tmp = i;
					while (1) {
						if (a.arr[j][tmp - 1] == '.')//
							tmp--;
						else if (a.arr[j][tmp - 1] == 'O') {
							R = 1; break;
						}
						else break;
					}
					if (R == 1)
						a.arr[j][i] = '.';
					else swap(a.arr[j][i], a.arr[j][tmp]);

				}
				else if (a.arr[j][i] == 'B') {
					int tmp = i;
					while (1) {
						if (a.arr[j][tmp - 1] == '.')//
							tmp--;
						else if (a.arr[j][tmp - 1] == 'O') {
							B = 1; break;
						}
						else break;
					}
					swap(a.arr[j][i], a.arr[j][tmp]);
				}
	}
	else if (dir == 4) {// ¿ì
		for (int j = 1; j < N - 1; j++)
			for (int i = M - 2; i>0; i--)
				if (a.arr[j][i] == 'R') {
					int tmp = i;
					while (1) {
						if (a.arr[j][tmp + 1] == '.')//
							tmp++;
						else if (a.arr[j][tmp + 1] == 'O') {
							R = 1; break;
						}
						else break;
					}
					if (R == 1)
						a.arr[j][i] = '.';
					else swap(a.arr[j][i], a.arr[j][tmp]);

				}
				else if (a.arr[j][i] == 'B') {
					int tmp = i;
					while (1) {
						if (a.arr[j][tmp + 1] == '.')//
							tmp++;
						else if (a.arr[j][tmp + 1] == 'O') {
							B = 1; break;
						}
						else break;
					}
					swap(a.arr[j][i], a.arr[j][tmp]);
				}
	}
	//cout << "µÑ´Ù 1ÀÏ°ÍÀÌ¿© R, B>>" << R << ", " << B << endl;
	if (R == 1 && B == 0) {
		a.flag = true;
		Q.push(a);
		//cout << "T ! R ! U ! E" << endl;
		//printM(a);
	}
	else if (R != 1 && B != 1) {
		//cout << "next\n";
		Q.push(a);
		//printM(a);
	}
	
	//return 'B' ÆÄ¶õ°ø °ñ, 'R' »¡°£°ø °ñ, 'D' µÑ ´Ù °ñ, 'N' ¾ÆÁ÷ ³ë°ñ
	if (R + B == 2) return 'D';
	else if (R + B == 0) return 'N';
	else if (R == 1) return 'R';
	else if (B == 1) return 'B';

}