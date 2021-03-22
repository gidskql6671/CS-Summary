/* Sorting Algorithm�� ���� */
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


// �⺻ �� �Լ�
template <typename T>
bool defaultCompare(T a, T b){
    return a <= b;
}

// Insertion Sort�� ����
// �迭�� ���� �ϳ��� insert�ϸ鼭 �����ϴ� ���
// T arr[] : ������ 1���� �迭
// int n : �迭 �� ������ ����
// bool (*compare)(T, T) : ���Ҹ� �����ִ� �� �Լ� 
template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T)){
    // arr[0] ~ arr[0] ������ ���Ұ� �Ѱ��̹Ƿ� �翬�� ���ĵ� ����. �� �ε��� 1���� ����
    for(int i = 1; i < n; i++){
        T key = arr[i];
        int j;
        
        // arr[0:i]�� ���ĵǾ��ִ� ������. �� i-1���� �������� �����ϸ�
        // key�� �� ��ġ�� ã�� ��.
        for(j = i - 1; j >= 0 && compare(key, arr[j]); j--)
            arr[j+1] = arr[j];
        
        arr[j+1] = key; // �ش� ��ġ�� key�� �־���.
    }
}

// Selection Sort�� ����
// �迭�� �� �ε����� ���� ���Ҹ� select�ϸ� �����ϴ� ���
// T arr[] : ������ 1���� �迭
// int n : �迭 �� ������ ����
// bool (*compare)(T, T) : ���Ҹ� �����ִ� �� �Լ� 
template <typename T> 
void selectionSort(T arr[], int n, bool (*compare)(T, T)){
    // 0��° index���� (n - 1)��° index����, �ش� ��ġ�� �� ���Ҹ� select�Ѵ�.
    for(int i = 0; i < n; i++){
        // i��° index�� �� ���� select�Ѵ�.
        
        
        // compare�� ���� i��° �ε����� �� ������ ���� ã��.
        int target = i;
        for(int j = i + 1; j < n; j++)
            if (compare(arr[j], arr[target]))
                target = j;
        
        // ���õ� ���� i��° �ε����� ���� �ʴٸ� �̵����ش�.
        if (i != target){
            T tmp;
            SWAP(arr[i], arr[target], tmp);
        }
    }
}

// Bubble Sort�� ����
// ���� ������ �� ���Ҹ� �˻��ذ��� �����ϴ� ���
// T arr[] : ������ 1���� �迭
// int n : �迭 �� ������ ����
// bool (*compare)(T, T) : ���Ҹ� �����ִ� �� �Լ� 
template <typename T> 
void bubbleSort(T arr[], int n, bool (*compare)(T, T)){
    // �ڿ������� ���Ҹ� �����ҰŴ�.
    for(int i = n - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            // ������ �� ���Ҹ� ���ذ���, ���ĵǾ����� �ʴٸ� �ڷ� �δ�.
            if (compare(arr[j + 1], arr[j])){
                T tmp;
                SWAP(arr[j], arr[j+1], tmp);
            }
        }
    }
}

// Quick Sort�� ����
// �������� ������ �������� ����
// 1. pivot�� �������� pivot���� ���� ���Ҵ� ��������, pivot���� ū ���Ҵ� ���������� �ű��.
// 2. pivot�� ������ ���� �κ� ����Ʈ�� ������ �κ� ����Ʈ���� �� ������ �ݺ��Ѵ�.
// 3. �κ� ����Ʈ�� ũ�Ⱑ 0 �Ǵ� 1�� �� ��� �����Ѵ�.
// T arr[] : ������ 1���� �迭
// int left : ������ �迭�� ù��° �ε���
// int right : ������ �迭�� ������ �ε���
// bool (*compare)(T, T) : ���Ҹ� �����ִ� �� �Լ� 
template<typename T>
void quickSort(T arr[], int left, int right, bool (*compare)(T, T)){
    
    // ������ �迭�� ũ�Ⱑ 2�̻��� ��� ����.
    // left == right �� ���, ���Ұ� �ϳ��̹Ƿ� �׻� ���ĵ� ����
    if (left < right){
        T tmp; // SWAP�� ���� �ӽ� ����
        int pivot = left; // pivot�� ���� ���� ������ ����.
        int low = left;
        int high = right + 1;
        
        
        do{
            // low�� �迭�� ������ ����ų�
            // arr[low]�� arr[pivot]���� ũ�ų� ���� ��� Ż��.
            do {
                low++;
            } while(low <= right && arr[low] < arr[pivot]);
            
            // high�� �迭�� ������ ����ų�
            // arr[high]�� arr[pivot]���� �۰ų� ���� ��� Ż��.
            do {
                high--;
            } while(high >= left && arr[high] > arr[pivot]);
            
            // ���� �ΰ��� �ݺ����� ���� 
            // arr[low]���� pivot���� ū ���� arr[high]���� pivot���� ���� ���� ����ִ�.
            // ���� low < high�� ��� ������ �Ǿ����� �ʴٴ� ���̹Ƿ� ���� �ٲ���.
            if (low < high){
                SWAP(arr[low], arr[high], tmp);
            }
        } while(low < high);
        
        // pivot ���� �������� ���ʿ� ���� ������ �����ʿ� ū������ �������� SWAP
        SWAP(arr[pivot], arr[high], tmp);
        
        // pivot�� �������� ���ʿ��� ���� ����, �����ʿ��� ū ������ ��ġ�ϵ��� ���ĵ�.
        // �� �� �迭�� ���ؼ��� ������ ������.
        quickSort(arr, left, high - 1);
        quickSort(arr, high + 1, right);
    }
}

