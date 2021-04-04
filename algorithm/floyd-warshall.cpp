/*
    ��� ��忡�� ��� ������ �ִ� ��θ� ���ϴ� �÷��̵� �ͼ� �˰����� ������.
*/
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;


vector<vector<int>> floydWarshall(vector<vector<int>> dist, int n);
void solve(vector<vector<int>> dist, int n);


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    int n, e;
    
    cin >> n >> e;
    
    vector<vector<int>> dist(n, vector<int>(n, 0));
    
    for(int i = 0; i < e; i++){
        int a, b, c;
        cin >> a >> b >> c;
        
        dist[a - 1][b - 1] = c;
    }
    
    vector<vector<int>> minDist = floydWarshall(dist, n);
    
    solve(minDist, n);
    
    return 0;
}

// �÷��̵� �ͼ� �˰��� ����.
// ���İ��� ��带 ���� �ִܰŸ��� ��� �ֽ�ȭ�س�����.
// �ð����⵵�� O(n^3)
vector<vector<int>> floydWarshall(vector<vector<int>> dist, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (dist[i][j] == 0)
                dist[i][j] = INF;
        }
    }
    
    // k : ���İ��� ���
    // i : ��� ���
    // j : ���� ���
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    return dist;
}


// ���� ������ Ǯ������ �Լ�
voist solve(vector<vector<int>> dist, int n){
    int result = INF;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (i == j)
                continue;
            
            // i -> j�� ���� ��ο� j -> i�� ���� ��ΰ� �ִ� ���
            if (dist[i][j] != INF && dist[j][i] != INF){
                result = min(result, dist[i][j] + dist[j][i]);
            }
        }
    }
    
    cout << (result == INF ? -1 : result) << endl;
}