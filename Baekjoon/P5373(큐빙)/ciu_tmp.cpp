#include <iostream>

using namespace std;

int T;
int ROT;
int circle[8][2] = { {0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0} };
int U[4][3][3] = { {{4, 0, 0}, {4, 0, 1}, {4, 0, 2}},
					{{3, 0, 0}, {3, 0, 1}, {3, 0, 2}},
					{{5, 0, 0}, {5, 0, 1}, {5, 0, 2}},
					{{1, 0, 0}, {1, 0, 1}, {1, 0, 2}} };
int D[4][3][3] = { {{4, 2, 0}, {4, 2, 1}, {4, 2, 2}},
					{{1, 2, 0}, {1, 2, 1}, {1, 2, 2}},
					{{5, 2, 0}, {5, 2, 1}, {5, 2, 2}},
					{{3, 2, 0}, {3, 2, 1}, {3, 2, 2}} };
int F[4][3][3] = { {{0, 2, 0}, {0, 2, 1}, {0, 2, 2}},
					{{5, 0, 0}, {5, 1, 0}, {5, 2, 0}},
					{{2, 2, 0}, {2, 2, 1}, {2, 2, 2}},
					{{4, 0, 2}, {4, 1, 2}, {4, 2, 2}} };
int B[4][3][3] = { {{0, 2, 0}, {0, 2, 1}, {0, 2, 2}},
					{{4, 0, 0}, {4, 1, 0}, {4, 2, 0}},
					{{2, 2, 0}, {2, 2, 1}, {2, 2, 2}},
					{{5, 0, 2}, {5, 1, 2}, {5, 2, 2}} };
int L[4][3][3] = { {{0, 0, 0}, {0, 1, 0}, {0, 2, 0}},
					{{1, 0, 0}, {1, 1, 0}, {1, 2, 0}},
					{{2, 0, 0}, {2, 1, 0}, {2, 2, 0}},
					{{3, 0, 0}, {3, 1, 0}, {3, 2, 0}} };
int R[4][3][3] = { {{0, 0, 0}, {0, 1, 0}, {0, 2, 0}},
					{{3, 0, 0}, {3, 1, 0}, {3, 2, 0}},
					{{2, 0, 0}, {2, 1, 0}, {2, 2, 0}},
					{{1, 0, 0}, {1, 1, 0}, {1, 2, 0}} };
char cube[6][3][3];
char tmp[3];

int isMap(int r, int c)
{
	return 0 <= r && r < 3 && 0 <= c && c < 3;
}

