#include<stdio.h>
#include<stdlib.h>

int main()
{
    
    printf("\n\tKernel version\n");
    system("cat /proc/version | awk '{print $1, $2, $3}'");

    printf("\n\tCPU Type\n");
    system("cat /proc/cpuinfo|awk 'NR==3'");
    system("cat /proc/cpuinfo|awk 'NR==8'");
    system("cat /proc/cpuinfo|awk 'NR==13'");

    printf("\n\tCPU Model\n");
    system("cat /proc/cpuinfo|awk 'NR==5'");  

    return 0;
}