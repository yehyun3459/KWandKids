#include <iostream>
using namespace std;
int N, M, a, b, K,  Map[21][21], dice[6];     // ufdblr
int my[5] = { 0,0,0,-1,1 }, mx[5] = { 0,1,-1,0,0 };
void fu(int dir) {
	int tmp;
	if (dir == 1) {
		tmp = dice[0];
		dice[0] = dice[4];
		dice[4] = dice[2];
		dice[2] = dice[5];
		dice[5] = tmp;
	}
	else if (dir == 2) {
		tmp = dice[0];
		dice[0] = dice[5];
		dice[5] = dice[2];
		dice[2] = dice[4];
		dice[4] = tmp;
	}
	else if (dir == 3) {
		tmp = dice[0];
		dice[0] = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[3];
		dice[3] = tmp;
	}
	else if (dir == 4) {
		tmp = dice[0];
		dice[0] = dice[3];
		dice[3] = dice[2];
		dice[2] = dice[1];
		dice[1] = tmp;
	}
}

int main() {
	cin >> N >> M >> a >> b >> K;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			cin >> Map[i][j];
	
	int tmp;
	for (int i = 1; i <= K; i++) {
		cin >> tmp;		
		if (a + my[tmp] >= 0 && a + my[tmp] < N && b + mx[tmp] >= 0 && b + mx[tmp] < M) {
			fu(tmp);
			a += my[tmp];
			b += mx[tmp];

			if (Map[a][b]) {
				dice[2] = Map[a][b];
				Map[a][b] = 0;
			}				
			else
				Map[a][b] = dice[2];

			cout << dice[0] << "\n";
		}		
	}
	return 0;
}
