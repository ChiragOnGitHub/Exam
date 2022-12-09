#include <iostream>
using namespace std;
template<typename T>
class lower_matrix{
    T *A;
    int size;
    public:
    T val;
    lower_matrix();
    lower_matrix(int size);
    ~lower_matrix();
    T get(int i,int j);
    int set(int i,int j,T val);
};
template<typename T>
lower_matrix<T>::lower_matrix(){
    size = 0;
}

template<typename T>
lower_matrix<T>::lower_matrix(int size){
    this->size = size;
    A = new T[size];
}

template <typename T>
lower_matrix<T>:: ~lower_matrix(){
    delete A;
}

//implementation of set function
template <typename T>
int lower_matrix<T>:: set(int i,int j,T val){
    if((i>size||i<0)||(j>size || j<0))
        throw invalid_argument("invalid position to set a value");
    if(i<j){
        int temp = i;
        i=j;
        j = temp;
    }
        int k;
        k = (i*(i-1)/2)+(j-1);
        *(A+k) = val;
        return 0;
}


//implementation of get function
template <typename T>
T lower_matrix<T>:: get(int i,int j){
    if((i>size||i<0)||(j>size || j<0))
        throw invalid_argument("invalid positions");
    if(i<j){
        int temp = i;
        i = j;
        j = temp;
    }
    int k = (i*(i-1)/2)+(j-1);
    return *(A+k);
}

int main(){
    int s;
    cout<<"Enter the order of the matrice: ";
    cin>>s;
    lower_matrix <int>mat(s);
    int op;
    bool flag = true;
    while(flag){
        cout<<"\n";
        cout<<"Enter the choice: \n1. set a value in the matrix \n2.get a value from matrix\n3.to exit\n";
        cin>>op;
        cout<<"\n";
        switch(op){
            case 1:
                try{
                    int row,col;
                    int val;
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
                flag = false;
                break;
            default:
                break;
        }
    }
}