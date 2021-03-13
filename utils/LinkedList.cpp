/* Linked List 구현 */
#ifndef MY_ERROR // include guard
#define MY_ERROR
#include "Error.cpp"
#endif

// Linked List의 노드
template<typename T>
struct Node{
public:
    T value;
    struct Node<T> *next = nullptr;
};

template <typename T>
class SingleLinkedList{
private:
    Node<T> *head;
    Node<T> *tail;
    int _size = 0;
    
    Node<T>* createNode(T value);
    
public:
    SingleLinkedList();
    ~SingleLinkedList();
    
    void push_front(T value);
    void push_back(T value); 
    void pop_front();
    void pop_back(); 
    
    void insert(int pos, T value);
    bool remove(T value);
    void printList();
    int size();
    
    void reverse();
    void sort();
};

// 새로운 노드를 반환
template <typename T>
Node<T>* SingleLinkedList<T>::createNode(T value){
    Node<T> *node = new Node<T>;
    node->value = value;
    node->next = nullptr;
    
    return node;
}

// 생성자
template <typename T>
SingleLinkedList<T>::SingleLinkedList(){
    head = nullptr;
    tail = nullptr;
}

// 소멸자. 할당된 노드들을 지움.
template <typename T>
SingleLinkedList<T>::~SingleLinkedList(){
    while(head){
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
}

// 가장 앞에 노드를 추가
template <typename T>
void SingleLinkedList<T>::push_front(T value){
    // 새로운 노드 생성
    Node<T>* node = createNode(value);
    
    // 다른 노드가 존재하는 경우, head 앞에 붙이고 head를 업데이트.
    if (head){
        node->next = head;
        head = node;
    }
    // 다른 노드가 없는 경우, head와 tail을 node로 지정.
    else{
        head = node;
        tail = node;
    }
    
    _size++;
}

// 가장 뒤에 노드를 추가
template <typename T>
void SingleLinkedList<T>::push_back(T value){
    // 새로운 노드 생성
    Node<T>* node = createNode(value);
    
    // 다른 노드가 존재하는 경우, tail 뒤에 붙이고 tail을 업데이트.
    if (tail){
        tail->next = node;
        tail = node;
    }
    // 다른 노드가 없는 경우, head와 tail을 node로 지정.
    else{
        head = node;
        tail = node;
    }
    
    _size++;
}

// 가장 앞의 노드를 제거
// 원소가 없을 때, 호출할 경우 error throw
template <typename T>
void SingleLinkedList<T>::pop_front(){
    if (head){
        if (head == tail){ // 노드가 하나밖에 없을 경우.
            delete head;
            head = tail = nullptr;
            return;
        }
        
        Node<T> *node = head; // 변수 node에 head가 가리키는 노드를 저장.
        
        head = head->next; // head가 가리키는 노드를 다음 노드로 바꾸어줌
        delete node; // 기존의 head가 가리키는 노드를 제거(pop)
        
        _size--;
    }
    else{
        throw Error::ElementEmpty;
    }
} 

// 가장 뒤의 노드를 제거
// 원소가 없을 때, 호출할 경우 error throw
template <typename T>
void SingleLinkedList<T>::pop_back(){
    if (tail){
        if (head == tail){ // 노드가 하나밖에 없을 경우.
            delete head;
            head = tail = nullptr;
            return;
        }
        
        Node<T> *node = head; // 변수 node에 head가 가리키는 노드를 저장.
        
        while(node->next != tail) // node의 값을 tail 바로 전 노드로 만듬.
            node = node->next;
        
        tail = node; // tail에 마지막에서 두번째 노드를 저장
        node = node->next; // node에 마지막 노드를 저장
        tail->next = nullptr; // 마지막에서 두번째 노드가 마지막 노드가 될 것이니, next 값을 지워줌.
        
        delete node; // 마지막 노드를 삭제
        
        _size--;
    }
    else{
        throw Error::ElementEmpty;
    }
} 

// index가 pos인 곳에 value를 삽입
// pos가 원소 개수이상일 경우 가장 뒤에 삽입
// pos가 0 이하일경우 가장 앞에 삽입.
template <typename T>
void SingleLinkedList<T>::insert(int pos, T value){
    // pos가 _size보다 크거나 같은 경우는 가장 뒤에 삽입해줌.
    if (pos >= _size){
        push_back(value);
        return;
    }
    // pos가 0보다 작거나 같은 경우는 가장 앞에 삽입해줌.
    else if (pos <= 0){
        push_front(value);
        return;
    }
    
    // 새로운 노드 생성
    Node<T>* node = createNode(value);
    
    // 삽입할 위치 바로 앞 노드
    Node<T> *prevNode = head;
    for(int i = 0; i < pos - 1; i++) 
        prevNode = prevNode->next;
    
    // prevNode와 (prevNode->next) 사이에 node를 넣어줌.
    node->next = prevNode->next;
    prevNode->next = node;
    
    _size++;
}

// value를 값으로 가지는 노드를 제거.
// 노드를 제거할 시 true 반환, 제거하지 않을 시 false 반환.
template <typename T>
bool SingleLinkedList<T>::remove(T value){
    // linkedList가 비어있는 경우
    if (!head)
        return false;
    
    Node<T> *node = head;
    Node<T> *prevNode = head;
    
    // value 값을 가진 node를 찾는 과정
    while(node){
        if (node->value == value)
            break;
        
        prevNode = node;
        node = node->next;
    }
    
    // 값과 일치하는 노드가 없는 경우
    if (!node){
        return false;
    }
    // 값과 일치하는 노드가 있는 경우
    else{
        // LinkedList에 원소가 하나밖에 없는 경우.
        if (_size == 1){
            head = tail = nullptr;
        }
        else{
            prevNode->next = node->next;
            
            if (node == head){
                head = node->next;
            }
            else if (node == tail){
                tail = prevNode;
            }
        }
        
        _size--;
        delete node;
        
        return true;
    }
    
}

template <typename T>
void SingleLinkedList<T>::printList(){
    Node<T>* node = head;
    
    while(node){
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

template <typename T>
int SingleLinkedList<T>::size(){
    return _size;
}

template <typename T>
void SingleLinkedList<T>::reverse(){
    if (!head)  return;
    
    Node<T>* prev = nullptr;
    Node<T>* node = head;
    
    // 현재 node의 next를 이전 node로 바꾸어줌
    while(node){
        Node<T>* tmp = node->next;
        
        node->next = prev;
        
        prev = node;
        node = tmp;
    }
    
    // swap 
    Node<T>* tmp = head;
    head = tail;
    tail = tmp;
}