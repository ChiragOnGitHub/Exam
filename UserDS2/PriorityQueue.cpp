#include <iostream>
#include <limits.h>
using namespace std;

template <typename T>
class MinHeap{
    T* arr;
    int size;
    int capacity;

    int left(int i){
        return 2*i+1;
    }
    int right(int i){
        return 2*i+2;
    }
    int parent(int i){
        return (i-1)/2;
    }
    public:

    MinHeap(int c){
        arr=new T[c];
        size=0;
        capacity=c;
    }

    int insert(T data){
        if(capacity==size){
            return -1;
        }
        size++;
        arr[size-1]=data;
        int i=size-1;
        while(arr[parent(i)]>arr[i] && i!=0){
            swap(arr[parent(i)],arr[i]);
            i=parent(i);
        }
        return 0;
    }
    bool isFull(){
        return size==capacity;
    }
    bool isEmpty(){
        return size==0;
    }

    //transfer element at i pos. to its correct place
    int minHeapify(int i){
        int l=left(i);
        int r=right(i);
        int smallest=i;
        if(l<size && arr[l]<arr[smallest]){
            smallest=l;
        }
        if(r<size && arr[r]<arr[smallest]){
            smallest=r;
        }
        if(smallest!=i){
            swap(arr[i],arr[smallest]);
            minHeapify(smallest);
        }
    }

    T printMin(){
        if(size==0){
            return INT_MAX;
        }
        else
            return arr[0];
    }

    //extract the top element and maintain the heap
    T extractMin(){
        if(size==0){
            return INT_MAX;
        }
        if(size==1){
            size--;
            return arr[0];
        }
        swap(arr[0],arr[size-1]);
        size--;
        minHeapify(0);
        return arr[size];
    }
};

int main(){
    int size,value,choice=0;
    cout<<"Enter the capacity of the priority Queue : ";
    cin>>size;
    MinHeap<int> p(size);
    while(choice!=4){
        cout<<"\n";
        cout<<"Enter the choice: \n1. Push into the priority Queue \n2. Print Top of Priority Queue\n3. Pop From The Priority Queue\n4. For Exit";
        cout<<endl;
        cin>>choice;
        cout<<"\n";
        switch(choice){
            case 1:
                if(p.isFull())
                    cout<<"Priority Queue Is Full !! "<<endl;
                else{
                    cout<<"Enter element To Insert : ";
                    cin>>value;
                    p.insert(value);
                    cout<<endl;
                }
                break;
            case 2:
                if(p.isEmpty())
                    cout<<"Priority Queue Is Empty !! "<<endl;
                else{
                    cout<<"Top ELement is : "<<p.printMin();
                    cout<<endl;
                }
                break;
            case 3:
                if(p.isEmpty())
                    cout<<"Priority Queue Is Empty !! "<<endl;
                else{
                    p.extractMin();
                    cout<<endl;
                }
                break;
            default:
                break;
        }
    }
}