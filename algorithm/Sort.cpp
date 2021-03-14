/* Sorting Algorithm을 구현 */

template <typename T>
bool defaultCompare(T a, T b);


template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template <typename T> 
void selectionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template <typename T> 
void bubbleSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);



// 기본 비교 함수
template <typename T>
bool defaultCompare(T a, T b){
    return a <= b;
}

// Insertion Sort의 구현
// 배열의 값을 하나씩 insert하면서 정렬하는 방식
// T arr[] : 정렬할 1차원 배열
// int n : 배열 안 원소의 개수
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수 
template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T)){
    // arr[0] ~ arr[0] 까지는 원소가 한개이므로 당연히 정렬된 상태. 즉 인덱스 1부터 시작
    for(int i = 1; i < n; i++){
        T key = arr[i];
        int j;
        
        // arr[0:i]는 정렬되어있는 상태임. 즉 i-1부터 역순으로 조사하며
        // key가 들어갈 위치를 찾아 줌.
        for(j = i - 1; j >= 0 && compare(key, arr[j]); j--)
            arr[j+1] = arr[j];
        
        arr[j+1] = key; // 해당 위치에 key를 넣어줌.
    }
}

// Selection Sort의 구현
// 배열의 각 인덱스에 넣을 원소를 select하며 정렬하는 방식
// T arr[] : 정렬할 1차원 배열
// int n : 배열 안 원소의 개수
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수 
template <typename T> 
void selectionSort(T arr[], int n, bool (*compare)(T, T)){
    // 0번째 index부터 (n - 1)번째 index까지, 해당 위치에 들어갈 원소를 select한다.
    for(int i = 0; i < n; i++){
        // i번째 index에 들어갈 값을 select한다.
        
        
        // compare를 통해 i번째 인덱스에 들어갈 적절한 값을 찾음.
        int target = i;
        for(int j = i + 1; j < n; j++)
            if (compare(arr[j], arr[target]))
                target = j;
        
        // 선택된 값이 i번째 인덱스에 있지 않다면 이동해준다.
        if (i != target){
            T tmp = arr[i];
            arr[i] = arr[target];
            arr[target] = tmp;
        }
    }
}

// Bubble Sort의 구현
// 서로 인접한 두 원소를 검사해가며 정렬하는 방식
// T arr[] : 정렬할 1차원 배열
// int n : 배열 안 원소의 개수
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수 
template <typename T> 
void bubbleSort(T arr[], int n, bool (*compare)(T, T)){
    // 뒤에서부터 원소를 정렬할거다.
    for(int i = n - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            // 인접한 두 원소를 비교해가며, 정렬되어있지 않다면 뒤로 민다.
            if (compare(arr[j + 1], arr[j])){
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

