#include <stdio.h>

struct Hole
{
    int capacity;
    int isOccupied;
    int processNum;
} typedef Hole;

struct Process{
    int processSize;
} typedef Process;

void output(Hole h[],int numOfBlock){
    printf("Block no.\t--->\tProcess no");

    for(int i=0;i<numOfBlock;i++)
    {
        printf("\n %d\t\t",i+1);
        if(h[i].processNum != -1)
            printf("\t%d",h[i].processNum+1);

        else
            printf("\tNot allocated");

    }
}

void first_fit(Hole h[],Process p[], int numOfBlock,int numOfProcess)
{
    for (int i = 0; i < numOfProcess; i++)
        for(int j=0;j<numOfBlock;j++)
            if (h[j].isOccupied==0 && h[j].capacity>=p[i].processSize){
                h[j].isOccupied=1;
                h[j].processNum=i;
                break;
            }
}

void best_fit(Hole h[],Process p[], int numOfBlock,int numOfProcess)
{
    int best;
    int smallest;
    for (int i = 0; i < numOfProcess; i++){
        best = -1;
        smallest = __INT_MAX__;
        for(int j=0;j<numOfBlock;j++){
            if (h[j].isOccupied==0 && (h[j].capacity>=p[i].processSize) && (h[j].capacity<smallest))
            {
                best = j;
                smallest = h[best].capacity;
            }
        }
        if(best!=-1){
            h[best].processNum=i;
            h[best].isOccupied=1;
        }
    }
}

void worst_fit(Hole h[],Process p[], int numOfBlock,int numOfProcess)
{
    int worst;
    int biggest;
    for (int i = 0; i < numOfProcess; i++){
        worst=-1;
        biggest=-__INT_MAX__-1;
        for(int j=0;j<numOfBlock;j++){
            if (h[j].isOccupied==0 && h[j].capacity>=p[i].processSize && h[j].capacity>biggest)
            {
                worst = j;
                biggest = h[worst].capacity;
            }
        }
        if(worst!=-1){
            h[worst].processNum=i;
            h[worst].isOccupied=1;
        }
    }
}

int main()
{
    int numOfBlocks,numOfProcess;

    printf("Enter number of memory holes : ");
    scanf("%d", &numOfBlocks);
    printf("Enter size of %d memory holes \n",numOfBlocks);

    Hole memory[numOfBlocks];
    for (int i = 0; i < numOfBlocks; i++)
    {
        scanf("%d", &memory[i].capacity);
        memory[i].isOccupied = 0;
        memory[i].processNum=-1;
    }

    printf("Enter number of processes : ");
    scanf("%d", &numOfProcess);
    printf("Enter size of %d process \n",numOfProcess);

    Process p[numOfProcess];
    for (int i = 0; i < numOfProcess; i++)
    {
        scanf("%d", &p[i].processSize);
    }

    int n;
    printf("\n\nPress 1 for First-Fit strategies \n");
    printf("Press 2 for Best-Fit strategies \n");
    printf("Press 3 for Worst-Fit strategies \n");
    printf("\n\nEnter your choice : ");
    scanf("%d",&n);
    switch(n)
    {
        case 1:
            first_fit(memory,p,numOfBlocks,numOfProcess);
            break;
            
        case 2:
            best_fit(memory,p,numOfBlocks,numOfProcess);
            break;
            
        case 3:
            worst_fit(memory,p,numOfBlocks,numOfProcess);
            break;
            
        default:
            printf("\nWrong Number Entered!!");
    }

    output(memory,numOfBlocks);

    return 0;
}