void rotate(char plat, char dir)
{
	if (dir == '+')
	{
		if (plat == 'U')
		{
			tmp[0] = cube[U[3][0][0]][U[3][0][1]][U[3][0][2]];
			tmp[1] = cube[U[3][1][0]][U[3][1][1]][U[3][1][2]];
			tmp[2] = cube[U[3][2][0]][U[3][2][1]][U[3][2][2]];
			for (int i = 3; i > 0; i--)
				for (int j = 0; j < 3; j++)
					cube[U[i][j][0]][U[i][j][1]][U[i][j][2]] = cube[U[i - 1][j][0]][U[i - 1][j][1]][U[i - 1][j][2]];
			cube[U[0][0][0]][U[0][0][1]][U[0][0][2]] = tmp[0];
			cube[U[0][1][0]][U[0][1][1]][U[0][1][2]] = tmp[1];
			cube[U[0][2][0]][U[0][2][1]][U[0][2][2]] = tmp[2];
			int p = 0; tmp[0] = cube[p][circle[8][0]][circle[8][1]]; tmp[1] = cube[p][circle[7][0]][circle[7][1]];
			for (int i = 8; i > 1; i--)
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i - 2][0]][circle[i - 2][1]];
			cube[p][circle[0][0]][circle[0][1]] = tmp[1];
			cube[p][circle[1][0]][circle[1][1]] = tmp[0];

		}
		else if (plat == 'D')
		{
			tmp[0] = cube[D[3][0][0]][D[3][0][1]][D[3][0][2]];
			tmp[1] = cube[D[3][1][0]][D[3][1][1]][D[3][1][2]];
			tmp[2] = cube[D[3][2][0]][D[3][2][1]][D[3][2][2]];
			for (int i = 3; i > 0; i--)
				for (int j = 0; j < 3; j++)
					cube[D[i][j][0]][D[i][j][1]][D[i][j][2]] = cube[D[i - 1][j][0]][D[i - 1][j][1]][D[i - 1][j][2]];
			cube[D[0][0][0]][D[0][0][1]][D[0][0][2]] = tmp[0];
			cube[D[0][1][0]][D[0][1][1]][D[0][1][2]] = tmp[1];
			cube[D[0][2][0]][D[0][2][1]][D[0][2][2]] = tmp[2];
			int p = 2; tmp[0] = cube[p][circle[8][0]][circle[8][1]]; tmp[1] = cube[p][circle[7][0]][circle[7][1]];
			for (int i = 8; i > 1; i--)
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i - 2][0]][circle[i - 2][1]];
			cube[p][circle[0][0]][circle[0][1]] = tmp[1];
			cube[p][circle[1][0]][circle[1][1]] = tmp[0];
		}
		else if (plat == 'F')
		{
			tmp[0] = cube[F[3][0][0]][F[3][0][1]][F[3][0][2]];
			tmp[1] = cube[F[3][1][0]][F[3][1][1]][F[3][1][2]];
			tmp[2] = cube[F[3][2][0]][F[3][2][1]][F[3][2][2]];
			for (int i = 3; i > 0; i--)
				for (int j = 0; j < 3; j++)
					cube[F[i][j][0]][F[i][j][1]][F[i][j][2]] = cube[F[i - 1][j][0]][F[i - 1][j][1]][F[i - 1][j][2]];
			cube[F[0][0][0]][F[0][0][1]][F[0][0][2]] = tmp[0];
			cube[F[0][1][0]][F[0][1][1]][F[0][1][2]] = tmp[1];
			cube[F[0][2][0]][F[0][2][1]][F[0][2][2]] = tmp[2];
			int p = 1; tmp[0] = cube[p][circle[8][0]][circle[8][1]]; tmp[1] = cube[p][circle[7][0]][circle[7][1]];
			for (int i = 8; i > 1; i--)
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i - 2][0]][circle[i - 2][1]];
			cube[p][circle[0][0]][circle[0][1]] = tmp[1];
			cube[p][circle[1][0]][circle[1][1]] = tmp[0];
		}
		else if (plat == 'B')
		{
			tmp[0] = cube[B[3][0][0]][B[3][0][1]][B[3][0][2]];
			tmp[1] = cube[B[3][1][0]][B[3][1][1]][B[3][1][2]];
			tmp[2] = cube[B[3][2][0]][B[3][2][1]][B[3][2][2]];
			for (int i = 3; i > 0; i--)
				for (int j = 0; j < 3; j++)
					cube[B[i][j][0]][B[i][j][1]][B[i][j][2]] = cube[B[i - 1][j][0]][B[i - 1][j][1]][B[i - 1][j][2]];
			cube[B[0][0][0]][B[0][0][1]][B[0][0][2]] = tmp[0];
			cube[B[0][1][0]][B[0][1][1]][B[0][1][2]] = tmp[1];
			cube[B[0][2][0]][B[0][2][1]][B[0][2][2]] = tmp[2];
			int p = 3; tmp[0] = cube[p][circle[8][0]][circle[8][1]]; tmp[1] = cube[p][circle[7][0]][circle[7][1]];
			for (int i = 8; i > 1; i--)
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i - 2][0]][circle[i - 2][1]];
			cube[p][circle[0][0]][circle[0][1]] = tmp[1];
			cube[p][circle[1][0]][circle[1][1]] = tmp[0];
		}
		else if (plat == 'L')
		{
			tmp[0] = cube[L[3][0][0]][L[3][0][1]][L[3][0][2]];
			tmp[1] = cube[L[3][1][0]][L[3][1][1]][L[3][1][2]];
			tmp[2] = cube[L[3][2][0]][L[3][2][1]][L[3][2][2]];
			for (int i = 3; i > 0; i--)
				for (int j = 0; j < 3; j++)
					cube[L[i][j][0]][L[i][j][1]][L[i][j][2]] = cube[L[i - 1][j][0]][L[i - 1][j][1]][L[i - 1][j][2]];
			cube[L[0][0][0]][L[0][0][1]][L[0][0][2]] = tmp[0];
			cube[L[0][1][0]][L[0][1][1]][L[0][1][2]] = tmp[1];
			cube[L[0][2][0]][L[0][2][1]][L[0][2][2]] = tmp[2];
			int p = 4; tmp[0] = cube[p][circle[8][0]][circle[8][1]]; tmp[1] = cube[p][circle[7][0]][circle[7][1]];
			for (int i = 8; i > 1; i--)
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i - 2][0]][circle[i - 2][1]];
			cube[p][circle[0][0]][circle[0][1]] = tmp[1];
			cube[p][circle[1][0]][circle[1][1]] = tmp[0];
		}
		else if (plat == 'R')
		{
			tmp[0] = cube[R[3][0][0]][R[3][0][1]][R[3][0][2]];
			tmp[1] = cube[R[3][1][0]][R[3][1][1]][R[3][1][2]];
			tmp[2] = cube[R[3][2][0]][R[3][2][1]][R[3][2][2]];
			for (int i = 3; i > 0; i--)
				for (int j = 0; j < 3; j++)
					cube[R[i][j][0]][R[i][j][1]][R[i][j][2]] = cube[R[i - 1][j][0]][R[i - 1][j][1]][R[i - 1][j][2]];
			cube[R[0][0][0]][R[0][0][1]][R[0][0][2]] = tmp[0];
			cube[R[0][1][0]][R[0][1][1]][R[0][1][2]] = tmp[1];
			cube[R[0][2][0]][R[0][2][1]][R[0][2][2]] = tmp[2];
			int p = 5; tmp[0] = cube[p][circle[8][0]][circle[8][1]]; tmp[1] = cube[p][circle[7][0]][circle[7][1]];
			for (int i = 8; i > 1; i--)
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i - 2][0]][circle[i - 2][1]];
			cube[p][circle[0][0]][circle[0][1]] = tmp[1];
			cube[p][circle[1][0]][circle[1][1]] = tmp[0];
		}
	}
	else
	{
		if (plat == 'U')
		{
			tmp[0] = cube[U[0][0][0]][U[0][0][1]][U[0][0][2]];
			tmp[1] = cube[U[0][1][0]][U[0][1][1]][U[0][1][2]];
			tmp[2] = cube[U[0][2][0]][U[0][2][1]][U[0][2][2]];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[U[i][j][0]][U[i][j][1]][U[i][j][2]] = cube[U[i + 1][j][0]][U[i + 1][j][1]][U[i + 1][j][2]];
			cube[U[3][0][0]][U[3][0][1]][U[3][0][2]] = tmp[0];
			cube[U[3][1][0]][U[3][1][1]][U[3][1][2]] = tmp[1];
			cube[U[3][2][0]][U[3][2][1]][U[3][2][2]] = tmp[2];
			int p = 0; tmp[0] = cube[p][circle[0][0]][circle[0][1]]; tmp[1] = cube[p][circle[1][0]][circle[1][1]];
			for (int i = 0; i < 7; i++)
			{
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i + 2][0]][circle[i + 2][1]];
			}
			cube[p][circle[8][0]][circle[8][1]] = tmp[1];
			cube[p][circle[7][0]][circle[7][1]] = tmp[0];
		}
		else if (plat == 'D')
		{
			tmp[0] = cube[D[0][0][0]][D[0][0][1]][D[0][0][2]];
			tmp[1] = cube[D[0][1][0]][D[0][1][1]][D[0][1][2]];
			tmp[2] = cube[D[0][2][0]][D[0][2][1]][D[0][2][2]];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[D[i][j][0]][D[i][j][1]][D[i][j][2]] = cube[D[i + 1][j][0]][D[i + 1][j][1]][D[i + 1][j][2]];
			cube[D[3][0][0]][D[3][0][1]][D[3][0][2]] = tmp[0];
			cube[D[3][1][0]][D[3][1][1]][D[3][1][2]] = tmp[1];
			cube[D[3][2][0]][D[3][2][1]][D[3][2][2]] = tmp[2];
			int p = 2; tmp[0] = cube[p][circle[0][0]][circle[0][1]]; tmp[1] = cube[p][circle[1][0]][circle[1][1]];
			for (int i = 0; i < 7; i++)
			{
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i + 2][0]][circle[i + 2][1]];
			}
			cube[p][circle[8][0]][circle[8][1]] = tmp[1];
			cube[p][circle[7][0]][circle[7][1]] = tmp[0];
		}
		else if (plat == 'F')
		{
			tmp[0] = cube[F[0][0][0]][F[0][0][1]][F[0][0][2]];
			tmp[1] = cube[F[0][1][0]][F[0][1][1]][F[0][1][2]];
			tmp[2] = cube[F[0][2][0]][F[0][2][1]][F[0][2][2]];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[F[i][j][0]][F[i][j][1]][F[i][j][2]] = cube[F[i + 1][j][0]][F[i + 1][j][1]][F[i + 1][j][2]];
			cube[F[3][0][0]][F[3][0][1]][F[3][0][2]] = tmp[0];
			cube[F[3][1][0]][F[3][1][1]][F[3][1][2]] = tmp[1];
			cube[F[3][2][0]][F[3][2][1]][F[3][2][2]] = tmp[2];
			int p = 1; tmp[0] = cube[p][circle[0][0]][circle[0][1]]; tmp[1] = cube[p][circle[1][0]][circle[1][1]];
			for (int i = 0; i < 7; i++)
			{
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i + 2][0]][circle[i + 2][1]];
			}
			cube[p][circle[8][0]][circle[8][1]] = tmp[1];
			cube[p][circle[7][0]][circle[7][1]] = tmp[0];
		}
		else if (plat == 'B')
		{
			tmp[0] = cube[B[0][0][0]][B[0][0][1]][B[0][0][2]];
			tmp[1] = cube[B[0][1][0]][B[0][1][1]][B[0][1][2]];
			tmp[2] = cube[B[0][2][0]][B[0][2][1]][B[0][2][2]];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[B[i][j][0]][B[i][j][1]][B[i][j][2]] = cube[B[i + 1][j][0]][B[i + 1][j][1]][B[i + 1][j][2]];
			cube[B[3][0][0]][B[3][0][1]][B[3][0][2]] = tmp[0];
			cube[B[3][1][0]][B[3][1][1]][B[3][1][2]] = tmp[1];
			cube[B[3][2][0]][B[3][2][1]][B[3][2][2]] = tmp[2];
			int p = 3; tmp[0] = cube[p][circle[0][0]][circle[0][1]]; tmp[1] = cube[p][circle[1][0]][circle[1][1]];
			for (int i = 0; i < 7; i++)
			{
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i + 2][0]][circle[i + 2][1]];
			}
			cube[p][circle[8][0]][circle[8][1]] = tmp[1];
			cube[p][circle[7][0]][circle[7][1]] = tmp[0];
		}
		else if (plat == 'L')
		{
			tmp[0] = cube[L[0][0][0]][L[0][0][1]][L[0][0][2]];
			tmp[1] = cube[L[0][1][0]][L[0][1][1]][L[0][1][2]];
			tmp[2] = cube[L[0][2][0]][L[0][2][1]][L[0][2][2]];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[L[i][j][0]][L[i][j][1]][L[i][j][2]] = cube[L[i + 1][j][0]][L[i + 1][j][1]][L[i + 1][j][2]];
			cube[L[3][0][0]][L[3][0][1]][L[3][0][2]] = tmp[0];
			cube[L[3][1][0]][L[3][1][1]][L[3][1][2]] = tmp[1];
			cube[L[3][2][0]][L[3][2][1]][L[3][2][2]] = tmp[2];
			int p =4; tmp[0] = cube[p][circle[0][0]][circle[0][1]]; tmp[1] = cube[p][circle[1][0]][circle[1][1]];
			for (int i = 0; i < 7; i++)
			{
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i + 2][0]][circle[i + 2][1]];
			}
			cube[p][circle[8][0]][circle[8][1]] = tmp[1];
			cube[p][circle[7][0]][circle[7][1]] = tmp[0];
		}
		else if (plat == 'R')
		{
			tmp[0] = cube[R[0][0][0]][R[0][0][1]][R[0][0][2]];
			tmp[1] = cube[R[0][1][0]][R[0][1][1]][R[0][1][2]];
			tmp[2] = cube[R[0][2][0]][R[0][2][1]][R[0][2][2]];
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[R[i][j][0]][R[i][j][1]][R[i][j][2]] = cube[R[i + 1][j][0]][R[i + 1][j][1]][R[i + 1][j][2]];
			cube[R[3][0][0]][R[3][0][1]][R[3][0][2]] = tmp[0];
			cube[R[3][1][0]][R[3][1][1]][R[3][1][2]] = tmp[1];
			cube[R[3][2][0]][R[3][2][1]][R[3][2][2]] = tmp[2];
			int p = 5; tmp[0] = cube[p][circle[0][0]][circle[0][1]]; tmp[1] = cube[p][circle[1][0]][circle[1][1]];
			for (int i = 0; i < 7; i++)
			{
				cube[p][circle[i][0]][circle[i][1]] = cube[p][circle[i + 2][0]][circle[i + 2][1]];
			}
			cube[p][circle[8][0]][circle[8][1]] = tmp[1];
			cube[p][circle[7][0]][circle[7][1]] = tmp[0];
		}
	}
}

int main()
{

	scanf("%d", &T);
	for (int t_case = 0; t_case < T; t_case++)
	{
		for (int c = 0; c < 6; c++)
		{
			char color;
			switch (c)
			{
			case 0: color = 'w'; break;
			case 1: color = 'r'; break;
			case 2: color = 'y'; break;
			case 3: color = 'o'; break;
			case 4: color = 'g'; break;
			case 5: color = 'b'; break;
			}
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					cube[c][i][j] = color;
		}
		scanf("%d", &ROT);
		for (int rot_cnt = 0; rot_cnt < ROT; rot_cnt++)
		{
			char plat, direction;
			scanf(" %c", &plat);
			scanf(" %c", &direction);

			rotate(plat, direction);
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				printf("%c", cube[0][i][j]);
			printf("\n");
		}
	}
}
