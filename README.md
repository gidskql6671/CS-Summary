# data-structure
자료구조를 직접 구현할 것이며, C++ STL의 기능들을 비슷하게 구현해본다.


## 프로젝트 구조
data structure
+ utils/
    + Error.cpp
    + Stack.cpp
    + Queue.cpp

### Error.cpp
각종 자료구조의 에러 핸들링에서 throw할 Enum을 구현.

### Stack.cpp
배열로 Stack을 구현함. 
배열이 꽉차면 사이즈를 두배로 늘려줌
+ push, pop, top, size, empty 기능 구현

### Queue.cpp
배열로 Circular Queue를 구현함. 
배열이 꽉차면 사이즈를 두배로 늘려줌
+ push, pop, front, back, size, empty 기능 구현

### LinkedList.cpp
Single Linked List를 구현함
+ push_front, push_back, pop_front, pop_back, insert, remove, size, reverse, sort 기능 구현