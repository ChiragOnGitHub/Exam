#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
    
    T element;
    Node<T>* next;
    Node<T>* prev;

    Node(T data){
        element=data;
        next=NULL;
        prev=NULL;
    }
};


template <typename T>
class DoublyLinkedList{
    public:
    Node<T>* front;
    Node<T>* rear;

    DoublyLinkedList(){
        front=NULL;
        rear=NULL;
    }
    ~DoublyLinkedList(){
        while(front!=NULL){
            deleteFromfront();   
        }
    }
    void insertAtfront(T data){
        Node<T>* temp=new Node<T>(data);
        if(front==NULL){
            front=temp;
            rear=temp;
        }
        else{
            temp->next=front;
            front->prev=temp;
            front=temp;
        }
    }
    void deleteFromfront(){
        if(front==rear){
            delete front;
            front=NULL;
            rear=NULL;
        }
        else{
            Node<T>* temp=front;
            front=temp->next;
            front->prev=NULL;
            delete temp;
        }
    }
    void insertAtRear(T data){
        Node<T>* temp=new Node<T>(data);
        if(front==NULL){
            front=temp;
            rear=temp;
        }
        else{
            rear->next=temp;
            temp->prev=rear;
            rear=temp;
        }
    }

    void deleteFromRear(){
        if(front==rear){
            delete rear;
            front=NULL;
            rear=NULL;
        }
        else{
            Node<T>* temp=rear;
            rear=rear->prev;
            rear->next=NULL;
            delete temp;
        }
    }

    T getFront(){
        return front->element;
    }

    T getRear(){
        return rear->element;
    }

};


template <typename T>
class DEQUE{
    DoublyLinkedList<T> queue;
    int numOfElements;

    public:
    DEQUE(){
        numOfElements=0;
    }
    void insertFront(T data){
        queue.insertAtfront(data);
        numOfElements++;
    }
    void insertRear(T data){
        queue.insertAtRear(data);
        numOfElements++;
    }
    int deleteFront(){
        if(numOfElements==0){
            return -1;
        }
        queue.deleteFromfront();
        numOfElements--;
    }
    int deleteRear(){
        if(numOfElements==0){
            return -1;
        }
        queue.deleteFromRear();
        numOfElements--;
    }
    T Front(){
        if(numOfElements==0){
            return -1;
        }
        
        return queue.getFront();
    }
    T Rear(){
        if(numOfElements==0){
            return -1;
        }
        
        return queue.getRear();
    }

};

int main()
{
    DEQUE<int> s;
    s.insertFront(0);
    s.insertFront(10);
    s.insertRear(20);
    s.insertRear(30);

    cout<<s.Front()<<" ";
    cout<<s.Rear()<<" ";
    cout<<endl;

    s.deleteFront();
    cout<<s.Front()<<" ";
    cout<<s.Rear()<<" ";
    cout<<endl;

    s.deleteRear();
    cout<<s.Front()<<" ";
    cout<<s.Rear()<<" ";
    cout<<endl;

    s.deleteFront();
    cout<<s.Front()<<" ";
    cout<<s.Rear()<<" ";
    cout<<endl;
    
    return 0;
}