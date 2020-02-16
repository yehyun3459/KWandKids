#include <cstdio>
//Baekjoon - 13460(구슬탈출2)
using namespace std;

int N, M;
char map[10][10];
int dR[4] = { -1, 0, 1, 0 }; //상, 우, 하, 좌
int dC[4] = { 0, 1, 0, -1 };
int check = 0; //디버깅 용
//int o_r, o_c;

struct state {
	int dir;
	int red_r;
	int red_c;
	int blue_r;
	int blue_c;
	int time;
};
state que[1024*1024+1000000];
//queue<state> que;

//빨간공을 기울인 방향으로 움직이게 하는 함수
int moveR(state *s)
{
	int d = s->dir;
	int r = s->red_r, c = s->red_c, rr, cc;
	while (map[r][c] != '#')
	{
		rr = r + dR[d]; cc = c + dC[d];
		if (map[rr][cc] == '#' || (rr == s->blue_r && cc == s->blue_c)) break;
		if (map[rr][cc] == 'O')
		{
			s->red_r = -1; s->red_c = -1;
			return 1;
		}
		r = rr; c = cc;
	}
	s->red_r = r; s->red_c = c;
	return 0;
}

//파란공을 기울인 방향으로 움직이게 하는 함수
int moveB(state *s)
{
	int d = s->dir;
	int r = s->blue_r, c = s->blue_c, rr, cc;
	while (map[r][c] != '#')
	{
		rr = r + dR[d]; cc = c + dC[d];
		if (map[rr][cc] == '#' || (rr == s->red_r && cc == s->red_c)) break;
		if (map[rr][cc] == 'O')
		{
			s->blue_r = -1; s->blue_c = -1;
			return 1;
		}
		r = rr; c = cc;
	}
	s->blue_r = r; s->blue_c = c;
	return 0;
}

//기울이기 방법들을 정하는 bfs
int bfs(int r_r, int r_c, int b_r, int b_c)
{
	int f = -1, r = -1; //큐 인덱스
	for (int i = 0; i < 4; i++) //제일 처음 4방향에 대해 다 큐에 넣기
	{
		state s;
		s.red_r = r_r; s.red_c = r_c;
		s.blue_r = b_r; s.blue_c = b_c;
		s.time = 1; s.dir = i;
		que[++r] = s;
		//que.push(s);
	}
	int r_flag=0, b_flag = 0; //빨간공, 파란공이 구멍에 들어가는지 나타내는 flag
	//while (!que.empty())
	while(f!=r)	//큐가 다 빌때까지
	{
		r_flag = 0; b_flag = 0;
		//state s = que.front(); que.pop();
		state s = que[++f];
		switch (s.dir) //판을 기울이는 방향과 공 위치에 따라 어느 공을 먼저 움직일지 정함
		{
		case 0: if (s.red_r < s.blue_r) { r_flag = moveR(&s); b_flag = moveB(&s); }
			  else { b_flag = moveB(&s); r_flag = moveR(&s); }break;
		case 1: if (s.red_c > s.blue_c) { r_flag = moveR(&s); b_flag = moveB(&s); }
			  else { b_flag = moveB(&s); r_flag = moveR(&s); }break;
		case 2: if (s.red_r > s.blue_r) { r_flag = moveR(&s); b_flag = moveB(&s); }
			  else { b_flag = moveB(&s); r_flag = moveR(&s); }break;
		case 3: if (s.red_c < s.blue_c) { r_flag = moveR(&s); b_flag = moveB(&s); }
			  else { b_flag = moveB(&s); r_flag = moveR(&s); }break;
		}
		if (r_flag && !b_flag) //빨간 공만 들어갔을 때
		{
			return s.time; //횟수 반환
		}
		//어떤 공도 들어가지 않았고 10번 미만인 상태만 다시 4방향에 대해 조사
		if (s.time < 10 && !r_flag&&!b_flag)
		{
			for (int i = 0; i < 4; i++)
			{
				state next_s;
				next_s.red_r = s.red_r; next_s.red_c = s.red_c;
				next_s.blue_r = s.blue_r; next_s.blue_c = s.blue_c;
				next_s.dir = i; next_s.time = s.time + 1;
				//que.push(next_s);
				que[++r] = next_s;
			}
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d", &N, &M);
	int r_r=0, r_c=0, b_r=0, b_c=0;	//빨간 공 행, 열, 파란공 행, 열
	for(int i=0; i<N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'R') { r_r = i; r_c = j; }
			else if(map[i][j] == 'B') { b_r = i; b_c = j; }
			//else if (map[i][j] == 'O') { o_r = i; o_c = j; }
		}
	int result = bfs(r_r, r_c, b_r, b_c);
	printf("%d", result);
}
