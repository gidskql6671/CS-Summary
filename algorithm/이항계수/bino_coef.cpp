/* 이항계수(binomial coefficient)을 구현함 */
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


// Dynamic Programing을 이용한 이항 계수 구하기.
// 이항 계수의 방정식 중 하나인 nCr = n-1Cr + n-1Cr-1을 이용한 구현
ll bino_coef_dp(int n, int r){
    static ll dp[100][100] = { 0 };
    
    // r이 n보다 큰 경우의 수는 0이다.
    if (r > n)
        return 0;
    
    // 이미 계산했다면 바로 반환
    if (dp[n][r] > 0)
        return dp[n][r];
    
    // n개에서 0개를 선택하는 경우의 수와 n개에서 r개를 선택하는 경우의 수는 1
    if (r == 0 || r == n)
        return dp[n][r] = 1;
    
    // nCr = n-1Cr + n-1Cr-1
    return dp[n][r] = bino_coef_dp(n - 1, r - 1) + bino_coef_dp(n - 1, r);
}


// 이항 계수를 원소를 실제로 뽑아가며 경우의 수를 구함
// n개의 원소 중 r개를 뽑아야하는데, 현재까지 원소를 times번 선택하였으며, got개의 원소를 뽑은 상태이다.
// 좀더 다양한 경우에 적용이 가능함.
// 만약 r개 이상을 뽑는 경우의 수라면 got == r을 got >= r로 바꾸어주면 됨.
// bino_coef_dp2에서 사용함.
ll choose(int n, int r, ll **dp, int times, int got){
    // n번 선택했으면 재귀함수를 탈출한다.
    if (times == n)
        return got == r; // 뽑은 원소의 개수가 r개면 true(1), r개가 아니면 false(0)을 반환한다.
    
    // 해당 부분 문제가 이미 계산되어 있으면, 바로 반환한다.
    if (dp[times][got] != -1)
        return dp[times][got];
    
    // times번째 선택에서 뽑는 경우 + times번째 선택에서 뽑지 않는 경우
    return dp[times][got] = choose(n, r, dp, times + 1, got) + choose(n, r, dp, times + 1, got + 1);
}

// 이항계수를 좀더 범용적인 경우에 사용할 수 있도록 구현한 방식
// 직접 아이템을 뽑아가며 경우의 수를 구한다.
ll bino_coef_dp2(int n, int r){
    // r이 n보다 큰 경우의 수는 0이다.
    if (r > n)
        return 0;
        
    // Memoization을 위한 이차원 배열 선언
    ll **dp = new ll*[n + 1];
    for(int i = 0; i <= n; i++){
        dp[i] = new ll[n + 1];
        for(int j = 0; j <= n; j++)
            dp[i][j] = -1;
    }
    
    // 실제로 뽑아가며 경우의 수를 구함.
    ll result = choose(n, r, dp, 0, 0);
    
    // 할당된 메모리 해제
    for(int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;
    
    return result;
}


// 페르마의 소정리를 이용한 이항 계수 구하기.
// 모듈러 연산을 취하는 것이 전제되어있다.
ll bino_coef_ferma(int n, int r){
    ll MOD = 1000000007LL;
    ll A = 1, B = 1; // A = n!, B = k!(n-k)!
    
    // n! 구하기
    for(ll i = 1; i <= n; i++){
        A *= i;
        A %= MOD;
    }
    
    // k! 구하기
    for(ll i = 1; i <= r; i++){
        B *= i;
        B %= MOD;
    }
    // k!(n-k)! 구하기
    for(ll i = 1; i <= n - r; i++){
        B *= i;
        B %= MOD;
    }
    
    // B^(MOD-2)를 구함. 2진수 표현을 통해 O(logN)의 시간복잡도로 구함.
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
    
    // 결과를 구함.
    ll result = A * B2;
    result %= MOD;
    
    return result;
}