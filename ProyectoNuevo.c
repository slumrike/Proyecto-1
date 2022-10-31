#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrices.h"

Node_columna *New_nodo_columna();
Node_Fila *New_nodo_fila(int num);
Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp);
Node_columna *add_end_columna(Node_columna *listp, Node_columna *newp);
Node_Principal *CrearMatriz();
void print_Matriz(Node_Principal *matriz);
Node_Principal *Suma(Node_Principal *m1, Node_Principal *m2);
Node_Principal *ProductoPorEscalar(int e, Node_Principal *listp);

void main()
{
  Principal = CrearMatriz();
  // matriz = CrearMatriz();
  print_Matriz(Principal);
  printf("\n");
  // print_Matriz(matriz);

  // matrizsumada = Suma(Principal, matriz);
  printf("holahola\n");
  // print_Matriz(matrizsumada);
  Mescalar = ProductoPorEscalar(5, Principal);
  print_Matriz(Mescalar);
}
