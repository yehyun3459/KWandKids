#include<iostream>
using namespace std;

int arr[50][9];
int p[9] = { 1,2,3,4,5,6,7,8,0 };
int player[9]; // 선수 하나 빼고하고, 나머지를 순열을 통해 얻은 타자 순서
int pcopy[9]; // 뺀 선수 고정 자리에 넣음
bool v[8] = { 0, };

bool base[5]; // 홈을 나갈 때, 들어올 때 구분하였다. 홈 1 2 3 홈
int MAX = 0;

bool hit(int h, int &score) { // if 1, out
	if (h == 0) // 아웃
		return 1;
	else {
		base[0] = 1; // 홈에서 진루 대기 
		for (int j = 0; j < h; j++) { // h루타, h칸 전진
			for (int i = 4; i > 0; i--)
				base[i] = base[i - 1]; // 한 칸씩 전진한다.
			base[0] = 0; // 진루 했으니 다시 0으로
			if (base[4]) { // 홈에 들어온 사람이 있으면
				score++; //점수 겟
				base[4] = 0;
			}

		}
		return 0;
	}
}

int baseball(int inn) { // 1 게임을 시뮬레이션 한다.
	bool of = 0; // 아웃 확인용 플래그
	int order = 0, out=0, score=0; // 배팅 순서 ,아웃 카운트, 점수
	for (int j = 0; j < inn; j++) {
		for (int i = 0; i < 5; i++) // 베이스 초기화
			base[i] = 0;
		while (1) {
			of = hit(arr[j][pcopy[order++]], score); // 순서대로 플레이. 아웃이면 1 리턴
			order %= 9; // 9명이서 돌아가면서. 다음이닝에도 이어진다.
			if (of)
				out++;
			if (out == 3) { // 3아웃 한 이닝 끝.
				out = 0;
				break;
			}
		}
	}
	return score;
}

void perm(int N, int depth, int inn){
	if (N == depth) {
		for (int i = 0; i < 3; i++) 
			pcopy[i] = player[i];
		for (int i = 8; i > 3; i--)
			pcopy[i] = player[i - 1];
		pcopy[3] = 0; // 고정 선수를 원래 자리에 넣음으로써 순서 완성
		
		int tmp = baseball(inn); // 완성된 순서로 플레이. 결과 점수 리턴
		if (MAX < tmp) {
			MAX = tmp;
			
			//cout << "P : ";
			//for (int i = 0; i < 9; i++)
			//	cout << pcopy[i] << " ";
			//cout << " - score : " << MAX << endl;
		
		}
		

	}
	else {
		for (int i = 0; i < N; i++) {
			if (!v[i]) {
				v[i] = 1;
				player[depth] = p[i];
				perm(N, depth + 1, inn);
				v[i] = 0;
			}
		}
	}

}

int main() {
	int inn; // 2~50

	cin >> inn;

	for (int j = 0; j < inn; j++)
		for (int i = 0; i < 9; i++)
			cin >> arr[j][i];

	perm(8, 0, inn);

	cout << MAX;

	return 0;
}