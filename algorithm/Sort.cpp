/* Sorting Algorithm을 구현 */
#define SWAP(x, y, tmp) ( (tmp) = (x), (x)=(y), (y)=(tmp) )

template <typename T>
bool defaultCompare(T a, T b);


template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template <typename T> 
void selectionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template <typename T> 
void bubbleSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template<typename T>
void quickSort(T arr[], int left, int right, bool (*compare)(T, T) = defaultCompare);

template<typename T>
void mergeSort(T arr[], int left, int right, bool (*compare)(T, T) = defaultCompare);


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
            T tmp;
            SWAP(arr[i], arr[target], tmp);
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
                T tmp;
                SWAP(arr[j], arr[j+1], tmp);
            }
        }
    }
}

// Quick Sort의 구현
// 오름차순 정렬을 기준으로 설명
// 1. pivot을 기준으로 2개의 부분 배열로 분할한다.
// 2. pivot보다 작은 값은 왼쪽으로, pivot보다 큰 값을 오른쪽으로 옮긴다.
// T arr[] : 정렬할 1차원 배열
// int left : 정렬할 배열의 첫번째 인덱스
// int right : 정렬할 배열의 마지막 인덱스
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수 
template<typename T>
void quickSort(T arr[], int left, int right, bool (*compare)(T, T)){
    
    // 정렬할 배열의 크기가 2이상일 경우 수행.
    // left == right 일 경우, 원소가 하나이므로 항상 정렬된 상태
    if (left < right){
        T tmp; // SWAP을 위한 임시 변수
        int pivot = left; // pivot은 가장 왼쪽 값으로 결정.
        int low = left;
        int high = right + 1;
        
        
        do{
            // low가 배열의 범위를 벗어나거나
            // arr[low]가 arr[pivot]보다 크거나 같은 경우 탈출.
            do {
                low++;
            } while(low <= right && arr[low] < arr[pivot]);
            
            // high가 배열의 범위를 벗어나거나
            // arr[high]가 arr[pivot]보다 작거나 같은 경우 탈출.
            do {
                high--;
            } while(high >= left && arr[high] > arr[pivot]);
            
            // 위의 두개의 반복문을 통해 
            // arr[low]에는 pivot보다 큰 값이 arr[high]에는 pivot보다 작은 값이 들어있다.
            // 만약 low < high인 경우 정렬이 되어있지 않다는 것이므로 서로 바꿔줌.
            if (low < high){
                SWAP(arr[low], arr[high], tmp);
            }
        } while(low < high);
        
        // pivot 값을 기준으로 왼쪽에 작은 값들을 오른쪽에 큰값들을 몰기위한 SWAP
        SWAP(arr[pivot], arr[high], tmp);
        
        // pivot을 기준으로 왼쪽에는 작은 값들, 오른쪽에는 큰 값들이 위치하도록 정렬됨.
        // 이 두 배열에 대해서도 정렬을 시작함.
        quickSort(arr, left, high - 1);
        quickSort(arr, high + 1, right);
    }
}

// Merge Sort에서 분할된 부분 문제를 합병하는 과정
template<typename T>
void merge(T arr[], int left, int mid, int right, bool (*compare)(T, T)){
    
}

// Merge Sort의 구현
// 분할 정복(Divide and Conquer) 방법으로 정렬을 수행한다.
// 문제를 2개 이상의 부분 문제로 분할하고, 각각을 해결한 뒤 결과를 모아 합병하는 방식이다.
// T arr[] : 정렬할 1차원 배열
// int left : 정렬할 배열의 첫번째 인덱스
// int right : 정렬할 배열의 마지막 인덱스
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수
template<typename T>
void mergeSort(T arr[], int left, int right, bool (*compare)(T, T)){
    
}