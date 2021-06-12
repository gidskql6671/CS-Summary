/* Linked List ���� */
#ifndef MY_ERROR // include guard
#define MY_ERROR
#include "../utils/Error.cpp"
#endif

// Linked List�� ���
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

// ���ο� ��带 ��ȯ
template <typename T>
Node<T>* SingleLinkedList<T>::createNode(T value){
    Node<T> *node = new Node<T>;
    node->value = value;
    node->next = nullptr;
    
    return node;
}

// ������
template <typename T>
SingleLinkedList<T>::SingleLinkedList(){
    head = nullptr;
    tail = nullptr;
}

// �Ҹ���. �Ҵ�� ������ ����.
template <typename T>
SingleLinkedList<T>::~SingleLinkedList(){
    while(head){
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ���� �տ� ��带 �߰�
template <typename T>
void SingleLinkedList<T>::push_front(T value){
    // ���ο� ��� ����
    Node<T>* node = createNode(value);
    
    // �ٸ� ��尡 �����ϴ� ���, head �տ� ���̰� head�� ������Ʈ.
    if (head){
        node->next = head;
        head = node;
    }
    // �ٸ� ��尡 ���� ���, head�� tail�� node�� ����.
    else{
        head = node;
        tail = node;
    }
    
    _size++;
}

// ���� �ڿ� ��带 �߰�
template <typename T>
void SingleLinkedList<T>::push_back(T value){
    // ���ο� ��� ����
    Node<T>* node = createNode(value);
    
    // �ٸ� ��尡 �����ϴ� ���, tail �ڿ� ���̰� tail�� ������Ʈ.
    if (tail){
        tail->next = node;
        tail = node;
    }
    // �ٸ� ��尡 ���� ���, head�� tail�� node�� ����.
    else{
        head = node;
        tail = node;
    }
    
    _size++;
}

// ���� ���� ��带 ����
// ���Ұ� ���� ��, ȣ���� ��� error throw
template <typename T>
void SingleLinkedList<T>::pop_front(){
    if (head){
        if (head == tail){ // ��尡 �ϳ��ۿ� ���� ���.
            delete head;
            head = tail = nullptr;
            return;
        }
        
        Node<T> *node = head; // ���� node�� head�� ����Ű�� ��带 ����.
        
        head = head->next; // head�� ����Ű�� ��带 ���� ���� �ٲپ���
        delete node; // ������ head�� ����Ű�� ��带 ����(pop)
        
        _size--;
    }
    else{
        throw Error::ElementEmpty;
    }
} 

// ���� ���� ��带 ����
// ���Ұ� ���� ��, ȣ���� ��� error throw
template <typename T>
void SingleLinkedList<T>::pop_back(){
    if (tail){
        if (head == tail){ // ��尡 �ϳ��ۿ� ���� ���.
            delete head;
            head = tail = nullptr;
            return;
        }
        
        Node<T> *node = head; // ���� node�� head�� ����Ű�� ��带 ����.
        
        while(node->next != tail) // node�� ���� tail �ٷ� �� ���� ����.
            node = node->next;
        
        tail = node; // tail�� ���������� �ι�° ��带 ����
        node = node->next; // node�� ������ ��带 ����
        tail->next = nullptr; // ���������� �ι�° ��尡 ������ ��尡 �� ���̴�, next ���� ������.
        
        delete node; // ������ ��带 ����
        
        _size--;
    }
    else{
        throw Error::ElementEmpty;
    }
} 

// index�� pos�� ���� value�� ����
// pos�� ���� �����̻��� ��� ���� �ڿ� ����
// pos�� 0 �����ϰ�� ���� �տ� ����.
template <typename T>
void SingleLinkedList<T>::insert(int pos, T value){
    // pos�� _size���� ũ�ų� ���� ���� ���� �ڿ� ��������.
    if (pos >= _size){
        push_back(value);
        return;
    }
    // pos�� 0���� �۰ų� ���� ���� ���� �տ� ��������.
    else if (pos <= 0){
        push_front(value);
        return;
    }
    
    // ���ο� ��� ����
    Node<T>* node = createNode(value);
    
    // ������ ��ġ �ٷ� �� ���
    Node<T> *prevNode = head;
    for(int i = 0; i < pos - 1; i++) 
        prevNode = prevNode->next;
    
    // prevNode�� (prevNode->next) ���̿� node�� �־���.
    node->next = prevNode->next;
    prevNode->next = node;
    
    _size++;
}

// value�� ������ ������ ��带 ����.
// ��带 ������ �� true ��ȯ, �������� ���� �� false ��ȯ.
template <typename T>
bool SingleLinkedList<T>::remove(T value){
    // linkedList�� ����ִ� ���
    if (!head)
        return false;
    
    Node<T> *node = head;
    Node<T> *prevNode = head;
    
    // value ���� ���� node�� ã�� ����
    while(node){
        if (node->value == value)
            break;
        
        prevNode = node;
        node = node->next;
    }
    
    // ���� ��ġ�ϴ� ��尡 ���� ���
    if (!node){
        return false;
    }
    // ���� ��ġ�ϴ� ��尡 �ִ� ���
    else{
        // LinkedList�� ���Ұ� �ϳ��ۿ� ���� ���.
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
    
    // ���� node�� next�� ���� node�� �ٲپ���
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