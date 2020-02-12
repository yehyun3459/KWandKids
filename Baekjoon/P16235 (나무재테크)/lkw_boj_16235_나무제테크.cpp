#include <time.h>
#include<iostream>
using namespace std;

int N, M, K; //변 길이, 나무 수, 햇 수

struct tree {
	int y = 0, x = 0, age = 0;
	tree* next = NULL;
	tree* prev = NULL;
};
tree Tr[10000000]; // 동적은 너무 느리오. 정적으로 갑시다.
int Trd = 0;


struct trist { // 연결리스트 너무너무 싫다
	tree* head = NULL;
	tree* tail = NULL;

	void insert(tree* a) { // 리스트 삽입
		if (head == NULL) { // 첫 삽입일 때
			head = a;
			tail = a;
			return;
		}
		else if (head == tail) { // 기존 리스트가 하나 밖에 업을 때
			//cout << "chk 0";
			tree* tmp = head;
			if (cmp(a, tmp)) {
				head = a;
				a->next = tmp;
				tmp->prev = a;
			}
			else {
				tail = a;
				a->prev = tmp;
				tmp->next = a;
			}
			return;
		}
		else {
			//cout << "chk 1";
			tree* tmp = head;
			while (tmp->next != NULL) {
				//cout << "chk 2!";
				if (cmp(a, tmp) == 0) { // 삽입 위치를 찾아나가자
					//cout << "chk 3!";
					tmp = tmp->next;
				}
				else {
					//cout << "chk 4!";
					if (tmp != head) { // 맨 앞에 삽입이 아니다
						tmp->prev->next = a; // if tmp head, error
						a->prev = tmp->prev;
						tmp->prev = a;
						a->next = tmp;
						return;
					}
					else { // 대가리에 삽입해야한다
						head = a;
						tmp->prev = a;
						a->next = tmp;
						a->prev = NULL;
						return;
					}
				}
				//cout << "chk !";
			}
			if (cmp(a, tmp)) { // 꼬리에 삽입
				tmp->prev->next = a;
				a->prev = tmp->prev;
				a->next = tmp;
				tmp->prev = a;
				tmp->next = NULL;
				tail = tmp;
			}
			else { // 꼬리 직전
				tmp->next = a;
				a->prev = tmp;
				tail = a;
			}
		}
	}
	void remove(tree* a) { // 삭제 ㅠㅠ
		if (a->next == NULL && a->prev == NULL) {// 혼자야?
			head = NULL;
			tail = NULL;
			//delete a;
		}
		else if (a->prev == NULL) { // 헤드야?
			head = a->next;
			head->prev = NULL;
			//delete a;
		}
		else if (a->next == NULL) { // 꼬리야?
			tail = a->prev;
			tail->next = NULL;
			//delete a;
		}
		else { // 중간이구나
			a->prev->next = a->next;
			a->next->prev = a->prev;
			//delete a;
		}
	}
	bool cmp(tree* a, tree* b) { // 1 나올 때 까지
		if (a->age > b->age)
			return 0;
		else if (b->age >= a->age)
			return 1;

	}
	void prt() {
		tree* tmp = head;
		cout << "-tree info-\n";
		while (tmp != NULL) {
			cout << "r :" << tmp->y << ", c : " << tmp->x << ", age : " << tmp->age << endl;
			tmp = tmp->next;
		}
		cout << endl;
	}
};

int a[11][11]; // static양분
int land[11][11];
int deadenergy[11][11];

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

trist T[11][11];

void spring() {
	//나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다. 
	//각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다. 
	//	하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다. 
	//만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			deadenergy[j][i] = 0;

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* tmp = T[j][i].head;
			tree* tmp2;
			while (tmp != NULL) {
				if (land[j][i] < tmp->age) {
					tmp2 = tmp;
					tmp = tmp->next;
					deadenergy[j][i] += tmp2->age / 2;
					//cout << "r :" << tmp2->y << ", c : " << tmp2->x << ", age : " << tmp2->age << endl;
					T[j][i].remove(tmp2);
				}
				else {
					land[j][i] -= tmp->age;
					tmp->age++;
					tmp = tmp->next;
				}
			}
		}
	}
}
void summer() {
	// summer
			//여름에는 봄에 죽은 나무가 양분으로 변하게 된다.
			//각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다.소수점 아래는 버린다.
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			land[j][i] += deadenergy[j][i];
}
void autumn() {
	//가을에는 나무가 번식한다.번식하는 나무는 나이가 5의 배수이어야 하며, 
	//인접한 8개의 칸에 나이가 1인 나무가 생긴다.
	//상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.
	tree* auttmp[11][11];
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			auttmp[j][i] = T[j][i].head;

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* tmp = auttmp[j][i];
			int y0, x0;
			while (tmp != NULL) {
				if (tmp->age % 5 == 0) {
					for (int i = 0; i < 8; i++) {
						y0 = tmp->y + dy[i];
						x0 = tmp->x + dx[i];
						if (y0 >= 1 && y0 <= N && x0 >= 1 && x0 <= N) {
							tree* nt = &Tr[Trd];//new tree;
							Trd++;
							nt->age = 1;
							nt->y = y0;
							nt->x = x0;
							//cout << "chk 4";
							T[y0][x0].insert(nt); // error
							//cout << "r :" << nt->y << ", c : " << nt->x << ", age : " << nt->age << endl;
						}
					}
				}
				tmp = tmp->next;
			}
		}
	}
}
void winter() {
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			land[j][i] += a[j][i];
}
int main() {
	clock_t start, end; // 동적 할당에서 많은 시간이 요구되는 것을 알았고, 이를 개선하고자 정적으로 겁나게 미리 잡아놈

	cin >> N >> M >> K;

	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++) {
			cin >> a[j][i];
			land[j][i] = 5;
		}
	int r, c, a;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> a;
		tree* tmp = &Tr[Trd];//new tree;
		Trd++;
		tmp->y = r;
		tmp->x = c;
		tmp->age = a;
		T[r][c].insert(tmp);
		//T.prt();
	}

	double tspr = 0, tsum = 0, taut = 0, twin = 0;

	for (int i = 1; i <= K; i++) {
		//cout << i << "번째 봄" << endl;
		//start = clock();
		spring();
		//end = clock();
		//tspr += end - start;
		//cout << "봄째 여름" << endl;

		//start = clock();
		summer();
		//end = clock();
		//tsum += end - start;
		//T.prt();

		//cout << i << "번째 가을" << endl;
		//start = clock();
		autumn();
		//end = clock();
		//t/aut += end - start;
		//T.prt();

		//cout << i << "번째 겨울" << endl;
		//start = clock();
		winter();
		//end = clock();
		//twin += end - start;
		//T.prt();
	}
	//T[1][1].prt();

	//cout << " 봄  : " << tspr <<endl;
	//cout << "여름 : " << tsum << endl;
	//cout << "가을 : " << taut << endl;
	//c/out << "겨울 : " << twin << endl;

	int count = 0;

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* tmp = T[j][i].head;
			while (tmp != NULL)
			{
				count++;
				tmp = tmp->next;
			}
		}
	}
	cout << count;

	/*
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* rp = T[j][i].head;
			tree* rp2;
			while (rp != NULL) {
				rp2 = rp;
				rp = rp->next;
				delete rp2;
			}
		}
	}
	*/

	return 0;
}