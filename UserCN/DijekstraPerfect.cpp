#include <iostream>
#include <limits.h>
using namespace std;

int* Dijkstra(int** arr,int vertex,int source){
    //creating a distance array which stores shortest distance of all nodes from source
    //initially sourceNode distance is 0 and rest is infinite
    int* dist= new int[vertex];
    for(int i=0;i<vertex;i++){
        dist[i]=INT_MAX;
    }
    dist[source]=0;

    //creating a finalised array which tells which node is finalised
    bool* finalised=new bool[vertex];
    for(int i=0;i<vertex;i++){
        finalised[i]=false;
    }


    for(int k=0;k<vertex-1;k++){
        //finding the node with shortest distance(u) to finalised it!!
        //first node which is not finalised is considered as shortest and 
        //if we get any other node which has shoter distance than that then we consider it as shortest
        // u is the node with shortest distance means which is going to be finalised 
        int u=-1;
        for(int i=0;i<vertex;i++){
            if(!finalised[i] && (u==-1||dist[i]<dist[u]))
                u=i;
        }
        finalised[u]=true;

        //now we compare our current finalised node with all its adjacent node which are not finalised
        for(int v=0;v<vertex;v++){
            if(arr[u][v]!=0 && finalised[v]==false && dist[v]>(dist[u]+arr[u][v])){
                    dist[v]=dist[u]+arr[u][v];
            }
        }
    }
    return dist;
}


int main(){
    int nodes;
    cout<<"Enter Number of routers : ";
    cin>>nodes;

    int** graph=new int*[nodes];
    for(int i=0;i<nodes;i++){
        graph[i]=new int[nodes];
    }

    cout<<"Enter Matrix of Network "<<endl;
    for(int i=0;i<nodes;i++)
        for(int j=0;j<nodes;j++)
            cin>>graph[i][j];
    
    int root;
    cout<<"Select Your Root among 0 to "<<nodes-1<<endl;
    cin>>root;

    int* finalDistance= new int[nodes];
    finalDistance=Dijkstra(graph,nodes,root);
    for(int i=0;i<nodes;i++){
        cout<<"Shortest Distance between Source and Router "<<i<<" is "<<finalDistance[i]<<endl;    
    }

    return 0;
}