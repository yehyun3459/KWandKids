#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int N, M, H;
int Min = 4, cnt=0;
bool Fg;
struct ladder {
	//int V[12][32] = { {0,}, }; // 수직
	int H[32][12] = { {0,}, }; // 수평
};
struct test {
	int flg[300] = { 0,};
};
struct pos {
	int y, x;
	pos() {}
	pos(int Y, int X) {
		y = Y; x = X;
	}
};
vector<pos> Vec;

void printV(ladder L) {
	cout <<endl<< "Sero" <<endl;
	for (int j = 0; j <= H+1; j++) {
		for (int i = 1; i <= N; i++) {
			//cout << L.V[j][i];
		}cout << endl;
	}

}
void printH(ladder L) {
	cout << endl << "Garo" << endl;
	for (int j = 0; j <= H + 1; j++) {
		for (int i = 1; i <= N-1; i++) {
			cout << L.H[j][i];
		}cout << endl;
	}

}
bool line_trace(ladder L, int lineNum) {
	int x = lineNum;
	for (int j = 0; j <= H; j++) {
		if (L.H[j + 1][x] == 1) {
			x = x + 1;
		}
		else if (L.H[j + 1][x - 1] == 1)
			x = x - 1;
		
	}
	if (lineNum == x)
		return 1;
	else return 0;
}
void comb(ladder a, int n, int k,int index, int size) {
	if (n == k) {
		//cnt++;
		//printH(a);
		bool flag = true;
		for (int i = 1; i <= N; i++)
			if (!line_trace(a, i)) {
				flag = false;
				break; 
			}
		
		if (flag) {
			if (Min > n) {
				Min = n;
				Fg = true;
				//cout << "n : " << n << endl;
				//printH(a);
			}
			//return;
		}
		
	}
	else if(index < size){
		pos tmp;	
		
		tmp = Vec.at(index);
		comb(a, n, k, index + 1, size);
		if (a.H[tmp.y][tmp.x - 1] != 1 && a.H[tmp.y][tmp.x + 1] != 1) {
			a.H[tmp.y][tmp.x] = 1;
			comb(a, n + 1, k, index + 1, size);
		}
		
			//cout << "check1";		
			//a.H[tmp.y][tmp.x] = 0;
			
			
			
			
		
	}	

}

int main() {
	int a, b, size;
	ladder A;
	cin >> N >> M >> H;
	
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		A.H[a][b] = 1;
	}

	//cout << "ee";
	for(int j=1; j <= H; j++){
		for (int i = 1; i < N; i++) {
			if (A.H[j][i] == 0) {
				pos tmp(j,i);
				Vec.push_back(tmp);
			}
		}

	}

	//printV(A);
	//cout << "org" << endl;
	//printH(A);	
	size = Vec.size();
	//cout << "size : " << size << endl;
	
	bool flag = true;
	for (int i = 1; i <= N; i++)
		if (!line_trace(A, i)) {
			flag = false;
			break;
		}
	if(!flag)
		for (int k = 1; k <= 3; k++) {
			Fg = false;
			comb(A, 0, k, 0, size);
			if (Fg)
				break;
		}
	else Min = 0;
	//cout << endl << "min : ";
	if (Min == 4)
		cout << -1;
	else 
		cout << Min;

	//cout << endl << "count : " << cnt;
	
}