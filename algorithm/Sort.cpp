/* Sorting Algorithm을 구현 */

template <typename T>
bool defaultCompare(T a, T b);


template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);





// 기본 비교 함수
template <typename T>
bool defaultCompare(T a, T b){
    return a <= b;
}

// Insertion Sort의 구현
// T arr[] : 정렬할 1차원 배열
// int n : 배열 안 원소의 개수
// bool (*compare)(T, T) : 원소를 비교해주는 정렬 함수 
template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T)){
    // arr[0] ~ arr[0] 까지는 원소가 한개이므로 당연히 정렬된 상태. 즉 인덱스 1부터 시작
    for(int i = 1; i < n; i++){
        T key = arr[i];
        int j;
        
        // arr[0:i]는 정렬되어있는 상태임. 즉 i-1부터 역순으로 조사하며
        // key보다 작은 값을 가지는 원소 뒤에 key값을 넣어 줌.
        for(j = i - 1; j >= 0 && compare(key, arr[j]); j--)
            arr[j+1] = arr[j];
        
        arr[j+1] = key; // key보다 작은 값을 가지는 원소 뒤에 key를 넣어줌.
    }
}