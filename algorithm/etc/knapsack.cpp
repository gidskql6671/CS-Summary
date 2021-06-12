/* 
    배낭 채우기 문제를 해결하기 위한 알고리즘
    배낭에 넣을 수 있는 물건을 자를 수 없는 0-1 Knapsack을 해결.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#define ITEM_COUNT 100
#define MAX_WEIGHT 100000

using namespace std;


int n, k;
int value[ITEM_COUNT + 1][MAX_WEIGHT + 1];
int thing[ITEM_COUNT + 1][2]; // thing[i][0], thing[i][1] : 각각 i번째 물건의 무게와 가치

// input을 처리하는 함수
void input(){
    cin >> n >> k;
    
    for(int i = 1; i <= n; i++)
        cin >> thing[i][0] >> thing[i][1];
}

// 0-1 Knapsack 알고리즘
// 다음 점화식을 바탕으로 구현됨
// value[i, w] = 
//   if wi > w :  value[i - 1, w]
//   else      :  max{ vi + value[p - 1, w - wk], value[i - 1, w] }
// value[i, w] 란 i개의 보석이 있고 배낭의 무게 한도가 w일 때, 담을 수 있는 최대 가치를 뜻한다.
// i번째 보석이 배낭의 무게 한도보다 무거우면 넣을 수 없으므로, i번째 보석을 뺀 i-1개의 보석을 가지고 구한 최적의 해를 가진다.
// 그렇지 않으면, 'i번째 보석을 넣기 위해 i번째 보석만큼의 무게를 비웠을 때 최적 값에 i번째 보석의 가치를 더한 값'과
//               'i번째 보석을 넣지 않고 i - 1개의 보석을 가지고 구한 최적의 해' 중 더 높은 값을 취한다.
int knapsack(){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= k; j++){
            int w = thing[i][0];
            int v = thing[i][1];
            
            if (w > j){
                value[i][j] = value[i - 1][j];
            }
            else{
                value[i][j] = max(value[i - 1][j], v + value[i - 1][j - w]);
            }
        }
    }
    
    return value[n][k];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    input();
    
    cout << knapsack() << endl;
    
    return 0;
}