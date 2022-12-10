#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
class Node{
    public:
        T value;
        Node<T>* leftChild;
        Node<T>* rightChild;

    Node(T data){
        leftChild=NULL;
        rightChild=NULL;
        value=data;
    }
};


template <typename T>
class BinarySearchTree{

    public:
    Node<T>* root;

    BinarySearchTree(){
        root=NULL;
    }

    int insert(int data){
        Node<T>* temp=new Node<T>(data);
        if(root==NULL){
            root=temp;
            return 0;
        }
        else{
            Node<T>* curr=root;
            while(true){
                if(curr->value==data){
                    return -1;
                }
                else if(data>curr->value){
                    if(curr->rightChild==NULL){
                        curr->rightChild=temp;
                        return 0;
                    }
                    curr=curr->rightChild;
                }
                else{
                    if(curr->leftChild==NULL){
                        curr->leftChild=temp;
                        return 0;
                    }
                    curr=curr->leftChild;
                }
            }
        }
    }

    void levelorderTraversal(){
        if(root==NULL){
            return;
        }
        queue<Node<T>*> q;
        q.push(root);
        while(!q.empty()){
            cout<<q.front()->value<<" ";
            if(q.front()->leftChild!=NULL)
                q.push(q.front()->leftChild);
            if(q.front()->rightChild!=NULL)
                q.push(q.front()->rightChild);
            q.pop();
        }
    }

    void preorder(Node<T>* r){
        if(r!=NULL){
            cout<<r->value<<" ";
            preorder(r->leftChild);
            preorder(r->rightChild);
        }
    }

    void inorder(Node<T>* r){
        if(r!=NULL){
            inorder(r->leftChild);
            cout<<r->value<<" ";
            inorder(r->rightChild);
        }
    }
    void postorder(Node<T>* r){
        if(r!=NULL){
            postorder(r->leftChild);
            postorder(r->rightChild);
            cout<<r->value<<" ";
        }
    }

    int height(Node<T>* r){
        if(r==NULL){
            return 0;
        }
        return max(height(r->leftChild),height(r->rightChild)) + 1;
    }

    //print top node(starting from root) then add its right and left node into the stack and repeat
    void iterativePreorder(){
        if(root==NULL){
            return;
        }
        stack<Node<T>*> s;
        s.push(root);
        Node<T>* temp;
        while(!s.empty()){
            temp=s.top();
            cout<<temp->value<<" ";
            s.pop();
            if(temp->rightChild!=NULL)
                s.push(temp->rightChild);
            if(temp->leftChild!=NULL)
                s.push(temp->leftChild);
        }
    }

    //push the node into the stack and move to the left node
    //repeat it until there is no left node
    //then print top of the stack and move to the right node and repeat!!
    void iterativeInorder(){
        if(root==NULL){
            return;
        }
        stack<Node<T>*> s;
        Node<T>* curr=root;
        while(!s.empty()||curr!=NULL){
            while(curr!=NULL){
                s.push(curr);
                curr=curr->leftChild;
            }
            curr=s.top();
            s.pop();
            cout<<curr->value<<" ";
            curr=curr->rightChild;
        }
    }

    //remove top element(root is present in starting) from stack 1 and add it to the stack 2
    //add left and right node of the removed element in the stack 1 itself and repeat this
    //print stack 2 after all this
    void iterativePostorder(){
        if(root==NULL){
            return;
        }
        stack<Node<T>*> s1,s2;
        s1.push(root);
        Node<T>* curr=root;
        while(!s1.empty()){
            curr=s1.top();
            s1.pop();
            s2.push(curr);
            if(curr->leftChild!=NULL)
                s1.push(curr->leftChild);
            if(curr->rightChild!=NULL)
                s1.push(curr->rightChild);
        }

        while(!s2.empty()){
            cout<<s2.top()->value<<" ";
            s2.pop();
        }
    }

    Node<T>* search(int data){
        Node<T>* curr=root;
        while(true){
            if(curr==NULL){
                return NULL;
            }
            else if(curr->value==data){
                return curr;
            }
            else if(data > curr->value){
                curr=curr->rightChild;
            }
            else{
                curr=curr->leftChild;
            }
        }
    }

    //initially find the node which need to be deleted and its parent node
    //after this assign new left or right child to the parent or new root
    int deleteByMerging(T data){
        Node<T>* prev=NULL;
        Node<T>* curr=root;
        while(true){
            if(curr==NULL){
                break;
            }
            else if(curr->value==data){
                break;
            }
            else if(data > curr->value){
                prev=curr;
                curr=curr->rightChild;
            }
            else{
                prev=curr;
                curr=curr->leftChild;
            }
        }

        if(curr==NULL){
            return -1;
        }
        else{
            if (curr == root)
                root=deleteRootByMerge(curr);
            else if (prev->leftChild == curr)
                prev->leftChild=deleteRootByMerge(curr);
            else 
                prev->rightChild=deleteRootByMerge(curr);
        }
    }

    Node<T>* deleteRootByMerge(Node<T>*& node){
        Node<T>* temp=node;
        if(node!=NULL){
            if(node->rightChild==NULL){
                node=node->leftChild;
            }
            else if(node->leftChild==NULL){
                node=node->rightChild;
            }
            else{
                temp=temp->leftChild;
                while(temp->rightChild!=NULL){
                    temp=temp->rightChild;
                }
                temp->rightChild=node->rightChild;
                temp=node;
                node=node->leftChild;
            }
            delete temp;
            return node;
        }
    }


    //recursive method to delete a node by copy
    //just making tree slowly from root till leaf
    Node<T>* delByCopy(Node<T>* r,T x){
        if(r==NULL)
            return NULL;
        if(r->value>x)
            r->leftChild=delByCopy(r->leftChild,x);
        else if(r->value<x)
            r->rightChild=delByCopy(r->rightChild,x);
        else{
            //node to be deleted is found here and now deleting work start!!
            //above this else block we are just finding the node to be deleted
            if(r->leftChild==NULL){
                Node<T> *temp=r->rightChild;
                delete r;
                return temp;
            }
            else if(r->rightChild==NULL){
                Node<T> *temp=r->leftChild;
                delete r;
                return temp;
            }
            else{
                //both of the child of the node to be deleted is present hence
                //we substitute the value of root by right inorder successor and 
                //make another rec. call to delete successor in right child
                Node<T> *succ=getSuccessor(r);
                r->value=succ->value;
                r->rightChild=delByCopy(r->rightChild,succ->value);
            }
        }
        return r;
    } 

    Node<T>* getSuccessor(Node<T> *curr){
        curr=curr->rightChild;
        while(curr!=NULL && curr->leftChild!=NULL)
            curr=curr->leftChild;
        return curr;
    }
    
    int changeXtoY(T x,T y){
        Node<T>* change=search(x);
        Node<T>* tochange=search(y);
        
        if(change==NULL || tochange!=NULL){
            return -1;
        }
        deleteByMerging(x);
        insert(y);
        inorder(root);
        cout<<endl;
    }
};


int main(){
    BinarySearchTree<int> a;
    a.insert(20);
    a.insert(10);
    a.insert(30);
    a.insert(70);
    a.insert(40);
    a.insert(50);
    a.insert(60);
    a.insert(15);
    
    return 0;
}