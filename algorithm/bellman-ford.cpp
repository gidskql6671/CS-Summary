/*
    �� ��忡�� �ٸ� ��� ������ �ִ� ��θ� ���ϴ� ���� ���� �˰����� ������.
    ������ ����� ������ ����� �����ϴ�.
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
    // next = edges[start][i].first, weight = edges[start][i].second :  weight�� ����ġ�� ������ start���� next���� ������ �ִ�.
    vector<vector<pair<int, int>>> edges(n);
    
    for(int i = 0; i < e; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edges[a - 1].push_back({b - 1, c});
    }
    
    vector<ll> dist; // �ִ� �Ÿ�
    bool isNegativeCycle; // ���� ����Ŭ�� �ִ��� ���θ� ����
    tie(dist, isNegativeCycle) = bellmanFord(edges, n, 0);
    
    
    solve(dist, isNegativeCycle, n);
    
    return 0;
}

// �������� �˰����� ����
tuple<vector<ll>, int> bellmanFord(vector<vector<pair<int, int>>> edges, int n, int start){
    vector<ll> dist(n, INF);
    
    // ���� �������� ���� �������� ���� ���� �Ÿ��� 0�̴�.
    dist[start] = 0;
    // i��° �ݺ� ��, ���� ��忡������ i���� ������ Ÿ�� Ư�� ��忡 �����ϴ� ���̴�.
    // ���� ����Ŭ�� ���ٸ�, ���� ��忡�� Ư�� ������ �����ϱ� ���� ���İ��� �ִ� ������ ���� n - 1���̴�.
    // �� 0 ~ n - 1�� ����.
    for(int i = 0; i < n - 1; i++){
        // j��° �ݺ� ��, ���� ��忡������ j ��带 ���� �ٸ� ���� �� �� �ִ� �ִܰŸ��� ã�´�.
        // ���� start�� 0, i�� 2, j�� 1�϶� 3�� ���� ���� �ִܰŸ��� ������Ʈ�� �̷�����ٸ�, 
        // start�������� 2���� ������ Ÿ�� j�� ����������, j���� 3�� ���� ���� �Ÿ��� ������ �ִܰŸ����� ª�ٴ� ���� �ǹ��Ѵ�.
        for(int j = 0; j < n; j++){
            // ���� �湮�� ��忡 ���� ������ ���ߴٸ� �Ѿ��.
            if (dist[j] == INF)
                continue;
            
            // ���� �湮�� ��忡 ����� ���� ���� �ٸ� ���� ���� �Ÿ��� �����ų �� �ִ��� üũ�Ѵ�.
            for(int k = 0; k < edges[j].size(); k++){
                int next = edges[j][k].first;
                int distance = edges[j][k].second;
                
                dist[next] = min(dist[next], dist[j] + distance);
            }
        }
    }
    
    // ���� ����Ŭ�� �ִ��� Ȯ��.
    // ���� ���� ����Ŭ�� ���ٸ� ���� ��忡������ Ư�� ���� ���� �ִܰŸ����� Ÿ�� �� �ִ� �ִ� ������
    // n - 1���̱� ������ n��° �ݺ����� �ִܰŸ��� ������ �̷�����ٸ� ���� ����Ŭ�� �ִ°��̴�.
    
    bool isNegativeCycle = false;
    for(int i = 0; i < n; i++){
        // ���� �湮�� ��忡 ���� ������ ���ߴٸ� �Ѿ��.
        if (dist[i] == INF)
            continue;
        
        // ���� �湮�� ��忡 ����� ���� ���� �ٸ� ���� ���� �Ÿ��� �����ų �� �ִ��� üũ�Ѵ�.
        for(int j = 0; j < edges[i].size(); j++){
            int next = edges[i][j].first;
            int distance = edges[i][j].second;
            
            // ���� �ִܰŸ��� �����ų �� �ִٸ�, ���� ����Ŭ�� �ִٴ� ����.
            if (dist[next] > dist[i] + distance){
                isNegativeCycle = true;
                break;
            }
        }
    }
    
    return make_tuple(dist, isNegativeCycle);
}

// ���� ������ Ǯ������ �Լ�
void solve(vector<ll> dist, bool isNegativeCycle, int n){
    if (isNegativeCycle){
        cout << -1 << "\n";
        return;
    }
    
    for(int i = 1; i < n; i++){
        cout << (dist[i] == INF ? -1 : dist[i]) << "\n";
    }
}