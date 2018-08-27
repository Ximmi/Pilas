#include <stdio.h>
#define MAX 1000


typedef struct elemento{

} elemento;

typedef struct pila{
	elemento A[MAX];
	int tope;
} pila;

typedef char booleano;

void Initialize(pila *S);
void Push(pila *S; elemento e);
elemento Pop(pila *S);
booleano Empty(pila *S);
elemento Top(pila *S);
int Size(pila *S);
void Destroy(pila *S);

int main(int argc, char *argv[]) {
	return 0;
}

void Initialize(pila *S){
	(*S).tope=-1;
}

void Push(pila *S, elemento e){
	//mueve el tope a 0 para poder introducir un elemento
	(*S).tope++;
	if(S->tope>=MAX){
		printf("ERROR PUSH: Se ha desbordado la pila \n");
		exit(1);
	}
	(*S).A[S->tope]=e;
}

elemento Pop(pila *S){
	//saca elementos de la pila
	elemento r;
	if(S->tope==-1){
		printf("ERROR POP: Subdesbordamiento de la pila \n");
		exit(1);
	}
	r=S->A[S->tope];
	S->tope--;
	return r;	
}

booleano Empty(pila *S){
	booleano b=FALSE;
	if(S->tope==-1)
		b=TRUE;
	return b;
}

elemento Top(pila *S){
	if(S->tope==-1){
		printf("ERROR TOP: Desbordamiento de la pila \n");
		exit(1);
	}
	return S->A[S->tope];
}

int Size(pila *S){
	return S->tope+1;
}

void Destroy(pila *S){
	Initialize(S);
}



