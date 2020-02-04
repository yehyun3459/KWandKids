#include <iostream>
#include <algorithm>
using namespace std;
int r, c, k, Arr[201][201], row_size, col_size;
void col() {
	int tmp_row_cnt = row_size;
	for (int j = 0; j < col_size; j++) {
		pair<int, int> p[101] = { { 0, 0 } };
		int maxx = 0;
		for (int i = 0; i < tmp_row_cnt; i++) {
			if (Arr[i][j]) {
				p[Arr[i][j]].first++;
				p[Arr[i][j]].second = Arr[i][j];
				maxx = Arr[i][j] > maxx ? Arr[i][j] : maxx;
			}
		}
		sort(p + 1, p + maxx + 1);
		int idx = 0;
		for (int i = 1; i <= maxx; i++) {
			if (p[i].second) {
				Arr[idx][j] = p[i].second;
				Arr[idx+1][j] = p[i].first;
				idx += 2;
			}
		}
		for (int i = idx; i < tmp_row_cnt * 2; i++)
			Arr[i][j] = 0;
		if (row_size < idx)
			row_size = idx;
	}
}

void row() {
	int tmp_col_cnt = col_size;
	for (int j = 0; j < row_size; j++) {
		pair<int, int> p[101] = { { 0, 0 } };
		int maxx = 0;
		for (int i = 0; i < tmp_col_cnt; i++) {
			if (Arr[j][i]) {
				p[Arr[j][i]].first++;
				p[Arr[j][i]].second = Arr[j][i];
				maxx = Arr[j][i] > maxx ? Arr[j][i] : maxx;
			}
		}
		sort(p + 1, p + maxx + 1);
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