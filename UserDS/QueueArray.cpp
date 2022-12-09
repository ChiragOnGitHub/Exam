#include <iostream>
using namespace std;

template <class T>
class Queue{
    private:
        T *arr;
        int capacity; // capacity of queue
        
        int front;
        int numOfElements;

    public:
        Queue(int num){
            arr= new T[num];
            front=0;
            capacity=num;
            numOfElements=0;
        }

        int enqueue(T num){
            if(isFull()){
                return -1;
            }

            int rear=(front+numOfElements)%capacity;
            arr[rear]=num;
            numOfElements++;
        }

        int dequeue(){
            if(isEmpty())
                return -1;

            front=(front+1)%capacity;
            numOfElements--;
            return 0;
        }

        int getFront(){
            if(isEmpty())
                return -1;
            return arr[front];
        }
        
        bool isEmpty(){
            return numOfElements==0;
        }

        bool isFull(){
            return numOfElements==capacity;
        }

};

int main()
{   
    int capacity;
    cout<<"Enter capacity of Queue : ";
    cin>>capacity;

    int value,option;

    Queue<int> a(capacity);
    
    do{   
        cout<<endl;
        cout<<"Press 1 for Enqueue : "<<endl;
        cout<<"Press 2 for Dequeue : "<<endl;
        cout<<"Press 3 to access front element : "<<endl;
        cout<<"Press 4 to quit : "<<endl;
        cout<<endl;

        cout<<"Enter Your Choice : "<<endl;
        cin>>option;

        switch (option)
        {
        case 1:
            if(a.isFull()){
                cout<<"Overflow !! ";
            }
            else{
                cout<<"Enter the Number :";
                cin>>value;
                a.enqueue(value);
                cout<< value<<" is enqueued in the queue "<<endl;
            }
            break;

        case 2:
            if(a.isEmpty()){
                cout<<"Underflow !! ";
            }
            else{
                a.dequeue();
                cout<<"Element is dequeued from the queue "<<endl;
            }
            break;
        
        case 3:
            if(a.isEmpty()){
                cout<<"Underflow!! "<<endl;
            }
            else{
                cout<<"Front element is : "<<a.getFront()<<endl;
            }
            break;

        case 4:
            break;
            
        default:
            cout<<"Invalid Choice !!"<<endl;
            break;
        }
    }
    while(option!=4);

    return 0;
}