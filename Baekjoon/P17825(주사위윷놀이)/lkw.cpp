#include<iostream>
using namespace std;

struct node {
	int index=0; // self.index
	int next[2] = { 0,0 }; // if blue disk, start next index is 1.
	int weight=0; // get point
	char status = 'r'; // most of disk is 'r', special disk is 'b'
		// start disk is 's', end disk is 'e'
};

node nd[33]; // 점수판
bool h_check[33] = { 0, }; // 말 겹치기 안된다니까 그거 구분하려고. 말 있으면 1 없으면 0

int dice_num[10] = { 0, }; // 1~5, 주사위 10번
int horse[4] = { 0,0,0,0 }; // 4개의 주사위가 현재 어디에 있는지 0~32
int Max_socre = 0; // 가장 높은 점수

void ndset() { // 말판 초기 세팅.
	// blue, start, end
	nd[5].status = 'b'; // blue disk
	nd[10].status = 'b';
	nd[15].status = 'b';
	nd[0].status = 's';
	nd[32].status = 'e';

	// disk 0~20
	for (int i = 0; i <= 20; i++) {
		nd[i].index = i;
		nd[i].weight = i * 2;		
		nd[i].next[0] = i + 1;
	}
	nd[20].next[0] = 32; // move to end
	nd[5].next[1] = 21; // 
	nd[10].next[1] = 24;
	nd[15].next[1] = 29;
	// disk 21~23
	for (int i = 1; i <= 3; i++) {
		nd[20+i].index = 20 + i;
		nd[20+i].weight = 10 + i*3;		
		nd[20+i].next[0] = 21 + i;
	}
	nd[23].next[0] = 26;
	// disk 24 ~ 28
	nd[24].index = 24;
	nd[24].weight = 22;
	nd[24].next[0] = 25;

	nd[25].index = 25;
	nd[25].weight = 24;
	nd[25].next[0] = 26;

	nd[26].index = 26;
	nd[26].weight = 25;
	nd[26].next[0] = 27;

	nd[27].index = 27;
	nd[27].weight = 30;
	nd[27].next[0] = 28;

	nd[28].index = 28;
	nd[28].weight = 35;
	nd[28].next[0] = 20;
	// 29~31
	nd[29].index = 29;
	nd[29].weight = 28;
	nd[29].next[0] = 30;

	nd[30].index = 30;
	nd[30].weight = 27;
	nd[30].next[0] = 31;

	nd[31].index = 31;
	nd[31].weight = 26;
	nd[31].next[0] = 26;
	// 32
	nd[32].index = 32;
	nd[32].weight = 0;
	nd[32].next[0] = 32;
}
void prtnd() { // 세팅 잘 되었나 확인하려구
	for (int i = 0; i < 33; i++) {
		cout << nd[i].index << ") "  << ", weight : " << nd[i].weight << ", next : " << nd[i].next[0] << ", " << nd[i].next[1] << endl;
	}
}
void prtH() {// 각 말이 현재 어디에 있나 출력하는 함수
	cout << "Horse : \n";
	for (int i = 0; i < 4; i++) {
		cout << i << ")  " << horse[i] << endl;
	}cout << endl;
}
int play(int play_s, int horse_idx) {  // 주사위에 나온 수 만큼 말을 이동시키는 함수.
	// 던질 차례, 던질 말 idx
	int num = dice_num[play_s]; // 주사위 뭐나왔나 1~5
	int htmp = horse[horse_idx]; // 현재 말의 위치. 이동 후 위치에 다른말이 있으면 롤백 해야해서.
	
	if (nd[htmp].status == 'b')  // 파랑 디스크 시작이면
		htmp = nd[htmp].next[1];	
	else if(nd[htmp].status == 's' || nd[htmp].status == 'r')
		htmp = nd[htmp].next[0];

	for (int i = 1; i < num; i++) {
		if (nd[htmp].status == 'e') // 말판의 끝에 다다르면 그만
			break;
		htmp = nd[htmp].next[0];
	}
	if (h_check[htmp] == 1 && htmp != 32) // 이미 말이 있는 곳이면 노노
		return -1;

	horse[horse_idx] = htmp; // 놓을 수 있으면 말의 위치 변경
	return nd[horse[horse_idx]].weight; // 그 때의 점수 리턴
}

void dfs(int s, int e, int score) {// s : dice roll count, e: 10, score : score
	if (s >= e) { // 다 던졋으면
		if (score > Max_socre) {
			Max_socre = score;
			//cout << "SCORE : " << score  <<endl;
		}
		return; // 함수의 종료를 명시적으로 표현해 보았습니다.
	}
	else {
		for (int i = 0; i < 4; i++) { // 모든 말에 대해
			if (nd[horse[i]].status != 'e') { // 끝까지 간 말이 아니라면
				int hidx = horse[i]; // 현재 위치를 기억

				int tmp_s = play(s, i); // 현재 말을 움직이고, 그 때의 점수 ( 말의 위치도 바뀜. 안 움직였을 때는 안 바뀜 )
				if (tmp_s == -1) // 이미 있는 곳이면 다른 말 시도
					continue;

				h_check[hidx] = 0; //이동 전 위치를 0으로
				h_check[horse[i]] = 1; // 이동 후 위치를 1로 변경
				
				dfs(s + 1, e, score+tmp_s); // 이 상태에서 탐색을 해보고, 				
				
				h_check[hidx] = 1; // 다시 주사위 굴리기 전으로 롤백
				h_check[horse[i]] = 0;
				horse[i] = hidx; 
			}
		}
	}
}

int main() {
	ndset(); // 말판, 말  등 초기 세팅
	//prtnd();

	for (int i = 0; i < 10; i++)  
		cin >> dice_num[i]; // 주사위 숫자 입력 받아
		
	dfs(0, 10, 0); // 돌려 보고
	cout << Max_socre << endl; // 최대 점수 출력
	
	return 0;
}