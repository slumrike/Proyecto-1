#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// DECLARACION DE ESTRUCTURAS

typedef struct Node_Fila
{
    int value;              // este indica el valor que contiene
    int posicion;           // este define la posicion en x;
    struct Node_Fila *next; // Puntero que apunta a siguiente nodo de la fila(horizontal)

} Node_Fila;

typedef struct Node_columna
{
    int posicion;               // esta define la posicion en y;
    struct Node_columna *abajo; // Puntero que apunta a siguiente nodo de la columna(vertical)
    struct Node_Fila *next;     // Puntero que apunta a siguiente nodo de la fila(horizontal)
} Node_columna;

typedef struct Node_Principal // Nodo principal que alamcena la longitud en filas y columnas de la matriz
{
    int SizeColumna;             // guarda el total de columnas
    int SizeFila;                // guarda el total de filas
    struct Node_columna *matriz; // apuntador a el primer nodo columna(vertical) "revisar diagrama"

} Node_Principal;

/// DECLARACION DE VARIABLES GLOBALES
int sizeFila, sizeColumna, elemento;
Node_Principal *Principal, *matrizsumada, *matriz2, *Mescalar; // matrices necesarias para poder operar
int Pos_x = 0;                                                 // variable global para la posicion de las filas

// crea nuevo nodo de columnas(verticalmente)
Node_columna *New_nodo_columna(int Pos_y)
{

    Node_columna *newp;
    if ((newp = (Node_columna *)malloc(sizeof(Node_columna))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }
    newp->posicion = Pos_y; // aqui determinamos que posicion tiene el nodo en la matriz con respecto a las columnas
    newp->next = NULL;
    newp->abajo = NULL;
    return newp;
}

// crea nuevo nodo de fila(horizontalmente)
Node_Fila *New_nodo_fila(int num)

{

    Node_Fila *newp;
    if ((newp = (Node_Fila *)malloc(sizeof(Node_Fila))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }

    newp->posicion = Pos_x; // determina la posicion que tendra el nodo en la fila
    newp->value = num;      // valor de la posicion en la matriz
    newp->next = NULL;
    return newp;
}

// crea un nuevo nodo principal que apunta a la matriz y contiene las dimenciones de esta
Node_Principal *New_nodo_Principal(int n, int m)
{
    Node_Principal *newp;
    if ((newp = (Node_Principal *)malloc(sizeof(Node_Principal))) == NULL)
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }

    newp->matriz = NULL;
    newp->SizeColumna = n; // total de columnas
    newp->SizeFila = m;    // total de filas
}

// Recorre la fila y adiciona un nodo nuevo de tipo filo al final de esta
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

// recorre la columna y adiciona un nuevo nodo de tipo columna al final de esta
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

// determina si existe una columna que se pide segun su posicion
int Buscar_columna(Node_columna *columna, int pos)
{

    while (columna) // mientras la columna sea diferente de NULL
    {
        if (columna->posicion == pos) // verifica si donde estamos ubicados se encuentra la posicion deseada
        {
            return 1; // de ser positivo retornamos 1(verdadero)
        }
        columna = columna->abajo; // al no ser verdadero nos movemos hacia el siguiente nodo
    }
    return 0; // de nunca encontrar un nodo columna con la posicion pedida retornamos 0(falso)
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

// esta funcion busca un elemento de una fila ya determinada
int Buscar_Elemento_fila(Node_Fila *Fila, int posicion)
{
    while (Fila) // mientras lista != Null
    {
        if (Fila->posicion == posicion) // determina si donde esta parado tiene la misma posicion que la pedida
        {
            return Fila->value; // de ser verdadero retorna el valor que contiene esa posicion;
        }
        Fila = Fila->next; // si no es verdadero la condicion seguira reccoriendo el resto de la fila
    }
    return 0; // de no encontrar la posicion deseada en toda la fila retorna que el valor es 0 puesto que no esta guardado
}

// Funcion de Impresion de una matriz
void print_Matriz(Node_Principal *Principal)
{
    Node_columna *matriz = Principal->matriz; /*Principal->matriz nos indica la columna principal y es asignada a matriz que es la variable de una columna*/
    int filas, columnas;                      // enteros que guaradan las dimenciones de la matriz

    filas = Principal->SizeFila; // asignasion de longitudes correspondientes
    columnas = Principal->SizeColumna;

    for (int i = 1; i <= columnas; i++) // desde 1 hasta el total de columnnas
    {

        if (matriz != NULL && matriz->posicion == i) // si la posicion de la matriz es la misma que la ubicacion i, se buscara los elementos que tiene adentro
        {
            for (int j = 1; j <= filas; j++) // desde 1 hasta la longitud de las filas
            {
                printf("|%i|", Buscar_Elemento_fila(matriz->next, j)); // llama a buscar en una fila los valores de las posiciones j
            }
            matriz = matriz->abajo; // movimiento hacia abajo para ir al siguiente nodo de la columna
        }
        else
        {
            // de no cumplirse la condicion anterior significa que no existe la columna de i por lo que imprimimos puros 0 hasta la longitud de la fila
            for (int j = 1; j <= filas; j++)
            {
                printf("|0|");
            }
        }
        printf("\n");
    }
}
// Funcion encargada de recibir dos matrices y sumarlas generando la matriz resultado
Node_Principal *Suma(Node_Principal *m1, Node_Principal *m2)
{
    // Declaracion de variables a utilizar y sus auxiliares para movimiento
    Node_columna *columna1, *columna2, *columna3 = NULL, *aux;
    Node_Fila *fila1, *fila2, *fila3 = NULL;
    Node_Principal *Resultado = NULL;
    int valor, columnas, filas;

    // verificacion de que sean iguales las matrices
    if ((m1->SizeColumna != m2->SizeColumna) || (m1->SizeFila != m2->SizeFila))
    {
        return Resultado; // de ser diferentes se sale puesto que no se pueden sumar matrices desiguales
    }

    // asignamos las columnas por las que nos moveremos en cada matriz para hacer el recorrido
    columna1 = m1->matriz;
    columna2 = m2->matriz;

    // Variables que indican la longitud en fila y columnas de la matriz total
    filas = m1->SizeFila;
    columnas = m1->SizeColumna;

    // esta sera el Nodo principal donde se guardara la matriz resultado
    Resultado = New_nodo_Principal(m1->SizeColumna, m1->SizeFila);

    for (int i = 1; i <= columnas; i++) // recorremos todas las posibles columnas que puede tener la matriz
    {
        // el primer paso es verificar si las columnas existen en donde estan ubicadas para despues comparar posiciones
        // si la posicon de la columna 1 es igual a la columna 2 significa que ambas existen
        if ((columna1 != NULL && columna1->posicion == i) && (columna2 != NULL && columna2->posicion == i))
        {
            // creamos filas correspondientes a cada columna
            fila1 = columna1->next;
            fila2 = columna2->next;
            for (int j = 1; j <= filas; j++)
            {
                // se buscan los elementos por posicion por fila de ambas columnas y se suman
                valor = (Buscar_Elemento_fila(fila1, j) + Buscar_Elemento_fila(fila2, j));

                Pos_x++;
                // si el valor es 0 no se crea ningun nodo;
                if (valor != 0)
                    fila3 = add_end_fila(fila3, New_nodo_fila(valor));
            }
            columna1 = columna1->abajo;
            columna2 = columna2->abajo;
            columna3 = add_end_columna(columna3, New_nodo_columna(i));
            aux = columna3;
            while (aux->abajo != NULL)
            {
                aux = aux->abajo;
            }
            aux->next = fila3;
            fila3 = NULL;
            Pos_x = 0;
        }
        else
        {
            if ((Buscar_columna(columna1, i)) && (!Buscar_columna(columna2, i)))
            {
                fila3 = columna1->next;

                columna3 = add_end_columna(columna3, New_nodo_columna(i));
                aux = columna3;
                while (aux->abajo != NULL)
                {
                    aux = aux->abajo;
                }
                aux->next = fila3;
                fila3 = NULL;
                columna1 = columna1->abajo;
            }
            else

                if ((!Buscar_columna(columna1, i)) && (Buscar_columna(columna2, i)))
            {
                fila3 = columna2->next;

                columna3 = add_end_columna(columna3, New_nodo_columna(i));
                aux = columna3;
                while (aux->abajo != NULL)
                {
                    aux = aux->abajo;
                }
                aux->next = fila3;
                fila3 = NULL;
                columna2 = columna2->abajo;
            }
        }
    }

    Resultado->matriz = columna3;
    return Resultado;
}

Node_Principal *ProductoPorEscalar(int e, Node_Principal *listp)

{

    Node_columna *columna;
    Node_Fila *fila;

    columna = listp->matriz;

    while (columna)
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
    while (auxColumna != NULL && auxColumna->posicion != Pos_Columna)
    {
        auxColumna = auxColumna->abajo;
    }
    if (auxColumna == NULL)
        return 0;
    return Buscar_Elemento_fila(auxColumna->next, Pos_Fila);
}

void Asignar_Elemento(int Pos_Fila, int Pos_Columna, int elemento, Node_Principal *listp)
{
    Node_columna *auxColumna, *prev, *newpColumna;
    Node_Fila *Fila, *aux, *newpFila;
    int Pos_y = 0;
    Pos_x = Pos_Fila;
    auxColumna = listp->matriz;
    prev = auxColumna;
    if (auxColumna == NULL)
    {
        printf("si pase");
        auxColumna = New_nodo_columna(Pos_Columna);
        Pos_x = Pos_Fila;
        newpFila = New_nodo_fila(elemento);
        listp->matriz = auxColumna;
        auxColumna->next = newpFila;
        return;
    }

    while (auxColumna->abajo != NULL && auxColumna->posicion < Pos_Columna)
    {
        prev = auxColumna;
        auxColumna = auxColumna->abajo;
    }

    if (auxColumna->posicion == Pos_Columna)
    {

        Fila = auxColumna->next;
        aux = Fila;
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

    newpColumna = New_nodo_columna(Pos_Columna);
    Pos_x = Pos_Fila;
    newpFila = New_nodo_fila(elemento);
    newpColumna->next = newpFila;
    if (prev == auxColumna)
    {
        prev->abajo = newpColumna;
        return;
    }
    prev->abajo = newpColumna;
    newpColumna->abajo = auxColumna;

    return;
}

Node_Principal *trans(Node_Principal *Principal)
{
    Node_Principal *NewMatriz;
    Node_columna *Base, *aux;
    NewMatriz = New_nodo_Principal(Principal->SizeFila, Principal->SizeColumna);
    Node_Fila *newFila;
    int e;
    newFila = NULL;
    Base = NewMatriz->matriz;

    for (int i = 1; i <= Principal->SizeFila; i++)
    {

        for (int j = 1; j <= Principal->SizeColumna; j++)
        {
            Pos_x = j;
            e = Obtener_elemento(i, j, Principal);
            if (e)
                newFila = add_end_fila(newFila, New_nodo_fila(e));
        }
        if (newFila != NULL)
        {
            Base = add_end_columna(Base, New_nodo_columna(i));
            NewMatriz->matriz = Base;
            aux = Base;
            while (aux->abajo)
                aux = aux->abajo;
            aux->next = newFila;
        }
        newFila = NULL;
    }

    return NewMatriz;
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
 */

/*Node_Principal *Trans(Node_Principal *Principal)
{
    Node_Principal *newp;
    newp = New_nodo_Principal(Principal->SizeFila, Principal->SizeColumna);
    Node_columna *matriz = Principal->matriz;

    for (int i = 1; i < Principal->SizeColumna; i++)
    {
        if (matriz->posicion = i)
        {
            int elemento = Buscar_elemento_fila(matriz->next, j);
            if (elemento)
            {
                Asignar_Elemento(j, i, elemento, newp);
            }
        }
    }
}*/
