#include <iostream>
#include <limits.h>
using namespace std;

void read(int* arr, int size)   
{
    cout<<"Enter Matrix : ";
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cin>>arr[i * size + j];
        }
    }
}

void print3d(int* arr, int size)  
{
    
    for(int i = 0; i < size; i++)
    {
        cout<<"Node Number "<<i+1<<endl;
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < size; k++)
            {
                cout<<arr[i * size * 3 + j * size + k]<<"   ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

void constructInititalTable(int* arr, int* table, int size) 
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            table[i * size * 3 + j] = j+1;  
            if(arr[i * size + j] == -1)    
            {
                table[i * 3 * size + size + j] = INT_MAX; 
                table[i * 3 * size + 2 * size + j] = 0;         
            }

            else
            {
                table[i * size * 3 + size + j] = arr[i * size + j]; 
                table[i * size * 3 + 2 * size + j] = j+1;       
            }

            
        }
    }
}

void updateTable(int* arr, int* table, int size, int node)  
{
    for(int j = 0; j < size; j++)  
    {
        if(arr[node * size + j]!= -1)  
        {
            for(int k = 0; k < size; k++)  
            {
                if(table[node * size * 3 + size + k] > arr[node * size + j] + table[j * size * 3 + size + k] && table[node * 3 * size + 2 * size + k] != k + 1) 
                {                                                                                   
                    table[node * 3 * size + size + k] = table[j * size * 3 + size + k] +arr[node * size + j];  
                    table[node * 3 * size + 2 * size + k] = j + 1;                        
                }
            }
        }
    }
}

int main()
{
    int size;
    cout<<"Enter the number of routers in the network:";
    cin>>size;

    int* arr = new int[size * size];  
    read(arr, size);

    int* table_matrix = new int[size * size * 3];

    constructInititalTable(arr, table_matrix, size);
    cout<<"Read the tables as:"<<endl;  
    cout<<"1st Row means Destination node "<<endl;
    cout<<"2nd Row means Distance"<<endl;
    cout<<"3rd Row means Next Node"<<endl;
    print3d(table_matrix,size);

    cout<<"\nThe tables after updating are:"<<endl;
    for(int i = 0; i < size; i++){
        updateTable(arr, table_matrix, size,i);
    }

    print3d(table_matrix,size);
}