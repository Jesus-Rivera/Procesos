// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd;
    char *myfifo = "/tmp/fifo"; 
    mkfifo(myfifo, 0666);
    char *arr1 = (char*)malloc(sizeof(char)*512);
    char *arr2 = (char*)malloc(sizeof(char)*512); 
    do
    {
        fd = open(myfifo, O_WRONLY);
        //fgets(arr2, 80, stdin);
        scanf("%[^\n]",arr2);
        arr2[strlen(arr2)+1] = '\0';
        write(fd, arr2, strlen(arr2)+1); 
        close(fd); 

        fd = open(myfifo, O_RDONLY);  
        read(fd, arr1, sizeof(arr1)); 

        printf("Clientes: %s\n", arr1); 
        close(fd); 
    }while(1);
    return 0; 
} 