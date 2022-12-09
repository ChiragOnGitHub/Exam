#include <stdio.h>
#include <unistd.h>

struct Process{
    int processNumber;
    int processArrivalTime; 
    int processBurstTime;
    int processWaitingTime;
    int processTurnaroundTime;
    int remainingBurstTime;
    int processEndTime;
    int processCompleted;
};

//sort the array on the basis of arrival time of processes
void arrivalTimeSort(struct Process p[], int NumOfProcess){
    struct Process temp;
    for(int i=0;i<NumOfProcess;i++){
        for(int j=0;j<NumOfProcess-i-1;j++){
            if(p[j].processArrivalTime>p[j+1].processArrivalTime){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    return;
}

//sort the array on the basis of process Number
void processNumberSort(struct Process p[], int NumOfProcess){
    struct Process temp;
    for(int i=0;i<NumOfProcess;i++){
        for(int j=0;j<NumOfProcess-i-1;j++){
            if(p[j].processNumber>p[j+1].processNumber){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    return;
}

int main(){
    int currentProcess, currentExecutionTime, numOfProcess, numOfProcessLeft , time_quantum;
    int flag;
    double avgWaitingTime=0, avgTurnaroundTime=0;

    printf("Enter Number of Processes !! ");
    scanf("%d",&numOfProcess);
    printf("\n");
    if(numOfProcess<=0){
        printf("Number of process should be greater than 0 ");
        return -1;
    }
    numOfProcessLeft = numOfProcess;

    struct Process processArray[numOfProcess];

    
    for(int i=0;i<numOfProcess;i++){
        printf("Enter Arrival time of Process %d :",i+1);
        scanf("%d",&processArray[i].processArrivalTime);

        printf("Enter Burst time of Process %d : ",i+1);
        scanf("%d",&processArray[i].processBurstTime);

        processArray[i].remainingBurstTime=processArray[i].processBurstTime;
        processArray[i].processNumber=i+1;
        processArray[i].processCompleted=0;

        if(&processArray[i].processArrivalTime<0){
            printf("Arrival time cannot be negative ");
            return -1;
        }
        if(&processArray[i].processBurstTime<0){
            printf("Burst time cannot be negative ");
            return -1;
        }
        printf("\n");  
    }

    printf("\n");
    printf("Enter time quantum : ");
    scanf("%d", &time_quantum);
    printf("\n");

    currentProcess=0;
    arrivalTimeSort(processArray,numOfProcess);
    currentExecutionTime=processArray[0].processArrivalTime;

    while(numOfProcessLeft != 0)
    {
        if(processArray[currentProcess].remainingBurstTime>time_quantum){
            printf("Process %d executes from %d to %d \n",currentProcess+1,currentExecutionTime,currentExecutionTime+time_quantum);
            processArray[currentProcess].remainingBurstTime -= time_quantum;
            currentExecutionTime += time_quantum;   
        }
        else if(processArray[currentProcess].remainingBurstTime>0){
            printf("Process %d executes from %d to %d \n",currentProcess+1,currentExecutionTime,currentExecutionTime+processArray[currentProcess].remainingBurstTime);
            currentExecutionTime += processArray[currentProcess].remainingBurstTime;
            processArray[currentProcess].remainingBurstTime = 0;
            numOfProcessLeft--;
            processArray[currentProcess].processEndTime=currentExecutionTime;
        }

        
        if(currentProcess == numOfProcess - 1){
                currentProcess = 0;
        }

        else if(processArray[currentProcess+1].processArrivalTime <= currentExecutionTime){
                currentProcess++;
        }

        else{   
            
            flag=1;
            for(int i=0;i<=currentProcess;i++){
                if(processArray[i].remainingBurstTime!=0){
                    currentProcess = 0;
                    flag=0;
                    break;
                }
            }
  
            if(flag==1){
                printf("CPU remain idle from %d to %d \n",currentExecutionTime,currentExecutionTime+1);
                currentExecutionTime+=1;
            }
        }
    }
    
    processNumberSort(processArray,numOfProcess);
    printf("\nProcess\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\n");
    for(int i =0;i<numOfProcess;i++){
        processArray[i].processTurnaroundTime=processArray[i].processEndTime-processArray[i].processArrivalTime;
        processArray[i].processWaitingTime=processArray[i].processTurnaroundTime-processArray[i].processBurstTime;

        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n",processArray[i].processNumber,processArray[i].processArrivalTime,processArray[i].processBurstTime,processArray[i].processWaitingTime,processArray[i].processTurnaroundTime);
        
        avgTurnaroundTime+=processArray[i].processTurnaroundTime;
        avgWaitingTime+=processArray[i].processWaitingTime;
    }

    avgWaitingTime = (double)avgWaitingTime / numOfProcess;
    avgTurnaroundTime = (double)avgTurnaroundTime  / numOfProcess;

    printf("\n\nAverage Waiting Time:\t%f", avgWaitingTime);
    printf("\nAverage Turnaround Time:\t%f\n", avgTurnaroundTime);

    return 0;

}