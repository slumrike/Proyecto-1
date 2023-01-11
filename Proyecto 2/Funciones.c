#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "Funciones.h"

// Funcion de exort
Node *Xor(Node *Nodo1, Node *Nodo2)
{
    return ((Node *)((uintptr_t)(Nodo1) ^ (uintptr_t)(Nodo2)));
}

// Funcion que crea la lista a trabajar
Principal *CrearLista()
{
    Principal *lista;

    if ((lista = (Principal *)malloc(sizeof(Principal))) == NULL) // Se crea el espacio de memoria
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }

    // Se inicializa el inicio y el final
    lista->end = NULL;
    lista->first = NULL;
}

// Funcion que crea cada nodo de la lista
Node *CrearNodo(int value)
{
    Node *newp;
    if ((newp = (Node *)malloc(sizeof(Node))) == NULL) // Crea el espacio de memoria
    {
        fprintf(stderr, "new_item: error en malloc\n");
        exit(1);
    }

    // Inicializacion de la posicion y se le asigna el valor
    newp->value = value;
    newp->pos = NULL;
}

// Funcion de verificacion si la lista esta vacia
int EsVacia(Principal *lista)
{
    if (lista->first == NULL) // Verifica si esta en NUll el primer nodo, de ser asi esta vacia y retorma verdadero
        return 1;
    // en caso contrario retorna falso
    return 0;
}

// Funcion que inserta al principio de la lista
int InsertarPrincipio(Principal *lista, int value)
{
    Node *newp, *aux;
    newp = CrearNodo(value); // Crea el nodo a insertar

    if (EsVacia(lista)) // Verifica si la lista esta vacia
    {
        // Asigna al incio y al final el mismo nodo
        lista->first = newp;
        lista->end = newp;
        return 1; // retorna verdadero
    }

    // de lo contrario significa que hay nodos en la lista
    aux = lista->first;  // se designa un auxiliar para poder insertar antes del primero
    lista->first = newp; // ahora asignamos el primero al nuevo nodo
    // se actualizan los cambios en las posiciones con el Xor
    newp->pos = Xor(NULL, aux);
    aux->pos = Xor(newp, Xor(NULL, aux->pos));
    return 1;
}

// Funcion Que muestra la lista de inicio a fin
void listarInicioFinal(Principal *lista)
{
    Node *aux, *prev, *t;
    prev = NULL;        // inicializacion del previo
    aux = lista->first; // se le asigna a auxiliar el primero para poder recorrer

    if (EsVacia(lista)) // se verifica si esta vacia
    {
        printf("la lista esta vacia \n");
        return;
    }

    if (lista->end == lista->first) // verifica si solo hay un elemennto en la lista
    {
        printf("NULL <->|%i|<-> NULL \n", aux->value);
        return;
    }
    printf("NULL");
    // de resto se hace su respectivo recorrido
    do
    {
        printf("<->| %i |", aux->value);
        // Movimiento hacia la derecha
        t = prev;
        prev = aux;
        aux = Xor(t, aux->pos);
        //---------------------------

    } while (prev != lista->end); // lo repetira hasta que llegue al final de la lista

    printf("<-> NULL\n");
    return;
}

// Funcion que muestra la lista de inicio a fin
void listarFinalInicio(Principal *lista)
{
    Node *aux, *prev, *t;
    prev = NULL;      // Inicializacion del previo
    aux = lista->end; // se determina que el auxiliar sea el final para ir inverso

    if (EsVacia(lista))
    {
        printf("la lista esta vacia \n");
        return;
    }

    if (lista->end == lista->first) // Si solo hay un elemento se imprime dicho elemento
    {
        printf(" NULL <->| %i |<->NULL \n", aux->value);
        return;
    }
    printf("NULL ");
    // de resto se recorre hacia la izquierda
    do
    {
        printf("<->| %i |", aux->value);
        // Movimiento con el XOR
        t = prev;
        prev = aux;
        aux = Xor(t, aux->pos);
        //-------------

    } while (prev != lista->first);
    printf(" <-> NULL\n");
    return;
}

// Funcion que borra la lista de haber algo
void inicializar(Principal *lista)
{
    Node *t, *prev, *aux;
    // Se hace un auxiliar de primer elemento para recorrer la lista
    aux = lista->first;
    // inicializacion de previo
    prev = NULL;

    if (EsVacia(lista)) // si esta vacia ya esta inicializada
        return;

    if (lista->end == lista->first) // verifica si solo hay un elemento
    {
        free(aux);                        // libera el elemento
        lista->end = lista->first = NULL; // inicializa ambos inicio y final
        return;
    }
    // de lo contrario se recorre toda la lista
    do
    {
        // Movimiento Con el Xor
        lista->first = Xor(prev, lista->first->pos);
        t = prev;
        prev = aux;
        //--------------------
        free(t); // Se libera el nodo
    } while (lista->first != lista->end);
    // continua hata que el primero sea igual al ultimo
    // se asigna el unico nodo a aux
    aux = lista->first;
    lista->first = NULL;
    lista->end = NULL;
    // se libera auxiliar
    free(aux);
    return;
}

