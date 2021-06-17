### Algorithm

## 목록
각 폴더에 Algorithm들을 C++로 구현하였음.
+ [정렬 코드](./Sort)
+ [이항 계수(Binomial Coefficient)](./이항계수)
+ [최단거리](./최단거리)
+ [기타](./etc)

## 이론
### 자세한 설명은 블로그에 정리해놨다.
[Sorting Algorithm - Insertion Sort, Selection Sort, Bubble Sort](https://velog.io/@gidskql6671/Sorting-Algorithm-Insertion-Sort)
[Sorting Algorithm - Quick Sort, Merge Sort, Heap Sort](https://velog.io/@gidskql6671/Sorting-Algorithm-Quick-Sort-Merge-Sort-Heap-Sort)

### ? 정렬
정렬을 하는 가장 큰 이유는 **탐색**을 위해서. 데이터가 정렬되어 있다면, 이진 탐색이라는 강력한 알고리즘을 사용할 수 있다.

+ **Insertion Sort**
    + 기존의 정렬된 배열에 새로운 원소를 Insert하면서 정렬한다.
    + 새로운 원소가 들어갈 위치를 차례로 탐색하며, 적절한 위치를 찾으면 Insert한다.
    + 시간복잡도는 평균적으로 O(n<sup>2</sup>)이다.
        + 탐색을 역순으로 할 때 입력자료가 이미 정렬이 되어있는 경우, 매번 단 한번의 비교만 수행한다. 즉, 시간복잡도가 O(n)이 된다.
    + 알고리즘이 매우 간결하기 때문에, 데이터가 적을 경우 다른 알고리즘보다 더 빠르게 수행되는 경우가 있다.
    + Stable Sort에 속하며, 이는 같은 값을 가진 원소들의 순서가 정렬 후에도 변경되지 않는 것을 의미한다.
+ **Selection Sort**
    + 특정 위치에 들어갈 원소를 선택하며 정렬하는 알고리즘이다.
    + 해당 순서에 원소를 넣을 위치는 이미 정해져있고, 해당 위치에 넣을 원소를 찾는다.
    + 데이터 분포에 관계없이 동일한 반복횟수를 가진다. 시간 복잡도는 O(n<sup>2</sup>)이다.
    + Unstable Sort에 속하며, 이는 같은 값을 가진 원소들의 순서가 정렬 후에도 동일하다는 것을 보장할 수 없다는 것을 의미한다.
+ **Bubble Sort**
    + 서로 인접한 두 원소를 비교하며 정렬하는 알고리즘이다.
    + 서로 인접한 2개의 원소를 비교하여 정렬되어 있지않다면 서로 위치를 변경한다.
    + 데이터 분포에 관계없이 동일한 반복횟수를 가진다. 시간 복잡도는 O(n<sup>2</sup>)이다.
+ **Merge Sort**
    + 분할 정복(Divide and Conquer) 전략을 사용하는 대표적인 정렬 알고리즘이다.
    + 리스트의 크기가 1이하가 될때까지 절반씩 나눈 후, 나눠진 리스트들을 다시 하나의 정렬된 리스트로 합병한다.
        + 합병 과정에서 새로운 메모리 공간을 할당받아 합병한다.
    + 시간복잡도는 O(nlogn)이다.
    + In-place Algorithm(제자리 알고리즘)이 아니다. O(n)만큼의 새로운 공간이 요구되며, 해당 공간으로 정렬된 배열이 자리잡는다.
+ **Quick Sort**
    + 수행 과정
        1. 리스트 안에 있는 임의의 한 요소를 선택하는데, 이를 pivot이라고 한다.
        2. pivot을 기준으로 pivot의 값보다 작은 요소들을 왼쪽, 큰 요소들을 오른쪽으로 옮긴다.
        3. pivot을 제외한 왼쪽, 오른쪽 리스트 각각에 대해 위 작업을 반복한다.
    + 시간복잡도는 평균적으로 O(nlogn)이며, 최악의 경우 O(n<sup>2</sup>)이 걸린다.
        + 최악의 경우는 배열이 매우 심한 편차(1:n-1)로 계속 나눠지는 경우이다.
        + pivot을 단순히 맨 앞 혹은 맨 뒤로 선택한다면, 이미 정렬된 리스트가 입력으로 주어졌을 때 최악의 경우가 된다.
        + 이런 경우를 방지하기 위해, pivot을 임의로 정하는 것을 Randomized Quicksort라고 하며, 이때의 기대값은 O(nlogn)이다.
    + In-place Algorithm(제자리 알고리즘)이다.
+ **Heap Sort**
    + 배열의 요소로 Heap을 만들고, Heap에서 원소를 하나씩 꺼내어 배열에 저장하면 정렬이 된다.
    + 시간복잡도는 O(nlogn)이 된다.
    + In-place Algorithm(제자리 알고리즘)이다.