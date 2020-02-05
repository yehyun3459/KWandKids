#include<iostream>
using namespace std;

int arr[101][101];
int Y, X, MX, MY;
int R, C, K;

void sortR(int y) {
	int tmp[101] = { 0, };
	int t_arr[101] = { 0, };
	int sort[101] = { 0, };
	int sdx = 1;

	int tadx = 1;
	for (int i = 1; i <= X; i++) 
		tmp[arr[y][i]]++;	
	for (int i = 1; i <= 100; i++) 
		if (tmp[i] > 0) {
			sort[sdx] = i;
			sdx++;
		}
		
	int Min, MinIdx, swapidx;
	for (int j = 1; j < sdx; j++) {
		Min = tmp[sort[j]];
		MinIdx = sort[j];
		swapidx = j;
		for (int i = j + 1; i < sdx; i++) {
			if (tmp[sort[i]] < Min) {
				Min = tmp[sort[i]];
				MinIdx = sort[i];
				swapidx = i;
			}
			else if (tmp[sort[i]] == Min && MinIdx > sort[i]) {
				Min = tmp[sort[i]];
				MinIdx = sort[i];
				swapidx = i;
			}
		}		
		arr[y][tadx] = MinIdx;
		arr[y][tadx+1] = Min;
		tadx += 2;
		if (tadx > 100)
			break;
		swap(sort[j], sort[swapidx]);
	}
	for (int i = tadx; i <= 100; i++)
		arr[y][i] = 0;

	if (tadx - 1 > MX)
		MX = tadx - 1;
}
void sortC(int x) {
	int tmp[101] = { 0, };
	int t_arr[101] = { 0, };
	int sort[101] = { 0, };
	int sdx = 1;

	int tadx = 1;
	for (int j = 1; j <= Y; j++) 
		tmp[arr[j][x]]++;	 // 카운팅 소트를 이용한다. 갯수 저장
	for (int i = 1; i <= 100; i++) 
		if (tmp[i] > 0) {
			sort[sdx] = i; // 카운팅 대상 숫자만 저장
			sdx++;
		}	

	int Min, MinIdx, swapidx;
	for (int j = 1; j < sdx; j++) { // 선택정렬
		Min = tmp[sort[j]];
		MinIdx = sort[j];
		swapidx = j;
		for (int i = j + 1; i < sdx; i++) {
			if (tmp[sort[i]] < Min) {
				Min = tmp[sort[i]];
				MinIdx = sort[i];
				swapidx = i;
			}
			else if (tmp[sort[i]] == Min && MinIdx > sort[i]) {
				Min = tmp[sort[i]];
				MinIdx = sort[i];
				swapidx = i;
			}
		}
		arr[tadx][x] = MinIdx;
		arr[tadx + 1][x] = Min;
		tadx += 2;
		if (tadx > 100) // 최대 100까지만
			break;
		swap(sort[j], sort[swapidx]);
	}
	for (int j = tadx; j <= 100; j++) // 빈곳은 0으로 채운다.
		arr[j][x] = 0;

	if (tadx - 1 > MY)
		MY = tadx - 1; // 최대 인덱스 저장
}
void Rfunc() {
	MX = 0;
	for (int j = 1; j <= Y; j++) {
		sortR(j);
	}
	X = MX;
}
void Cfunc() {
	MY = 0;
	for (int i = 1; i <= X; i++)
		sortC(i);
	Y = MY;
}

void prt() {
	cout << "arr\n";
	for (int j = 1; j <= Y; j++) {
		for (int i = 1; i <= X; i++)
			cout << arr[j][i] << " ";
		cout << endl;
	}cout << endl;
}

int main() {
	for (int j = 1; j <= 100; j++)
		for (int i = 1; i <= 100; i++)
			arr[j][i] = 0;

	cin >> R >> C >> K;

	for (int j = 1; j <= 3; j++)
		for (int i = 1; i <= 3; i++)
			cin >> arr[j][i]; // 초기 배열

	Y = 3; X = 3; MX = 3; MY = 3;

	int cnt = 0;
	while (arr[R][C] != K && cnt < 100) { // R,C에 해당하는 배열의 값이 K이거나 반복이 100을 넘어가면 종료
		if (Y >= X) {
			Rfunc();
		}
		else {
			Cfunc();
		}
		//cout << " Y : " << Y << " , X : " << X <<"cnt : " << cnt+1 <<" -> arr[" << R << "][" << C << "] : " << arr[R][C] << ", K : " << K << " - ";
		//prt();
		cnt++;
	}
	if (cnt == 100 && arr[R][C] != K)
		cout << -1;
	else 
		cout << cnt;

	return 0;
}