#include <iostream>
using namespace std;

const int N = 7; // Número de nodos
const int INF = 10000; // Infinito predefinido

char nombre[N] = {'A','B','C','D','E','F','G'};

int main() {
    // Definición de aristas: (nodo1, nodo2, peso)
    int edges[][3] = {
        {0,1,2},  // A-B
        {0,2,4},  // A-C
        {0,3,6},  // A-D
        {1,2,3},  // B-C
        {1,4,6},  // B-E
        {2,3,1},  // C-D
        {2,4,5},  // C-E
        {3,4,4},  // D-E
        {3,5,3},  // D-F
        {4,6,2},  // E-G
        {5,6,5}   // F-G
    };
    int E = sizeof(edges) / sizeof(edges[0]);  // Número de aristas calculado

    // Construimos la matriz de adyacencia para diseñar bien el grafo
    int grafo[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grafo[i][j] = 0; // Inicializamos con 0 (sin arista)

    for (int i = 0; i < E; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        int w = edges[i][2];
        grafo[a][b] = w;
        grafo[b][a] = w; // Grafo no dirigido
    }

    // Arreglamos nombres para impresión
    int llave[N];
    int padre[N];
    bool enMST[N];

    for (int i = 0; i < N; i++) {
        llave[i] = INF;     // Inicialmente todas las llaves son infinitas
        padre[i] = -1;      // Ningún nodo tiene padre aún
        enMST[i] = false;   // Ningún nodo está en el MST aún
    }

    // Nodo inicial = 0
    llave[0] = 0;

    // Algoritmo de Prim
    for (int contador = 0; contador < N-1; contador++) {

        // Buscar nodo con llave mínima no incluido en MST
        int u = -1;
        int mejor = INF;
        for (int v = 0; v < N; v++) { // Recorremos todos los nodos para encontrar el menor peso
            if (!enMST[v] && llave[v] < mejor) {
                mejor = llave[v];
                u = v;
            }
        }

        enMST[u] = true; // Marcamos el nodo como incluido en MST

        // Relajar vecinos
        for (int v = 0; v < N; v++) {
            int w = grafo[u][v];
            if (w != 0 && !enMST[v] && w < llave[v]) {
                llave[v] = w;
                padre[v] = u;
            }
        }
    }

    // Imprimimos el resultado
    int total = 0;
    cout << "Aristas del MST:" << endl;
    for (int v = 1; v < N; v++) {
        int u = padre[v];
        cout << nombre[u] << " - " << nombre[v] << "  peso = " << grafo[u][v] << endl;
        total += grafo[u][v];
    }

    cout << "Peso total = " << total << endl;
    return 0;
}