#include <iostream>
using namespace std;
int N, M, dir[12], my[4] = { 0,0,1,-1 }, mx[4] = { 1,-1,0,0 }, minn = 11;
pair<int, int> ball[2], tmp[2]; //r,b
char board[11][11];
int fu() { // 구슬판 회전하기
	char arr[11][11] = {0}; // 구슬판 백업
	for (int i = 1; i <= N; i++)  
		for (int j = 1; j <= M; j++) 
			arr[i][j] = board[i][j];
		
	tmp[0] = ball[0], tmp[1] = ball[1]; //최초 R,B 위치
	for (int n = 1; n < minn; n++) { // 최대 10번 기울리기 
		int dd = dir[n] - 1, flag, isred = 1; //dd : 기울리는 방향, flag : 구슬 움직임 확인, isred : 빨간구슬을 넣었는지 확인
		while (1) {
			flag = 1;
			if (isred) { //빨간공 있을때만
				if (arr[tmp[0].first + my[dd]][tmp[0].second + mx[dd]] == '.' || arr[tmp[0].first + my[dd]][tmp[0].second + mx[dd]] == 'O') {
					arr[tmp[0].first][tmp[0].second] = '.';
					tmp[0].first += my[dd];
					tmp[0].second += mx[dd];

					if (arr[tmp[0].first][tmp[0].second] == '.') 
						arr[tmp[0].first][tmp[0].second] = 'R'; //이동한곳으로 R 교체
					else 
						isred = 0; //O에 도착을 때 표시
				
					flag = 0; // 한번이라도 움직였으면 표시
				}
			}		
		  
      //파란공 
			if (arr[tmp[1].first + my[dd]][tmp[1].second + mx[dd]] == '.' || arr[tmp[1].first + my[dd]][tmp[1].second + mx[dd]] == 'O') {
				arr[tmp[1].first][tmp[1].second] = '.';
				tmp[1].first += my[dd];
				tmp[1].second += mx[dd];

				if (arr[tmp[1].first][tmp[1].second] == '.') 
					arr[tmp[1].first][tmp[1].second] = 'B'; //이동한 곳으로 B교체
				else 
					//파란볼이 먼저 들어면 실패 그대로 종료
					return -1;
                
				flag = 0; //구슬 움직임 확인
			}			
			if (flag) //두 구슬 모두 안움직였으면 이번 기울임은 종료
				break;
		}
		//빨간 들어가고 동작 끝날때 - 한턴에 파란구슬과 같이 들어가는거 구별하기위해 루프 밖에서 확인
		if (isred == 0) {
			if(minn > n)
				minn = n; //현재까지 최소 기울임 횟수
			return 1;
		}
	}
    //10번 넘을 때
	return -1;
}

void dfs(int cnt) { //순서에 따른 방향구하기
	if (cnt == minn) { 횟수가 최소값 이상이면 시뮬하고 리턴
		fu();return;
	}
	if (cnt >= minn)	return;
    
	for (int i = 1; i <= 4; i++) {
		if (dir[cnt - 1] != i) {
			dir[cnt] = i; //순서에 따른 방향 지정
			dfs(cnt + 1);
			dir[cnt] = 0;
		}	
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j <= M; j++) {
			scanf(" %c", &board[i][j]);
			if (board[i][j] == 'R') {
				ball[0].first = i;
				ball[0].second = j;
			}
			else if (board[i][j] == 'B') {
				ball[1].first = i;
				ball[1].second = j;
			}
		}	
	dfs(1);
	if (minn > 10)
		cout << -1;
	else
		cout << minn;
	return 0;
}
