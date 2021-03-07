// Stack ����. ������ size�� �ʰ��� ��� size�� doubling ��
#ifndef MY_ERROR // include guard
#define MY_ERROR
#include "Error.cpp"
#endif


template <typename T> 
class Stack{
private:
    int _top, _maxSize;
    T *_stack;
    
    bool _isFull();
public:
    Stack(int size = 10);
    
    bool empty();
    
    void push(T value);
    T pop();
    
    T top();
    int size();
};

// ������. size �⺻�� 10
template <typename T> 
Stack<T>::Stack(int size){
    _maxSize = size;
    _stack = new T[_maxSize];
    _top = -1;
}

// ������ �����ִ��� ���θ� Ȯ��
template <typename T> 
bool Stack<T>::_isFull(){
    if (_top >= _maxSize)
        return true;
    else
        return false;
}

// ������ ����ִ��� ���θ� Ȯ��
template <typename T> 
bool Stack<T>::empty(){
    if (_top <= -1)
        return true;
    else
        return false;
}

// ���ÿ� value ���� push���ش�.
template <typename T> 
void Stack<T>::push(T value){
    _top++;
    
    // ������ ��� ����, size doubling ���ش�.
    if (_isFull()){
        T *newStack = new T[_maxSize * 2];
        for (int i = 0; i < _maxSize; i++)
            newStack[i] = _stack[i];
        delete[] _stack;
        _stack = newStack;
        
        _maxSize *= 2;
    }
    
    _stack[_top] = value;
}

// ������ ���� ���� ���Ҹ� ������ ��ȯ�Ѵ�.
// ���Ұ� ���� ��, Error.cpp�� ElementEmpty �߻�
template <typename T> 
T Stack<T>::pop(){
    if (empty())
         throw Error::ElementEmpty;
    else
        return _stack[_top--];
}

// ������ top�� ��ȯ�Ѵ�.
template <typename T> 
T Stack<T>::top(){
    if (empty())
        throw Error::StackEmpty;
    else
        return _stack[_top];   
}

// ���� ������ size�� ��ȯ�Ѵ�.
template <typename T> 
int Stack<T>::size(){
    return _top + 1;
}