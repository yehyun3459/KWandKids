#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> tree; //자식 노드 참조
vector<vector<int>> ptree; //부모 노드 참조

int main()
{

	int N, M;
	cin >> N >> M;
	tree.resize(N + 1); //자식 노드 참조
	ptree.resize(N + 1); //부모 노드 참조

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		ptree[b].push_back(a);
	}

	int ans = 0;
	for (int i = 1; i <= N; i++)
	{
		//자식 구하기(BFS)
		queue<int> cSet;
		cSet.push(i);
		int cnt = 0;
		vector<int> visited(N + 1, 0);
		while (!cSet.empty())
		{
			int cInd = cSet.front();
			cSet.pop();
			for (unsigned int t = 0; t < tree[cInd].size(); t++)
			{
				if (visited[tree[cInd][t]])continue;
				visited[tree[cInd][t]] = 1;
				cnt++;
				cSet.push(tree[cInd][t]);//자식 저장
			}
		}

		//부모 구하기(BFS)
		visited.clear();
		visited.resize(N + 1, 0);
		cSet.push(i);
		int pcnt = 0;
		while (!cSet.empty())
		{
			int cInd = cSet.front();
			cSet.pop();
			for (unsigned int t = 0; t < ptree[cInd].size(); t++)
			{
				if (visited[ptree[cInd][t]])continue;
				visited[ptree[cInd][t]] = 1;
				pcnt++;
				cSet.push(ptree[cInd][t]);//부모 저장
			}
		}
		if ((cnt + pcnt) == N - 1)ans++;
	}
	cout << ans << "\n";
	return 0;
}
