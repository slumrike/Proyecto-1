#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
    int value;
    struct Node *next;

}Node; 

//crear nodos de listas

Node *New_nodo(int num){
    Node *newp;
if((newp=(Node *)malloc(sizeof(Node)))==NULL){
fprintf(stderr,"new_item: error en malloc\n");
exit(1);
}
newp->value=num;
newp->next=NULL;
return newp;
}

//adiciona un nodo a una lista
Node *add_front(Node *listp,Node *newp){
    newp->next = listp;
    return newp;
}

Node *add_end(Node *listp, Node *newp){
Node *p;
if(listp==NULL)
 return newp;
for(p=listp;p->next!=NULL;p=p->next);
p->next = newp;
return listp;
}

//matrices 


int ObtenerElement(Node *matriz[],int size,int posx,int poxy){

}

void AsingElemnt(int fila,int columna,int element,Node *matriz[]){

}



void main()
{   
    int filas,nodos,n;
    
    printf("ingresar la capacidad de la matriz= \n");

    scanf("%i\n",&nodos);    //cantidad de nodos
    scanf("%i",&filas);

    Node *matriz[filas];

    printf("%p",matriz);

    for(int i=0; i < filas ;i++){  
     for (int j=0;j<nodos;j++){
        printf("ingresar el valor de la posicion %i:%i ",i,j);
        scanf("%i",&n);

        if (j==0){
            
            matriz[i] = New_nodo(n);}
        else {
       matriz[i] = add_end(matriz[i],New_nodo(n));
     }
     }
    }

    printf("el valor de la posicion 0:1 es %i\n",(matriz[0]->next)->value);
    return; 
}