// Funcion que inserta al final de la lista
int insertarFinal(Principal *lista, int value)
{
    Node *newp, *aux;

    // se crea el nuevo nodo a insertar
    newp = CrearNodo(value);

    if (EsVacia(lista))
    {
        // Se hace que inicio y fin sea el nuevo nodo
        lista->first = newp;
        lista->end = newp;
        return 0;
    }

    // se hace una sustitucion del ultimo nodo
    aux = lista->end;
    lista->end = newp;
    // se actualizan los Xor de los ultimos 2 nodos
    newp->pos = Xor(NULL, aux);
    aux->pos = Xor(newp, Xor(NULL, aux->pos));
    return 1;
}

// Funcion que cuenta la cantidad de elementos
int CantidadElemntos(Principal *lista)
{
    Node *aux, *prev, *t;
    prev = NULL;
    aux = lista->first;
    // Contador de elementos
    int cont = 0;

    if (EsVacia(lista)) // si la lista esta vacia no hay elementos
        return cont;

    // Movimiento que se repite hasta que llega la final
    while (prev != lista->end)
    {
        cont++;
        // Movimiento con Xor
        t = prev;
        prev = aux;
        aux = Xor(t, aux->pos);
        //-------------
    }
    return cont;
}

// Funcion que busca un elementoo
int Buscar(Principal *lista, int elemento)
{
    Node *aux, *prev, *t;
    prev = NULL;
    aux = lista->first;

    if (elemento == lista->end->value || elemento == lista->first->value) // Verifica si el primer o ultimo Nodo tienen el elemento que se busca
        return 1;                                                         // de ser asi retorna verdadero

    // moovimiento hasta que llega al final de la lista
    while (aux != lista->end)
    {
        // Movimiento  con Xor
        t = prev;
        prev = aux;
        aux = Xor(t, aux->pos);
        //-----------------
        if (aux->value == elemento) // si el nodo tiene el elemento retorna verdadero
            return 1;
    }
    // si no lo encuentra devuelve falso
    return 0;
}

// Funcion que saca el primer elemento
int SacarPrincipio(Principal *lista, int *Elemento)
{
    Node *aux;
    if (EsVacia(lista)) // Verifica si esta vacia la lista
    {
        return 0; // de estar vacia no se puede sacar el elemento
    }

    (*Elemento) = lista->first->value; // aqui se determina el elemento del primero nodo, lo cual devuelve dicho valor al terminar la funcion

    if (lista->first == lista->end) // Verifica si la lista solo tiene un elemento
    {
        // al estar un solo elemento la lista quedara vacia por lo que se puede inicializar
        inicializar(lista);
        return 1; // retorna verdadero ya que se logro sacar el elemento
    }

    // se guarda el primer elemento
    aux = lista->first;
    // el primero ahora sera el segundo de la lista original
    lista->first = aux->pos;
    // se actualiza el Xor del nuevo primer elemento
    lista->first->pos = Xor(NULL, Xor(aux, lista->first->pos));
    // se libera el nodo guardado
    free(aux);
    return 1;
}

// Funcion que saca el ultimo elemento
int SacarFinal(Principal *lista, int *Elemento)
{
    Node *aux;

    if (EsVacia(lista)) // Verifica si esta vacia la lista
    {

        return 0; // de estar vacia no se puede sacar el elemento
    }

    (*Elemento) = lista->end->value; // aqui se determina el elemento del ultimo nodo, lo cual devuelve dicho valor al terminar la funcion

    if (lista->first == lista->end) // Verifica si la lista solo tiene un elemento
    {
        // al estar un solo elemento la lista quedara vacia por lo que se puede inicializar
        inicializar(lista);
        return 1; // retorna verdadero ya que se logro sacar el elemento
    }

    // se guarda el ultimo elemento
    aux = lista->end;
    // el ultimo ahora sera el penultimo de la lista original
    lista->end = aux->pos;
    // se actualiza el Xor del nuevo primer elemento
    lista->end->pos = Xor(NULL, Xor(aux, lista->end->pos));
    // se libera el nodo guardado
    free(aux);
    return 1;
}

// Funcion que saca la primera ocurrencia de un elemento
int SacarPrimeraOcurrencia(Principal *lista, int *Elemento)
{
    Node *aux, *aux2, *prev, *t;
    prev = NULL;
    aux = lista->first;

    if (EsVacia(lista)) // verifica si esta vacia, de estarlo no puede sacar la primera ocurrencia
    {
        return 0;
    }

    if (!Buscar(lista, *Elemento)) // busca el elemento, de no estar no se puede sacar
    {
        return 0;
    }

    if (lista->first->value == *Elemento) // verifica si el primer elemento es la ocurrencia
    {
        return SacarPrincipio(lista, Elemento); // de ser asi lo saca y retorna
    }

    while (aux != lista->end->pos) // se repite hasta que llegue al penultimo elemento
    {
        // movimiento con Xor
        t = prev;
        prev = aux;
        aux = Xor(t, aux->pos);
        //------------------
        if (aux->value == *Elemento) // esto determina si el nodo contiene el elemento buscado
        {
            // aux2 representa el siguiente nodo al actual
            aux2 = Xor(prev, aux->pos);
            // se actualizan los Xor del nodo previo y el siguiente
            prev->pos = Xor(aux2, Xor(prev->pos, aux));
            aux2->pos = Xor(prev, Xor(aux, aux2->pos));
            // Elimina el nodo donde se encontraba el elemento buscado
            free(aux);
            return 1;
        }
    }
    // verifica si el ultimo elemento es la ocurrencia
    if (lista->end->value == *Elemento)
    {
        return SacarFinal(lista, Elemento); // de ser asi lo saca y retorna
        return 1;
    }

    return 0;
}

