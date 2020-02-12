#include <cstdio>
//Baejoon - 15684
//자바로 돌린것 보다 시간 느리게 나옴, 추후에 다시 볼 예정
int N, M, H; //세로선 수(열), 가로선 넣을 수 있는 수, 가로선 들어갈수 있는 수(행)
int ladder[30][9]; //사다리 가로선 맵(가로 선만 표현)
int done_flag=0; //탐색 됐음을 나타내는 flag

//사다리 타고 갔을 때 다 시작과 동일한 도착점인지 확인하는 함수
int isCorrect()
{
	int r, c;
	for (int i = 0; i < N; i++)
	{
		r = 0; c = i;
		while (r < H)
		{
			if (0 <= c - 1 && ladder[r][c - 1]) 
				c--;
			else if (c < N - 1 && ladder[r][c])
				c++;
			r++;
		}
		if (c != i)
			return 0;
	}
	return 1;
}

//가로선을 놓을 수 있는 공간을 1차원으로 생각해서 0~(N-1)*H 까지의 수 중에 n개를 뽑음
void dfs(int n, int k, int idx)
{
	//n개 다 뽑으면
	if (n == k)
	{
		if (isCorrect()) //가능한 사다리인지 확인
			done_flag = 1;
	}
	else
	{
		int r, c;
		int i = idx; //for문 while문으로 바꿔본 것
		while (i < (N - 1)*H)
		{
			r = i / (N - 1); c = i % (N - 1); //현재 1차원 인덱스인 i를 r과 c로 바꿈
			if (done_flag) //이미 끝났으면 그냥 return
				return;
			if (!ladder[r][c]&&!((c>0&&ladder[r][c-1])||(c+1<(N-1)&&ladder[r][c+1]))) //사다리 현재 인덱스와 좌,우에 기존에 놓인 가로선이 있는지 확인
			{
				ladder[r][c] = 1; //현재 인덱스에 가로선 놓기
				dfs(n, k + 1, i+1); //다음 뽑을 수 정하러 더 탐색
				ladder[r][c] = 0; //가로선 다시 회수
			}
			i++;
		}
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &H);
	int a, b;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &a, &b);
		ladder[a - 1][b - 1] = 1;
	}
	int result = 0;
	for (; result < 4; result++) //0~3까지 가로선 뽑을 수 정함
	{
		dfs(result, 0, 0);
		if (done_flag)
			break;
	}
	result = result == 4 ? -1 : result; //가로선이 4개 이상 필요한 경우 -1로 바꿈
	printf("%d", result);
	return 0;
}
