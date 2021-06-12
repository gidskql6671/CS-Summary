/*
�ſ� ū ���� ������ ������ ó���ϱ� ���� Karatsuba Algorithm

�迭�� �� �ε������� ���� �ڸ������� ���ʴ�� ����ȴ�.
��, num[0]���� 10^0�� �ڸ�, num[1]���� 10^1�� �ڸ�, ..., num[i]���� 10^i �ڸ��� ���� ����ȴ�.
���� ���·� ���� ������ ��, �� �ε����� 10�� ��������� ��Ÿ���� ������ ������ �� ���� ó���� �� �ִ�.

Karatsuba Algorithm�� ���̵��� ������ ����.
n�ڸ��� �� ���� a, b�� ������ ���� ǥ���� �� �ִ�.
a = a1 * 10^(n/2) + a0
b = b1 * 10^(n/2) + b0
�̸� ���� a * b�� ������ ���� ���� �� �ִ�.
a*b = a1*b1*10^n + (a1*b0 + a0*b1)*10^(n/2) + a0*b0
      ----z2----   ------z1-------            --z0--
�ش� ���� ������ �� 4�� �̷������. 
�׷��� ������ ���� ������ ���� z1�� ���� �ѹ��� ���� ���ϸ�, ���� Ƚ���� 3������ ���� �� �ִ�.
(a0+a1)*(b0+b1) = a0*b0 + a1*b0+a0*b1 + a1*b1
                  --z0--  -----z1----   --z2--
z2 = a1 * b1
z0 = a0 * b0
z1 = (a0 + a1) * (b0 + b1) - z0 - z2

��ó�� ���� Ƚ���� �������ν� �ð����⵵�� O(n^log3)���� ���� �� �ִ�.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



void nomalize(vector<int> &num);
vector<int> multiply(const vector<int> &a, const vector<int> &b);
void addTo(vector<int> &a, const vector<int> &b, int k);
void subFrom(vector<int> &a, const vector<int> &b);
vector<int> karatsuba(const vector<int> &a, const vector<int> &b);


int main(){
    vector<int> a, b;
    string str;
    
    cin >> str;
    for(int i = str.length() - 1; i >= 0 ; i--)
        a.push_back(str[i] - '0');
    
    cin >> str;
    for(int i = str.length() - 1; i >= 0 ; i--)
        b.push_back(str[i] - '0');
    
    vector<int> c = karatsuba(a, b);
    
    for(int i = c.size() - 1; i >= 0; i--)
        cout << c[i];
    cout << endl;
    
    return 0;
}



// num�� �ڸ��� �ø��� ó���Ѵ�.
void nomalize(vector<int> &num){
    // ���� ū �ڸ����� ���� 10�̻��� ��츦 ó���ϱ� ���� 0�� �߰�����.
    num.push_back(0);
    
    // �ڸ����� �ø��� ó���Ѵ�.
    for(int i = 0; i < num.size() - 1; i++){
        if (num[i] < 0){
            int borrow = (abs(num[i]) + 9) / 10;
            num[i + 1] -= borrow;
            num[i] += borrow * 10;
        }
        else{
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    
    // �տ� �����ִ� 0�� �����Ѵ�.
    while(num.size() > 1 && num.back() == 0)
        num.pop_back();
}

// a�� b�� ���� ����� ��ȯ�Ѵ�.
// ���� ���� �� ����� ���� ���� �˰���.
// O(n^2)���� karatsuba algorithm���� �ð����⵵�� ũ����,
// ������ �����Ͽ� ���� ���� ��� �� ������ ����ȴ�.
vector<int> multiply(const vector<int> &a, const vector<int> &b){ 
    vector<int> c(a.size() + b.size() + 1, 0);
    
    for(int i = 0; i < a.size(); i++)
        for(int j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    
    nomalize(c);
    
    return c;
}

// a += b * (10^k)
void addTo(vector<int> &a, const vector<int> &b, int k){
    
    // ���� a�� �ִ� �ڸ����� b*10^k�� �ִ� �ڸ������� �۴ٸ�, 
    // a�� ũ�⸦ Ű���ְ� �߰��� �ڸ����� 0���� �ʱ�ȭ
    if (a.size() < b.size() + k)
        a.resize(b.size() + k, 0);
    
    
    for(int i = 0; i < b.size(); i++)
        a[i + k] += b[i];
        
    nomalize(a);
}

// a -= b
// a >= b�� ��쿡�� ��� ����
void subFrom(vector<int> &a, const vector<int> &b){
    for(int i = 0; i < b.size(); i++)
        a[i] -= b[i];
    
    nomalize(a);
}

// a�� b�� ���� ����� ��ȯ�Ѵ�.
// O(n^log3)���� ���� Ŭ ���, �ܼ��� �������� ������ �����Ѵ�.
// �ٸ� ������ ���⼺���� ���� ���� ���� ��� ������ �� ������ �����ϹǷ�, 
// ���� ���� ���� �ܼ��� �������� ���� ���Ѵ�.
vector<int> karatsuba(const vector<int> &a, const vector<int> &b){
    int an = a.size(), bn = b.size();
    
    // a�� ũ�Ⱑ ���� ���, ���� �ٲپ� �ش�.
    // ��, �׻� a�� ũ�ٰ� �����ϰ� �˰����� �ۼ��� �� �ִ�.
    if (an < bn)
        return karatsuba(b, a);
    // base case : �� �� �ϳ��� 0�� ���
    if (an == 0 || bn == 0)
        return vector<int>();
    // base case : ���� ũ�Ⱑ ���� ���� ���, �ܼ��� �������� ����.
    if (an <= 50)
        return multiply(a, b);
    
    
    int half = an / 2;
    
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
    
    // z2 = a1 * b1
    vector<int> z2 = karatsuba(a1, b1);
    
    // z0 = a0 * b0
    vector<int> z0 = karatsuba(a0, b0);
    
    // z1 = (a0 + a1) * (b0 + b1) - z0 - z2
    addTo(a0, a1, 0); // a0 + a1
    addTo(b0, b1, 0); // b0 + b1
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    
    // z2 * 10^n + z1 * 10^(n/2) + z0
    vector<int> result(z2.size() + half * 2, 0);
    addTo(result, z0, 0);
    addTo(result, z1, half);
    addTo(result, z2, half * 2);
    
    return result;
}