#include <stdio.h>
#include <stdlib.h>

#define LONGITUD 10

typedef struct
{
	int inicio;
	int fin;
}Extremos;

typedef struct nodo
{
	Extremos extremos;
	struct nodo *sig;
}Nodo;

typedef struct
{
	Nodo *inicio;
	int cantidad;
}Lista;

Nodo* crearNodo(Extremos extremos);
void insertar(Lista *lista,int inicio,int fin);
Extremos quitar(Lista *lista);
int vacia(Lista lista);


void quickSort_iterativo(int *arreglo,int inicio,int fin);

void quickSortArreglosDinamicos(int *arreglo,int inicio,int fin);

void quickSort(int *arreglo,int low,int high);

int partition(int *arreglo,int low,int high);
void intercambiar(int *arreglo,int a,int b);

void imprimir(int *arreglo,int longitud);

int main(void)
{
	int arreglo_1[LONGITUD] = {6,4,8,7,9,3,2,1,10,5};
	int arreglo_2[LONGITUD] = {6,4,8,7,9,3,2,1,10,5};
	
	printf("\n HOLA MUNDO");
	printf("\n ARREGLO_1: ");
	imprimir(arreglo_1,LONGITUD);
	printf("\n RESULTADO DE QUICKSORT ITERATIVO");
	quickSortArreglosDinamicos(arreglo_1,0,9);
	printf("\n ARREGLO_1: ");
	imprimir(arreglo_1,LONGITUD);
	
	
	/*
	printf("\n ARREGLO_1: ");
	imprimir(arreglo_1,LONGITUD);
	printf("\n RESULTADO DE QUICKSORT RECURSIVO");
	quickSort(arreglo_1,0,9);
	printf("\n ARREGLO_1: ");
	imprimir(arreglo_1,LONGITUD);
	
			
	printf("\n\n ARREGLO_2: ");
	imprimir(arreglo_2,LONGITUD);
	quickSort_iterativo(arreglo_2,0,9);
	printf("\n RESULTADO DE QUICKSORT ITERATIVO");
	printf("\n ARREGLO_2: ");
	imprimir(arreglo_2,LONGITUD);
	*/

	return 0;
}


void imprimir(int *arreglo,int longitud)
{
	for(int i = 0; i < longitud ; i++)
	{
		printf(" %d",arreglo[i]);
	}
}


void quickSortArreglosDinamicos(int *arreglo,int inicio,int fin)
{
	int pivote,i;
	int numParticiones = 1;
	int *aux;
	int *inicios = calloc(numParticiones,sizeof(int));
	int *finales = calloc(numParticiones,sizeof(int));
	inicios[0] = inicio;
	finales[0] = fin;
	for( i = 0; i < numParticiones; i++)
	{
		if(inicios[i]<finales[i])
		{
			pivote = partition(arreglo,inicios[i],finales[i]);	
			//AUMENTA PARA REGISTRAR PARTICIONES		
			aux = NULL;
			while(!aux)
				aux = realloc(inicios,sizeof(int) * (numParticiones+2));
			inicios = aux;	
			aux = NULL;
			while(!aux)
				aux = realloc(finales,sizeof(int) * (numParticiones+2));
			finales = aux;
			//IZQUIERDA
			inicios[numParticiones] = inicios[i];
			finales[numParticiones] = pivote-1;		
			//DERECHA
			inicios[numParticiones+1] = pivote+1;
			finales[numParticiones+1] = finales[i];
			numParticiones+=2;		
		}
	}
	free(inicios);
	free(finales);	
}

void quickSort(int *arreglo,int low,int high)
{
	int pivote;
	if( high > low )
	{		
		pivote = partition(arreglo,low,high);
		quickSort(arreglo,low,pivote-1);
		quickSort(arreglo,pivote+1,high);
	}
}


