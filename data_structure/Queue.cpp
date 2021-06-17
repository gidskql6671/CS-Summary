// queue 구현. 설정된 size가 초과될 경우 size를 doubling 함
#ifndef MY_ERROR // include guard
#define MY_ERROR
#include "../utils/Error.cpp"
#endif

// Circular Queue로 구현 
template <typename T>
class Queue{
private:
    // _front는 가장 첫번째 원소 앞칸을 가리킴. 해당 칸은 항상 비어있는 상태임.
    // _rear는 가장 마지막 원소를 가리킴. 해당 칸이 비어있다면, queue가 비어있음
    int _front, _rear, _maxSize;
    T *_queue;
    
    void _sizeDoubling();
public:
    Queue(int size = 10);
    
    bool empty();
    
    void push(T value);
    T pop();
    
    T front();
    T back();
    int size();
};

template <typename T>
void Queue<T>::_sizeDoubling(){
    T *newQueue = new T[_maxSize * 2];
    
    // 모든 데이터가 차례대로 저장되어 있는 경우. (첫번째 데이터의 index가 0 또는 1인 경우)
    if ((_front + 1) % _maxSize <= 1 ){
        for(int i = (_front + 1) % _maxSize, j = 1; i < _maxSize; i++, j++)
            newQueue[j] = _queue[i];
    }
    else{
        int j = 1;
        for(int i = _front + 1; i < _maxSize; i++, j++)
            newQueue[j] = _queue[i];
        for(int i = 0; i < _rear; i++, j++)
            newQueue[j] = _queue[i];
    }
    
    delete[] _queue;
    _queue = newQueue;
    
    _front = 0;
    _rear = _maxSize - 1;
    
    _maxSize *= 2;
}

template <typename T>
Queue<T>::Queue(int size){
    _maxSize = size;
    _queue = new T[_maxSize];
    _front = _rear = 0;
}

template <typename T>
bool Queue<T>::empty(){
    if (_front == _rear)
        return true;
    else
        return false;
}

template <typename T>
void Queue<T>::push(T value){
    _rear = (_rear + 1) % _maxSize;
    
    if (_front == _rear){
        _sizeDoubling();
        
        return push(value);
    }
    
    _queue[_rear] = value;
}

// queue의 front에서 값을 빼옴.
// queue가 비어있으면 Error.cpp의 ElementEmpty 발생
template <typename T>
T Queue<T>::pop(){
    if (empty())
        throw Error::ElementEmpty;
    else{
        _front = (_front + 1) % _maxSize;
        return _queue[_front];
    }
}

template <typename T>
T Queue<T>::front(){
    if (empty())
        throw Error::ElementEmpty;
    else
        return _queue[(_front + 1) % _maxSize];
}

template <typename T>
T Queue<T>::back(){
    if (empty())
        throw Error::ElementEmpty;
    else
        return _queue[_rear];
}

template <typename T>
int Queue<T>::size(){
    return (_rear - _front + _maxSize) % _maxSize;
}