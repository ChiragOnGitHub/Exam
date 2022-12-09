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
    Node<T>* head;
    Node<T>* tail;

        DoublyLinkedList(){
            head=NULL;
            tail=NULL;
        }
        ~DoublyLinkedList(){
            while(head!=NULL){
                deleteFromHead();   
            }
        }
        void insertAtHead(T data){
            Node<T>* temp=new Node<T>(data);
            if(head==NULL){
                head=temp;
                tail=temp;
            }
            else{
                temp->next=head;
                head->prev=temp;
                head=temp;
            }
        }
        int deleteFromHead(){
            if(head==NULL){
                return -1;
            }
            else if(head==tail){
                delete head;
                head=NULL;
                tail=NULL;
            }
            else{
                Node<T>* temp=head;
                head=temp->next;
                head->prev=NULL;
                delete temp;
            }
        }

        void insertAtTail(T data){
            Node<T>* temp=new Node<T>(data);
            if(head==NULL){
                head=temp;
                tail=temp;
            }
            else{
                tail->next=temp;
                temp->prev=tail;
                tail=temp;
            }
        }

        int deleteFromTail(){
            if(head==NULL){
                return -1;
            }
            else if(head==tail){
                delete tail;
                head=NULL;
                tail=NULL;
            }
            else{
                Node<T>* temp=tail;
                tail=tail->prev;
                tail->next=NULL;
                delete temp;
            }
        }

        int insertAtPos(T data,int pos){
            Node<T>* node=new Node<T>(data);
            if(pos==1){
                if(head==NULL){
                    head=node;
                    tail=node;
                }
                else{
                    node->next=head;
                    head->prev=node;
                    head=node;
                }
            }
            else{
                if(head==NULL){
                    return -1;
                }
                Node<T>* curr=head;
                for(int i=0;i<pos-2;i++){
                    curr=curr->next;
                    if(curr==NULL){
                        return -1;
                    }
                }
                if(curr->next==NULL){
                    node->prev=curr;
                    curr->next=node;
                    tail=node;
                }
                else{
                    node->next=curr->next;
                    node->prev=curr;
                    curr->next->prev=node;
                    curr->next=node;
                }
            }
        }

        int DeleteFromPos(int pos){
            if(head==NULL){
                return -1;
            }
            if(pos==1){
                if(head==tail){
                    delete head;
                    head=NULL;
                    tail=NULL;
                }
                else{
                    Node<T>* temp=head;
                    head->next->prev=NULL;
                    delete head;
                }
            }
            else{
                Node<T>* curr= head;
                for(int i=0;i<pos-1;i++){
                    curr=curr->next;
                    if(curr==NULL){
                        return -1;
                    }
                }
                if(curr->next==NULL){
                    tail=curr->prev;
                    tail->next=NULL;
                    delete curr;
                }
                else{
                    curr->prev->next=curr->next;
                    curr->next->prev=curr->prev;
                    delete curr;
                }
            }
        }
        Node<T>* search(T data){
            Node<T>* curr=head;
            while(curr!=NULL){
                if(curr->element==data){
                    return curr;
                }
                curr=curr->next;
            }
            return NULL;
        }

        int display(){
            if(head==NULL){
                return -1;
            }
            Node<T>* curr=head;
            while(curr!=NULL){
                cout<<curr->element<<" ";
                curr=curr->next;
            }
            return 0;
        }

        int concatenate(Node<T>* h2){
            if(h2==NULL)
                return -1;
            else{
                Node<T>* curr = h2;
                while(curr->next!=NULL){
                    curr = curr->next;
                }
                tail->next = h2;
                h2->prev=tail;
                tail=curr;
                return 0;
            }
        }
};

int main(){
    DoublyLinkedList<int> c;
    DoublyLinkedList<int> s2;
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
                check=c.DeleteFromPos(p);
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
                if(s2.head!=NULL){
                    s2.head=NULL;
                    s2.tail=NULL;
                }
                for(int i=0;i<num;i++){
                    cout<<"Enter element "<<i+1<<" : "<<endl;
                    cin>>value;
                    c.insertAtTail(value);
                }
                c.concatenate(s2.head);
                cout<<"List concatenated successfully"<<endl;
                break;

            case 10:
                exit(0);
        }
    }

    return 0;
}