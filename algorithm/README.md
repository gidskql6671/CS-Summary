### algorithm/
Algorithm들을 구현해둔 디렉토리

각 파일들은 자체적으로 main문과 input 구문들을 가지고 있음.
가능하다면 백준 문제를 바탕으로 구현을 할 것임. 


## 프로젝트 구조
+ sort.cpp
+ bino_coef.cpp
+ karatsuba.cpp
+ knapsack.cpp
+ floyd-warshall.cpp
+ bellman-ford.cpp
+ dijkstra.cpp


+++++
### sort.cpp
Sorting Algorithm을 구현함.
Insertion Sort, Selection Sort, Bubble Sort, Quick Sort, Merge Sort, Heap Sort가 구현되어 있음.

### bino_coef.cpp
이항 계수(binomial coefficient)을 구현함. 
[이항 계수 3](https://www.acmicpc.net/problem/11401)

### karatsuba.cpp
큰 수의 곱셈을 처리하는 알고리즘인 Karatsuba Algorithm을 구현함.
"프로그래밍 대회에서 배우는 알고리즘 문제해결전략"의 내용을 참고하여 구현함.

### knapsack.cpp
무게 제한이 있는 배낭에 물건들을 넣을 때, 배낭에 넣을 수 있는 물건들의 가치의 최대값을 구하는 알고리즘
각각의 물건을  여러개로 쪼갤 수 없는 0-1 Knapsack이며, 각각의 물건은 한개씩만 존재함. 
[평범한 배낭](https://www.acmicpc.net/problem/12865)

### floyd-warshall.cpp
모든 노드에서 모든 노드로의 최단 경로를 구하는 플로이드 와샬 알고리즘을 구현함. 
[운동](https://www.acmicpc.net/problem/1956)

### bellman-ford.cpp
한 노드에서 다른 모든 노드로의 최단 경로를 구하는 벨만 포드 알고리즘을 구현함. 
간선의 비용이 음수라도 사용이 가능하다.
[타임머신](https://www.acmicpc.net/problem/11657)

### dijkstra.cpp
한 노드에서 다른 모든 노드로의 최단 경로를 구하는 다익스트라 알고리즘을 구현함.
간선의 비용이 음수라면 사용이 불가능하지만, 현실에서는 음의 간선이 존재하지 않기에 현실 세계의 문제를 해결하는데 유용함.