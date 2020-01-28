import java.util.*;
public class Main {

	static int[][] circles; //원판
	static int[] startIdx; //원판의 각 시작 인덱스
	static int N, M; //원판 수, 각 원판의 숫자 개수
	static int[] dr = {0, 1, 0, -1}; //인접 탐색 시 사용할 방향(위, 아래)
	static int[] dc = {1, 0, -1, 0}; //인접 탐색 시 사용할 방향(좌, 우)
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		N = in.nextInt();
		M = in.nextInt();
		int T = in.nextInt();	//원판 회전 수 입력
		circles = new int[N][M];
		startIdx = new int[N];
		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				circles[i][j] = in.nextInt();
		int x,d,k;	//회전할 원판(x의 배수에 해당하는 원판 회전), 회전 방향, 회전 수 
		for(int i=0; i<T; i++)
		{
			Queue<Pos> queue = new LinkedList<>(); //탐색을 위한 큐
			x=in.nextInt();
			d = in.nextInt();
			k = in.nextInt();
			rotate(x, d, k);	//원판들 회전
			boolean flag = false; //회전 이후 인접 탐색 시 지워지는 게 없는 경우를 위한  flag
			for(int n=0; n<N; n++)
				for(int m=0; m<M; m++)
				{
					queue = new LinkedList<>();
					queue.add(new Pos(n, m));	//원판의 원소 하나를 큐에 추가
					if(bfs(queue, circles[n][m])) //원판들의 각 원소마다 인접 탐색
						flag = true;			  //지워진 게 하나라도 있으면 true
				}
			if(!flag)	//지워진게 없으면 평균 계산하여 조정
				meanCalc();
		}
		int sum=0;
		//마지막으로 총합 구하기
		for(int n=0; n<N; n++)
			for(int m=0; m<M; m++)
			{
				if(circles[n][m]>0)
					sum+=circles[n][m];
			}
		System.out.println(sum);
		in.close();
	}
	
	public static void rotate(int x, int d, int k) {
		k%=M;	//회전 수를 모듈러 연산하여 원판의 길이(M)을 못 넘게 만듦
		int dir = d==0 ? -1*k : 1*k; //회전 방향에 따라 -를 할 지 +할 지 정함 
		for(int i=1; i*x-1<N; i++) //x의 배수에 해당하는 원판에 대해 시작 인덱스 조정
		{
			//해당 시작 인덱스에 회전수를 더해주되 음수가 될 수 있으므로 길이(M)을 더해줌(양수였어도 결과는 2*M-1 이하가 됨)
			//음수였던 경우 M을 더해준 것만으로도 원하는 시작 인덱스로 됨
			//양수였던 경우 M을 더해줬으므로 %M을 하게 되면 원하는 시작 인덱스로 됨
			startIdx[(i*x)-1] = (startIdx[(i*x)-1]+dir+M)%M; 
		}
	}
	
	public static boolean bfs(Queue<Pos> queue, int ori) {
		boolean flag = false;	//한 번이라도 인접한 수가 있어 삭제한 것이 있는지 확인하는 flag
		
		/*
		 *현재 행, 현재 열, 다음행, 다음열(추상), 실제 다음열.
		 *nextC의 경우 회전된 배열들에 대해 해당 원판 기준으로 위, 아래 원판의 열을 의미
		 *r=0, c=0일 때 nextR=1, nextC=0이면 아래 행, 같은 열을 의미 함
		 *그러나 실제 바로 위나 아래의 원판의 시작 인덱스가 해당 원판의 시작 인덱스와는 다름
		 *따라서 현재 원판의 시작인덱스가 1, 아래 행에 해당하는 원판(바깥쪽 원판)의 시작인덱스가 M-1인 경우
		 *다음 원판의 열은 0이 아니라 M-3이 됨(M>2일 때).
		 *따라서 실제로 배열의 인덱스로 활용할 realC를 만듦.
		*/
		int r, c, nextR, nextC, realC;  
		Pos pos; //r,c를 담을 Pos 객체
		if(ori<0) //해당 위치의 원소의 값이 0이하면 이미 삭제된 곳이므로 false를 반환하며 종료.
			return flag;
		while(!queue.isEmpty()) //큐가 전부 비워질 때 까지(인접 원소 없을때 까지)
		{
			pos = queue.poll();
			r = pos.r;
			c = pos.c;
			for(int i=0; i<dr.length; i++) //상,하,좌,우에 대해 탐색
			{
				nextR = r+dr[i]; 
				nextC = c+dc[i];
				if(0<=nextR&&nextR<N) //원판의 범위 안에 해당 될 때(0이하 원판이나 M넘는 원판은 없으므로)
				{
					/*다음 행의 열 인덱스를 구할 때 
					 *현재 원판의 시작 인덱스만큼 빼줘서 원래 배열(회전되지 않은 원판)이었을 때의 열을 구하고
					 *다음 원판의 시작 인덱스만큼 더해줘서 다음 원판에 맞는 열 인덱스를 구하되
					 *음수 일 수 있으므로 M을 더해주고 M보다 큰 수가 될 경우를 위해 %M을 해줌
					 */
					realC = (nextC-startIdx[r]+startIdx[nextR]+M)%M;
					
					//결과로 나온 (다음 행, 실제 다음 열)의 숫자가 현재 수와 같으면 탐색 진행 
					if(circles[nextR][realC]==ori)
					{
						circles[r][c]=-1;	//현재 수 삭제
						circles[nextR][realC] = -1; //(다음 행, 실제 다음 열)의 수 삭제
						queue.add(new Pos(nextR, realC)); //큐에 추가 하여 다음 탐색 진행
						flag = true; //삭제 한 적이 있음을 표시하기 위한 flag
					}
				}
			}
		}
		return flag;
	}
	
	//평균을 구한 뒤 평균 보다 작은 수들은 +1 평균 보다 큰 수들은 -1
	public static void meanCalc() {
		int sum = 0, count=0;;
		for(int n=0; n<N; n++)
			for(int m=0; m<M; m++)
			{
				if(circles[n][m]>0)
				{
					sum+=circles[n][m];
					count++;
				}
			}
		
		double mean = (double)sum/(double)count;
		
		int num=0;
		for(int n=0; n<N; n++)
			for(int m=0; m<M; m++)
			{
				num = circles[n][m];
				if(num>0)
				{
					if(num>mean)
						circles[n][m]--;
					else if(num<mean)
						circles[n][m]++;
				}
			}
	}
	
	static class Pos{ //행, 열의 인덱스를 담을 객체
		int r;
		int c;
		public Pos(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
}