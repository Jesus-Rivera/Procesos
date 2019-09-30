#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void parir(int,int,int,int);
int main ()
{
	int *status;
	int i,j,lado,profundidad = 0,k,veces;
	printf("Ingrese la profundidad que desea en el arbol: ");
	scanf("%d",&veces);
	for(i = 0; i < 2; i ++)
	{
		switch(fork())
		{
			case -1:
				printf("Error al crear el proceso\n");
				exit(0);
			break;
			case 0:
				if(i == 0)
					lado = 3;
				else
					lado = 4;
				parir(++profundidad,lado,--veces,1);
				exit(0);
			break;
			default:
				if(i != 1)
				{
					for(k = 0; k < profundidad; k ++)
						printf("\t");
					printf("\nSoy el proceso padre y mi id es %d\n",getpid());
				}
				wait(status);
			break;
		}
	}
	return 0;
}
void parir (int profundidad, int lado, int veces,int primero)
{
	int *status;
	int k,j;
	if(veces != 0)
	{
		for(j = 0; j < lado; j ++)
		{
			switch(fork())
			{
				case -1:
					printf("Error al crear el proceso\n");
					exit(0);
				break;
				case 0:
					profundidad++;
					for(k = 0; k < profundidad; k ++)
						printf("\t");
					printf("Soy el proceso con el id %d hijo de %d\n",getpid(),getppid()); 
					parir(++profundidad,lado,--veces,0);
					exit(0);
				break;
				default:
					if(primero == 1)
					{
						for(k = 0; k < profundidad; k ++)
							printf("\t");
						printf("Soy el proceso con el id %d hijo de %d\n",getpid(),getppid()); 	
					}
					wait(status);	
				break;
			}
		}
	}	
	else
	{
		exit(0);
	}			
}