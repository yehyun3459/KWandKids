#include <iostream>
using namespace std;
int paper[11][11], cnt[6] = { 0,5,5,5,5,5 };
int nOnecnt, minn = INT32_MAX;

void dfs(int y, int x, int colorpaperCnt, int nCnt_OneNum) {// y,x, 붙인 색종이 갯수, 남은 1값 개수
	if (nCnt_OneNum == 0) {
		if (minn > colorpaperCnt)
			minn = colorpaperCnt;

		return;
	}

	if (y > 10)               //1,1부터 오른쪽으로 한칸씩 탐색
		return;
	
	if (paper[y][x]) {        //1값 찾을 시 1~5크기의 색종이 전부 탐색
		for (int nsize = 1; nsize <= 5; nsize++) {
			if (cnt[nsize]) {			//쓸 색종이가 남았는지 

				for (int i = 0; i < nsize; i++) 
					for (int j = 0; j < nsize; j++) 
						if (paper[y + i][x + j] == 0)   //크기 안맞으면 탈출
							goto Pass;

				for (int i = 0; i < nsize; i++) 
					for (int j = 0; j < nsize; j++) 
						paper[y + i][x + j] = 0;	      //맞으면 붙인부분 0으로 변경
			
				cnt[nsize]--;

				if (x == 10)          //다음 위치 dfs 반복
					dfs(y + 1, 1, colorpaperCnt + 1, nCnt_OneNum - nsize * nsize);
				else
					dfs(y, x + 1, colorpaperCnt + 1, nCnt_OneNum - nsize * nsize);
								
				for (int i = 0; i < nsize; i++)  //색종이 붙인 부분 다시 1 복구
					for (int j = 0; j < nsize; j++) 
						paper[y + i][x + j] = 1;

				cnt[nsize]++;   //크기별 색종이 카운트


			Pass:
				int test = 0;
			}
		}
	}
	else {
		if (x == 10)
			dfs(y + 1, 1, colorpaperCnt, nCnt_OneNum);
		else
			dfs(y, x + 1, colorpaperCnt, nCnt_OneNum);
	}	
}

int main() {
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cin >> paper[i][j];
			if (paper[i][j]) 
				nOnecnt++; //1 값 카운트
		}
	}

	dfs(1, 1, 0, nOnecnt);	

	if (minn == INT32_MAX)
		cout << -1;
	else
		cout << minn;

	return 0;
}
