#include <iostream>
#include "utils/Stack.cpp"
using namespace std;


int main(){
    Stack stack(5);
    
    while(true){
        int value;
        cin >> value;
        
        if (value == -1)
            break;
        else if (value == 0)
            printf("pop : %d\n", stack.pop());
        else
            stack.push(value);
        
        stack.printStack();
        stack.printStackSize();
        stack.printTop();
    }
    
    return 0;
} 