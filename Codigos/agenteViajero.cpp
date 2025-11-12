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

Result agenteViajero(int n, vector<Edge> aristas, int nodo_inicio) { 
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
    // Rotar el vector 'camino' para que empiece en 'nodo_inicio' y recalcular peso y cadenas
    int start_idx = -1;
    for (int i = 0; i < n; ++i) {
        if (camino[i] == nodo_inicio) { start_idx = i; break; }
    }
    if (start_idx == -1) start_idx = 0; // fallback por si no se encuentra

    vector<int> nuevo_camino;
    nuevo_camino.reserve(camino.size());
    for (int i = 0; i < n; ++i) {
        nuevo_camino.push_back(camino[(start_idx + i) % n]);
    }
    camino = move(nuevo_camino);

    // Recalcular el peso total del recorrido (ida + regreso)
    peso_total = 0;
    if (n > 0) {
        for (int i = 0; i < n - 1; ++i) {
            int a = camino[i];
            int b = camino[i + 1];
            peso_total += matriz_adyacencia[a][b];
        }
        peso_total += matriz_adyacencia[camino.back()][camino.front()];
    }

    // Reconstruir la cadena del camino de ida (sin el regreso final, que se añade después)
    camino_ida.clear();
    for (size_t i = 0; i < camino.size(); ++i) {
        camino_ida += to_string(camino[i]);
        if (i + 1 < camino.size()) camino_ida += " -> ";
    }

    // Reconstruir la cadena del camino de vuelta empezando desde el nodo inicial
    camino_vuelta.clear();
    camino_vuelta += to_string(camino.front());
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
    /*
    Se usará la siguiente notación para los nodos:
    0 -> Y
    1 -> CH
    2 -> CA
    3 -> TG
    4 -> V
    5 -> O
    6 -> X
    7 -> P
    8 -> T
    9 -> PA
    */
    vector<Edge> aristas1 = {
        {0,1,259}, {1,0,259},
        {0,2,177}, {2,0,177},
        {0,3,611}, {3,0,611},
        {0,4,504}, {4,0,504},
        {0,5,899}, {5,0,899},
        {0,6,827}, {6,0,827},
        {0,7,971}, {7,0,971},
        {0,8,969}, {8,0,969},
        {0,9,1007},{9,0,1007},

        {1,2,277}, {2,1,277},
        {1,3,546}, {3,1,546},
        {1,4,492}, {4,1,492},
        {1,5,906}, {5,1,906},
        {1,6,912}, {6,1,912},
        {1,7,1045},{7,1,1045},
        {1,8,1049},{8,1,1049},
        {1,9,1110},{9,1,1110},

        {2,3,440}, {3,2,440},
        {2,4,327}, {4,2,327},
        {2,5,723}, {5,2,723},
        {2,6,670}, {6,2,670},
        {2,7,811}, {7,2,811},
        {2,8,830}, {8,2,830},
        {2,9,859}, {9,2,859},

        {3,4,139}, {4,3,139},
        {3,5,385}, {5,3,385},
        {3,6,507}, {6,3,507},
        {3,7,597}, {7,3,597},
        {3,8,612}, {8,3,612},
        {3,9,702}, {9,3,702},

        {4,5,415}, {5,4,415},
        {4,6,453}, {6,4,453},
        {4,7,569}, {7,4,569},
        {4,8,578}, {8,4,578},
        {4,9,655}, {9,4,655},

        {5,6,274}, {6,5,274},
        {5,7,270}, {7,5,270},
        {5,8,296}, {8,5,296},
        {5,9,401}, {9,5,401},

        {6,7,146}, {7,6,146},
        {6,8,142}, {8,6,142},
        {6,9,202}, {9,6,202},

        {7,8,28},  {8,7,28},
        {7,9,131}, {9,7,131},

        {8,9,105}, {9,8,105}
    };
    
    int n = 10; // Número de nodos
    for (int i = 0; i < n; ++i) {
        Result resultado = agenteViajero(n, aristas1, i);
        cout << "Nodo inicio: " << i << endl;
        cout << "Matriz de distancias mínimas:" << endl;
        for (const auto& fila : resultado.matriz) {
            for (const auto& valor : fila) {
                if (valor == 9999)
                    cout << "INF" << "\t";
                else
                    cout << valor << "\t";
            }
            cout << endl;
        }
        cout << "Camino de ida: " << resultado.camino_ida << endl;
        cout << "Camino de vuelta: " << resultado.camino_vuelta << endl;
        cout << "Peso mínimo del recorrido: " << resultado.peso_minimo << endl;
        cout << "----------------------------------------" << endl;
    }
    return 0;
}
