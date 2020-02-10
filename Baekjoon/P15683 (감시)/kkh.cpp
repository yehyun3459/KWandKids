#include <iostream>
#include <vector>
using namespace std;
int N, M, Arr[9][9], mode[8], my[4] = { 0 , 0, 1, -1 }, mx[4] = { 1,-1,0,0 }, maxx, zeroCnt;
int del_x[4][2] = { {1,0},{-1,0},{-1,0},{1,0} }; //3번 카메라 델타 값
int del_y[4][2] = { {0,-1},{0,-1},{0,1},{0,1} }; 
int Del_x[4][3] = { {1,0, -1},{0,-1,0},{-1,0,1},{0,1,0} }; //4번 카메라 델타 값
int Del_y[4][3] = { {0,-1,0},{-1,0,1},{0,1,0},{1,0,-1} };
struct cctv { int y, x, model; }; //cctv 위치 및 카메라 정보 저장
vector<cctv> v;
void fu() {         //카메라 방향 정한 뒤 시야 계산 함수
	int isvis[9][9] = { 0 }, yy, xx;
	int cnt = 0;
	for (int i = 0; i < (int)v.size(); i++) {//카메라 위치 및 종류 불러오기
		cctv tmp = v[i];
		int mod = mode[i]; //카메라 별 방향 표시
		switch (tmp.model) { //카메라 종류
		case 1:         //1번 카메라 일 경우
			yy = tmp.y, xx = tmp.x;
			while (1) {      //범위를 벗어나거나 벽을 만나기 전까지 시야 추가
				yy += my[mod - 1];
				xx += mx[mod - 1];
				if (yy <= 0 || yy > N || xx <= 0 || xx > M || Arr[yy][xx] == 6) 
					break;
				else if (!Arr[yy][xx] && !isvis[yy][xx]) {  //감시 된 범위값 추가
					isvis[yy][xx] = 1;
					cnt++;
				}
			}
			break;
		case 2:       //2번 카메라
			if (mod == 1) //세로 방향일경우
				for (int k = 2; k <= 3; k++) {
					yy = tmp.y, xx = tmp.x;
					while (1) {     //범위를 벗어나거나 벽을 만나기 전까지 시야 추가
						yy += my[k];

						if (yy <= 0 || yy > N || Arr[yy][xx] == 6)	
							break;
						else if (!Arr[yy][xx] && !isvis[yy][xx]) {
							isvis[yy][xx] = 1;
							cnt++;
						}
					}
				}
			else if (mod == 2)  //가로 방향일경우
				for (int k = 0; k <= 1; k++) {
					yy = tmp.y, xx = tmp.x;
					while (1) {     //범위를 벗어나거나 벽을 만나기 전까지 시야 추가
						xx += mx[k];
						if (xx <= 0 || xx > M || Arr[yy][xx] == 6)	
							break;
						else if (!Arr[yy][xx] && !isvis[yy][xx]) {
							isvis[yy][xx] = 1;
							cnt++;
						}
					}
				}
			break;
		case 3: //   3번 카메라
			for (int k = 0; k <= 1; k++) { //두가지 방향 표시
				yy = tmp.y, xx = tmp.x;
				while (1) {      
					yy += del_y[mod - 1][k];  //방향에 따라 다른 델타값 추가
					xx += del_x[mod - 1][k];
					if (yy <= 0 || yy > N || xx <= 0 || xx > M || Arr[yy][xx] == 6)	
						break;
					else if (!Arr[yy][xx] && !isvis[yy][xx]) {
						isvis[yy][xx] = 1;
						cnt++;
					}
				}
			}
			break;
		case 4: //  4번 카메라
			for (int k = 0; k <= 2; k++) { // 3가지 방향 표시
				yy = tmp.y, xx = tmp.x;
				while (1) {
					yy += Del_y[mod - 1][k]; //방향에 따라 다른 델타값 추가
					xx += Del_x[mod - 1][k];
					if (yy <= 0 || yy > N || xx <= 0 || xx > M || Arr[yy][xx] == 6)	
						break;
					else if (!Arr[yy][xx] && !isvis[yy][xx]) {
						isvis[yy][xx] = 1;
						cnt++;
					}
				}
			}
			break;
		case 5:  // 5번 카메라
			for (int k = 0; k < 4; k++) {
				yy = tmp.y, xx = tmp.x;
				while (1) {
					yy += my[k];
					xx += mx[k];
					if (yy <= 0 || yy > N || xx <= 0 || xx > M || Arr[yy][xx] == 6)	
						break;
					else if (!Arr[yy][xx] && !isvis[yy][xx]) {
						isvis[yy][xx] = 1;
						cnt++;
					}
				}
			}
			break;
		}
	}

	if (zeroCnt == cnt) { //전부 시야를 확보했으면 조기 종료
		cout << 0;
		exit(0);
	}		

	if (maxx < cnt) // 확보된 시야 중 최대값 저장
		maxx = cnt;
}

void dfs(int cnt) {  // 카메라 종류 별 가능한 방향 모두 설정
	if (cnt == v.size()) { //마지막 카메라까지 모두 설정했으면 시야 계산
		fu();
		return;
	}

	cctv tmp = v[cnt];
	if (tmp.model == 2)  //2번카메일 경우 2가지 방향 설정
		for (int i = 1; i <= 2; i++) {
			mode[cnt] = i;
			dfs(cnt + 1);
		}
	else if (tmp.model == 5) { // 5번카메일경우 한가지 방향설정
		mode[cnt] = 1;	
		dfs(cnt + 1);
	}
	else {        //나머지 4가지 방향 설정
		for (int i = 1; i <= 4; i++) {
			mode[cnt] = i;
			dfs(cnt + 1);
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= M; j++) {
			cin >> Arr[i][j];
			if (Arr[i][j] && Arr[i][j] < 6)	
				v.push_back({ i,j,Arr[i][j] }); // 카메라 정보 백터로 저장
			else if (!Arr[i][j])	
				zeroCnt++;  //빈칸 갯수 
		}
	dfs(0);
	cout << zeroCnt - maxx; 사각지대 출력
	return 0;
}
