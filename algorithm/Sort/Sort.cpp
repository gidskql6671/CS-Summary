/* Sorting Algorithm을 구현 */
#define SWAP(x, y, tmp) ( (tmp) = (x), (x)=(y), (y)=(tmp) )
#include <iostream>

using namespace std;

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

template<typename T>
void heapSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

// 내림차순 정렬
bool compareReverse(int a, int b){
    return a > b;
}


int main(){
    int n;
    
    cout << "원소의 개수를 입력 : ";
    cin >> n;
    
    int *arr = new int[n];
    for(int i = 0; i < n; i++){
        cout << i + 1 << "번째 원소 : ";
        cin >> arr[i];
    }
    
    cout << "정렬 전 배열 : ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
    
    /* 오름차순 정렬 */
    insertionSort(arr, n);
    // selectionSort(arr, n);
    // bubbleSort(arr, n);
    // quickSort(arr, 0, n - 1);
    // mergeSort(arr, 0, n - 1);
    // heapSort(arr, n);
    
    /* 내림차순 정렬 */
    // insertionSort(arr, n, compareReverse);
    
    cout << "정렬 후 배열 : ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
    
    
    delete[] arr;
    
    return 0;
}




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
// 1. pivot을 기준으로 pivot보다 작은 원소는 왼쪽으로, pivot보다 큰 원소는 오른쪽으로 옮긴다.
// 2. pivot을 제외한 왼쪽 부분 리스트와 오른쪽 부분 리스트에도 위 과정을 반복한다.
// 3. 부분 리스트의 크기가 0 또는 1이 될 경우 종료한다.
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
            // low가 배열의 범위를 벗어나거나, arr[low]가 arr[pivot]보다 크거나 같은 경우 탈출.
            do {
                low++;
            } while(low <= right && arr[low] < arr[pivot]);
            
            // high가 배열의 범위를 벗어나거나, arr[high]가 arr[pivot]보다 작거나 같은 경우 탈출.
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
        
        // pivot을 기준으로 왼쪽에는 작은 값들, 오른쪽에는 큰 값들이 위치시킴.
        // 이 두 배열에 대해서도 정렬을 시작함.
        quickSort(arr, left, high - 1);
        quickSort(arr, high + 1, right);
    }
}

// Merge Sort에서 분할된 부분 배열을 합병하는 과정
// Merge Sort에서 첫번째 인덱스가 left, 마지막 인덱스가 right인 한 배열을 mid를 기준으로 두 개로 쪼개었다.
// 이 쪼개진 두 배열을 합병하는 것이며, 합병 과정에서 정렬이 이루어진다.
// T arr[] : 정렬할 1차원 배열
// int left : 합병할 두 배열 중 왼쪽 배열의 첫번째 인덱스
// int mid : 합병할 두 배열의 중간 인덱스 -> 왼쪽 배열의 마지막 인덱스 + 1이면서 오른쪽 배열의 첫번째 인덱스이다.
// int right : 합병할 두 배열 중 오른쪽 배열의 마지막 인덱스
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수
template<typename T>
void merge(T arr[], int left, int mid, int right, bool (*compare)(T, T)){
    int i = left;
    int j = mid + 1;
    int cur = 0;
    
    T *tmp = new T[right - left + 1]; // merge sort는 추가 메모리가 필요함.
    
    // 분할된 부분 배열을 각각 탐색하면서 더 작은 값을 먼저 임시 배열에 넣어준다.
    while(i <= mid && j <= right){
        if (arr[i] <= arr[j])
            tmp[cur++] = arr[i++];
        else
            tmp[cur++] = arr[j++];
    }
    
    // 만약 왼쪽 부분이 남아있다면, 그 값들을 임시 배열에 넣어줌
    while(i <= mid){
        tmp[cur++] = arr[i++];
    }
    // 만약 오른쪽 부분이 남아있는 경우는 원래 배열(arr)에 정렬된 상태로 저장되어있기 때문에 옮길 필요가 없다.
    
    // 임시 배열에 있는 정렬된 값을 원래 배열에 넣어준다.
    for(int idx = 0; idx < cur; idx++){
        arr[left + idx] = tmp[idx];
    }
    
    delete[] tmp;
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
    if (left < right){
        int mid = (left + right) / 2;
        
        // 리스트를 중간을 기준으로 두개로 분할함
        mergeSort(arr, left, mid, compare);
        mergeSort(arr, mid + 1, right, compare);
        
        // 분할한 리스트를 합병하며 정렬함.
        merge(arr, left, mid, right, compare);
    }
}

// Insertion in Heap
// heap에 value를 넣어줌.
// T heap[] : heap
// T value : heap에 넣을 값
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수
template<typename T>
void insert_heap(T heap[], T value, bool (*compare)(T, T)){
    // heap의 가장 마지막에 원소를 넣음.
    int cur = ++(heap[0]);
    
    // 삽입할 원소와 부모 노드를 비교하면서 삽입할 원소의 우선순위가 높다면 위치를 바꿔줌.
    while((cur != 1) && compare(value, heap[cur / 2])){
        heap[cur] = heap[cur / 2];
        
        cur /= 2;
    }
    
    // 새로운 노드를 적절한 위치에 삽입함.
    heap[cur] = value;
}

// Deletion in Heap
// heap에서 우선순위가 큰 값을 삭제 및 반환해줌.
// T heap[] : heap
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수
template<typename T>
T delete_heap(T heap[], bool (*compare)(T, T)){
    int parent, child;
    T item, last;
    
    item = heap[1]; // 루트 노드 값을 반환.
    
    // heap의 마지막 값을 루트 노드 위치부터 비교해가며 삽입하기 적절한 위치를 찾을 것임.
    last = heap[(heap[0])--]; 
    parent = 1;
    child = 2;
    
    // child가 heap의 크기를 초과하면 탈출
    while(child <= heap[0]){
        // 오른쪽 자식이 왼쪽 자식보다 우선순위가 크면, 오른쪽 자식을 대상으로 진행
        if ((child < heap[0]) && compare(heap[child + 1], heap[child])){
            child++;
        }
        
        // 만약 마지막 노드가 자식 노드보다 우선순위가 크거나 같다면, break
        if (!compare(heap[child], last)){
            break;
        }
        
        heap[parent] = heap[child];
        
        parent = child;
        child *= 2;
    }
    
    heap[parent] = last;
    
    return item;
}

// Heap Sort의 구현
// Heap을 이용한 정렬
// 배열의 원소 n개를 heap에 넣은 뒤, 하나씩 빼면서 정렬함
// T arr[] : 정렬할 1차원 배열
// int n : 배열 안 원소의 개수
// bool (*compare)(T, T) : 원소를 비교해주는 비교 함수
template<typename T>
void heapSort(T arr[], int n, bool (*compare)(T, T)){
    // 배열로 만든 heap은 인덱스 1부터 값이 들어감. 그렇기 때문에, 크기를 n + 1로 해줌.
    T *heap = new T[n + 1];
    
    // heap 초기화. 원소의 개수를 0으로 설정
    heap[0] = 0;
    
    // n개의 원소를 heap에 넣어줌.
    for(int i = 0; i < n; i++){
        insert_heap(heap, arr[i], compare);
    }
    
    // n개의 원소를 차례차례 빼주면서 배열에 넣어줌.
    for(int i = 0; i < n; i++){
        arr[i] = delete_heap(heap, compare);
    }
    
    // heap에 할당된 메모리 해제.
    delete[] heap;
}