// Merge Sort���� ���ҵ� �κ� �迭�� �պ��ϴ� ����
// Merge Sort���� ù��° �ε����� left, ������ �ε����� right�� �� �迭�� mid�� �������� �� ���� �ɰ�����.
// �� �ɰ��� �� �迭�� �պ��ϴ� ���̸�, �պ� �������� ������ �̷������.
// T arr[] : ������ 1���� �迭
// int left : �պ��� �� �迭 �� ���� �迭�� ù��° �ε���
// int mid : �պ��� �� �迭�� �߰� �ε��� -> ���� �迭�� ������ �ε��� + 1�̸鼭 ������ �迭�� ù��° �ε����̴�.
// int right : �պ��� �� �迭 �� ������ �迭�� ������ �ε���
// bool (*compare)(T, T) : ���Ҹ� �����ִ� �� �Լ�
template<typename T>
void merge(T arr[], int left, int mid, int right, bool (*compare)(T, T)){
    int i = left;
    int j = mid + 1;
    int cur = 0;
    
    T *tmp = new T[right - left + 1]; // merge sort�� �߰� �޸𸮰� �ʿ���.
    
    // ���ҵ� �κ� �迭�� ���� Ž���ϸ鼭 �� ���� ���� ���� �ӽ� �迭�� �־��ش�.
    while(i <= mid && j <= right){
        if (arr[i] <= arr[j])
            tmp[cur++] = arr[i++];
        else
            tmp[cur++] = arr[j++];
    }
    
    // ���� ���� �κ��� �����ִٸ�, �� ������ �ӽ� �迭�� �־���
    while(i <= mid){
        tmp[cur++] = arr[i++];
    }
    // ���� ������ �κ��� �����ִ� ���� ���� �迭(arr)�� ���ĵ� ���·� ����Ǿ��ֱ� ������ �ű� �ʿ䰡 ����.
    
    // �ӽ� �迭�� �ִ� ���ĵ� ���� ���� �迭�� �־��ش�.
    for(int idx = 0; idx < cur; idx++){
        arr[left + idx] = tmp[idx];
    }
    
    delete[] tmp;
}

// Merge Sort�� ����
// ���� ����(Divide and Conquer) ������� ������ �����Ѵ�.
// ������ 2�� �̻��� �κ� ������ �����ϰ�, ������ �ذ��� �� ����� ��� �պ��ϴ� ����̴�.
// T arr[] : ������ 1���� �迭
// int left : ������ �迭�� ù��° �ε���
// int right : ������ �迭�� ������ �ε���
// bool (*compare)(T, T) : ���Ҹ� �����ִ� �� �Լ�
template<typename T>
void mergeSort(T arr[], int left, int right, bool (*compare)(T, T)){
    if (left < right){
        int mid = (left + right) / 2;
        
        // ����Ʈ�� �߰��� �������� �ΰ��� ������
        mergeSort(arr, left, mid, compare);
        mergeSort(arr, mid + 1, right, compare);
        
        // ������ ����Ʈ�� �պ��ϸ� ������.
        merge(arr, left, mid, right, compare);
    }
}