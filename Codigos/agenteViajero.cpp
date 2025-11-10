#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge { // Estructura para representar una arista en el gráfo 
    int n1; // Nodo 1
    int n2; // Nodo 2
    int w;  // Peso
};

// Estructura para devolver los 4 valores desde agenteViajero
struct Result {
        vector<vector<int>> matriz;
        string camino_ida;
        string camino_vuelta;
        int peso_minimo;
};


vector<vector<int>> construirMInicial(int n, vector<Edge> aristas){// Función para construir el tablero inicial
    vector<vector<int>> tablero(n, vector<int>(n, 9999)); // Inicializar con un valor alto
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
    vector<vector<int>> M = construirMInicial(n, aristas) ; // Matriz de distancias mínimas inicializada con valores altos y en la diagonal 0
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
    return M;
}

Result agenteViajero(int n, vector<Edge> aristas) { 
    vector<int> camino; // Vector para almacenar el mejor camino
    vector<vector<int>> matriz_adyacencia = construirMInicial(n, aristas); // Obtener la matriz de distancias mínimas usando Floyd-Warshall
    for (int i = 0; i < n; ++i) camino.push_back(i);

    int peso_total = 0;
    if (n > 0) {
        for (int i = 0; i < n - 1; ++i) {
            int a = camino[i];
            int b = camino[i + 1];
            int w = matriz_adyacencia[a][b];
            peso_total += w;
        }
        // regresar al inicio
        peso_total += matriz_adyacencia[camino.back()][camino.front()];
    }

    // Construir las representaciones en string
    string camino_ida;
    for (size_t i = 0; i < camino.size(); ++i) {
        camino_ida += to_string(camino[i]);
        if (i + 1 < camino.size()) camino_ida += " -> ";
    }
    
    // Camino vuelta: listado inverso de nodos
    string camino_vuelta;
    camino_vuelta = to_string(camino.front()); // Empezar con el nodo inicial
    camino_vuelta += " -> ";
    for (size_t i = 0; i < camino.size(); ++i) {
        if (i) camino_vuelta += " -> ";
        camino_vuelta += to_string(camino[camino.size() - 1 - i]);
    }

    // Añadir el regreso al nodo inicial en el camino de ida
    camino_ida += " -> " + to_string(camino.front());

    // Regresamos el resultado
    return {matriz_adyacencia, camino_ida, camino_vuelta, peso_total};
}

int main() {
    // Se deben poner todas las aristas de manera simetrica, en caso de ser un gráfo no dirigido debe ponerse el mismo peso en el camino de regreso
    vector<Edge> aristas1 = {
        {0, 1, 2},
        {1, 0, 2},
        {0, 2, 3},
        {2, 0, 3},
        {0, 3, 5},
        {3, 0, 5},
        {1, 2, 4},
        {2, 1, 4},
        {1, 3, 6},
        {3, 1, 6},
        {2, 3, 1},
        {3, 2, 1}
    };
    int n = 4; // Número de nodos
    Result res = agenteViajero(n, aristas1);
    cout << "Matriz de distancias mínimas:\n";
    for (const auto& fila : res.matriz) {
        for (const auto& valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
    cout << "Mejor camino de ida: " << res.camino_ida << endl;
    cout << "Mejor camino de vuelta: " << res.camino_vuelta << endl;
    cout << "Peso mínimo del recorrido: " << res.peso_minimo << endl; 
    return 0;
}