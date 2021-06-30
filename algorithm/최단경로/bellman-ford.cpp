/*
    한 노드에서 다른 모든 노드로의 최단 경로를 구하는 벨만 포드 알고리즘을 구현함.
    간선의 비용이 음수라도 사용이 가능하다.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#define INF 987654321
typedef long long ll;

using namespace std;


tuple<vector<ll>, int> bellmanFord(vector<vector<pair<int, int>>> edges, int n, int start);
void solve(vector<ll> dist, bool isNegativeCycle, int n);


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    int n, e;
    
    cin >> n >> e;
    // next = edges[start][i].first, weight = edges[start][i].second :  weight를 가중치로 가지는 start에서 next로의 간선이 있다.
    vector<vector<pair<int, int>>> edges(n);
    
    for(int i = 0; i < e; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edges[a - 1].push_back({b - 1, c});
    }
    
    vector<ll> dist; // 최단 거리
    bool isNegativeCycle; // 음수 사이클이 있는지 여부를 저장
    tie(dist, isNegativeCycle) = bellmanFord(edges, n, 0);
    
    
    solve(dist, isNegativeCycle, n);
    
    return 0;
}

// 벨만포드 알고리즘의 구현
tuple<vector<ll>, int> bellmanFord(vector<vector<pair<int, int>>> edges, int n, int start){
    vector<ll> dist(n, INF);
    
    // 시작 지점에서 시작 지점으로 가는 것은 거리가 0이다.
    dist[start] = 0;
    // i번째 반복 시, 시작 노드에서부터 i개의 간선을 타고 특정 노드에 도착하는 것이다.
    // 음수 사이클이 없다면, 시작 노드에서 특정 노드까지 도달하기 위해 거쳐가는 최대 간선의 수는 n - 1개이다.
    // 즉 0 ~ n - 1번 돈다.
    for(int i = 0; i < n - 1; i++){
        // j번째 반복 시, 시작 노드에서부터 j 노드를 거쳐 다른 노드로 갈 수 있는 최단거리를 찾는다.
        // 만약 start가 0, i가 2, j가 1일때 3번 노드로 가는 최단거리의 업데이트가 이루어졌다면, 
        // start에서부터 2개의 간선을 타고 j로 도착했으며, j에서 3번 노드로 가는 거리가 기존의 최단거리보다 짧다는 것을 의미한다.
        for(int j = 0; j < n; j++){
            // 현재 방문한 노드에 아직 도달을 못했다면 넘어간다.
            if (dist[j] == INF)
                continue;
            
            // 현재 방문한 노드에 연결된 길을 통해 다른 노드로 가는 거리를 단축시킬 수 있는지 체크한다.
            for(int k = 0; k < edges[j].size(); k++){
                int next = edges[j][k].first;
                int distance = edges[j][k].second;
                
                dist[next] = min(dist[next], dist[j] + distance);
            }
        }
    }
    
    // 음의 사이클이 있는지 확인.
    // 만약 음의 사이클이 없다면 시작 노드에서부터 특정 노드로 가는 최단거리에서 타고갈 수 있는 최대 간선은
    // n - 1개이기 때문에 n번째 반복에서 최단거리의 단축이 이루어진다면 음의 사이클이 있는것이다.
    
    bool isNegativeCycle = false;
    for(int i = 0; i < n; i++){
        // 현재 방문한 노드에 아직 도달을 못했다면 넘어간다.
        if (dist[i] == INF)
            continue;
        
        // 현재 방문한 노드에 연결된 길을 통해 다른 노드로 가는 거리를 단축시킬 수 있는지 체크한다.
        for(int j = 0; j < edges[i].size(); j++){
            int next = edges[i][j].first;
            int distance = edges[i][j].second;
            
            // 만약 최단거리를 단축시킬 수 있다면, 음의 사이클이 있다는 것임.
            if (dist[next] > dist[i] + distance){
                isNegativeCycle = true;
                break;
            }
        }
    }
    
    return make_tuple(dist, isNegativeCycle);
}

// 백준 문제를 풀기위한 함수
void solve(vector<ll> dist, bool isNegativeCycle, int n){
    if (isNegativeCycle){
        cout << -1 << "\n";
        return;
    }
    
    for(int i = 1; i < n; i++){
        cout << (dist[i] == INF ? -1 : dist[i]) << "\n";
    }
}