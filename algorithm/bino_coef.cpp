/* ���װ��(binomial coefficient)�� ������ */
#include <iostream>
typedef long long ll;

using namespace std;


ll bino_coef_dp(int n, int r);
ll bino_coef_dp2(int n, int r);
ll bino_coef_ferma(int n, int r);


int main(){
    int n, r;
    
    cin >> n >> r;
    
    cout << bino_coef_ferma(n, r) << endl;
    
    return 0;
}


// Dynamic Programing�� �̿��� ���� ��� ���ϱ�.
// ���� ����� ������ �� �ϳ��� nCr = n-1Cr + n-1Cr-1�� �̿��� ����
ll bino_coef_dp(int n, int r){
    static ll dp[100][100] = { 0 };
    
    // r�� n���� ū ����� ���� 0�̴�.
    if (r > n)
        return 0;
    
    // �̹� ����ߴٸ� �ٷ� ��ȯ
    if (dp[n][r] > 0)
        return dp[n][r];
    
    // n������ 0���� �����ϴ� ����� ���� n������ r���� �����ϴ� ����� ���� 1
    if (r == 0 || r == n)
        return dp[n][r] = 1;
    
    // nCr = n-1Cr + n-1Cr-1
    return dp[n][r] = bino_coef_dp(n - 1, r - 1) + bino_coef_dp(n - 1, r);
}


// ���� ����� ���Ҹ� ������ �̾ư��� ����� ���� ����
// n���� ���� �� r���� �̾ƾ��ϴµ�, ������� ���Ҹ� times�� �����Ͽ�����, got���� ���Ҹ� ���� �����̴�.
// ���� �پ��� ��쿡 ������ ������.
// ���� r�� �̻��� �̴� ����� ����� got == r�� got >= r�� �ٲپ��ָ� ��.
// bino_coef_dp2���� �����.
ll choose(int n, int r, ll **dp, int times, int got){
    // n�� ���������� ����Լ��� Ż���Ѵ�.
    if (times == n)
        return got == r; // ���� ������ ������ r���� true(1), r���� �ƴϸ� false(0)�� ��ȯ�Ѵ�.
    
    // �ش� �κ� ������ �̹� ���Ǿ� ������, �ٷ� ��ȯ�Ѵ�.
    if (dp[times][got] != -1)
        return dp[times][got];
    
    // times��° ���ÿ��� �̴� ��� + times��° ���ÿ��� ���� �ʴ� ���
    return dp[times][got] = choose(n, r, dp, times + 1, got) + choose(n, r, dp, times + 1, got + 1);
}

// ���װ���� ���� �������� ��쿡 ����� �� �ֵ��� ������ ���
// ���� �������� �̾ư��� ����� ���� ���Ѵ�.
ll bino_coef_dp2(int n, int r){
    // r�� n���� ū ����� ���� 0�̴�.
    if (r > n)
        return 0;
        
    // Memoization�� ���� ������ �迭 ����
    ll **dp = new ll*[n + 1];
    for(int i = 0; i <= n; i++){
        dp[i] = new ll[n + 1];
        for(int j = 0; j <= n; j++)
            dp[i][j] = -1;
    }
    
    // ������ �̾ư��� ����� ���� ����.
    ll result = choose(n, r, dp, 0, 0);
    
    // �Ҵ�� �޸� ����
    for(int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;
    
    return result;
}


// �丣���� �������� �̿��� ���� ��� ���ϱ�.
// ��ⷯ ������ ���ϴ� ���� �����Ǿ��ִ�.
ll bino_coef_ferma(int n, int r){
    ll MOD = 1000000007LL;
    ll A = 1, B = 1; // A = n!, B = k!(n-k)!
    
    // n! ���ϱ�
    for(ll i = 1; i <= n; i++){
        A *= i;
        A %= MOD;
    }
    
    // k! ���ϱ�
    for(ll i = 1; i <= r; i++){
        B *= i;
        B %= MOD;
    }
    // k!(n-k)! ���ϱ�
    for(ll i = 1; i <= n - r; i++){
        B *= i;
        B %= MOD;
    }
    
    // B^(MOD-2)�� ����. 2���� ǥ���� ���� O(logN)�� �ð����⵵�� ����.
    ll B2 = 1;
    int exponent = MOD - 2;
    while(exponent){
        if (exponent % 2){
            B2 *= B;
            B2 %= MOD;
        }
        
        B *= B;
        B %= MOD;
        exponent /= 2;
    }
    
    // ����� ����.
    ll result = A * B2;
    result %= MOD;
    
    return result;
}