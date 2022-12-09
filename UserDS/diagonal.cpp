#include <iostream>
using namespace std;
template <typename T>
class diagonal{
    T *A;
    int size;
    public:
    diagonal();
    diagonal(int size);
    ~diagonal();
    T get(int i,int j);
    int set(int i,int j,T val);
};

template <typename T>
 diagonal<T>:: diagonal(){
    size=0;
}

template <typename T>
 diagonal<T>:: diagonal(int size){
    this->size=size;
    A = new T[size];
 }

template <typename T>
diagonal<T>:: ~diagonal(){
    delete A;
}

//implementation of get() function
template <typename T>
T diagonal<T>:: get(int i,int j){
    if((i>size||i<0) || (j>size || j<0)){
        throw invalid_argument("not a valid position");
    }
    if(i==j){
        int k = i-1;
        return *(A+k);
    }
    else
        return NULL;
}

//timplementation of set() function
template <typename T>
int diagonal<T>:: set(int i,int j,T val){
    int k;
    if(i!=j || (i>size || i<0) || (j>size || j<0))
    throw invalid_argument("not a position for diagonal element");
    else{
        k = i-1;
        *(A+k) = val;
        return 0;
    }
}

int main(){
    int s;
    cout<<"Enter the order of the matrice: ";
    cin>>s;
    diagonal <int>mat(s);
    int op;
    while(true){
        cout<<"\n";
        cout<<"Enter the choice: \n1. set a value in the matrix \n2.get a value from matrix\n3.to exit\n";
        cin>>op;
        cout<<"\n";
        switch(op){
            case 1:
                try{
                    int row,col,val;
                    cout<<"Enter the row value: ";
                    cin>>row;
                    cout<<"Enter the column value: ";
                    cin>>col;
                    cout<<"Enter the value to be set: ";
                    cin>>val;
                    mat.set(row,col,val);
                }
                catch(invalid_argument& e){
                    cout<<e.what()<<endl;
                }
            break;
            case 2:
                try{
                    int row,col;
                    cout<<"Enter the row value: ";
                    cin>>row;
                    cout<<"Enter the column value: ";
                    cin>>col;
                    cout<<"Value: "<<mat.get(row,col)<<endl;
                }
                catch(invalid_argument& e){
                    cout<<e.what()<<endl;
                }
            break;
            case 3:
                break;
            default:
                break;
        }
    }
}

