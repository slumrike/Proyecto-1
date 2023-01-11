// structuras del TAD
// Estructura de cada nodo de la lista
typedef struct Node
{
    int value;
    struct Node *pos;
} Node;

// Estructura de la lista principal
typedef struct Principal
{
    struct Node *first, *end;
} Principal;

Principal *CrearLista();
Node *CrearNodo(int value);
Node *Xor(Node *Nodo1, Node *Nodo2);
int EsVacia(Principal *lista);
int InsertarPrincipio(Principal *lista, int value);
void listarInicioFinal(Principal *lista);
void listarFinalInicio(Principal *lista);
void inicializar(Principal *lista);
int insertarFinal(Principal *lista, int value);
int CantidadElemntos(Principal *lista);
int Buscar(Principal *lista, int elemento);
int SacarPrincipio(Principal *lista, int *Elemento);
int SacarFinal(Principal *lista, int *Elemento);
int SacarPrimeraOcurrencia(Principal *lista, int *Elemento);
int VerificacionDeOrden(Principal *lista);
int InsertarOrdenado(Principal *lista, int Elemento);
