/*
    모든 노드에서 모든 노드로의 최단 경로를 구하는 플로이드 와샬 알고리즘을 구현함.
*/
#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

vector<vector<int>> floydWarshall(vector<vector<int>> dist, int n);

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
        
        dist[a][b] = c;
    }
    
    vector<vector<int>> minDist = floydWarshall(dist, n);
    
    return 0;
}

// 플로이드 와샬 알고리즘 구현.
// 거쳐가는 노드를 통해 최단거리를 계속 최신화해나간다.
// 시간복잡도는 O(n^3)
vector<vector<int>> floydWarshall(vector<vector<int>> dist, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (dist[i][j] == 0)
                dist[i][j] = INF;
        }
    }
    
    // k : 거쳐가는 노드
    // i : 출발 노드
    // j : 도착 노드
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    return dist;
}
