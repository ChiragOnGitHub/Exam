#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char command[1024];
    if (argc != 2)
    {
        printf("Please provide appropriate numbers of arguments ");
    }
    sprintf(command,"stat %s",argv[1]);
    system(command);
    return 0;
}