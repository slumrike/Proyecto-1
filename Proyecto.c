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

void main()
{   
    int longitud_x,longitud_y;
    
    printf("ingresar la capacidad de la matriz= \n");
    scanf("%i \n",&longitud_x);    //cantidad de nodos
    scanf("%i \n",&longitud_y);


    
    Node *array[longitud_y];
    for(int i=0; i<3;i++);
     
     
}
