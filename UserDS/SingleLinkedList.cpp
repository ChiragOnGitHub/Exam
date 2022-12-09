#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
    int element;
    Node<T>* next;

    Node(T data){
        element=data;
        next=NULL;
    }
};

template <typename T>
class SingleLinkedList{
    public:
    Node<T>* head;
    Node<T>* tail;

        SingleLinkedList(){
            head=NULL;
            tail=NULL;
        }
        ~SingleLinkedList(){
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
                return 0;
            }
            else{
                Node<T>* temp=head;
                head=head->next;
                delete temp;
                return 0;
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
                tail=temp;
            }
        }

        int deleteFromTail(){
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
            while(temp->next->next!=NULL){
                temp=temp->next;
            }
            temp->next=NULL;
            delete tail;
            tail=temp;}
        }
        int insertAtN(T data, int pos){
            Node<T>* temp=new Node<T>(data);

            if(pos==1){
                if(head==NULL){
                    head=temp;
                    tail=temp;
                }
                else{
                    temp->next=head;
                    head=temp;
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
                temp->next=curr->next;
                curr->next=temp;
                if(temp->next==NULL){
                    tail=temp;
                }
            }
        }

        int deleteAtN(int pos){
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
                    head=temp->next;
                    delete temp;
                }
            }
            else{
                Node<T>* temp=head;
                for(int i=0;i<pos-2;i++){
                    if(temp->next==NULL){
                        return -1;
                    }
                    temp=temp->next;
                }
                Node<T>* del=temp->next;
                temp->next=del->next;
                delete del;

                if(temp->next==NULL){
                    tail=temp;
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
            else{
                Node<T>* curr=head;
                while(curr!=NULL){
                    std::cout<<curr->element<<" ";
                    curr=curr->next;
                }
            }
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
                tail=curr;
                return 0;
            }
        }
};

int main(){
    SingleLinkedList<int> c;
    SingleLinkedList<int> s2;
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
                check=c.insertAtN(value,p);
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
                check=c.deleteAtN(p);
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


