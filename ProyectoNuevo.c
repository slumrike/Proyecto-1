#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrices.h"

Node_columna *New_nodo_columna();
Node_Fila *New_nodo_fila(int num);
Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp);
Node_columna *add_end_columna(Node_columna *listp, Node_columna *newp);
Node_columna *CrearMatriz();
void print_Matriz(Node_columna *matriz);

void main()
{
  matriz = CrearMatriz();
  print_Matriz(matriz);
}
