// Stack 구현. 설정된 size가 초과될 경우 size를 doubling 함

template <typename T> 
class Stack{
private:
    int _top, _maxSize;
    T *_stack;
    
    bool _isFull();
    void _sizeDoubling();
public:
    Stack(int size = 10);
    
    bool empty();
    
    void push(T value);
    T pop();
    
    T top();
    int size();
};


// 스택이 꽉차있는지 여부를 확인
template <typename T> 
bool Stack<T>::_isFull(){
    if (_top >= _maxSize)
        return true;
    else
        return false;
}

// 사이즈 더블링
template <typename T> 
void Stack<T>::_sizeDoubling(){
    T *newStack = new T[_maxSize * 2];
    
    for (int i = 0; i < _maxSize; i++)
        newStack[i] = _stack[i];
        
    delete[] _stack;
    
    _stack = newStack;
    _maxSize *= 2;
}

// 생성자. size 기본값 10
template <typename T> 
Stack<T>::Stack(int size){
    _maxSize = size;
    _stack = new T[_maxSize];
    _top = -1;
}

// 스택이 비어있는지 여부를 확인
template <typename T> 
bool Stack<T>::empty(){
    if (_top <= -1)
        return true;
    else
        return false;
}

// 스택에 value 값을 push해준다.
template <typename T> 
void Stack<T>::push(T value){
    _top++;
    
    // 스택이 모두 차면, size doubling 해준다.
    if (_isFull()){
        _sizeDoubling();
    }
    
    _stack[_top] = value;
}

// 스택의 가장 위의 원소를 꺼내어 반환한다.
// 원소가 없을 시, Error.cpp의 ElementEmpty 발생
template <typename T> 
T Stack<T>::pop(){
    if (empty())
         throw "Stack Empty";
    else
        return _stack[_top--];
}

// 스택의 top을 반환한다.
template <typename T> 
T Stack<T>::top(){
    if (empty())
         throw "Stack Empty";
    else
        return _stack[_top];   
}

// 현재 스택의 size를 반환한다.
template <typename T> 
int Stack<T>::size(){
    return _top + 1;
}