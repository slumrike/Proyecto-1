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

// Producto escalar multiplica toda una matriz por el mismo numero
Node_Principal *ProductoPorEscalar(int e, Node_Principal *listp)
{
    Node_columna *columna; // esta sera la columna de la matriz(vertical)
    Node_Fila *fila;       // esta sera la fila de la matriz(fila)

    columna = listp->matriz; // Asignamos la columna de nuestro nodo principal a la variable columna

    while (columna) // mientras columna sea distinto de NULL
    {
        fila = columna->next; // nos posicionamos en la fila de la columna actual

        while (fila != NULL) // sirve para repetir los cambios de valores
        {

            fila->value = fila->value * e; // Modificamos el valor contenido en fila por fila por el elemto
            fila = fila->next;             // despues de modificar nos movemos al siguiente nodo
        }
        columna = columna->abajo; // nos movemos en columnas para seguir modificando hasta terminar la matriz
    }

    return listp;
}

// Funcion que devuelve el valor de un elemento en cualquier parte de la matriz
int Obtener_elemento(int Pos_Fila, int Pos_Columna, Node_Principal *listp)
{
    Node_columna *auxColumna; // declaramos la columna donde buscaremos

    auxColumna = listp->matriz; // asignamos la columna de la lista principal

    // preguntamos si la columna es NUll y despues si su posicion es difertene a la de columna
    //  por lo que mientras no la consiga o sea NUll el resultado estara dentro del ciclo
    while (auxColumna != NULL && auxColumna->posicion != Pos_Columna)
    {
        auxColumna = auxColumna->abajo; // movimiento para recorrer toda la columna
    }
    if (auxColumna == NULL) // de no conseguirla terminara en NULL
        return 0;           // devolvera 0 indicando que no existe la columna

    // de existir la columna ahora busca en la fila de esa columna y retorna el valor encontrado
    return Buscar_Elemento_fila(auxColumna->next, Pos_Fila);
}

