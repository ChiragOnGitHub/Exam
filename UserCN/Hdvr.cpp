#include <iostream>
using namespace std;

class Node{
public:
    int **table;
};

class DVR{
public:
    Node *routers;
    int num;
    int **network;
    DVR(int **matrix, int n){
        network=matrix;
        num=n;
        routers=new Node[num];
        for (int i=0; i<num; i++)
        {
            routers[i].table=new int*[num];
            for (int j=0; j<num; j++)
            {
                routers[i].table[j]=new int[2];
                if (i!=j)
                {
                    if (network[i][j]!=0)
                    {
                        routers[i].table[j][0]=network[i][j];
                        routers[i].table[j][1]=j;
                    }
                    else
                    {routers[i].table[j][0]=10000;}
                }
                else
                {
                    routers[i].table[j][0]=0;
                    routers[i].table[j][1]=-1;
                }
            }
            
        }
    }
 
    void learn(){
        bool completed=false;
        int distance;
        while (!completed)
        {
            completed=true;
            for (int i=0; i<num; i++)
            {
                for (int j=0; j<num; j++)
                {
                    if (network[i][j]!=0)
                    {
                        for (int k=0; k<num; k++)
                        {
                            distance=routers[j].table[k][0]+routers[i].table[j][0];
                            if (distance<routers[i].table[k][0])
                            {
                                completed=false;
                                routers[i].table[k][0]=distance;
                                routers[i].table[k][1]=j;
                            }
                        }
                    }
                }
            }
        }
    }
   
    void display(){
        for (int i=0; i<num; i++)
        {
            cout << "Table of Router " << i << " :" << endl;
            for (int j=0; j<num; j++)
            {
                cout << "Router " << j << "    ";
                for (int k=0; k<2; k++)
                {
                    cout << routers[i].table[j][k] << "   ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    
    ~DVR(){
        for (int i=0; i<num; i++)
        {
            for (int j=0; j<num; j++)
            {
                delete [] routers[i].table[j];
            }
            delete [] routers[i].table;
        }
        delete [] routers;
    }
};

int main(){
    int **matrix;
    int n;
    cout << "Enter the number of routers in the network : ";
    cin >> n;
    matrix=new int *[n];
    for (int i=0; i<n; i++)
    {
        matrix[i]=new int[n];
    }
    
    cout << "Enter the adjacency matrix of the network :" << endl;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cin >> matrix[i][j];
        }
    }
    
    DVR d(matrix, n);
    d.learn();
    d.display();
    
    
    
    return 0;
}