void quickSort_iterativo(int *arreglo,int inicio,int fin)
{
	int pivote;
	Extremos extremos;
	Lista lista = {NULL,0};
	insertar(&lista,inicio,fin);
	//ITERAR MIENTRAS EXISTAN EXTREMOS EN LA LISTA
	while( !vacia(lista))
	{
		extremos = quitar(&lista);
		//SI HAY MAS DE 1 ELEMENTO HAY QUE DIVIDIR
		if(extremos.fin > extremos.inicio)
		{
			//DIVIDIR SEGUN UN PIVOTE, COLOCANDO LOS MAYORES AL PIVOTE
			//EN EL LADO DERECHO Y LOS MENORES EN EL IZQUIERDO
			//EL INDICE QUE INDICA LA MITAD ES EL PIVOTE
			pivote = partition(arreglo,extremos.inicio,extremos.fin);
			//AGREGAR LOS INDICES DE LA MITAD IZQUIERDA A LA LISTA
			insertar(&lista, extremos.inicio,pivote-1);
			//AGREGAR LOS INDICES DE LA MITAD DERECHA A LA LISTA
			insertar(&lista, pivote+1,extremos.fin);
		}
	}
}

int partition(int *arreglo,int low,int high)
{
	int izquierda,derecha,pivote;
	//SE SELECCIONA EL VALOR DEL PIVOTE
	//ARBRITARIAMENTE
	pivote = arreglo[low];
	//SE UTILIZAN 2 VARIABLES AUXILIARES
	//PARA RECORRER LOS EXTREMOS Y COMPARAR
	//DE AFUERA HACIA ADENTRO
	izquierda = low;
	derecha = high;
	//ESTE CICLO COLOCA EN LA MITAD IZQUIERDA
	//LOS VALORES MENORES AL PIVOTE
	//Y EN LA MITAD DERECHA LOS MAYORES AL PIVOTE
	while( izquierda < derecha )
	{
		//MOVER INDICE IZQUIERDA MIENTRAS
		//QUE EL VALOR SEA MENOR QUE EL PIVOTE
		while( arreglo[izquierda] <= pivote )
			izquierda++;
		//MOVER INDICE DERECHA MIENTRAS
		//QUE EL VALOR SEA MAYOR QUE EL PIVOTE
		while( arreglo[derecha] > pivote )
			derecha--;
		if( izquierda<derecha)
			intercambiar(arreglo,izquierda,derecha);	
	}
	//AQUI SE COLOCA EL PIVOTE EN LA POSICION DE LA DERECHA
	//SIENDO EL CENTRO DE LAS DOS MITADES
	//DERECHA ES LA POSICION FINAL PARA EL PIVOTE
	arreglo[low] = arreglo[derecha];
	arreglo[derecha] = pivote;
	return derecha;	
}

void intercambiar(int *arreglo,int a,int b)
{
	int aux;
	aux = arreglo[a];
	arreglo[a] = arreglo[b];
	arreglo[b] = aux;
}

Nodo* crearNodo(Extremos extremos)
{
	Nodo *nuevo = calloc(1,sizeof(Nodo));
	nuevo->extremos.inicio = extremos.inicio;
	nuevo->extremos.fin = extremos.fin;
	return nuevo;
}

void insertar(Lista *lista,int inicio,int fin)
{
	Extremos extremos = (Extremos){inicio,fin};
	if( vacia(*lista) )
		lista->inicio = crearNodo(extremos);
	else
	{
		Nodo *p = lista->inicio;
		while( p->sig != NULL )
			p = p->sig;
		p->sig = crearNodo(extremos);
	}
	lista->cantidad++;
}

Extremos quitar(Lista *lista)
{
	Extremos extremos;
	Nodo *tmp;
	tmp = lista->inicio;
	lista->inicio = tmp->sig;
	extremos = tmp->extremos;
	free(tmp);
	lista->cantidad--;
	return extremos;	
}

int vacia(Lista lista)
{
	return lista.inicio == NULL && lista.cantidad==0;
}