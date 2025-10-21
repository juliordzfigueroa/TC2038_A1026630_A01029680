#include <iostream>
#include <vector>

using namespace std;

struct Edge { // Estructura para representar una arista en el gráfo 
    int n1; // Nodo 1
    int n2; // Nodo 2
    int w;  // Peso
};

vector<vector<int>> construirTablero(int n, vector<Edge> aristas){// Función para construir el tablero inicial
    vector<vector<int>> tablero(n, vector<int>(n, 999)); // Inicializar con un valor alto (infinito)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                tablero[i][j] = 0; // La distancia de un nodo a sí mismo es 0
            }
        }
    }
    for (int i = 0; i < aristas.size(); i++) { // Asignar el peso de la arista en el tablero
        int nodo1 = aristas[i].n1;
        int nodo2 = aristas[i].n2;
        int peso = aristas[i].w;
        tablero[nodo1][nodo2] = peso; 
    }
    return tablero;
}

vector<vector<int>> floyd(int n, vector<Edge> aristas){
    vector<vector<int>> M = construirTablero(n, aristas) ; // Matriz de distancias mínimas inicializada con valores altos y en la diagonal 0
    for (int k = 0; k < n; k++) { // Número de matrices que se van a generar
        for (int i = 0; i < n; i++) { // Filas
            for (int j = 0; j < n; j++) { // Columnas
                if (M[i][j] > M[i][k] + M[k][j]) {
                    M[i][j] = M[i][k] + M[k][j];
                }
                else continue;
            }
        }
    }
    // Imprimir la matriz de distancias mínimas

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }

    return M;
}

int main(){
    // Se deben poner todas las aristas de manera simetrica, en caso de ser un gráfo no dirigido debe ponerse el mismo peso en el camino de regreso
    vector<Edge> aristas1 = {
        {0, 1, 5},
        {1, 0, 5},
        {0, 2, 8},
        {2, 0, 8},
        {0, 3, 7},
        {3, 0, 7},
        {0, 4, 10},
        {1, 2, 1},
        {2, 1, 1},
        {2, 3, 9},
        {3, 2, 9},
        {3, 4, 2},
        {4, 3, 2} 
    };

    int n1 = 5; // Número de nodos

    vector<vector<int>> resultado = floyd(n1, aristas1);

    vector<Edge> aristas2 = {
        {0, 1, 2},
        {1, 0, 8},
        {0, 3, 2},
        {3, 0, 7}, 
        {1, 2, 2},
        {2, 0, 5},
        {2, 3, 1}
    };

    int n2 = 4; // Número de nodos
    vector<vector<int>> resultado2 = floyd(n2, aristas2);

    return 0;
}