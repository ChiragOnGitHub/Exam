#include <iostream>
using namespace std;

template <typename T>
class Stack{
    T* stack;
    int topPointer;
    int size;

    public:

    Stack(int s){
        stack=new T(s);
        topPointer=-1;
        size=s;
    }
    ~Stack(){
        delete [] stack;
    }

    int push(T element){
        if(isFull()){
            return -1;
        }
        stack[++topPointer]=element;
        return 0;
    }

    int pop(){
        if(isEmpty()){
            return -1;
        }
        topPointer--;
    }

    T top(){
        if(isEmpty()){
            return 0;
        }
        return stack[topPointer];
    }

    bool isFull(){
        return topPointer==size-1;
    }

    bool isEmpty(){
        return topPointer<0;
    }
};

int main(){
    Stack<int> s(3);
    s.push(0);
    s.push(10);
    s.push(20);
    s.push(30);
    cout<<s.top()<<" ";
    s.pop();
    cout<<s.top()<<" ";
    s.pop();
    cout<<s.top()<<" ";
    s.pop();
    cout<<s.top()<<" ";
    s.pop();
    return 0;
}