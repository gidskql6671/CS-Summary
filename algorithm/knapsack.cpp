/* 
    �賶 ä��� ������ �ذ��ϱ� ���� �˰���
    �賶�� ���� �� �ִ� ������ �ڸ� �� ���� 0-1 Knapsack�� �ذ�.
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
int thing[ITEM_COUNT + 1][2]; // thing[i][0], thing[i][1] : ���� i��° ������ ���Կ� ��ġ

// input�� ó���ϴ� �Լ�
void input(){
    cin >> n >> k;
    
    for(int i = 1; i <= n; i++)
        cin >> thing[i][0] >> thing[i][1];
}

// 0-1 Knapsack �˰���
// ���� ��ȭ���� �������� ������
// value[i, w] = 
//   if wi > w :  value[i - 1, w]
//   else      :  max{ vi + value[p - 1, w - wk], value[i - 1, w] }
// value[i, w] �� i���� ������ �ְ� �賶�� ���� �ѵ��� w�� ��, ���� �� �ִ� �ִ� ��ġ�� ���Ѵ�.
// i��° ������ �賶�� ���� �ѵ����� ���ſ�� ���� �� �����Ƿ�, i��° ������ �� i-1���� ������ ������ ���� ������ �ظ� ������.
// �׷��� ������, 'i��° ������ �ֱ� ���� i��° ������ŭ�� ���Ը� ����� �� ���� ���� i��° ������ ��ġ�� ���� ��'��
//               'i��° ������ ���� �ʰ� i - 1���� ������ ������ ���� ������ ��' �� �� ���� ���� ���Ѵ�.
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