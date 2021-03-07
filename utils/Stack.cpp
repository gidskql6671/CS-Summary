// Stack 구현. 설정된 size가 초과될 경우 size를 doubling 함
#ifndef MY_ERROR // include guard
#define MY_ERROR
#include "Error.cpp"
#endif


class Stack{
private:
    int top, maxSize;
    char *stack;
public:
    Stack(int size = 10);
    
    bool isFull();
    bool isEmpty();
    
    int push(int value);
    int pop();
    
    void printStackSize();
    void printStack();
    void printTop();
};

Stack::Stack(int size){
    maxSize = size;
    stack = new char[maxSize];
    top = -1;
}


bool Stack::isFull(){
    if (top >= maxSize)
        return true;
    else
        return false;
}
bool Stack::isEmpty(){
    if (top <= -1)
        return true;
    else
        return false;
}


int Stack::push(int value){
    top++;
    
    // 스택이 모두 차면, size doubling 해준다.
    if (isFull()){
        char *newStack = new char[maxSize * 2];
        for (int i = 0; i < maxSize; i++)
            newStack[i] = stack[i];
        delete[] stack;
        stack = newStack;
        
        maxSize *= 2;
    }
    
    stack[top] = value;
    return stack[top];
}
// 원소가 없을 시, Error.cpp의 Error 발생
int Stack::pop(){
    if (isEmpty())
         throw Error::StackEmpty;
    else
        return stack[top--];
}


void Stack::printStackSize(){
    printf("maxSize : %d\n", maxSize);
}
void Stack::printStack(){
    for(int i = top; i >= 0; i--)
        printf("상단으로부터 %d번째 값 : %d\n", top - i + 1, stack[i]);
}
void Stack::printTop(){
    printf("Stack top : %d\n", top);
}