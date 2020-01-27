package p17825;

import java.util.*;
public class Main {

	static int[][] map = {{0, 2, 4, 6, 8},
						{12, 14, 16, 18, 20},
						{22, 24, 26, 28, 30},
						{32, 34, 36, 38},
						{10, 13, 16, 19},
						{20, 22, 24},
						{30, 28, 27, 26},
						{25, 30, 35, 40},
						{0}
						};
	static int[][] horsePos = new int[4][2];
	static int[] dices;
	static int[] currPos = new int[2];
	static int resultMax=0;
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		dices = new int[10];
		for(int i=0; i<10; i++)
			dices[i] = in.nextInt();
		dfs(10, 0, 0);
		System.out.println(resultMax);
		in.close();
	}
	
	public static void dfs(int K, int k, int sum)
	{
		if(K==k)
		{
			if(sum>resultMax)
			{
				resultMax = sum;				
			}
		}
		else
		{
			boolean flag = true;
			for(int i=0; i<4; i++)
			{
				currPos[0]=horsePos[i][0];
				currPos[1]=horsePos[i][1];
				movePos(i, dices[k]);
				if(canMove(i))
				{
					flag = false;
					int prevR = horsePos[i][0];
					int prevC = horsePos[i][1];
					horsePos[i][0] = currPos[0]<8 ? currPos[0] : 9;
					horsePos[i][1] = currPos[1];
					
					dfs(K, k+1, calcul(sum));
					
					horsePos[i][0] = prevR;
					horsePos[i][1] = prevC;
				}
			}
			if(flag)
				dfs(K, K, sum);
		}
	}
	
	public static void movePos(int horse, int dice)
	{
		int r = currPos[0];
		int c = currPos[1]+dice;
		if(r>7)
			return;
		if(c>=map[r].length-1)
		{
			if(r==0)
			{
				if(c>map[r].length)
				{
					r++; c-=6;
				}
				else if(c==map[r].length)
				{
					r=4;c=0;
				}
					
			}
			else if(r==1||r==2)
			{
				if(c>map[r].length-1)
				{
					r++; c-=5;
				}
				else
				{
					r+=4;c=0;
				}
			}
			else if(r==3&&c==4)
			{
				r=7;c=3;
			}
			else if(r==4||r==5||r==6)
			{
				if(c>=map[r].length)
				{
					c-=map[r].length;r=7;
				}
			}
		}
		if((r==3&&c>4)||(r==7&&c>3))
		{
			r=8;c=0;
		}
		currPos[0] = r;
		currPos[1] = c;
	}
	
	public static int calcul(int sum)
	{
		return sum+map[currPos[0]][currPos[1]];
	}
	
	public static boolean canMove(int now)
	{
		if(currPos[0]>8)
			return false;
		for(int i=0; i<4; i++)
			if(now!=i&&currPos[0]==horsePos[i][0]&&currPos[1]==horsePos[i][1])
				return false;
		return true;
	}

}
