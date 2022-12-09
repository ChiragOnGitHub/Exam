#include<stdio.h>
#include<stdlib.h>

int main()
{

    printf("\nConfigured Memory :\n");
    system("cat /proc/meminfo|awk 'NR==1' |awk '{print $2,$3}'");

    printf("\nFree Memory :\n");
    system("cat /proc/meminfo|awk 'NR==2'|awk ' {print $2,$3}'");

    return 0;
}