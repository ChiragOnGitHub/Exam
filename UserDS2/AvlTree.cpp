#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
        T value;
        Node<T>* leftChild;
        Node<T>* rightChild;
        int height;

    Node(T data){
        leftChild=NULL;
        rightChild=NULL;
        value=data;
        height=1;
    }
};
template <typename T>
int height(Node<T>* r){
    if(r==NULL){
        return 0;
    }
    return r->height;
}


//          y                                      x 
//         / \                                   /    \
//        x   T4      Right Rotate (y)          T1     y
//       / \          - - - - - - - - ->              /  \ 
//      T1   T2                                      T2  T4
//this func. will right rotate the root node and return root of modified tree!!
template <typename T>
Node<T>* rightRotate(Node<T> *y)
{
    Node<T> *x = y->leftChild;
    Node<T> *T2 = x->rightChild;
 
    x->rightChild = y;
    y->leftChild = T2;
 
    // Update heights
    y->height = max(height(y->leftChild),
                    height(y->rightChild)) + 1;
    x->height = max(height(x->leftChild),
                    height(x->rightChild)) + 1;
 
    // Return new root
    return x;
}

//   x                                y
//  /  \                            /   \ 
// T1   y     Left Rotate(x)       x     T3
//     /  \   - - - - - - - ->    / \    
//    T2   T3                    T1  T2
//this function will left rotate the tree and return the root node of modified tree
template <typename T>
Node<T>* leftRotate(Node<T> *x)
{
    Node<T> *y = x->rightChild;
    Node<T> *T2 = y->leftChild;
 
    // Perform rotation
    y->leftChild = x;
    x->rightChild = T2;
 
    // Update heights
    x->height = max(height(x->leftChild),height(x->rightChild)) + 1;
    y->height = max(height(y->leftChild),height(y->rightChild)) + 1;
 
    // Return new root
    return y;
}

template <typename T>
int balanceFactor(Node<T>* r){
    if(r==NULL)
        return 0;
    return  height(r->leftChild)-height(r->rightChild);
}

//insert key into node's avl tree and return the new avl tree
template <typename T>
Node<T>* insert(Node<T>* node, int key)
{   
    //finding the place where we have to insert the key just like normal insertion
    if (node == NULL){
        Node<T>* newNode=new Node<T>(key);
        return newNode;
    }
    if (key < node->value)
        node->leftChild = insert(node->leftChild, key);
        //after inserting the element in left of this tree
        //we update its height and rotate it if balance factor is not right
    else if (key > node->value)
        node->rightChild = insert(node->rightChild, key);
        //after inserting the element in right of this tree
        //we update its height and rotate it if balance factor is not right
    else 
        return node;
 
    //we do all this procedure executing from nearest ancestor of the inserted node to the root!!

    //modify height of all ancestors, if no element is inserted,height remains same
    node->height = 1 + max(height(node->leftChild),height(node->rightChild));
 
    //finding balance factor of all ancestors node and is it is unbalanced then
    //do either of 4 cases to make it balanced and return balanced tree to above node
    int balance = balanceFactor(node);
 

    
    // Left Left Case
    //balance>1 means element inserted in left subtree
    //if value of left node is greater than key means key is inserted on left of left node
    if (balance > 1 && key < node->leftChild->value)
        return rightRotate(node);
 
    // Right Right Case
    //balance<-1 means element inserted in right subtree
    //if value of right node is less than key means key is inserted on right of right node
    if (balance < -1 && key > node->rightChild->value)
        return leftRotate(node);
 
    // Left Right Case
    //balance>1 means element inserted in left subtree
    //if value of left node is lesser than key means key is inserted on right of left node
    if (balance > 1 && key > node->leftChild->value)
    {
        node->leftChild = leftRotate(node->leftChild);
        return rightRotate(node);
    }
 
    // Right Left Case
    //balance<-1 means element inserted in right subtree
    //if value of right node is greater than key means key is inserted on left of right node
    if (balance < -1 && key < node->rightChild->value)
    {
        node->rightChild = rightRotate(node->rightChild);
        return leftRotate(node);
    }
 
    //if balance factor is balanced return the node itself
    return node;
}
template <typename T>
void preorder(Node<T>* r){
        if(r!=NULL){
            cout<<r->value<<" ";
            preorder(r->leftChild);
            preorder(r->rightChild);
        }
}

