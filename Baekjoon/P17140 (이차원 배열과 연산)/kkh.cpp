#include <iostream>
#include <algorithm>
using namespace std;
int r, c, k, Arr[201][201], row_size, col_size;
void col() {//열 정렬
	int tmp_row_cnt = row_size; //행 개수 임시 저장
	for (int j = 0; j < col_size; j++) {
		pair<int, int> p[101] = { { 0, 0 } }; //(반복횟수, 숫자)
		int maxx = 0;
		for (int i = 0; i < tmp_row_cnt; i++) {
			if (Arr[i][j]) {
				p[Arr[i][j]].first++;
				p[Arr[i][j]].second = Arr[i][j];
				maxx = Arr[i][j] > maxx ? Arr[i][j] : maxx;//젤 큰 숫자 저장
			}
		}
		sort(p + 1, p + maxx + 1);//오름차순 정렬 횟수 기준으로
		int idx = 0;
		for (int i = 1; i <= maxx; i++) {
			if (p[i].second) {//0값 제외 후 횟수적은 순으로 입력
				Arr[idx][j] = p[i].second;
				Arr[idx+1][j] = p[i].first;
				idx += 2;
			}
		}
		for (int i = idx; i < tmp_row_cnt * 2; i++) //열 사이즈 줄어들 경우를 위해 0값으로 추가 
			Arr[i][j] = 0;
		if (row_size < idx) //정렬한 열 크기 중 젤 높은 값 설정
			row_size = idx;
	}
}

void row() {//행 정렬
	int tmp_col_cnt = col_size;//열 개수 임시저장
	for (int j = 0; j < row_size; j++) {
		pair<int, int> p[101] = { { 0, 0 } };//(횟수, 숫자)
		int maxx = 0;
		for (int i = 0; i < tmp_col_cnt; i++) {
			if (Arr[j][i]) {
				p[Arr[j][i]].first++;
				p[Arr[j][i]].second = Arr[j][i];
				maxx = Arr[j][i] > maxx ? Arr[j][i] : maxx;
			}
		}
		sort(p + 1, p + maxx + 1);//횟수별 정렬
		int idx = 0;
		for (int i = 1; i <= maxx; i++) {
			if (p[i].second) {
				Arr[j][idx] = p[i].second;
				Arr[j][idx + 1] = p[i].first;
				idx += 2;
			}
		}
		for (int i = idx; i < tmp_col_cnt * 2; i++)
			Arr[j][i] = 0;
		if (col_size < idx)
			col_size = idx;
	}
}

int main() {
	cin >> r >> c >> k;
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			cin >> Arr[i][j];

	col_size = 3, row_size = 3;
	int cnt = 0;
	for (cnt; Arr[r-1][c-1] != k; cnt++) {
		if (cnt > 100)
			break;
		if (col_size <= row_size)
			row();
		else
			col();	
	}
	if (cnt > 100)
		cout << -1;
	else
		cout << cnt;
	return 0;
}
