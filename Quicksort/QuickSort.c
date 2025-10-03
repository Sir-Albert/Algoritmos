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
	Nodo *fin;
	int cantidad;
}Lista;

Nodo* crearNodo(Extremos extremos);
void insertar(Lista *lista,int inicio,int fin);
Extremos quitar(Lista *lista);
int vacia(Lista lista);


void quickSort_iterativo(int *arreglo,int inicio,int fin);
void quickSort(int *arreglo,int inicio,int fin);

int partition(int *arreglo,int inicio,int fin);
void intercambiar(int *arreglo,int a,int b);

void imprimir(int *arreglo,int longitud);

int main(void)
{
	int arreglo_1[LONGITUD] = {6,4,8,7,9,3,2,1,10,5};
	int arreglo_2[LONGITUD] = {6,4,8,7,9,3,2,1,10,5};
	
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

	return 0;
}


void imprimir(int *arreglo,int longitud)
{
    int i;
	for(i = 0; i < longitud ; i++)
	{
		printf(" %d",arreglo[i]);
	}
}

void quickSort(int *arreglo,int inicio,int fin)
{
	int pivote;
	if( fin > inicio )
	{		
		pivote = partition(arreglo,inicio,fin);
		quickSort(arreglo,inicio,pivote-1);
		quickSort(arreglo,pivote+1,fin);
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

int partition(int *arreglo,int inicio,int fin)
{
	int izquierda,derecha,pivote;
	//SE SELECCIONA EL VALOR DEL PIVOTE
	//ARBRITARIAMENTE
	pivote = arreglo[inicio];
	//SE UTILIZAN 2 VARIABLES AUXILIARES
	//PARA RECORRER LOS EXTREMOS Y COMPARAR
	//DE AFUERA HACIA ADENTRO
	izquierda = inicio;
	derecha = fin;
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
	arreglo[inicio] = arreglo[derecha];
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
	nuevo->extremos = extremos;
	return nuevo;
}

void insertar(Lista *lista,int inicio,int fin)
{
	Extremos extremos = (Extremos){inicio,fin};
	if( vacia(*lista) )
		lista->inicio = lista->fin = crearNodo(extremos);
	else
        lista->fin = lista->fin->sig = crearNodo(extremos);
	lista->cantidad++;
}

Extremos quitar(Lista *lista)
{
	Nodo *tmp;
	Extremos extremos;
	tmp = lista->inicio;
	lista->inicio = tmp->sig;
	lista->cantidad--;
    if(!lista->inicio)
        lista->fin = NULL;
	extremos = tmp->extremos;
	free(tmp);
	return extremos;	
}

int vacia(Lista lista)
{
	return lista.inicio == NULL && lista.inicio == lista.fin && lista.cantidad==0;
}