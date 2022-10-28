#include <stdio.h>
#include <math.h>

int Pos_y=0,Pos_x=0; //sirven de posicion para los nodos

typedef struct Node_Fila{
    int value; 
    int posicion;       //este define la posicion en x;
    struct Node_Fila *next;

}Node_Fila;

typedef struct Node_columna{
        int posicion;    //esta define la posicion en y;
        struct Node_columna *next;
        struct Node_Fila *abajo;
}Node_columna;

//crea nuevo nodo en y
Node_columna *New_nodo_columna(int num){
    Pos_y++;
    Node_columna *newp;
if((newp=(Node_columna *)malloc(sizeof(Node_columna)))==NULL){
fprintf(stderr,"new_item: error en malloc\n");
exit(1);
}
newp->posicion = Pos_y;
newp->next=NULL;
return newp;
}

//crea nuevo nodo en x
Node_Fila *New_nodo_fila(int num){
    Pos_x++;
    Node_Fila *newp;
    if (num = 0) return;
if((newp=(Node_Fila *)malloc(sizeof(Node_Fila)))==NULL){
fprintf(stderr,"new_item: error en malloc\n");
exit(1);
}

newp->posicion=Pos_x;
newp->value=num;
newp->next=NULL;
return newp;
}


Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp){
Node_Fila *p;
if(listp==NULL)
 return newp;
for(p=listp;p->next!=NULL;p=p->next);
p->next = newp;
return listp;
}

Node_columna *add_end_columna(Node_columna *listp, Node_columna *newp){
Node_columna *p;
if(listp==NULL)
 return newp;
for(p=listp;p->next!=NULL;p=p->next);
p->next = newp;
return listp;
}

Node_columna CrearMatriz(int columnas,int filas){
     Node_columna *Newp;
     int i; //

     for(int i=0; i < filas ;i++){  
     for (int j=0;j<;j++){
        printf("ingresar el valor de la posicion %i:%i ",i,j);
        scanf("%i",&n);

        if (j==0){
            
            matriz[i] = New_nodo(n);}
        else {
       matriz[i] = add_end(matriz[i],New_nodo(n));
     
     }
    }


}

void print(){
  
}