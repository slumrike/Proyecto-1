#include <stdio.h>
#include "Funciones.h"
#include <math.h>

void main()
{
    int valor;
    Principal *lista;
    int cond = 1, e;

    lista = CrearLista();
    // menu
    while (cond)
    {
        printf("\nIngresar que desea hacer \n\n");
        printf("0.- salir\n");
        printf("1.- inicializar la lista \n");
        printf("2.- Ver si esta vacia la lista \n");
        printf("3.- Insertar al principio de la lista \n");
        printf("4.- Insertar al final de la lista \n");
        printf("5.- Insertar en orden en la lista\n");
        printf("6.- Buscar un elemento en la lista \n");
        printf("7.- Sacar primer elemento \n");
        printf("8.- Sacar ultimo elemento \n");
        printf("9.- Sacar primera ocurrencia de un elemento \n");
        printf("10.- Listar la lista de inicio a final \n");
        printf("11.- Listar la lista de final a inicio  \n");
        printf("12.- Contar la cantidad de elementos de la lista \n");
        scanf("%i", &cond);
        switch (cond)
        {
        case 1:
            inicializar(lista);
            printf("la lista ha sido inicializada\n");
            break;

        case 2:
            if (EsVacia(lista))
                printf("La lista esta vacia \n");
            else
                printf("La lista tiene elementos \n");

            break;

        case 3:
            printf("ingresar el valor a insertar :");
            scanf("%i", &e);
            InsertarPrincipio(lista, e);

            break;

        case 4:

            printf("ingresar el valor a insertar :");
            scanf("%i", &e);
            insertarFinal(lista, e);

            break;

        case 5:
            printf("ingresar el valor a insertar :");
            scanf("%i", &e);
            if (InsertarOrdenado(lista, e))
            {
                printf("se ha insertado exitosamente");
            }
            else
                printf("no se ha podido insertar el elemento, compruebe que la lista este ordenada");

            break;

        case 6:
            printf("ingresar el valor a buscar : ");
            scanf("%i", &e);
            if (Buscar(lista, e))
                printf("si esta el elemento en la lista \n");
            else
                printf("No se encuentra el elemento en la lista\n");
            break;

        case 7:

            if (SacarPrincipio(lista, &valor))
                printf("El elemento sacado es %i\n", valor);
            else
                printf("la lista esta vacia, nos se puede sacar nada\n");

            break;
        case 8:
            if (SacarFinal(lista, &valor))
                printf("El elemento sacado es %i\n", valor);
            else
                printf("la lista esta vacia, nos se puede sacar nada\n");
            break;
        case 9:
            printf("ingresar el valor a sacar : ");
            scanf("%i", &valor);
            if (SacarPrimeraOcurrencia(lista, &valor))
                printf("El elemento %i ha sido sacado exitosamente\n", valor);
            else
                printf("el elemento no se encuentra en la lista");
            break;
        case 10:
            listarInicioFinal(lista);

            break;
        case 11:
            listarFinalInicio(lista);
            break;
        case 12:
            printf("La cantidad de elementos es= %i \n", CantidadElemntos(lista));
            break;

        default:
            break;
        }
    }
}
