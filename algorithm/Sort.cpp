/* Sorting Algorithm�� ���� */

template <typename T>
bool defaultCompare(T a, T b);


template <typename T> 
void insertionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template <typename T> 
void selectionSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);

template <typename T> 
void bubbleSort(T arr[], int n, bool (*compare)(T, T) = defaultCompare);



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
            T tmp = arr[i];
            arr[i] = arr[target];
            arr[target] = tmp;
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
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

