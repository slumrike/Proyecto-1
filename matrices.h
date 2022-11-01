#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// DECLARACION DE ESTRUCTURAS

typedef struct Node_Fila
{
    int value;
    int posicion; // este define la posicion en x;
    struct Node_Fila *next;

} Node_Fila;

typedef struct Node_columna
{
    int posicion; // esta define la posicion en y;
    struct Node_columna *abajo;
    struct Node_Fila *next;
} Node_columna;

typedef struct Node_Principal
{
    int SizeColumna;
    int SizeFila;
    struct Node_columna *matriz;

} Node_Principal;

/// DECLARACION DE VARIABLES GLOBALES

int sizeFila, sizeColumna;
// sirven de posicion para los nodos

Node_Principal *Principal, *matrizsumada, *matriz, *Mescalar;
int Pos_x = 0;

// crea nuevo nodo en y
Node_columna *New_nodo_columna(int Pos_y)
{

    Node_columna *newp;
    if ((newp = (Node_columna *)malloc(sizeof(Node_columna))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }
    newp->posicion = Pos_y;
    newp->next = NULL;
    newp->abajo = NULL;
    return newp;
}

// crea nuevo nodo en x
Node_Fila *New_nodo_fila(int num)

{

    Node_Fila *newp;
    if ((newp = (Node_Fila *)malloc(sizeof(Node_Fila))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }

    newp->posicion = Pos_x;
    newp->value = num;
    newp->next = NULL;
    return newp;
}

Node_Principal *New_nodo_Principal(int n, int m)
{
    Node_Principal *newp;
    if ((newp = (Node_Principal *)malloc(sizeof(Node_Principal))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }

    newp->matriz = NULL;
    newp->SizeColumna = n;
    newp->SizeFila = m;
}

Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp)
{
    Node_Fila *p;
    if (listp == NULL)
        return newp;
    if (newp == NULL)
        return listp;
    for (p = listp; p->next != NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

Node_columna *add_end_columna(Node_columna *listp, Node_columna *newp)
{
    Node_columna *p;
    if (listp == NULL)
        return newp;
    for (p = listp; p->abajo != NULL; p = p->abajo)
        ;
    p->abajo = newp;
    return listp;
}

Node_Principal *CrearMatriz()
{
    Node_Principal *MatrizPrincipal = NULL;
    Node_columna *Newp = NULL, *aux;
    Node_Fila *New_fila = NULL;
    int i, j, n;
    int Pos_y = 0;

    printf("ingresar las dimenciones del arreglo (0x0)\n");
    printf("Columnas = ");
    scanf(" %i", &sizeColumna);
    printf("Filas = ");
    scanf(" %i", &sizeFila);

    MatrizPrincipal = New_nodo_Principal(sizeColumna, sizeFila);

    i = 1;
    for (int i = 1; i <= sizeColumna; i++)
    {

        for (j = 1; j <= sizeFila; j++)
        {
            printf("ingresar el num de la posicion (%i,%i) = ", i, j);
            scanf(" %i", &n);
            Pos_x++;
            if (n != 0)
                New_fila = add_end_fila(New_fila, New_nodo_fila(n));
        }

        if (New_fila != NULL)
        {
            Newp = add_end_columna(Newp, New_nodo_columna(i));

            aux = Newp;
            while (aux->abajo != NULL)
                aux = aux->abajo;
            aux->next = New_fila;
            New_fila = NULL;
        }

        Pos_x = 0;
    }
    MatrizPrincipal->matriz = Newp;
    return MatrizPrincipal;
}

int Buscar_Elemento_fila(Node_Fila *Fila, int posicion)
{
    while (Fila)
    {
        if (Fila->posicion == posicion)
        {
            return Fila->value;
        }
        Fila = Fila->next;
    }
    return 0;
}

void print_Matriz(Node_Principal *Principal)
{
    Node_columna *auxColumna1, *matriz, *bajar, *auxPosMatriz;
    Node_Fila *auxFila;
    int x = 0, num = 0;
    int Pos_y = 0;

    if (Principal == NULL)
    {
        printf("no existe la matriz");
        return;
    }
    matriz = Principal->matriz;

    bajar = matriz;
    auxPosMatriz = matriz;

    Pos_y = 1;

    while (bajar != NULL)
    {

        auxPosMatriz = bajar;
        bajar = bajar->abajo;
        auxFila = auxPosMatriz->next;
        if (bajar != NULL)
        {
            x = bajar->posicion;
        }
        else
            x = Principal->SizeColumna;

        if (auxPosMatriz->posicion == Pos_y)
        {
            for (int i = 1; i <= Principal->SizeFila; i++)
            {
                num = Buscar_Elemento_fila(auxFila, i);
                printf("%i ", num);
            }

            printf("\n");
        }

        if (auxPosMatriz->posicion != Pos_y)
        {

            for (int i = 1; i <= (x - auxPosMatriz->posicion - 1); i++)
            {

                for (int j = 1; j <= Principal->SizeFila; j++)
                {
                    printf("0 ");
                }
            }
            Pos_y = auxPosMatriz->posicion;
        }
        Pos_y++;
    }
}

/*Node_Principal *Suma(Node_Principal *m1, Node_Principal *m2)
{
    Node_columna *columna1, *columna2, *columna3, *aux;
    Node_Fila *fila1, *fila2, *fila3 = NULL;
    Node_Principal *Resultado = NULL;
    int valor;

    // paso 1 verificar que sean iguales las matrices
    if ((m1->SizeColumna != m2->SizeColumna) || (m1->SizeFila != m2->SizeFila))
    {
        return Resultado;
    }

    // paso 2 ver las columnas y asignarlas
    columna1 = m1->matriz;
    columna2 = m2->matriz;

    Resultado = New_nodo_Principal(m1->SizeColumna, m1->SizeFila);
    Pos_y = 0;
    for (int i = 1; i <= m1->SizeColumna; i++)
    {
        columna3 = add_end_columna(columna3, New_nodo_columna());
    }

    aux = columna3;

    for (int i = 1; i <= m1->SizeColumna; i++)
    {

        fila1 = columna1->next;
        fila2 = columna2->next;

        for (int j = 1; j <= m1->SizeFila; j++)
        {

            valor = (Buscar_Elemento_fila(fila1, j) + Buscar_Elemento_fila(fila2, j));
            printf("valor a guardar %i\n", valor);
            Pos_x++;
            if (valor != 0)
                fila3 = add_end_fila(fila3, New_nodo_fila(valor));
            printf("posision %i\n", fila3->value);
        }
        Pos_x = 0;
        columna1 = columna1->abajo;
        columna2 = columna2->abajo;
        columna3->next = fila3;
        fila3 = NULL;

        columna3 = columna3->abajo;
    }

    Resultado->matriz = aux;
    return Resultado;
}*/

Node_Principal *ProductoPorEscalar(int e, Node_Principal *listp)

{

    Node_columna *columna;
    Node_Fila *fila;

    columna = listp->matriz;

    for (int i = 1; i <= listp->SizeColumna; i++)
    {
        fila = columna->next;

        while (fila != NULL)
        {

            fila->value = fila->value * e;
            fila = fila->next;
        }
        columna = columna->abajo;
    }

    return listp;
}

int Obtener_elemento(int Pos_Fila, int Pos_Columna, Node_Principal *listp)
{
    Node_columna *auxColumna;

    auxColumna = listp->matriz;
    for (int i = 1; i < Pos_Columna; i++, auxColumna = auxColumna->abajo)
        ;

    return Buscar_Elemento_fila(auxColumna->next, Pos_Fila);
}

void Asignar_Elemento(int Pos_Fila, int Pos_Columna, int elemento, Node_Principal *listp)
{
    Node_columna *auxColumna;
    Node_Fila *Fila, *aux;
    int Pos_y = 0, Pos_x = 0;
    Pos_x = Pos_Fila;
    auxColumna = listp->matriz;
    for (int i = 1; i < Pos_Columna; i++, auxColumna = auxColumna->abajo)
        ;
    Fila = auxColumna->next;
    aux = Fila;
    if (Fila)
    {
        while (Fila)
        {

            if (Fila->posicion == Pos_Fila)
            {
                Fila->value = elemento;
                return;
            }
            Fila = Fila->next;
        }

        aux = add_end_fila(aux, New_nodo_fila(elemento));
        return;
    }
    auxColumna->next = New_nodo_fila(elemento);

    return;
}

/*Node_Principal *Producto(Node_Principal *m1, Node_Principal *m2)
{

     Node_Principal *matriz_Resultado_principal;
     Node_columna *columnaResultado, auxcolumna;
     int valor1, valor2, auxfila, auxcolumna;

     if (m1->SizeFila != m2->SizeColumna)
         ;
     return;

     matriz_Resultado_principal = New_nodo_Principal(m1->SizeColumna, m2->SizeFila);

     for (int i = 1; i <= sizeColumna; i++)
     {
         columnaResultado = add_end_columna(columnaResultado, New_nodo_columna());
     }

     for (int i = 1; i <= m1->SizeFila; i++)
     {
         }
 }*/