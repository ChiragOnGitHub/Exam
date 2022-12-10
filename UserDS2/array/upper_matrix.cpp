#include <iostream>
using namespace std;

class upper_matrix{
    int *A;
    int size;

    public:
    upper_matrix();
    upper_matrix(int size);
    ~upper_matrix();
    int get(int i,int j);
    int set(int i,int j,int val);
};

upper_matrix::upper_matrix(){
    size = 0;
}


upper_matrix::upper_matrix(int size){
    this->size = size;
    A = new int[size];
    for (int i = 0; i < size; i++)
    {
        *(A+i)=0;
    }
    
}


upper_matrix:: ~upper_matrix(){
    delete[] A;
}


int upper_matrix:: set(int i,int j,int val){
    if((i>j && val!=0)||(i>size||i<=0)||(j>size || j<=0)){
        throw invalid_argument("invalid position to set a value");
    }
    else{
        int k;
        k = (size*(i-1))-((i-2)*(i-1)/2)+(j-1);
        *(A+k) = val;
        return 0;
    }
}


int upper_matrix:: get(int i,int j){
    if((i>size||i<=0)||(j>size || j<=0))
        throw invalid_argument("invalid positions");
    if(i>j)
        return 0;
    else{
        int k = (size*(i-1))-((i-2)*(i-1)/2)+(j-1);
        return *(A+k);
    }
}

int main(){
    int s;
    cout<<"Enter the order of the matrice: ";
    cin>>s;
    upper_matrix mat(s);
    int op;
    while(op!=3){
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
            default:
                break;
        }
    }
    return 0;
}