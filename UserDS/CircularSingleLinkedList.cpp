#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
    T element;
    Node<T>* next;

    Node(T data){
        element=data;
        next=NULL;
    }
};

template <typename T>
class CircularSingleLinkedList{
    public:
    Node<T>* tail;

    CircularSingleLinkedList(){
        tail=NULL;
    }
    ~CircularSingleLinkedList(){
        while(tail!=NULL){
            deleteFromTail();
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

    void insertAtHead(T data){
        Node<T>* temp= new Node<T>(data);
        if(tail==NULL){
            tail=temp;
            tail->next=tail;
        }
        else{
            temp->next=tail->next;
            tail->next=temp;
        }
    }

    int deleteFromHead(){
        if(tail==NULL){
            return -1;
        }
        else if(tail->next==tail){
            delete tail;
            tail=NULL;
        }
        else{
            Node<T>* temp=tail->next;
            tail->next=tail->next->next;
            delete temp;
        }
    }

    int deleteFromTail(){
        if(tail==NULL){
            return -1;
        }
        else if(tail->next==tail){
            delete tail;
            tail=NULL;
        }
        else{
            Node<T>* curr=tail->next;
            while(curr->next!=tail){
                curr=curr->next;
            }
            curr->next=tail->next;
            delete tail;
            tail=curr;
        }
    }

    int insertAtPos(T data, int pos){
        Node<T>* temp=new Node<T>(data);
        if(pos==1){
            insertAtHead(data);
        }
        else{
            if(tail==NULL){
                return -1;
            }
            else{
                Node<T>* curr=tail->next;
                for(int i=0;i<pos-2;i++){
                    curr=curr->next;
                    if(curr==tail->next){
                        return -1;
                    }
                }
                if(curr==tail){
                    tail=temp;
                }
                temp->next=curr->next;
                curr->next=temp;
            }
        }
    }

    void insertYAfterX(int y,int x){
        Node<T>* pos=search(x);
        if(pos==NULL){
            insertAtHead(y);
        }
        else{
            if(pos==tail){
                insertAtTail(y);
            }
            else{
                Node<T>* temp= new Node<T>(y);
                temp->next=pos->next;
                pos->next=temp;
            }
        }
    }

    int deleteX(int x){
        Node<T>* pos=search(x);
        if(pos==NULL){
            return -1;
        }
        else if(pos==tail){
            deleteFromTail();
        }
        else if(pos==tail->next){
            deleteFromHead();
        }
        else{
            Node<T>* prev=tail->next;
            while(prev->next!=pos){
                prev=prev->next;
            }
            prev->next=pos->next;
            delete pos;
        }
    }

    int deleteFromPos(int pos){
        if (tail==NULL){
            return -1;
        }
        else if(pos==1){
            return deleteFromHead();
        }
        else{
            Node<T>* curr=tail->next;
            for(int i=0;i<pos-2;i++){
                curr=curr->next;
                if(curr==tail){
                    return -1;
                }
            }
            Node<T>* temp=curr->next;
            if(curr->next==tail){
                tail=curr;
            }
            curr->next=curr->next->next;
            delete temp;

        }
    }
    int display(){
        if (tail==NULL){
            return -1;
        }
        else{
            Node<T>* curr=tail->next;
            do{
                cout<<curr->element<<" ";
                curr=curr->next;
            }
            while(curr!=tail->next);
        }
    }

    Node<T>* search(T data){
        if(tail==NULL){
            return NULL;
        }
        Node<T>* curr= tail->next;
        do{
            if(curr->element==data){
                return curr;
            }
            curr=curr->next;
        }
        while(curr!=tail->next);
        return NULL;
    }

    int concatenate(Node<T>* tl){
            if(tl==NULL)
                return -1;
            else{
                Node<T>* curr = tail->next;
                tail->next = tl;
                tail=tl;
                tl->next=curr;
                return 0;
            }
    }
};

int main(){
    CircularSingleLinkedList<int> c;
    CircularSingleLinkedList<int> s2;
    int choice;
    int value;
    int p;
    int check;

    cout<<endl;
    cout<<endl;
    cout<<"Press 1 to add element at Head "<<endl;
    cout<<"Press 2 to add element at Tail "<<endl;
    cout<<"Press 3 to add element at Any Position "<<endl;
    cout<<"Press 4 to remove element from Head "<<endl;
    cout<<"Press 5 to remove element from Tail "<<endl;
    cout<<"Press 6 to remove element from Any Position "<<endl;
    cout<<"Press 7 to search an element "<<endl;
    cout<<"Press 8 to display linked list "<<endl;
    cout<<"Press 9 to Concatenate a linked list "<<endl;
    cout<<"Press 10 to Quit "<<endl;
    cout<<endl;
    cout<<endl;

    while(true){
        cout<<endl;
        cout<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter element to add at head "<<endl;
                cin>>value;
                c.insertAtHead(value);
                break;
            case 2:
                cout<<"Enter element to add at tail "<<endl;
                cin>>value;
                c.insertAtTail(value);
                break;
            case 3:
                cout<<"Enter position : "<<endl;
                cin>>p;
                if(p<1){
                    cout<<"Postion must be greater than or equal to 1 ";
                }
                cout<<"Enter element to add at that position "<<endl;
                cin>>value;
                check=c.insertAtPos(value,p);
                if(check<0){
                    cout<<"Postion provided is not accurate !! ";
                }
                break;
            case 4:
                check=c.deleteFromHead();
                if(check<0){
                    cout<<"Linked List is Empty !!";
                    break;
                }
                cout<<"Element is removed from head "<<endl;
                break;
            case 5:
                check=c.deleteFromTail();
                if(check<0){
                    cout<<"Linked List is Empty !!";
                    break;
                }
                cout<<"Element is removed from tail "<<endl;
                break;
            case 6:
                cout<<"Enter position : "<<endl;
                cin>>p;
                if(p<1){
                    cout<<"Postion must be greater than or equal to 1 ";
                }
                check=c.deleteFromPos(p);
                if(check<0){
                    cout<<" Error Occurred !! ";
                }
                break;
            case 7:
                cout<<"Enter element to search "<<endl;
                cin>>value;
                Node<int>* temp;
                temp = c.search(value);
                if(temp==NULL){
                    cout<<"No, Element is not present "<<endl;
                }
                else{
                    cout<<"Yes, Element is present  "<<endl;
                }
                break;
            case 8:
                check=c.display();
                if(check<0){
                    cout<<"Linked List is empty ";
                }
                cout<<endl;
                break;
            case 9:
                int num;
                cout<<"How many element you want to insert in 2nd linked list ?";
                cin>>num;
                if(num<1){
                    cout<<"Element must be greater than 1 ";
                    break;
                }
                if(s2.tail!=NULL){
                    s2.tail=NULL;
                }
                for(int i=0;i<num;i++){
                    cout<<"Enter element "<<i+1<<" : "<<endl;
                    cin>>value;
                    c.insertAtTail(value);
                }
                c.concatenate(s2.tail);
                cout<<"List concatenated successfully"<<endl;
                break;

            case 10:
                exit(0);
        }
    }

    return 0;
}