// Funcion que asigna a una posicion determinada un elemento determinado
void Asignar_Elemento(int Pos_Fila, int Pos_Columna, int elemento, Node_Principal *listp)
{
    // declaracion de variables
    Node_columna *auxColumna, *prev, *newpColumna, *liberar;
    Node_Fila *Fila, *aux, *newpFila;
    int Pos_y = 0;
    // se define la pos horizontal como la posicion de la fila a buscar
    Pos_x = Pos_Fila;
    prev = auxColumna;          // el nodo anterior a auxColumna sera dado por prev
    auxColumna = listp->matriz; // define la columna donde se trabajara

    if (elemento != 0)
    {
        if (auxColumna == NULL) // de ser la columna null significa que es una matriz vacia
        {
            auxColumna = New_nodo_columna(Pos_Columna); // creamos el nodo columna con la posicion pedida
            newpFila = New_nodo_fila(elemento);         // creamos una fila con el elemento pedido
            listp->matriz = auxColumna;                 // enlazamos la columna con la lista principal
            auxColumna->next = newpFila;                // enlazamos la columna con su respectiva fila
            return;
        }

        // Primero se pregunta si la columna de abajo de donde estamos es nula, puesto que protege que nuestras operaciones
        // Despues se pregunta si la posicion es menor que la posicion que buscamos
        while (auxColumna->abajo != NULL && auxColumna->posicion < Pos_Columna)
        {
            prev = auxColumna;
            auxColumna = auxColumna->abajo;
        } // nos movemos por las columnas hasta estar en el ultimo elemento o estar justo antes o encima de donde deberia estar la columna buscada
        // Verifica si auxColumna es igual a la posicion que buscamos
        if (auxColumna->posicion == Pos_Columna)
        {

            Fila = auxColumna->next; // fila de la columna
            aux = Fila;
            while (Fila) // mientras fila exista
            {

                if (Fila->posicion == Pos_Fila) // si la posicion de la fila corresponde con la que buscamos significa que existe y la encontramos
                {
                    Fila->value = elemento; // le cambiamos el elemento y retornamos
                    return;
                }
                Fila = Fila->next; // vamos moviendonos en las filas
            }
            // de no existir el elemento tenemos que crearlo
            aux = add_end_fila(aux, New_nodo_fila(elemento)); // se adiciona el elemento al final de la fila con su posicion correspondiente
            return;
        }

        newpColumna = New_nodo_columna(Pos_Columna); // creamos una nueva columna con la posicion indicada
        Pos_x = Pos_Fila;
        newpFila = New_nodo_fila(elemento); // creamos una nueva fila
        newpColumna->next = newpFila;       // asignamos la nueva fila a nuestra columna
        if (prev == auxColumna)             // si el anterior es igual a columna significa que el siguiente es NULL,
        // por tanto solo hay que asignarle a el prev la direccion del nuevo nodo de la columna
        {
            prev->abajo = newpColumna;
            return;
        }
        // en caso contrario asignamos al siguiente de prev a el nuevo nodo de columna,
        //  y a el posterios de el nuevo nodo le asignamos el auxColumna (asi queda ordenado en columnas)
        prev->abajo = newpColumna;
        newpColumna->abajo = auxColumna;

        return;
    }
    // si el elemento es 0 utilizamos otro tipo de condiciones para poder garantizar liberar los nodos
    if (Buscar_columna(auxColumna, Pos_Columna) != 0) // verifica si existe la columna a buscar
    {
        prev = NULL;
        while (auxColumna) // mientras la columna sea diferente de NULL
        {

            if (auxColumna->posicion == Pos_Columna) // verifica si donde estamos ubicados se encuentra la posicion deseada
            {

                if ((prev == NULL) && (auxColumna->next->next == NULL)) // esta condicion verifica si es la primera columna y la matriz solo tiene 1 elemento
                {
                    auxColumna = listp->matriz;
                    listp->matriz = listp->matriz->abajo; // asignamos al nodo principal la segunda columna
                    free(auxColumna->next);
                    free(auxColumna);
                    return; // free a la columna y la fila
                }

                if ((auxColumna->next->next == NULL)) // si solo hay un nodo de fila en la columna
                {
                    Fila = auxColumna->next;         // auxiliar que servira para hacerle free
                    liberar = auxColumna;            // guardamos el nodo columna actual para poder hacerle free
                    prev->abajo = auxColumna->abajo; // enlazamos el nodo anterior con el nodo actual
                    free(liberar);                   // liberacion de nodos
                    free(Fila);                      // liberacion de nodos

                    return;
                }

                Fila = auxColumna->next;                  // ahora asignamos la fila donde buscaremos el elemento
                if (Buscar_Elemento_fila(Fila, Pos_Fila)) // si la posicion a cambiar no se encuentra no entramos nisiquiera
                {
                    newpFila = NULL;
                    while (Fila)
                    {
                        // condicion que verifica si la primera fila encontrada es la necesitada
                        if (Fila->posicion == Pos_Fila && newpFila == NULL)
                        {
                            auxColumna->next = Fila->next; // se asigna como el primero de la fila el siguiente a fila
                            free(Fila);                    // liberamos el nodo deseado
                            return;
                        }

                        if (Fila->posicion == Pos_Fila)
                        {

                            newpFila->next = Fila->next;
                            free(Fila);
                            return;
                        }

                        newpFila = Fila;
                        Fila = Fila->next;
                    }
                }
            }
            prev = auxColumna;
            auxColumna = auxColumna->abajo; // al no ser verdadero nos movemos hacia el siguiente nodo
        }

        return;
    }
}

