#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int N, M, K, tmp, ed, totcnt, land[11][11], Add[11][11], move_y[8] = { -1, -1, -1, 0, 1, 1, 1, 0 }, move_x[8] = { -1,0,1,1,1,0,-1,-1 };
deque<int> v[11][11];

int main() {
	scanf(" %d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			scanf(" %d", &Add[i][j]); //매년 추가되는 양분값
			land[i][j] = 5; //토지 저장되있는 양분값
		}
	totcnt = M; //전체 심어져있는 나무 수
	int y, x, z;
	for (int i = 0; i < M; i++) {
		scanf(" %d %d %d", &y, &x, &z);
		v[y][x].push_back(z);//좌표 별 나무나이 저장
	}
	//////////////////////////////////////////////////////
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			sort(v[i][j].begin(), v[i][j].end()); //좌표 별 오름차순으로 정렬, 어린 나무 우선
	
	for (int year = 1; year <= K; year++) {
		//봄
		for (int i = 1; i <= N; i++) 
			for (int j = 1; j <= N; j++) {
				tmp = 0, ed = v[i][j].size();
				for (int cnt = 0; cnt < ed; cnt++) {
					if (land[i][j] < v[i][j][cnt]) { //토지 양분과 나무 나이 비교

						for (int kk = ed - 1; kk >= cnt; kk--) {
							tmp += v[i][j][kk] / 2; //나무가 더 클 경우 뒷 배열 전부 임시 저장 및 pop
							v[i][j].pop_back();
						}
						totcnt -= ed - cnt; //죽은 나무 만큼 카운트 다운
						break;
					}
					else {
						land[i][j] -= v[i][j][cnt]; //토지 양분이 더 많을 경우 나무 나이만큼 차감
						v[i][j][cnt]++; 
					}
				}
				land[i][j] += tmp; //여름 ,  죽은 나무 임시저장 값 토지에 추가
			}
		//가을 + 겨울
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				land[i][j] += Add[i][j];
				tmp = v[i][j].size();
				for (int cnt = 0; cnt < tmp; cnt++) {
					if (!(v[i][j][cnt] % 5)) {
						for (int k = 0; k < 8; k++) { //주변 8개 좌표 확인
							int tmp_y = i + move_y[k];
							int tmp_x = j + move_x[k];
							if (tmp_y > 0 && tmp_y <= N && tmp_x > 0 && tmp_x <= N) {
								v[tmp_y][tmp_x].push_front(1); // 1을 젤 앞으로 삽입
								totcnt++; //카운트 추가
							}}}}}}}
	printf("%d", totcnt);
	return 0;
}