template <typename T>
Node<T>* deleteNode(Node<T>* root, int key) 
{ 
    //base condition of recursion
    if (root == NULL) 
        return root;

    //if root's value is greater than key, then key must be in left of it hence modify left
    if ( key < root->value ) 
        root->leftChild = deleteNode(root->leftChild, key); 
  
    //if root's value is less than key, then key must be in right of it hence modify right
    else if( key > root->value )
        root->rightChild = deleteNode(root->rightChild, key); 

    //this execute when we found node to be deleted
    else
    { 

        // node with either one child or no child 
        // means this is node we actually going to delete
        //just update root to the new tree after deleting the key
        if( (root->leftChild == NULL) ||(root->rightChild == NULL) ) 
        { 
            //temp stores left child
            //but if left child is null it stores right child
            Node<T>* temp = root->leftChild ? root->leftChild : root->rightChild;  
            
            // temp null means this node has no children thus make root equal to null
            if (temp == NULL) { 
                temp = root; 
                root = NULL; 
            } 
            //this executes when node has one child and temp points to it
            //hence assign the content of temp to root
            else {
                *root = *temp; // Copy the contents of the non-empty child 
            }
            // deleting temp because we have created it
            delete temp; 
        } 

        // when deleting node has two childer thus we just divide this process to further
        //smaller process until we get a single child or no child
        else
        { 
            //Get the inorder successor (smallest in the right subtree) 
            Node<T>* temp = minValueNode(root->rightChild); 
            // Copy the inorder successor's data to this node 
            root->value = temp->value;
            // Delete the inorder successor 
            root->rightChild = deleteNode(root->rightChild,temp->value); 
        } 
    } 
  
    // if the node that is just delted come here just return it
    if (root == NULL) 
        return root; 
  
    //this code is executed by all the ancestors of the deleting node from its parent to root
    //we update their height , if any changes
    //and check balane factor and modify tree, if required
    root->height = 1 + max(height(root->leftChild), height(root->rightChild)); 
  
    int balance = balanceFactor(root); 

    // Left Left Case 
    //balance>1 means something is deleted from right thus right rotation required 
    //if balance of left child is >=0 ( means left child has higher height on left ) just do right rotation on parent
    if (balance > 1 && balanceFactor(root->leftChild) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    //balance>1 means something is deleted from right thus right rotation required 
    //if balance of left child is < 0 then left rotate this node and then right rotate the parent 
    if (balance > 1 && balanceFactor(root->leftChild) < 0) 
    { 
        root->leftChild = leftRotate(root->leftChild); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    //balance<-1 means something is deleted from left thus left rotation required 
    //if balance of right child is <=0( means right child has higher height on right )just do right rotation on parent
    if (balance < -1 && balanceFactor(root->rightChild) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    //balance<-1 means something is deleted from left thus left rotation required 
    //if balance of right child is >0 then right rotate this node and then left rotate parent
    if (balance < -1 && balanceFactor(root->rightChild) > 0) 
    { 
        root->rightChild = rightRotate(root->rightChild); 
        return leftRotate(root); 
        
    } 
  
    //if node is balanced
    return root; 
} 

//return the leftmost node of the tree
template <typename T>
Node<T> * minValueNode(Node<T>* node) 
{ 
    Node<T>* current = node; 

    while (current->leftChild != NULL) 
        current = current->leftChild; 
    return current; 
} 

template <typename T>
void inorder(Node<T>* r){
    if(r!=NULL){
        inorder(r->leftChild);
        cout<<r->value<<" ";
        inorder(r->rightChild);
    }
}

template <typename T>
void postorder(Node<T>* r){
    if(r!=NULL){
        postorder(r->leftChild);
        postorder(r->rightChild);
        cout<<r->value<<" ";
    }
}


int main(){
    Node<int>* root =NULL;
    int choice=0;
    int num;
    while(choice!=7){

        cout<<"Enter 1 to insert an element "<<endl;
        cout<<"Enter 2 to delete an element "<<endl;
        cout<<"Enter 3 for Preorder Traversal of Avl Tree "<<endl;
        cout<<"Enter 4 for Inorder Traversal of Avl Tree "<<endl;
        cout<<"Enter 5 for Postorder Traversal of Avl Tree "<<endl;
        cout<<"Enter 6 to get height of tree "<<endl;
        cout<<"Enter 7 to EXIT "<<endl;
        cout<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter Number : ";
                cin>>num;
                cout<<endl;
                root=insert(root,num);
                break;
            case 2:
                cout<<"Enter Number : ";
                cin>>num;
                cout<<endl;
                root=deleteNode(root,num);
                break;
            case 3:
                cout<<"Pre order traversal of the AVL tree is : ";
                preorder(root);
                cout<<endl;
                break;
            case 4:
                cout<<"In order traversal of the AVL tree is : ";
                inorder(root);
                cout<<endl;
                break;
            case 5:
                cout<<"Post order traversal of the AVL tree is : ";
                postorder(root);
                cout<<endl;
                break;
            case 6:
                cout<<"Height of the AVL tree is :";
                cout<<height(root);
                cout<<endl;
            default:
                break;
        }
    }

    return 0;
}