#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
int N, M, cnt, dp[501], dp_re[501], isvis[501], isvis_re[501];
vector<int> v[501]; //키큰사람
vector<int> v_re[501]; //작은 사람
int dfs(int idx, int dir) { // 1이 위로 -1 아래로 
    if (dir == 1) {     
        if (dp[idx]) //방문 했던 노드는 메모리제이션으로 출력
            return dp[idx];
 
        if (v[idx].empty()) 
            return 1;
 
        int summ = 0;
        for (int i = 0; i < v[idx].size(); i++) {
            if (!isvis[v[idx][i]]) {
            isvis[v[idx][i]] = 1;
                summ += dfs(v[idx][i], 1); // 자신 보다 키 큰 사람 탐색
            }           
        }
 
        return dp[idx] = summ + 1;     //자신 추가해서 값 리턴             
    }
    else {
        if (dp_re[idx])
            return dp_re[idx];
 
        if (v_re[idx].empty())
            return 1;
 
        int summ = 0;
        for (int i = 0; i < v_re[idx].size(); i++) {
            if (!isvis_re[v_re[idx][i]]) {
                isvis_re[v_re[idx][i]] = 1;
                summ += dfs(v_re[idx][i], -1); //작은 사람 탐색
            }
        }
 
        return dp_re[idx] = summ + 1;           
    }
}
 
int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b); //작은사람 ->큰사람
        v_re[b].push_back(a); // 큰사람 -> 작은사람
    }
         
    for (int i = 1; i <= N; i++) {
        int tmp1 = dfs(i, 1);
        int tmp2 = dfs(i, -1);
 
        if (tmp1 + tmp2 - 1 == N) // 모두 탐색 한경우만 카운트
            cnt++;
 
        memset(isvis, 0, sizeof(isvis));
        memset(isvis_re, 0, sizeof(isvis_re));
        memset(dp, 0, sizeof(dp));
        memset(dp_re, 0, sizeof(dp_re));
    }
 
    cout << cnt;
    return 0;
}
