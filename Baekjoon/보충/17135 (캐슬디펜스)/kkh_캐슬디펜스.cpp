#include <iostream>
#include <vector>
using namespace std;
int N, M, D, Arr[16][16], bow[3], maxx;
vector < pair<int, int> >  v;

void fu() {
	int isattack[16][16] = { 0 };  //적 죽었는지 표시
	for (int cnt = 0; cnt < N; cnt++) { // 적이 내려오는걸 사정거리가 1씩 증가하는걸로 대체
		pair<int, int> near[3] = { {0,0} }; //죽은 적 한번에 최대 3명
		for (int bow_idx = 0; bow_idx < 3; bow_idx++) { //활 3명
			int tmp_min = INT32_MAX;
			for (int i = 0; i < (int)v.size(); i++) {
				if (isattack[v[i].first][v[i].second])	continue; //이미 죽은 적 패스
				if (v[i].first > N - cnt)				continue;         //아래로 이미 내려간 적 패스

				int len = N + 1 - v[i].first + abs(bow[bow_idx] - v[i].second);
				if (D + cnt >= len) {
					if (tmp_min > len) {  //가장 가까운 적 확인
						tmp_min = len;
						near[bow_idx].first = v[i].first, near[bow_idx].second = v[i].second;
					}
					else if (tmp_min == len && near[bow_idx].second > v[i].second)
						near[bow_idx].first = v[i].first, near[bow_idx].second = v[i].second;
				}
			}
		}
		for (int i = 0; i < 3; i++) //중복 문제로 3명 다 쏜 뒤 변경
			isattack[near[i].first][near[i].second] = 1;
	}

	int totcnt = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (Arr[i][j] && isattack[i][j]) //최종 카운트
				totcnt++;

	if (maxx < totcnt) //최대값 구하기
		maxx = totcnt;
}

int main() {
	cin >> N >> M >> D;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			cin >> Arr[i][j];
			if (Arr[i][j])
				v.push_back({ i,j });  //적 위치 저장
		}

	for (int i = 1; i <= M - 2; i++)
		for (int j = i + 1; j <= M - 1; j++)
			for (int k = j + 1; k <= M; k++) {      //활 위치 3개 선택
				bow[0] = i, bow[1] = j, bow[2] = k;
				fu();
			}

	cout << maxx;
	return 0;
}
