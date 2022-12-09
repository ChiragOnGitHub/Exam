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
    Node<T>* head;

    public:
    LinkedList(){
        head=NULL;
    }
    ~LinkedList(){
        while(head!=NULL){
            removeFromHead();
        }
    }

    void removeFromHead(){
        Node<T>* temp=head;
        head=head->next;
        delete temp;
    }

    void insertAtHead(T data){
        Node<T>* temp=new Node<T>(data);
        temp->next=head;
        head=temp;
    }

    T displayHead(){
        return head->element;
    }
};

template <typename T>
class Stack{
    LinkedList<T> stack;
    int numOfElements;

    public:
    Stack(){
        numOfElements=0;
    }
    void push(T data){
        stack.insertAtHead(data);
        numOfElements++;
    }
    int pop(){
        if(numOfElements==0){
            return -1;
        }
        stack.removeFromHead();
        numOfElements--;
    }
    T top(){
        if(numOfElements==0){
            return -1;
        }
        return stack.displayHead();
    }

};

int main()
{
    Stack<int> s;
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