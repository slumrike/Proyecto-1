#include <stdio.h>
#include <math.h>

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

/// DECLARACION DE VARIABLES GLOBALES

int sizeFila = 2, sizeColumna = 2;
int Pos_y = 0, Pos_x = 0; // sirven de posicion para los nodos
Node_columna *matriz;

// crea nuevo nodo en y
Node_columna *New_nodo_columna()
{
    Pos_y++;
    Node_columna *newp;
    if ((newp = (Node_columna *)malloc(sizeof(Node_columna))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }
    newp->posicion = Pos_y;
    newp->next = NULL;
    return newp;
}

// crea nuevo nodo en x
Node_Fila *New_nodo_fila(int num)
{
    Pos_x++;
    Node_Fila *newp;
    // if (num = 0)
    //     return;
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

Node_Fila *add_end_fila(Node_Fila *listp, Node_Fila *newp)
{
    Node_Fila *p;
    if (listp == NULL)
        return newp;
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

Node_columna *CrearMatriz()
{
    Node_columna *Newp = NULL, *aux;
    Node_Fila *New_fila = NULL, *aux2 = NULL;
    int i, j, n = 0;

    printf("ingresar las dimenciones del arreglo (0x0)\n");
    printf("Columnas = ");
    scanf(" %d", &sizeColumna);
    printf("Filas = ");
    scanf(" %d", &sizeFila);

    for (i = 1; i <= sizeColumna; i++)
    {
        Newp = add_end_columna(Newp, New_nodo_columna());
    }
    aux = Newp;

    for (i = 1; i <= sizeColumna; i++)
    {

        Newp = Newp->abajo;
        for (j = 1; j <= sizeFila; j++)
        {
            printf("ingresar el num de la posicion (%i,%i) = ", i, j);
            scanf(" %i", &n);

            New_fila = add_end_fila(New_fila, New_nodo_fila(n));
        }

        printf("%i", Newp->posicion);
        aux2 = Newp->next;
        aux2 = New_fila;
        New_fila = NULL;

        // printf("el prmer valor es %i \n", (New_columna->next->value));
    }

    return Newp;
}

void print_Matriz(Node_columna *matriz)
{
    Node_columna *auxColumna1, auxColumna2;
    Node_Fila *auxFila;
    for (int i = 1; i <= sizeColumna; i++)
    {
        auxColumna1 = matriz;
        auxFila = matriz->next;

        for (int j = 1; j <= sizeFila; j++)
        {

            printf("%i\n", auxFila->value);
            auxFila = auxFila->next;
        }
        printf("\n");
        matriz = matriz->abajo;
    }
}

void prueba()
{

    Node_columna *newp = NULL;

    for (int i = 1; i < 4; i++)
    {
        newp = add_end_columna(newp, New_nodo_columna());
    }
    printf("%i\n", newp->posicion);
    printf("%i", newp->abajo->posicion);
}