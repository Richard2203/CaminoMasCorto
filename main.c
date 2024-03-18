#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NODOS 14  

// Definición de la estructura de conexión
typedef struct Conexion {
    struct Nodo *nodo;
    int distanciaXY;
} Conexion;

// Definición de la estructura del nodo
typedef struct Nodo {
    char nombre[50];
    int coordenadaX;
    int coordenadaY;
    Conexion **conexiones; // Arreglo dinámico de punteros a Conexion
    int numConexiones; // Número de conexiones
    int visitado; // Marca para evitar ciclos en el recorrido
} Nodo;

// Función para crear un nuevo nodo
Nodo *crearNodo(const char *nombre, int x, int y) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo != NULL) {
        // Copiar el nombre del nodo
        strncpy(nuevoNodo->nombre, nombre, sizeof(nuevoNodo->nombre) - 1);
        nuevoNodo->nombre[sizeof(nuevoNodo->nombre) - 1] = '\0';
        // Asignar las coordenadas
        nuevoNodo->coordenadaX = x;
        nuevoNodo->coordenadaY = y;
        // Inicializar conexiones como NULL y numConexiones como 0
        nuevoNodo->conexiones = NULL;
        nuevoNodo->numConexiones = 0;
    }
    return nuevoNodo;
}

// Función para agregar una conexión a un nodo
void agregarConexion(Nodo *nodo, Nodo *conexion, int distanciaXY) {
    // Incrementar el tamaño del arreglo de conexiones
    nodo->numConexiones++;
    nodo->conexiones = (Conexion **)realloc(nodo->conexiones, sizeof(Conexion *) * nodo->numConexiones);
    if (nodo->conexiones != NULL) {
        // Crear una nueva conexión y asignar el nodo y el distanciaXY
        Conexion *nuevaConexion = (Conexion *)malloc(sizeof(Conexion));
        if (nuevaConexion != NULL) {
            nuevaConexion->nodo = conexion;
            nuevaConexion->distanciaXY = distanciaXY;
            // Agregar la nueva conexión al final del arreglo
            nodo->conexiones[nodo->numConexiones - 1] = nuevaConexion;
        }
    }
}


// Función para recorrer el grafo a partir de un nodo dado
void recorrerGrafo(Nodo *nodo) {
    // Marcar el nodo como visitado
    nodo->visitado = 1;
    
    // Imprimir información del nodo
    printf("Nombre: %s\n", nodo->nombre);
    printf("\tCoordenadas: (%d, %d)\n", nodo->coordenadaX, nodo->coordenadaY);
    printf("\tCamino mas corto: \n");
    
    int caminoMasCorto=nodo->conexiones[0]->distanciaXY;
    Nodo *opcionATomar=nodo->conexiones[0]->nodo;;

    for (int i = 1; i < nodo->numConexiones; i++) {
        printf("\t- %s (distanciaXY: %d)\n", nodo->conexiones[i]->nodo->nombre, nodo->conexiones[i]->distanciaXY);
        
        if (nodo->conexiones[i]->distanciaXY < caminoMasCorto){
            caminoMasCorto=nodo->conexiones[i]->distanciaXY;
            opcionATomar=nodo->conexiones[i]->nodo;
        }
    }


    recorrerGrafo(opcionATomar);
    
    //printf("Opcion a tomar por ser mas corto: %d\n", caminoMasCorto);
    //if (opcionATomar != NULL) {
    //    printf("Nodo a tomar: %s\n", opcionATomar->nombre);
    //    printf("\tCoordenadas: (%d, %d)\n", opcionATomar->coordenadaX, opcionATomar->coordenadaY);
    //} else {
    //    printf("No hay opción a tomar.\n");
    //}

}


int main() {
    // Crear algunos nodos de ejemplo
    Nodo *nodoA = crearNodo("A", 0, 0);
    Nodo *nodoB = crearNodo("B", 1, 1);
    Nodo *nodoC = crearNodo("C", 2, 2);
    Nodo *nodoD = crearNodo("D", 3, 3);
    Nodo *nodoE = crearNodo("E", 4, 4);
    Nodo *nodoF = crearNodo("F", 5, 5);
    Nodo *nodoG = crearNodo("G", 6, 6);
    Nodo *nodoH = crearNodo("H", 7, 7);
    Nodo *nodoI = crearNodo("I", 8, 8);
    Nodo *nodoJ = crearNodo("J", 9, 9);
    Nodo *nodoK = crearNodo("K", 10, 10);
    Nodo *nodoL = crearNodo("L", 11, 11);
    Nodo *nodoM = crearNodo("M", 12, 12);
    Nodo *nodoN = crearNodo("N", 13, 13);


        // Establecer conexiones entre los nodos
    //NODO A
    agregarConexion(nodoA, nodoB, 9); 
    agregarConexion(nodoA, nodoE, 15); 
    agregarConexion(nodoA, nodoJ, 22); 


    //NODO B
    agregarConexion(nodoB, nodoA, 9); 
    agregarConexion(nodoB, nodoC, 11); 
    agregarConexion(nodoB, nodoE, 17); 


    //NODO C
    agregarConexion(nodoC, nodoB, 11); 
    agregarConexion(nodoC, nodoD, 19); 


    //NODO D
    agregarConexion(nodoD, nodoC, 19); 
    agregarConexion(nodoD, nodoE, 15); 
    agregarConexion(nodoD, nodoF, 14); 


    //NODO E
    agregarConexion(nodoE, nodoA, 15); 
    agregarConexion(nodoE, nodoB, 17); 
    agregarConexion(nodoE, nodoD, 15); 
    agregarConexion(nodoE, nodoH, 16); 
    agregarConexion(nodoE, nodoG, 14); 


    //NODO F
    agregarConexion(nodoF, nodoD, 14); 
    agregarConexion(nodoF, nodoH, 15); 
    agregarConexion(nodoF, nodoI, 12); 


    //NODO G
    agregarConexion(nodoG, nodoE, 14); 
    agregarConexion(nodoG, nodoK, 14); 
    agregarConexion(nodoG, nodoL, 25); 


    //NODO H
    agregarConexion(nodoH, nodoE, 16); 
    agregarConexion(nodoH, nodoF, 15); 
    agregarConexion(nodoH, nodoI, 15); 
    agregarConexion(nodoH, nodoL, 17); 

    //NODO I
    agregarConexion(nodoI, nodoF, 12); 
    agregarConexion(nodoI, nodoH, 15); 
    agregarConexion(nodoI, nodoM, 19); 


    //NODO J
    agregarConexion(nodoJ, nodoA, 22); 
    agregarConexion(nodoJ, nodoK, 6); 

    //NODO K
    agregarConexion(nodoK, nodoG, 14); 
    agregarConexion(nodoK, nodoJ, 6); 
    agregarConexion(nodoK, nodoN, 14); 
    


    //NODO L
    agregarConexion(nodoL, nodoH, 17); 
    agregarConexion(nodoL, nodoM, 18); 
    agregarConexion(nodoL, nodoN, 18); 
    agregarConexion(nodoL, nodoG, 25); 

    //NODO M
    agregarConexion(nodoM, nodoI, 19); 
    agregarConexion(nodoM, nodoL, 18); 
    agregarConexion(nodoM, nodoN, 24); 

    //NODO N
    agregarConexion(nodoN, nodoK, 14); 
    agregarConexion(nodoN, nodoL, 18); 
    agregarConexion(nodoN, nodoM, 24); 



    recorrerGrafo(nodoE);

    return 0;
}