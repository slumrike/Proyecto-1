#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrices.h"

Node_columna *New_nodo_columna();
Node_Fila *New_nodo_fila(int num);
Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp);
Node_columna *add_end_columna(Node_columna *listp, Node_columna *newp);
Node_Principal *CrearMatriz();
int Buscar_Elemento_fila(Node_Fila *Fila, int posicion);
void print_Matriz(Node_Principal *matriz);
Node_Principal *Suma(Node_Principal *m1, Node_Principal *m2);
Node_Principal *ProductoPorEscalar(int e, Node_Principal *listp);
void Asignar_Elemento(int Pos_Fila, int Pos_Columna, int elemento, Node_Principal *listp);
Node_Principal *Producto(Node_Principal *m1, Node_Principal *m2);

void main()
{
  Principal = CrearMatriz();
  print_Matriz(Principal);
  printf("\n");

  Asignar_Elemento(2, 2, 9, Principal);
  print_Matriz(Principal);
}
