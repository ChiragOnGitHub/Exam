#include <iostream>
using namespace std;

template <typename T>
class Node{
    public: 

    T element;
    Node<T>* next;
    Node(T data){
        next=NULL;
        element=data;
    }
};

template <typename T>
class LinkedList{
    Node<T>* tail;

    public:
    LinkedList(){
        tail=NULL;
    }
    ~LinkedList(){
        while(tail!=NULL){
            removeFromHead();
        }
    }

    void removeFromHead(){
        if(tail->next==tail){
            tail=NULL;
        }
        else{
            Node<T>* temp=tail->next;
            tail->next=temp->next;
            delete temp;
        }
    }

    void insertAtTail(T data){
        Node<T>* temp=new Node<T>(data);
        if(tail==NULL){
            tail=temp;
            tail->next=tail;
        }
        else{
            temp->next=tail->next;
            tail->next=temp;
            tail=temp;
        }
    }

    T getFront(){
        return tail->next->element;
    }
};

template <typename T>
class Queue{
    LinkedList<T> queue;
    int numOfElements;

    public:
    Queue(){
        numOfElements=0;
    }
    void push(T data){
        queue.insertAtTail(data);
        numOfElements++;
    }
    int pop(){
        if(numOfElements==0){
            return -1;
        }
        queue.removeFromHead();
        numOfElements--;
    }
    T top(){
        if(numOfElements==0){
            return -1;
        }
        
        return queue.getFront();
    }

};

int main()
{
    Queue<int> s;
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