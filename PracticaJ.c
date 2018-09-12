#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PilaEst.h"
/*-------------------------------------------------------Constantes----------------------------------------------------------------*/ 
#define TAMCAD 1000 //tamaño MAX de la cadena a evaluar
#define N_Operadores 7 //tamaño de arreglo para los operadores
const char operators[N_Operadores] = {'+', '-', '*', '/', '(',')', '^'}; //Arreglo de operadores, acomodados por su precedencia 
int precedences[N_Operadores] = {1, 1, 2, 2, 0,0, 3}; //Arreglo de precedencia en valor numerico
/*---------------------------------------------------Prototipo de Funciones----------------------------------------------------------------*/
boolean Validar(char *cad,int tamcad2);//valida que los parentesis estan correctos de lo contrario mata el programa
void Conversion(char *cad,int tamcad2);//Convierte la expresion de infija a posfija
int Precedencia(char c); 	//Saca el valor de precedencia de un signo
/*-------------------------------------------------Estructura de las Funciones----------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
    int tamcad;
    char cad[TAMCAD]; //Arreglo designado para almacenar la cadena ingresada
    printf("Introduzca la expresion a evaluar\n");
    scanf("%s",cad);
    tamcad=strlen(cad); //Obten el valor de la cadena ingresada
    Validar(cad,tamcad);
    Conversion(cad,tamcad);
	exit(0);  
}
////////////////////////////////////////////////////////////////////////////////////////////////
boolean Validar(char *cad,int tamcad2){
  boolean h=TRUE;
  int i;
  pila meapila;
  elemento e1;
  Initialize(&meapila);//Inicializa un a pila para validar los parentesis
  for(i=0;i<tamcad2;i++){
    if(cad[i]=='('){
      e1.c = '(';  
      Push(&meapila,e1);//Mete un elemento a la pila
    }
    else if(cad[i]==')'){
          if(Empty(&meapila)){//Evalua que la pila no sea vacia, en caso de estar vacia entonces mata al programa
            printf("ERROR: Existen mas parentesis que cierran de los que abren\n");             
            exit(1);
          }
          e1=Pop(&meapila); //Saca a un elemento de la pila                        
        }
  }  
    if(!Empty(&meapila)){ //Si al terminar el proceso la pila aun tiene elementos entonces mata al programa y no deja avanzar a las siguietes operaciones
      printf("ERROR: Existen mas parentesis que abren de los que cierran\n");
      exit(1);
    }
  printf("EXCELENTE: Expresion correcta\n");
  Destroy(&meapila);//Destruye la pila
  return h;//Regresa el valor de h que por defecto es TRUE
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void Conversion(char *cad,int tamcad2){
  int i,sizepos=1;
  pila meapila;
  elemento e1;
  char ax;	//Variable auxiliar para sacar los caracteres y formar la nueva cadena
  char posf[sizepos];
  Initialize(&meapila);
  for(i=0;i<tamcad2;i++){
	e1.c=cad[i];	//Elemento toma el valor de cad[1] par apoder entrar en la pila 
    if(cad[i]>='A' && cad[i]<='Z'){	//Pasa directamente a la expresion las letras
		ax=cad[i];
		posf[sizepos-1]=ax;
		sizepos++;
    }
	if(cad[i]=='*' || cad[i]=='/' || cad[i]=='-' || cad[i]=='+' || cad[i]=='^' ){	//Mete en la pila los operadores por precedencia
		if(Empty(&meapila)){	//SI la pila esta vacia entonces ingresa el primer elemento a la pila sin revisar precedencia
			Push(&meapila,e1);
			//printf("Entro en pila 1 :%c\n",Top(&meapila).c);
		}
		else if(!Empty(&meapila)){	//Si la pila no esta vacia entonces evalua la precedencia de los operadores
			if(Precedencia(Top(&meapila).c)<Precedencia(cad[i])){
				Push(&meapila,e1);	//Si el operador tiene mayor precedencia del que esta en la pila entonces entra
				//printf("Entro en pila 2 :%c\n",Top(&meapila).c);
			}
			else if(Precedencia(Top(&meapila).c)>=Precedencia(cad[i])){
				ax=Pop(&meapila).c;	//Si el operador tiene menor precedencia del que esta en la pila lo saca y lo guarda en una variable aux
				posf[sizepos-1]=ax;
				sizepos++;
				//printf("Saco : %c \n",ax);
				if(!Empty(&meapila)){
					if(Precedencia(Top(&meapila).c)>=Precedencia(cad[i])){
						ax=Pop(&meapila).c;
						posf[sizepos-1]=ax;
						sizepos++;
						//printf("Saco : %c \n",ax);
					}
				}
				Push(&meapila,e1);			//Empila el operador con mayor precedencia en la pila	
				//printf("Entro en pila 3 :%c\n",Top(&meapila).c);
			}
		}
	}
	//Mete en la pila '('  con precedencia 0 y al mismo tiempo cuando se detecta un ')'  saca por medio de POP los elementos hasta el '(' en la pila
	if(cad[i]=='('){	//Evalua si el caracter de la cadena es un '('  o ')'
		Push(&meapila,e1);	//Mete en la el '(' con precedencia 0
		//printf("Entro en pila 4 :%c\n",Top(&meapila).c);
	}
	else if(cad[i]==')'){	//En el caso de ser un ')'
		for(;Top(&meapila).c!='(';){		//Sacara todos los operadores almacenados hasta el siguiente '('
			ax=Pop(&meapila).c;
			posf[sizepos-1]=ax;
			sizepos++;
			//printf("Saco 2: %c \n",ax);
		}
		Pop(&meapila);			//Saca el '(' ya que este no es necesario pasarlo a la expresion posfija
		//printf("Saca el ( de la pila\n");
	}
  }
	if(!Empty(&meapila)){	//Si la pila aun contiene operadores, entonces los sacara y los agregara a la cadena
		for(;Size(&meapila)>0;){	//Ciclo repetitivo hasta que el tamaño de la pila sea 0
			ax=Pop(&meapila).c;
			posf[sizepos-1]=ax;
			sizepos++;
			//printf("Saco 3: %c \n",ax);
		}
	}
	printf("\nCadena:%s\n",posf);
	printf("\nSize de la pila:%d\n",Size(&meapila));
	return ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int Precedencia(char c){
	int i,valor;
	for(i=0;i<N_Operadores;i++){		//Ciclo para reconocer  de que caracter se desea conocer su valor
		if(operators[i]==c){					//Condicinal, una vez encontrado el caracter, entonces, guardara el valor del arreglo de valores y lo retornara
			valor=precedences[i];
		}
	}
	return valor;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