// Funcion que transpone una matriz
Node_Principal *transponer(Node_Principal *Principal)
{
    // Declaracion de variables
    Node_Principal *NewMatriz;
    Node_columna *Base, *aux;
    Node_Fila *newFila;

    NewMatriz = New_nodo_Principal(Principal->SizeFila, Principal->SizeColumna);
    // creacion de Nodo Principal con las filas y columnas correspondientes a la transpuesta

    int e;                    // variable que guarda el valor que contiene una posicion espesifica
    newFila = NULL;           // Inicializamos la nueva fila
    Base = NewMatriz->matriz; // Bases sera nuestra columna del resultado

    for (int i = 1; i <= Principal->SizeFila; i++) // para las filas
    {

        for (int j = 1; j <= Principal->SizeColumna; j++) // para las columnas
        {
            Pos_x = j; // determinamos la posicion para que sea igual a j
            e = Obtener_elemento(i, j, Principal);
            if (e)                                                 // si e es diferente de 0 lo adiciono a la fila
                newFila = add_end_fila(newFila, New_nodo_fila(e)); // se va creando una fila de los elementos que estan en las columnas
        }

        if (newFila != NULL) // Fila existe
        {
            Base = add_end_columna(Base, New_nodo_columna(i)); // le creamos un nodo de columna al final a al columna principal
            NewMatriz->matriz = Base;                          // se le asigna al nodo principal la columna
            aux = Base;                                        // creamos un auxiliar para movernos
            while (aux->abajo)
                aux = aux->abajo; // nos vamos al ultim elemento de la columna

            aux->next = newFila; // le asignamos la fila a la columna creada
        }
        // reiniciamos newFila
        newFila = NULL;
    }

    return NewMatriz;
}

// Funcion para eliminar matrices evitando basura
void FreeMatriz(Node_Principal *listp)
{
    Node_columna *columna, *auxcolumna;
    Node_Fila *auxfila, *fila;

    columna = listp->matriz;
    for (; columna != NULL; columna = auxcolumna)
    {
        fila = columna->next;
        for (; fila != NULL; fila = auxfila)
        {
            auxfila = fila->next;
            free(fila);
        }
        auxcolumna = columna->abajo;
        free(columna);
    }
    free(listp);
    return;
}

// Funcion que resuelve el producto de las matrices
Node_Principal *Producto(Node_Principal *m1, Node_Principal *m2)
{
    // declaracion de variables a usar
    Node_Principal *matriz_Resultado_principal, *trans;
    Node_columna *columnaResultado, *auxcolumna, *columna;
    Node_Fila *auxfila;
    int valores;

    // primero creamos la matriz del resultado que tendra las columnas de la priera matriz y las filas de la segunda matroiz
    matriz_Resultado_principal = New_nodo_Principal(m1->SizeColumna, m2->SizeFila);
    // verificamos que se puedan operar
    if (m1->SizeFila != m2->SizeColumna)
        return matriz_Resultado_principal;

    // la columna donde estaran los resultados de la multplicacion
    columnaResultado = matriz_Resultado_principal->matriz;

    trans = transponer(m2); // la transpuesta de la segunda matriz

    for (int i = 1; i <= matriz_Resultado_principal->SizeColumna; i++) // se usa para recorrer todas las columnas de la nueva matriz
    {
        auxfila = NULL;
        valores = 0;

        for (int j = 1; j <= matriz_Resultado_principal->SizeFila; j++) // se usa para recorrer todas las filas de la nueva matriz
        {
            Pos_x = j;
            for (int z = 1; z <= m1->SizeFila; z++) // calcula los valores que corresponden a una fila
            {
                valores += Obtener_elemento(z, i, m1) * Obtener_elemento(z, j, trans); // calcula los valores de la suma de la mulltiplicacion de las cordenadas
            }
            if (valores) // si existe un valor este se le pondra a la suma con su respectiva localizacion
            {
                auxfila = add_end_fila(auxfila, New_nodo_fila(valores));
            }
            valores = 0;
        }

        if (auxfila) // si existe la fila se la ponemos a la columna correspondiente de columnaResultado
        {
            columna = New_nodo_columna(i);
            columna->next = auxfila;

            columnaResultado = add_end_columna(columnaResultado, columna);
            matriz_Resultado_principal->matriz = columnaResultado;
        }
        // de no existir la fila nisiquiera se crea una columna
    }
    FreeMatriz(trans);
    return matriz_Resultado_principal;
}
