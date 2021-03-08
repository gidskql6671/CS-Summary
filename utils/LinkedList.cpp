/* Linked List 구현 */


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
    int size = 0;
    
public:
    SingleLinkedList();
    ~SingleLinkedList();
    
    void push_front(T value);
    void push_back(T value);
    void pop_front();
    void pop_back();
    
    void insert(T value, int pos);
    void remove(T value);
    void printList();
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList(){
    head = nullptr;
    tail = nullptr;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList(){
    while(head){
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <typename T>
void SingleLinkedList<T>::push_front(T value){
    Node<T> *node = new Node<T>;
    
    node->value = value;
    node->next = nullptr;
    
    if (head){
        node->next = head;
        head = node;
    }
    else{
        head = node;
        tail = node;
    }
}

template <typename T>
void SingleLinkedList<T>::push_back(T value){
    Node<T> *node = new Node<T>;
    
    node->value = value;
    node->next = nullptr;
    
    if (tail){
        tail->next = node;
        tail = node;
    }
    else{
        head = node;
        tail = node;
    }
}