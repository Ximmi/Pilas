#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADPilaEst.h"

#define TAM_MAX 100

void pedir_cadena(char A[TAM_MAX], int tam);
void validar_parentesis(char cadena[TAM_MAX], int tam);
void ordenar(char A[TAM_MAX], int tam);




int main(void){

	pila Pi;
	elemento e;
	int tam;
	char A[TAM_MAX];
	Initialize(&Pi);
	pedir_cadena(A, tam);
	validar_parentesis(A, tam);
	
	


}

void pedir_cadena(char A[TAM_MAX], int tam){
	printf("Hola guapo\n");
	printf("Introduce la operacion a evaluar\n");
	scanf("%s", A);
	tam=strlen(A);

}
void ordenar(char A[TAM_MAX], int tam){
	int i;	
	for(i=0; i<tam;i++){
							
	}
	
}

boolean validar_parentesis(char cadena[TAM_MAX], int tam){
	boolean h=TRUE;
  	int i;
  	pila mypila;
  	elemento e1;
  	Initialize(&mypila);//Inicializa un a pila para validar los parentesis
  	
	for(i=0;i<tam;i++){
    		if(cad[i]=='('){
      			e1.c = '(';  
      			Push(&mypila,e1);//Mete un elemento a la pila
    		}
    		else if(cad[i]==')'){
          		if(Empty(&mypila)){//Evalua que la pila no sea vacia, en caso de estar vacia entonces mata al programa
            			printf("ERROR: Existen mas parentesis que cierran de los que abren\n");             
            			exit(1);
          		}
          		e1=Pop(&mypila); //Saca a un elemento de la pila                        
        	}
  	}  
    
	if(!Empty(&mypila)){ //Si al terminar el proceso la pila aun tiene elementos entonces mata al programa y no deja avanzar a las siguietes operaciones
	      printf("ERROR: Existen mas parentesis que abren de los que cierran\n");
	      exit(1);
	    }

 	 printf("EXCELENTE: Expresion correcta\n");
  	Destroy(&mypila);//Destruye la pila
  	return h;//Regresa el valor de h que por defecto es TRUE

}
