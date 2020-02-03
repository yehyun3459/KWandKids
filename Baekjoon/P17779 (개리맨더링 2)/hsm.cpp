#include<stdio.h>
#include<iostream>

#define MAX 20

using namespace std;

struct POS
{
	int x;
	int y;
};

int n;
int ans = 987654321;
int map[MAX][MAX];
int map2[MAX][MAX];

POS point[4];

void calculate() {
	int a[5] = { 0,0,0,0,0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[map2[i][j]-1] += map[i][j];
		}
	}
	
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 5; j++) {
			if (a[i] < a[j]) {
				int temp;
				temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
		}
	}
	

	if (ans > a[0] - a[4]) {
		ans = a[0] - a[4];
	}
	//ans = (ans > (a[0] - a[4])) ? a[0] - a[4] : ans;
	//printf("%d %d %d %d %d ans:%d\n", a[0],a[1],a[2],a[3],a[4],ans);
}

void write_map(int x, int y, int d1, int d2) {
	//printf("%d %d %d %d\n", x, y, d1, d2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map2[i][j] = 5;
		}
	}

	//1锅 备开
	int count = 0;
	for (int i = 0; i < point[1].x; i++) {
		if (i >= point[0].x) count++;
		for (int j = 0; j <= point[0].y - count; j++) {
			map2[i][j] = 1;
		}
	}


	//2锅 备开
	count = 0;
	for (int i = 0; i <= point[2].x; i++) {
		if (i > point[0].x) count++;
		for (int j = point[0].y + 1 + count; j < n; j++) {
			map2[i][j] = 2;
		}
	}


	//3锅 备开
	count = 0;
	for (int i = n - 1; i >= point[1].x; i--) {
		if (i < point[3].x) count++;
		for (int j = 0; j < point[3].y - count; j++) {
			map2[i][j] = 3;
		}
	}


	//4锅 备开
	count = 0;
	for (int i = n - 1; i > point[2].x; i--) {
		if (i <= point[3].x) count++;
		for (int j = point[3].y + count; j < n; j++) {
			map2[i][j] = 4;
		}
	}

	/*
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", map2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*/
	calculate();
}


bool check(int x, int y, int d1, int d2) {
	if (x + d1 >= n || y - d1 < 0) return false;
	if (x + d2 >= n || y + d2 >= n) return false;
	if (x + d1 + d2 >= n || y - d1 + d2 >= n) return false;
	if (x + d2 + d1 >= n || y + d2 - d1 < 0) return false;

	return true;
}


void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			for (int d1 = 1; d1 <= j; d1++) {
				for (int d2 = 1; d2 < n - j; d2++) {
					if (check(i, j, d1, d2) == true) {
						point[0].x = i;
						point[0].y = j;
						point[1].x = i + d1;
						point[1].y = j - d1;
						point[2].x = i + d2;
						point[2].y = j + d2;
						point[3].x = point[2].x + d1;
						point[3].y = point[1].y + d2;
						write_map(i, j, d1, d2);
						//printf("-----------------------------------------\n");
					}
				}
			}
		}
	}
}


int main() {
/*
6
1 2 3 4 1 6
7 8 9 1 4 2
2 3 4 1 1 3
6 6 6 6 9 4
9 1 9 1 9 5
1 1 1 1 9 9
	->18
*/

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	solve();
	printf("%d\n", ans);
	system("pause");
	return 0;

}