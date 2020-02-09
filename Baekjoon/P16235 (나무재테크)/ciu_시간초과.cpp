#include <iostream>
#include <list>
//Baekjoon 16235
using namespace std;

int N, M, K;
int map[10][10];
int arr_a[10][10];
int dR[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dC[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };


struct tree {
	int r;
	int c;
	int age;
	int dead;
};

struct cmp {
	bool operator()(tree t, tree u) {
		return t.age > u.age;
	}
};

list<tree> v;

int isMap(int r, int c)
{
	return 0 <= r && r < N && 0 <= c && c < N;
}

void print_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
}

void spring()
{
	list<tree>::reverse_iterator iter = v.rbegin();
	while (iter != v.rend())
	{
		if (map[(*iter).r][(*iter).c] >= (*iter).age)
		{
			map[(*iter).r][(*iter).c] -= (*iter).age;
			(*iter).age++;
			//printf("r: %d c: %d, age: %d\n", v[i].r, v[i].c, v[i].age);
			//print_map();
		}
		else
			(*iter).dead = 1;
		iter++;
	}
}

void summer()
{
	//printf("start dead\n");
	list<tree>::iterator iter = v.begin();
	while (iter != v.end())
	{
		if ((*iter).dead)
		{
			map[(*iter).r][(*iter).c] += (*iter).age / 2;
			iter = v.erase(iter);
			M--;
			//printf("r: %d c: %d, age: %d\n", (*iter).r, (*iter).c, (*iter).age);
		}
		else
			iter++;
	}
	//printf("end dead\n");
}

void fall()
{
	list<tree>::iterator iter = v.begin();
	int rr, cc;
	int limit = M;
	for (int i = 0; i < limit; i++)
	{
		if ((*iter).age % 5 == 0)
		{
			for (int j = 0; j < 8; j++)
			{
				rr = (*iter).r + dR[j]; cc = (*iter).c + dC[j];
				if (isMap(rr, cc))
				{
					struct tree u;
					u.r = rr;
					u.c = cc;
					u.age = 1;
					u.dead = 0;
					v.push_back(u);
					M++;
				}
			}
		}
		iter++;
	}
}

void winter()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] += arr_a[i][j];
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &arr_a[i][j]);
			map[i][j] = 5;
		}

	for (int i = 0; i < M; i++)
	{
		struct tree t;
		scanf("%d", &t.r);
		scanf("%d", &t.c);
		t.r--;
		t.c--;
		scanf("%d", &t.age);
		t.dead = 0;
		v.push_back(t);
	}

	for (int i = 0; i < K; i++)
	{
		//printf("%d ==========================\n", i);
		spring();
		summer();
		fall();
		//print_map();
		winter();
		//print_map();
		//printf("============================\n");
	}

	cout << M;
}
