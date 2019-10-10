// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd1; 
    char *myfifo = "/tmp/fifo"; 
    mkfifo(myfifo, 0666); 
    char *str1 = (char*)malloc(sizeof(char)*512);
    char *str2 = (char*)malloc(sizeof(char)*512); 
    
    do
    {
        fd1 = open(myfifo,O_RDONLY); 
        read(fd1, str1, 80); 
        printf("Servidor: %s\n", str1); 
        close(fd1); 
 
        fd1 = open(myfifo,O_WRONLY); 
        //fgets(str2, 80, stdin); 
        scanf("%[^\n]",str2);
        str2[strlen(str2)+1] = '\0'; 
        write(fd1, str2, strlen(str2)+1); 
        close(fd1); 
    }while(1); 
    return 0; 
} 