#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrices.h"

// funciones del programa
Node_columna *New_nodo_columna(int Pos_y);
Node_Fila *New_nodo_fila(int num);
Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp);
Node_columna *add_end_columna(Node_columna *listp, Node_columna *newp);
Node_Principal *CrearMatriz();
int Buscar_Elemento_fila(Node_Fila *Fila, int posicion);
int Buscar_columna(Node_columna *columna, int pos);
void print_Matriz(Node_Principal *matriz);
Node_Principal *Suma(Node_Principal *m1, Node_Principal *m2);
Node_Principal *ProductoPorEscalar(int e, Node_Principal *listp);
int Obtener_elemento(int Pos_Fila, int Pos_Columna, Node_Principal *listp);
void Asignar_Elemento(int Pos_Fila, int Pos_Columna, int elemento, Node_Principal *listp);
Node_Principal *Producto(Node_Principal *m1, Node_Principal *m2);
Node_Principal *transponer(Node_Principal *Principal);
void FreeMatriz(Node_Principal *listp);

// variables del programa principal
Node_Principal *matriz3;
int operacion, x, y, e;

void main()
{
  Principal = CrearMatriz();

  printf("Que operacion desea realizar?\n1.Obtener elemento\n2.Asignar elemento\n3.Sumar matrices\n4.Producto por escalar\n5.Producto de Matrices\n6.Imprimir la matriz\n7.Transponerla\n");
  scanf("%i", &operacion);
  switch (operacion)
  {
  case 1:
    printf("Ubicacion en X:");
    scanf("%i", &x);
    printf("Ubicacion en Y:");
    scanf("%i", &y);
    printf("EL elemento es: %i", Obtener_elemento(y, x, Principal));
    break;
  case 2:
    printf("Ubicacion en X:");
    scanf("%i", &x);
    printf("Ubicacion en Y:");
    scanf("%i", &y);
    printf("elemento a asignar:");
    scanf("%i", &e);
    Asignar_Elemento(y, x, e, Principal);
    print_Matriz(Principal);
    break;
  case 3:
    matriz2 = CrearMatriz();
    matriz3 = Suma(Principal, matriz2);
    print_Matriz(matriz3);
    break;
  case 4:
    printf("escalar a multiplicar:");
    scanf("%i", &e);
    matriz3 = ProductoPorEscalar(e, Principal);
    print_Matriz(matriz3);
    break;
  case 5:
    matriz2 = CrearMatriz();
    matriz3 = Producto(Principal, matriz2);
    print_Matriz(matriz3);
    break;
  case 6:
    print_Matriz(Principal);
    break;
  case 7:
    matriz3 = transponer(Principal);
    print_Matriz(matriz3);
    break;
  }
}