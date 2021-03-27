/* ���װ��(binomial coefficient)�� ������ */
typedef long long ll;

ll bino_coef_dp(int n, int r);
ll bino_coef_dp2(int n, int r);
ll bino_coef_ferma(int n, int r);

long long bino_coef(int n, int r){
    // r�� n���� ū ����� ���� 0�̴�.
    if (r > n)
        return 0;
   
    // n������ 0���� �����ϴ� ����� ���� n������ r���� �����ϴ� ����� ���� 1�̴�.
    if (r == 0 || r == n)
        return 1;
    
    // nCr = n-1Cr + n-1Cr-1
    return bino_coef(n - 1, r - 1) + bino_coef(n - 1, r);
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