// Funcion que verifica si hay orden en la lista
int VerificacionDeOrden(Principal *lista)
{
    Node *aux, *prev, *t;
    aux = lista->first;
    prev = NULL;

    // Verifica si va de menor a mayor
    if (lista->first->value < lista->end->value)
    {
        while (aux != lista->end)
        {
            // Movimiento con Xor
            t = prev;
            prev = aux;
            aux = Xor(t, aux->pos);
            //-----------------

            if (prev->value > aux->value) // Si hay una inconsistencia se retorna que 0 (no esta ordenado )
            {
                return 0;
            }
        }
        return 1; // de no haber inconsistencia indica que esta ordenada de menor a mayor
    }

    // verifica si va de mayor a menor la lista
    if (lista->first->value > lista->end->value)
    {
        // repite hasta llegar al final de la lista
        while (aux != lista->end)
        {
            // Movimiento con Xor
            t = prev;
            prev = aux;
            aux = Xor(t, aux->pos);
            //--------------------

            if (prev->value < aux->value) // Si hay una inconsistencia se retorna que 0 (no esta ordenado )
            {
                return 0;
            }
        }

        return 2; // de no haber inconsistencia indica que esta ordenada de mayor a menor
    }

    return 0;
}

// Funcion que inserta de manera ordenada en la lista
int InsertarOrdenado(Principal *lista, int Elemento)
{

    Node *aux, *prev, *newp, *t;
    aux = lista->first;
    prev = NULL;
    if (EsVacia(lista))
    {
        InsertarPrincipio(lista, Elemento);
    }

    if (Buscar(lista, Elemento))
    {
        // El elemento ya esta en la lista por lo que no se puede insertar otra vez
        return 0;
    }

    if (lista->first == lista->end) // si la lista solo tiene un elemento se inserta al principio
    {
        InsertarPrincipio(lista, Elemento);
    }

    switch (VerificacionDeOrden(lista)) // Se verifica el orden y nos dira si es de mayor a menor o de menor a mayor, o si la lista no esta ordenada
    {
    case 1:

        // Caso 1 De menor a mayor
        if (Elemento < lista->first->value) // si el elemento ya es menor que el el primer nodo
        {
            // se inserta la principio y retornamos verdadero
            InsertarPrincipio(lista, Elemento);
            return 1;
        }

        if (Elemento > lista->end->value) // si el elemento ya es menor que el el primer nodo
        {
            // se inserta al final y retornamos verdadero
            insertarFinal(lista, Elemento);
            return 1;
        }

        while (Elemento > aux->value) // mientras el elemento sea mayor que el nodo actual
        {
            // movimiento Xor
            t = prev;
            prev = aux;
            aux = Xor(t, aux->pos);
            //------------
        }

        // se detendra al encontrar un elemento mayor
        // se crea el nuevo nodo
        newp = CrearNodo(Elemento);
        // se actualizan todos los pos de los elementos anteriores y siguientes de la ubicacion del nodo
        newp->pos = Xor(prev, aux);
        prev->pos = Xor(Xor(prev->pos, aux), newp);
        aux->pos = Xor(Xor(prev, aux->pos), newp);

        return 1;

    case 2:

        // Caso 2 de mayor a menor

        if (Elemento > lista->first->value) // si el elemento ya es mayor al primer valor se inserta al principio
        {
            InsertarPrincipio(lista, Elemento);
            return 1;
        }

        if (Elemento < lista->end->value) // si el elemento ya es menor que el ultimo elemento se inserta al final
        {
            insertarFinal(lista, Elemento);
            return 1;
        }

        while (Elemento < aux->value) // mientras el elemento sea menor que el nodo actual
        {
            // Movimiento Xor
            t = prev;
            prev = aux;
            aux = Xor(t, aux->pos);
            //---------------
        }
        // se detendra al encontrar un elemento menor
        // se crea el nuevo nodo
        newp = CrearNodo(Elemento);
        // se actualizan todos los pos de los elementos anteriores y siguientes de la ubicacion del nodo
        newp->pos = Xor(prev, aux);
        prev->pos = Xor(Xor(prev->pos, aux), newp);
        aux->pos = Xor(Xor(prev, aux->pos), newp);

        return 1;

    default:
        return 0;
    }
    return 0;
}
