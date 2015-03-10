/*Programa creado por Andres De La Rosa*/
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#define a 160
#define e 130
#define o 162
#define u 163
//----------estructuras---------------
typedef struct list
{
	int numero;
	int rey[21];
	struct list* siguiente;
}lista;
//--------variable goblales-----------
int reina[21]= {0};
int tablero[21][21]={0};
static int cont=0;
static int comprobaciones=0;
lista* anterior;
lista* cabeza;
lista* actual;

//-----------prototipos----------------
void reinas(int fila, int total, int reinas[]);
void modificarTablero(int fila, int columna,int total,int num);
void mostrarTablero(int num, int total);

int main(void)
{
	system("title N reinas");
	int tamano,k,op,resp='s';
	unsigned long long iteracion=1;
	anterior = (lista*)malloc(sizeof(lista));
	printf("Programa creado por Andr%cs De La Rosa\n",e);
	printf("Este programa c%clcula las posibles soluciones para\ncolocar N reinas en un tablero de ajedrez de N x N\n\n",a);
	printf("Cu%cl sera el valor de N: ",a);
	scanf("%d",&tamano);
	printf("\nLas posibles soluciones para un tablero de %d x %d son:\n",tamano,tamano);
	reinas(1,tamano,reina);
	if(cont == 0)
	{
		printf("No existen soluciones posibles\n");
		printf("\nComprobaciones realizadas con bactracking: %d\n",comprobaciones);
		for(k=1;k<=tamano;k++)
			iteracion *= tamano;
		printf("Comprobaciones que se hubieran realizado con iteraci%cn com%cn: %LLu\n\n",o,u,iteracion);
		fflush(stdin);
		getchar();
		exit(0);
	}
	printf("\nComprobaciones realizadas con bactracking: %d\n",comprobaciones);
	for(k=1;k<=tamano;k++)
		iteracion *= tamano;
	printf("Comprobaciones que se hubieran realizado con iteraci%cn com%cn: %LLu\n\n",o,u,iteracion);
	do
	{
		printf("\nTeclee un n%cmero para probar esa soluci%cn: ",u,o);
		fflush(stdin);
		scanf("%d",&op);
		mostrarTablero(op,tamano);
		resp='o';
		while(resp != 's' && resp != 'n')
		{
			printf("\n\n Probar otra soluci%cn < S/N >",o);
			fflush(stdin);
			resp=getchar();
			resp=tolower(resp);
		}
	}while(resp=='s');
	
	return 0;
}
//----------------------------------------------------------
void reinas(int fila, int total,int reina[])
{
	int columna,i,j;
	for(columna = 1; columna <= total; columna++)
	{
		if(reina[total] == 0)
		{
			if( tablero[fila][columna] == 0)
			{
				//-------------------llenado de tablero------------------
				reina[fila] = columna;
				modificarTablero(fila,columna,total,1);
				comprobaciones++;				
				reinas(fila+1,total,reina);
				//------Imprimir la serie que cumple las condiciones-----
				if(reina[total]!= 0)
				{
					cont++;
					printf("%d) ",cont);
					for(i=1;i <= total;i++)
						printf("%d,",reina[i]);
					printf("\n");
					actual = (lista*)malloc(sizeof(lista));
					actual->numero = cont;
					actual->siguiente = NULL;
					if(cont > 1 )
						anterior->siguiente = actual;
					for(i=1;i <= total;i++)
						actual->rey[i]=reina[i];
					anterior = actual;
					if(cont == 1)
						cabeza = actual;
				}
				//-----------------borrado de tablero---------------------
				reina[fila] = 0;
				modificarTablero(fila,columna,total,-1);
			}
		}
	}
}

void modificarTablero(int fila, int columna,int total,int num)
{
	int i,j;
	//columnas y filas
	for(i = 1;i <= total; i++)
	{
		tablero[fila][i] +=num;
		tablero[i][columna] +=num;
	}
	//diagonal principal
	if(columna+fila>total){
		i=total;
		j=columna+fila-total;}
	else{
		j=1;
		i=columna+fila-1;}
	for(;j <= total && i >=1; i--,j++)
		tablero[i][j]+=num;
	//diagonal secundaria
	if(fila>=columna){
		j=1;
		i=abs(columna-fila)+1;}
	else{
		i=1;
		j = abs(columna-fila)+1;}
	for( ;j <= total && i <= total; i++,j++)
		tablero[i][j]+=num;	
}      

void mostrarTablero(int num, int total)
{
	int i,x;
	actual = cabeza;
	while(actual->numero != num  && actual->siguiente != NULL)
		actual = actual->siguiente;
	for(x=1; x<= total;x++)
	{
		printf("%c",219);
		for(i = 1;i <= total;i++)
			printf("%c%c%c%c",223,223,223,219);
		printf("\n");
		for(i = 1;i <= total;i++)
		{
			if(actual->rey[x] == i)
			 	printf("%c %d ",219,actual->rey[x]);
			else
				printf("%c   ",219);
		}
		printf("%c\n",219);
	}
	printf("%c",223);
	for(i = 1;i <= total;i++)
		printf("%c%c%c%c",223,223,223,223);
}
