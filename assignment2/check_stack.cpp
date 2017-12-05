#include "stack.h"
#include <iostream>

using namespace std;

int main(){
    Stack<int> s; 
    s.Push(1);
    s.Push(2);
    s.Push(3);
    while(s.IsEmpty() == false){
        cout << s.Top() << endl;
        s.Pop();
    }
    return 0;
}
