#include <iostream>
#include "utils/Queue.cpp"
using namespace std;


int main(){
    Queue<int> queue(5);
    
    while(true){
        int value;
        cin >> value;
        
        if (value == -1)
            break;
        else if (value == 0)
            printf("pop : %d\n", queue.pop());
        else
            queue.push(value);
        
        printf("queue size : %d, front & rear : %d & %d\n", queue.size(), queue.ff(), queue.rr());
    }
    
    return 0;
} 