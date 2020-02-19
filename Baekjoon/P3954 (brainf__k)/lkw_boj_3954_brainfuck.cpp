#include<iostream>
using namespace std;

int m[100001]; // 포인터가 다루는 메모리
char c[4097];	// 명령어들이 담긴 배열
int pointer; // 메모리의 주소
char p[4097]; // 주어진 입력 문자열 저장
int pdx = 0; // 문자열을 가리키는 변수. 포인터처럼 주소 하나씩 가리켜
int ls, le; // 루프의 시작과 끝

int goto_idx[4097]; // 루프 발생시 이동할 명령어 인덱스

void init() { // 변수들 초기화
	for (int i = 0; i <= 100000; i++)
		m[i] = 0;
	for (int i = 0; i <= 4096; i++)
	{
		c[i] = 0;
		p[i] = 0;
	}
	pointer = 0;
	pdx = 0;
	ls = 0, le = 0;
}

bool compute(int m_s, int c_s, int i_s) {// 무한루프면 0, 정상종료되면 1
	int pc = 0;
	//int count_pc = 0;
	for(int count_pc=0; count_pc < 50000000; count_pc++) { // 오천만번 넘으면 무한

		if (c[pc] == '-') {
			m[pointer] = (m[pointer] - 1 + 256) % 256; // 0보다 작아지면 255로 가야해
			pc++;
			//cout << "- : " << m[pointer] << endl;
		}
		else if (c[pc] == '+') {
			m[pointer] = (m[pointer] + 1) % 256;
			pc++;
			//cout << "+ : " << m[pointer] << endl;
		}
		else if (c[pc] == '<') {
			pointer = (pointer + m_s - 1) % m_s; // 0에서 왼쪽으로 가면 오른쪽 끝으로
			pc++;
			//cout << "< : " << pointer << endl;
		}
		else if (c[pc] == '>') {
			pointer = (pointer + 1) % m_s; // 오른쪽 끝에서 오른쪽 가면 왼쪽 끝으로
			pc++;
			//cout << "> : " << pointer << endl;
		}
		else if (c[pc] == '.') { // 출력은 무시
			//char t = m[pointer];
			//cout << t << "\n";
			pc++;
		}
		else if (c[pc] == ',') { // 
			if (pdx >= i_s)
				m[pointer] = 255;
			else m[pointer] = p[pdx++];
			pc++;
		}
		else if (c[pc] == '[') {
			if (m[pointer] == 0) {
				pc = goto_idx[pc];
				//pc--;
				//pc++;
			}
			pc++;
		}
		else if (c[pc] == ']') {
			if (m[pointer] != 0) {
				//cout << "] : " << m[pointer] << '\n';				
				pc = goto_idx[pc];
				//pc--;
				//pc++;
			}
			pc++;
		}
		//pc++;
		if (le < pc) // 가장 바깥의 루프 구해야 통과된고 해서
			le = pc;
		//cout << "pc : " << pc << "\n";
		if (pc >= c_s)
			return 1;
	}
	return 0;
}

int main() {
	int T;
	int mem_size, code_size, input_size;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		cin >> mem_size >> code_size >> input_size;
		cin >> c; // 명령어
		cin >> p; // 출력문

		int ssnt = 0;
		int stack[2048];

		for (int i = 0; i < code_size; i++) {// 다음에 수행해야할 명령어 인덱스
			goto_idx[i] = i + 1;
			if (c[i] == '[') {
				stack[ssnt] = i;
				ssnt++;
			}
			else if (c[i] == ']') {
				goto_idx[i] = stack[ssnt - 1]; // 짝이 맞는 루프 ] -> [
				goto_idx[stack[ssnt - 1]] = i; // 짝이 맞는 루프 [ -> ]
				ssnt--;
			}

		}
		//cout << "goto : ";
		//for(int i=0; i < code_size; i++)
		//	cout << goto_idx[i] << " ";
		//cout << endl;
		//cout << c << endl;
		//cout << p << endl;
		bool f = compute(mem_size, code_size, input_size);
		if (f)
			cout << "Terminates\n";
		else cout << "Loops " << goto_idx[le] << " " << le << endl;
	}

	return 0;
}