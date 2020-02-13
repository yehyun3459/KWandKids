#include <iostream>
using namespace std;
int N, Arr[21][21], is[5], maxx;
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> Arr[i][j];
	int a[5];
	for (a[0] = 1; a[0] <= 4; a[0]++)
		for (a[1] = 1; a[1] <= 4; a[1]++)
			for (a[2] = 1; a[2] <= 4; a[2]++)
				for (a[3] = 1; a[3] <= 4; a[3]++)
					for (a[4] = 1; a[4] <= 4; a[4]++) { //5개 방향 지정

						int tmp_Arr[21][21] = { 0 }; //보드판 백업
						for (int i = 1; i <= N; i++)
							for (int j = 1; j <= N; j++)
								tmp_Arr[i][j] = Arr[i][j];

						int st, ed, del;
						for (int n = 0; n < 5; n++) { //5번 시도
							int tmp_tmp[21][21] = { 0 }; //백업의 백업

							if (a[n] == 1 || a[n] == 2) { //방향에 방향에 따라 시작 값, 델타 다르게 적용
								st = a[n] == 1 ? 1 : N;
								ed = a[n] == 1 ? N : 1;
								del = a[n] == 1 ? 1 : -1;							

								for (int i = 1; i <= N; i++) {            //한쪽으로 밀기
									int tmp = -1;
									int idx = 1;
									for (int j = st; j <= N && j >= 1; j += del) {
										if (!tmp_Arr[i][j]) continue;           //0일땐 건너뜀
										if (tmp != tmp_Arr[i][j]) {             //이전값과 다르면 tmp에 임시저장 후 입력
											tmp_tmp[i][idx++] = tmp_Arr[i][j];
											tmp = tmp_Arr[i][j];
										}								
										else {
											tmp_tmp[i][idx - 1] = tmp * 2; //이전값과 같으면 두배값 입력
											tmp = -1;
										}
											
									}
								}
							}
							else {                        //새로방향도 똑같이
								st = a[n] == 3 ? 1 : N;
								ed = a[n] == 3 ? N : 1;
								del = a[n] == 3 ? 1 : -1;

								for (int i = 1; i <= N; i++) {
									int tmp = -1;
									int idx = 1;
									for (int j = st; j <= N && j >= 1; j += del) {
										if (!tmp_Arr[j][i]) continue;
										if (tmp != tmp_Arr[j][i]) {
											tmp_tmp[idx++][i] = tmp_Arr[j][i];
											tmp = tmp_Arr[j][i];
										}
										else {
											tmp_tmp[idx-1][i] = tmp * 2;
											tmp = -1;
										}											
									}
								}
							}

							for (int i = 1; i <= N; i++)
								for (int j = 1; j <= N; j++)
									tmp_Arr[i][j] = tmp_tmp[i][j];  //백업의 백업을 백업에 옮기기
						}

						for (int i = 1; i <= N; i++) //5번 다 이동했으면 최대값 구하기
							for (int j = 1; j <= N; j++) 
								if (maxx < tmp_Arr[i][j]) 
									maxx = tmp_Arr[i][j];							
					}

	cout << maxx;
	return 0;
}
