/*
매우 큰 수의 곱셈을 빠르게 처리하기 위한 Karatsuba Algorithm

배열의 각 인덱스에는 낮은 자리수부터 차례대로 저장된다.
즉, num[0]에는 10^0의 자리, num[1]에는 10^1의 자리, ..., num[i]에는 10^i 자리의 수가 저장된다.
위의 형태로 수를 저장할 시, 각 인덱스가 10의 몇승인지를 나타내기 때문에 곱셈을 더 쉽게 처리할 수 있다.

Karatsuba Algorithm의 아이디어는 다음과 같다.
n자리의 두 정수 a, b는 다음과 같이 표현할 수 있다.
a = a1 * 10^(n/2) + a0
b = b1 * 10^(n/2) + b0
이를 통해 a * b를 다음과 같이 나눌 수 있다.
a*b = a1*b1*10^n + (a1*b0 + a0*b1)*10^(n/2) + a0*b0
      ----z2----   ------z1-------            --z0--
해당 식은 곱셈이 총 4번 이루어진다. 
그러나 다음과 같은 변형을 통해 z1을 곱셈 한번을 통해 구하며, 곱셈 횟수를 3번으로 줄일 수 있다.
(a0+a1)*(b0+b1) = a0*b0 + a1*b0+a0*b1 + a1*b1
                  --z0--  -----z1----   --z2--
z2 = a1 * b1
z0 = a0 * b0
z1 = (a0 + a1) * (b0 + b1) - z0 - z2

위처럼 곱셈 횟수를 줄임으로써 시간복잡도를 O(n^log3)으로 줄일 수 있다.
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



// num의 자릿수 올림을 처리한다.
void nomalize(vector<int> &num){
    // 가장 큰 자리수의 값이 10이상인 경우를 처리하기 위해 0을 추가해줌.
    num.push_back(0);
    
    // 자리수의 올림을 처리한다.
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
    
    // 앞에 남아있는 0을 제거한다.
    while(num.size() > 1 && num.back() == 0)
        num.pop_back();
}

// a와 b의 곱셈 결과를 반환한다.
// 수가 작을 때 사용할 정수 곱셈 알고리즘.
// O(n^2)으로 karatsuba algorithm보다 시간복잡도는 크지만,
// 구현이 간단하여 수가 작을 경우 더 빠르게 수행된다.
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
    
    // 만약 a의 최대 자리수가 b*10^k의 최대 자리수보다 작다면, 
    // a의 크기를 키워주고 추가된 자리수는 0으로 초기화
    if (a.size() < b.size() + k)
        a.resize(b.size() + k, 0);
    
    
    for(int i = 0; i < b.size(); i++)
        a[i + k] += b[i];
        
    nomalize(a);
}

// a -= b
// a >= b일 경우에만 사용 가능
void subFrom(vector<int> &a, const vector<int> &b){
    for(int i = 0; i < b.size(); i++)
        a[i] -= b[i];
    
    nomalize(a);
}

// a와 b의 곱셈 결과를 반환한다.
// O(n^log3)으로 수가 클 경우, 단순한 곱셈보다 빠르게 동작한다.
// 다만 구현의 복잡성으로 인해 수가 작을 경우 오히려 더 느리게 동작하므로, 
// 수가 작을 때는 단순한 곱셈으로 값을 구한다.
vector<int> karatsuba(const vector<int> &a, const vector<int> &b){
    int an = a.size(), bn = b.size();
    
    // a의 크기가 작을 경우, 서로 바꾸어 준다.
    // 즉, 항상 a가 크다고 간주하고 알고리즘을 작성할 수 있다.
    if (an < bn)
        return karatsuba(b, a);
    // base case : 둘 중 하나가 0인 경우
    if (an == 0 || bn == 0)
        return vector<int>();
    // base case : 수의 크기가 비교적 작은 경우, 단순한 곱셈으로 구함.
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