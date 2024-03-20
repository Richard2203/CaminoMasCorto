#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NODOS 14  
int nodosRecorridos = 1;
int contador=14;
int isSiguienteNodoOrigen=0;

typedef struct Conexion {
    struct Nodo *nodo;
    int distanciaXY;
} Conexion;


typedef struct Nodo {
    char nombre[50];
    int coordenadaX;
    int coordenadaY;
    Conexion **conexiones; 
    Conexion **conexionesProhibidos; 
    int numConexiones; 
    int numConexionesProhibidas;
    int visitado;
} Nodo;

// Función para crear un nuevo nodo
Nodo *crearNodo(const char *nombre, int x, int y) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo != NULL) {
        
        strncpy(nuevoNodo->nombre, nombre, sizeof(nuevoNodo->nombre) - 1);
        nuevoNodo->nombre[sizeof(nuevoNodo->nombre) - 1] = '\0';

        nuevoNodo->coordenadaX = x;
        nuevoNodo->coordenadaY = y;

        nuevoNodo->conexiones = NULL;
        nuevoNodo->numConexiones = 0;
        
        nuevoNodo->conexionesProhibidos=NULL;
        nuevoNodo->numConexionesProhibidas = 0;

        nuevoNodo->visitado=0;
    }
    return nuevoNodo;
}

// Función para agregar una conexión a un nodo
void agregarConexion(Nodo *nodo, Nodo *conexion, int distanciaXY) {
    nodo->numConexiones++;
    nodo->conexiones = (Conexion **)realloc(nodo->conexiones, sizeof(Conexion *) * nodo->numConexiones);
    
    if (nodo->conexiones != NULL) {
        Conexion *nuevaConexion = (Conexion *)malloc(sizeof(Conexion));

        if (nuevaConexion != NULL) {
            nuevaConexion->nodo = conexion;
            nuevaConexion->distanciaXY = distanciaXY;
            nodo->conexiones[nodo->numConexiones - 1] = nuevaConexion;
        }
    }
}


// Funcion para agregar nodo Prohibido
void agregarConexionProhibida(Nodo *nodo, Nodo *conexion) {
    nodo->numConexionesProhibidas++;
    nodo->conexionesProhibidos = (Conexion **)realloc(nodo->conexionesProhibidos, sizeof(Conexion *) * nodo->numConexionesProhibidas);

    if (nodo->conexionesProhibidos != NULL) {
        Conexion *nuevaConexion = (Conexion *)malloc(sizeof(Conexion));

        if (nuevaConexion != NULL) {
            nuevaConexion->nodo = conexion;
            nodo->conexionesProhibidos[nodo->numConexionesProhibidas - 1] = nuevaConexion;
        }
    }
}

// Función para verificar si un nodo está prohibido
int esProhibido(Nodo *nodoActual, Nodo *posibleProhibido) {
    for (int i = 0; i < nodoActual->numConexionesProhibidas; i++) 
        if (nodoActual->conexionesProhibidos[i]->nodo == posibleProhibido) 
            return 1; 
    return 0;
}

int recorrerGrafo(Nodo *nodo) {
    nodo->visitado = 1;
    int caminoMasCorto=__INT_MAX__;
    Nodo *opcionATomar=NULL;
    
    printf("Nombre: %s\n", nodo->nombre);
    printf("\tEstado actual: %d\n", nodo->visitado);

    for(int i=0; i<nodo->numConexiones;i++){
        if(!nodo->conexiones[i]->nodo->visitado){
            
            if(nodo->numConexionesProhibidas==0){
                opcionATomar = nodo->conexiones[i]->nodo;
                caminoMasCorto = nodo->conexiones[i]->distanciaXY;
                break;
            }
            else if(!esProhibido(nodo, nodo->conexiones[i]->nodo )){
                opcionATomar = nodo->conexiones[i]->nodo;
                caminoMasCorto = nodo->conexiones[i]->distanciaXY;
                break;
            }
        }
        if (strcmp(nodo->conexiones[i]->nodo->nombre, "E") == 0 && nodosRecorridos == TOTAL_NODOS) {
            opcionATomar = nodo->conexiones[i]->nodo;
            isSiguienteNodoOrigen=1;
            break;
        }
    }

    for (int i = 1; i < nodo->numConexiones; i++) {
        printf("\t- %s (distanciaXY: %d)\n", nodo->conexiones[i]->nodo->nombre, nodo->conexiones[i]->distanciaXY);
        
        if (nodo->conexiones[i]->nodo->visitado==0 && (nodo->conexiones[i]->distanciaXY <= caminoMasCorto)) {
            if(nodo->numConexionesProhibidas==0){
                opcionATomar = nodo->conexiones[i]->nodo;
                caminoMasCorto = nodo->conexiones[i]->distanciaXY;
            }
            else if(!esProhibido(nodo, nodo->conexiones[i]->nodo )){
                opcionATomar = nodo->conexiones[i]->nodo;
                caminoMasCorto = nodo->conexiones[i]->distanciaXY;
            }
            
            printf("\t\tNodo a tomar: %s\n", opcionATomar->nombre);
            printf("\t\tEstado actual: %d\n",opcionATomar->visitado);
        }
    }


    //
    if (opcionATomar != NULL) {
        nodosRecorridos+=nodo->visitado;

        printf("\n\tOpcion %s a tomar por ser mas corto: %d. Estado actual: %d\n", 
            opcionATomar->nombre, caminoMasCorto, opcionATomar->visitado
        );

        printf("\tnodosRecorridos: %d\n", nodosRecorridos);
        
        printf("\t\t\nContador: %d\n", contador--);
        printf("\tCumple la condicion recursiva...\n");


        //                       FIN DE LA BUSQUEDA
        if (isSiguienteNodoOrigen && nodosRecorridos == TOTAL_NODOS) {
            printf("Camino TOTALMENTE RECORRIDO...");
            return recorrerGrafo(opcionATomar) + caminoMasCorto; 
        }
    
        //nodosRecorridos--;
        //opcionATomar->visitado=0;
        //agregarConexionProhibida(nodo, opcionATomar);

    } else {
        printf("No hay opción a tomar.\n");
        return 0;
    }

}



int main() {
    //              CREACION DE NODOS
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


    //              CONEXIONES ENTRE NODOS
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



    // COMIENZO DEL PROGRAMA
    int longCaminoMasCorto = recorrerGrafo(nodoE);
    printf("\n\n\tEl camino mas corto fue de: %d", longCaminoMasCorto);

    
    free(nodoA);
    free(nodoB);
    free(nodoC);
    free(nodoD);
    free(nodoE);
    free(nodoF);
    free(nodoG);
    free(nodoH);
    free(nodoI);
    free(nodoJ);
    free(nodoK);
    free(nodoL);
    free(nodoM);
    free(nodoN);

    return 0;
}
