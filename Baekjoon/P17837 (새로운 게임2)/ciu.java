package p17837;

import java.util.*;
public class Main {

	static int N;
	static int K;
	static int[][] colorMap;
	static int[][][] map;
	static Horse[] horses;
	static int[] dr = {0, 0, -1, 1};
	static int[] dc = {1, -1, 0, 0};
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		N = in.nextInt();
		K = in.nextInt();
		colorMap = new int[N][N];
		map = new int[N][N][K];
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				for(int k=0; k<K; k++)
					map[i][j][k]=-1;
		horses = new Horse[K];
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				colorMap[i][j] = in.nextInt();
		int r,c,d;
		for(int i=0; i<K; i++)
		{	
			r=in.nextInt()-1;
			c=in.nextInt()-1;
			d=in.nextInt()-1;
			map[r][c][0]=i;
			horses[i] = new Horse(r, c, d);
		}
		int turn = game();
		turn = turn>1000 ? -1 : turn;
		System.out.println(turn);
		in.close();
	}
	public static int game() {
		int t = 1;
		int nextR, nextC;
		boolean flag=false;
		while(t<=1000)
		{
			for(int i=0; i<K; i++)
			{
				nextR = horses[i].r+dr[horses[i].dir];
				nextC = horses[i].c+dc[horses[i].dir];
				if(!((0<=nextR&&nextR<N)&&(0<=nextC&&nextC<N))||colorMap[nextR][nextC]==2)
				{
					if(blue(horses[i], i, nextR, nextC))
					{
						flag = true; break;
					}
				}
				else if(colorMap[nextR][nextC]==0)
				{
					if(white(horses[i], i, nextR, nextC))
					{
						flag=true;break;
					}
				}
				else
				{
					if(red(horses[i], i, nextR, nextC))
					{
						flag=true;break;
					}
				}
			}
			if(flag)
				break;
			t++;
		}
		return t;
	}
	
	public static boolean white(Horse h, int i, int nR, int nC) {
		int prevStartIdx = searchIdx(h.r, h.c, i);
		int startIdx = searchIdx(nR, nC, -1);
		return push(prevStartIdx, h.r, h.c, startIdx, nR, nC);
	}
	public static boolean red(Horse h, int i, int nR, int nC) {
		int prevStartIdx = searchIdx(h.r, h.c, i);
		int startIdx = searchIdx(nR, nC, -1);
		return pushRev(prevStartIdx, h.r, h.c, startIdx, nR, nC);
	}
	public static boolean blue(Horse h, int i, int nR, int nC) {
		switch(h.dir) {
			case 0: h.dir = 1; break;
			case 1: h.dir = 0; break;
			case 2: h.dir = 3; break;
			case 3: h.dir = 2; break;
		}
		nR = h.r+dr[h.dir];
		nC = h.c+dc[h.dir];
		if((0<=nR&&nR<N)&&(0<=nC&&nC<N))
		{
			if(colorMap[nR][nC]==0)
				return white(h,i, nR, nC);
			else if(colorMap[nR][nC]==1)
				return red(h,i, nR, nC);
		}
		return false;
	}
	
	public static int searchIdx(int r, int c, int x) {
		for(int i=0; i<K; i++)
		{
			if(map[r][c][i]==x)
				return i;
			else if(map[r][c][i]==-1)
				break;
		}		
		return 0;
	}
	
	public static boolean push(int currIdx, int cR, int cC,
			int nextIdx, int nR, int nC) {
		int lastIdx = currIdx;
		for(; lastIdx<K; lastIdx++)
		{
			if(map[cR][cC][lastIdx]==-1)
				break;
		}
		lastIdx = lastIdx>0 ? lastIdx-1: lastIdx;
		int i=0, j=0;
		for(i=nextIdx,j=currIdx; j<=lastIdx; i++,j++)
		{
			if(i==3)
				return true;
			map[nR][nC][i] = map[cR][cC][j];
			horses[map[cR][cC][j]].r = nR;
			horses[map[cR][cC][j]].c = nC;
			map[cR][cC][j]=-1;
		}
		map[nR][nC][i]=-1;
		return false;
	}
	
	public static boolean pushRev(int currIdx, int cR, int cC,
			int nextIdx, int nR, int nC) {
		int lastIdx = currIdx;
		for(; lastIdx<K; lastIdx++)
		{
			if(map[cR][cC][lastIdx]==-1)
				break;
		}
		lastIdx = lastIdx>0 ? lastIdx-1: lastIdx;
		int i=0, j=0;
		for(i=nextIdx, j=lastIdx; j>=currIdx; i++,j--)
		{
			if(i==3)
				return true;
			map[nR][nC][i] = map[cR][cC][j];
			horses[map[cR][cC][j]].r = nR;
			horses[map[cR][cC][j]].c = nC;
			map[cR][cC][j]=-1;
		}
		map[nR][nC][i]=-1;
		return false;
	}
	
	static class Horse{
		int r;
		int c;
		int dir;
		public Horse(int r, int c, int dir)
		{
			this.r = r;
			this.c = c;
			this.dir = dir;
		}
		public String toString()
		{
			return "r "+r+" c "+c+" d "+dir;
		}
	}

}
