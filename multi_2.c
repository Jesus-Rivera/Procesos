//Multiplicacion de matrices mediante procesos
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int obtenerValor(int*,int*,int);
void multiplicacion(int**,int**,int,int,int,int);
void imprimir (int**,int,int);

int main()
{
	srand(time(NULL));
	//Obtencion de datos para la creacion de matrices
	int filasA,columnasA,columnasB,filasB;
	printf("Ingrese el numero de filas del que desea la matriz A: ");
	scanf("%d",&filasA);
	printf("Ingrese el numero de columnas del que desea la matriz A: ");
	scanf("%d",&columnasA);
	filasB = columnasA;
	printf("Ingrese el numero de filas del que desea la matriz B: ");
	scanf("%d",&columnasB);
	printf("Tendra una matriz A de: %d x %d\n",columnasA,filasA);
	printf("Tendra una matriz B de: %d x %d\n",columnasB,filasB);
	//Creacion de espacio de memoria para crear las matrices
	int i,j;
	int **matrizA,**matrizB;
	matrizA = (int**)malloc(sizeof(int*)*filasA);
	matrizB = (int**)malloc(sizeof(int*)*filasB);
	for(i = 0; i < filasA; i ++)
		matrizA[i] = (int*)malloc(sizeof(int)*columnasA);
	for(i = 0; i < filasB; i ++)
		matrizB[i] = (int*)malloc(sizeof(int)*columnasB);
	//Se llena las matrices con numeros aleatorios
	for(i = 0; i < filasA; i ++)
	{
		for(j = 0; j < columnasA; j ++)
			matrizA[i][j] = rand()%4;
	}
	for(i = 0; i < filasB; i ++)
	{
		for(j = 0; j < columnasB; j ++)
			matrizB[i][j] = rand()%4;
	}
	//Impresión de la primer matriz
	for(i = 0; i < filasA; i ++)
	{
		for(j = 0; j < columnasA; j ++)
			printf("%d ",matrizA[i][j]);
		printf("\n");
	}
	printf("---------------------\n");
	//Impresion de la segunda matriz
	for(i = 0; i < filasB; i ++)
	{
		for(j = 0; j < columnasB; j ++)
			printf("%d ",matrizB[i][j]);
		printf("\n");
	}
	//Obtencion del numero de procesos
	int x,procesos,k;
	printf("Ingrese la cantidad de procesos con lo que desea ejecutar el programa: ");
	scanf("%d",&x);
	procesos = filasA/x;
	printf("Le toca de %d filas a cada proceso\n",procesos);
	i = 0;
	k = 0;
	multiplicacion(matrizA,matrizB,filasA,columnasA,filasB,columnasB);
	int ***partes = (int***)malloc(sizeof(int**)*x);
	for(i = 0; i < x; i ++)
	{

	}
	int *status;
	for(i = 0; i < x; i ++)
	{
		switch(fork())
		{
			case -1:
				printf("Error al crear el proceso\n");
			break;
			case 0:
				printf("Soy el proceso hijo de %d, con un id de %d\n",getppid(),getpid());
				exit(0);
			break;
			default:
				if(i == 0)
				{
					printf("Soy el proceso padre, con id %d\n",getpid());
				}
				wait(status);
			break;
		}
	}
	return 0;
}

void imprimir (int** matriz,int filas, int columnas)
{
	int i,j;
	for(i = 0; i < filas; i ++)
	{
		for(j = 0; j < columnas; j ++)
		{
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}

int obtenerValor(int* fila, int* columna,int tam)
{
	int i,temp,resultado = 0;
	for(i = 0; i < tam; i ++)
	{
		temp = fila[i]*columna[i];
		resultado += temp;
	}
	return resultado;
}

void multiplicacion(int** matrizA,int** matrizB,int filasA,int columnasA,int filasB,int columnasB)
{
	int i,j;
	int **temp = (int**)malloc(sizeof(int*)*columnasB);
	for(i = 0; i < columnasB; i ++)
	{
		temp[i] = (int*)malloc(sizeof(int)*filasB);
		for(j = 0; j < filasB; j ++)
			temp[i][j] = matrizB[j][i];
	}
	int **resultado = (int**)malloc(sizeof(int*)*filasA);
	for(i = 0; i < filasA; i ++)
		resultado[i] = (int*)malloc(sizeof(int)*columnasB);
	for(i = 0; i < filasA; i ++)
	{
		for(j = 0; j < columnasB; j ++)
		{
			resultado[i][j] = obtenerValor(matrizA[i],temp[j],columnasA);
		}
	}
	imprimir(resultado,filasA,columnasB);
	/*for(i = 0; i < filasA; i ++)
	{
		for(j = 0; j < columnasB; j ++)
		{
			printf("%d   ",resultado[i][j]);
		}
		printf("\n");
	}*/
}