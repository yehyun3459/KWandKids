#include <iostream>
using namespace std;
int N, player[51][10], ischoice[10], maxx;

void baseball() {
	int score = 0;
	int idx = 1;
	for (int i = 1; i <= N; i++) {
		int nOut = 0, nOne = 0, nTwo = 0, nThree = 0;
		while (nOut < 3) {
			int res = player[i][ischoice[idx++]];
			if (idx == 10)
				idx = 1;
			if (res == 0)
				nOut++;
			else if (res == 1) {
				if (nThree) {
					score++;
					nThree--;
				}					
				if (nTwo) {
					nThree++;
					nTwo--;
				}

				if (nOne) {
					nTwo++;
					nOne--;
				}

				nOne++;
			
			}
			else if (res == 2) {
				if (nThree) {
					score++;
					nThree--;
				}
				if (nTwo) {
					score++;
					nTwo--;
				}

				if (nOne) {
					nThree++;
					nOne--;
				}

				nTwo++;
			}
			else if (res == 3) {
				if (nThree) {
					score++;
					nThree--;
				}
				if (nTwo) {
					score++;
					nTwo--;
				}

				if (nOne) {
					score++;
					nOne--;
				}

				nThree++;
			}
			else if (res == 4) {
				if (nThree) {
					score++;
					nThree--;
				}
				if (nTwo) {
					score++;
					nTwo--;
				}

				if (nOne) {
					score++;
					nOne--;
				}

				score++;
			}
		}		
	}

	if (maxx < score)
		maxx = score;
}

void fu(int cnt) {
	if (cnt == 10) {
		baseball();
		return;
	}

	for (int i = 1; i <= 9; i++) {  //순열? 전체 탐색 
		if (!ischoice[i]) {
			ischoice[i] = cnt;
			fu(cnt + 1);
			ischoice[i] = 0;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) 
		for(int j = 1; j <= 9; j++)
			cin >> player[i][j];
	
	ischoice[4] = 1;  //1번 선수만 4번고정
	fu(2);
	
	cout << maxx;
	return 0;
}
