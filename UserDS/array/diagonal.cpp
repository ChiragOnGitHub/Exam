#include <iostream>
using namespace std;

class diagonal{
    int *A;
    int size;

    public:
    diagonal();
    diagonal(int size);
    ~diagonal();
    int get(int i,int j);
    void set(int i,int j,int val);
};


diagonal:: diagonal(){
    size=0;
}

diagonal:: diagonal(int s){
    size=s;
    A = new int[size];
    for(int i=0;i<size;i++){
        *(A+i)=0;
    }
 }

diagonal:: ~diagonal(){
    delete[] A;
}

//implementation of get() function
int diagonal:: get(int i,int j){
    if(i>size||i<=0 || j>size || j<=0){
        throw invalid_argument("not a valid position");
    }
    if(i==j){
        int k = i-1;
        return *(A+k);
    }
    else
        return 0;
}

//timplementation of set() function
void diagonal:: set(int i,int j,int val){
    int k;
    if((i!=j && val!=0) || i>size || i<=0 || j>size || j<=0)
        throw invalid_argument("not a position for diagonal element");
    else{
        k = i-1;
        *(A+k) = val;
    }
}

int main(){
    int s;
    cout<<"Enter the order of the matrice: ";
    cin>>s;
    diagonal mat(s);
    int op=0;
    while(op!=3){
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
            default:
                break;
        }
    }
}

