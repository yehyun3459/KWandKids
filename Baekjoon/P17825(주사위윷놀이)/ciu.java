import java.util.*;
public class Main {

	//맵 설정, 각 점수 입력.
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
	static int[][] horsePos = new int[4][2]; //각 말의 위치
	static int[] dices; // 주사위에서 나올 수 10개
	static int[] currPos = new int[2]; // 주사위에 따른 현재 말의 다음 위치
	static int resultMax=0; //최댓값
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		dices = new int[10]; //주사위 나올 수 10개 0으로 초기화
		for(int i=0; i<10; i++) //주사위 나올 수 10개 입력
			dices[i] = in.nextInt(); 
		dfs(10, 0, 0); //dfs를 통한 완전 탐색 시작
		System.out.println(resultMax);
		in.close();
	}
	
	//깊이 우선 탐색을 통한 완전 탐색
	public static void dfs(int K, int k, int sum)
	{
		if(K==k)
		{
			if(sum>resultMax) //최종 점수가 최댓값보다 크면 최댓값 갱신
			{
				resultMax = sum;				
			}
		}
		else
		{
			boolean flag = true; //혹시나 어떤 말도 움직이지 못하는 상황을 위한 flag
			for(int i=0; i<4; i++)
			{
				currPos[0]=horsePos[i][0]; //현재 말의 row 위치 저장
				currPos[1]=horsePos[i][1]; //현재 말의 column 위치 저장
				movePos(i, dices[k]); //다음 위치 예측
				if(canMove(i)) //움직일 수 있는 경우 해당 말에 대해 탐색 진행 할 수 있도록 함 
				{
					flag = false; //어떤 말이라도 하나는 움직였음음을 의미
					int prevR = horsePos[i][0]; //dfs 빠져 나올 것을 위해 위치 기억
					int prevC = horsePos[i][1];
					horsePos[i][0] = currPos[0]<8 ? currPos[0] : 9; //도착한 경우 더이상 움직이지 않도록 row를 9로 설정
					horsePos[i][1] = currPos[1]; //현재 말의 column 위치 설정
					
					dfs(K, k+1, calcul(sum)); //다음 주사위 눈에 대해 탐색
					
					horsePos[i][0] = prevR; //dfs 빠져 나온 후 이전 위치로 되돌림
					horsePos[i][1] = prevC;
				}
			}
			if(flag) //어떤 말도 움직이지 못하면 바로 max 값과 비교하도록 함
				dfs(K, K, sum);
		}
	}
	
	//주사위의 눈에 따라 현재 말의 다음 row, column 값 계산
	public static void movePos(int horse, int dice)
	{
		int r = currPos[0];
		int c = currPos[1]+dice; //이전 위치에서 주사위 눈 만큼 더 감
		if(r>7) //도착에 도달한 경우 말 이동하지 않음
			return;
		if(c>=map[r].length-1) //각 배열의 끝에 도달하거나 넘어 갔을 때
		{
			if(r==0) //시작하는 길인 경우
			{
				if(c>map[r].length) //파란원에 서지 못하면 다음 배열로 넘어감
				{
					r++; c-=6;
				}
				else if(c==map[r].length) //파란원에 서면 지름길로 감
				{
					r=4;c=0;
				}
					
			}
			else if(r==1||r==2) //밖을 돌아가는 길인 경우
			{
				if(c>map[r].length-1) //파란칸에 서지 못하면 다음 길로 감
				{
					r++; c-=5;
				}
				else //파란칸에 서면 각각의 지름길로 들어감
				{
					r+=4;c=0;
				}
			}
			else if(r==3&&c==4)
			/* 도착 전의 바깥길에서 40점 칸에 도착했을 시 지름길의 40점에 해당하는 배열로 가게 함
			 * 이를 통해 마지막 40점 칸에서 말이 겹치지 않도록 함
			 */
			{
				r=7;c=3;
			}
			else if(r==4||r==5||r==6) //안쪽 지름길인 경우
			{
				if(c>=map[r].length) //25점 칸 이상 가게 되면 도착 전의 지름길로 이동.
				{
					c-=map[r].length;r=7;
				}
			}
		}
		if((r==3&&c>4)||(r==7&&c>3)) //도착 전의 바깥길이나 도착 전의 지름길에서 도착하게 되면 도착 칸으로 위치 설정
		{
			r=8;c=0;
		}
		currPos[0] = r; //실제로 현재 말의 다음 row 위치를 설정함
		currPos[1] = c; //실제로 현재 말의 다음 column 위치를 설정함
	}
	
	public static int calcul(int sum) // 위치 이동 후 점수 가산
	{
		return sum+map[currPos[0]][currPos[1]];
	}
	
	//예측된 현재 말의 다음 위치로 이동 할 수 있는지 확인
	public static boolean canMove(int now) 
	{
		if(currPos[0]>8) 
			//이미 도착해 있는 경우 false 반환하여 더 탐색 못하게 함(도착점에 지금 도달한 경우 8, 이미 도착해 있는 경우 9)
			return false;
		for(int i=0; i<4; i++) //다른 말들과 비교하여 말이 겹치는지 확인
			if(now!=i&&currPos[0]==horsePos[i][0]&&currPos[1]==horsePos[i][1])
				return false;
		return true;
	}

}
