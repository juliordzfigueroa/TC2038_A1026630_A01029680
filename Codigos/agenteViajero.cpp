#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problema del Agente Viajero
// Julio César Rodríguez Figueroa A01029680
// Jin Sik Joon A01026630

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

Result agenteViajero(int n, vector<Edge> aristas, int nodo_inicio) { 
    vector<vector<int>> matriz_adyacencia = construirMInicial(n, aristas); // Obtener la matriz de distancias mínimas usando Floyd-Warshall
    vector<int> nodos; // Vector para verificar los nodos restantes
    for (int i = 0; i < n; ++i) {
        if (i != nodo_inicio) nodos.push_back(i); // Añadimos todo menos el inicio
    }

    int mejor_peso = 9999; // Inicializar el mejor peso con un valor alto
    vector<int> mejor_camino; // Vector para almacenar el mejor camino encontrado

    // Do while para para revisar todos los caminos posibles
    do {
        vector<int> camino; // Camino actual a revisar
        int peso_actual = 0;
        bool camino_valido = true; // Bandera para verificar si el camino es válido
        int nodo_actual = nodo_inicio;

        camino.push_back(nodo_actual);

        for (int i = 0; i < nodos.size(); ++i) {
            int nodo_siguiente = nodos[i]; // Nodo siguiente en el camino actual
            int peso = matriz_adyacencia[nodo_actual][nodo_siguiente];
            if (peso == 9999) { // Si no hay camino entre nodos
                camino_valido = false;
                break;
            }
            peso_actual += peso;
            camino.push_back(nodos[i]);
            nodo_actual = nodos[i];

            // Salir del ciclo si el peso actual ya supera el mejor peso encontrado
            if (peso_actual >= mejor_peso) {
                camino_valido = false;
                break;
            }
        }

        if (camino_valido) { // Buscar regreso al nodo inicial
            int peso = matriz_adyacencia[nodo_actual][nodo_inicio];
            if (peso == 9999) { // Si no hay camino de regreso al inicio
                camino_valido = false;
            } else {
                peso_actual += peso;
                camino.push_back(nodo_inicio);
            }
        }

        // Si el camino es válido y el peso es menor que el mejor encontrado, actualizar
        if (camino_valido && peso_actual < mejor_peso) {
            mejor_peso = peso_actual;
            mejor_camino = camino;
        }

    } while (next_permutation(nodos.begin(), nodos.end())); // Usamos un iterador para poder manerjar de mejor manera las permutaciones para los nodos.
    // Referencia aquí: https://en.cppreference.com/w/cpp/algorithm/next_permutation

    // Construir las representaciones en string
    string camino_ida;
    for (size_t i = 0; i < mejor_camino.size(); ++i) {
        camino_ida += to_string(mejor_camino[i]);
        if (i + 1 < mejor_camino.size()) camino_ida += " -> ";
    }
    
    // Camino vuelta
    string camino_vuelta;
    for (size_t i = 0; i < mejor_camino.size(); ++i) {
        if (i) camino_vuelta += " -> ";
        camino_vuelta += to_string(mejor_camino[mejor_camino.size() - 1 - i]);
    }

    // Regresamos el resultado
    return {matriz_adyacencia, camino_ida, camino_vuelta, mejor_peso};
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
    Result resultado1 = agenteViajero(n, aristas1, 0); // Nodo de inicio: Y (0)
    cout << "Nodo inicio: " << 0  << " Yucatan" << endl;
    cout << "Matriz de distancias mínimas:" << endl;
    for (int i = 0; i < resultado1.matriz.size(); ++i) {
        for (int j = 0; j < resultado1.matriz[i].size(); ++j) {
            if (resultado1.matriz[i][j] == 9999)
                cout << "INF" << "\t";
            else
                cout << resultado1.matriz[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Camino de ida: " << resultado1.camino_ida << endl;
    cout << "Camino de vuelta: " << resultado1.camino_vuelta << endl;
    cout << "Peso mínimo del recorrido: " << resultado1.peso_minimo << endl;
    cout << "----------------------------------------" << endl;
    Result resultado2 = agenteViajero(n, aristas1, 6); // Nodo de inicio: X (6)
    cout << "Nodo inicio: " << 6  << " Xalapa" << endl;
    cout << "Matriz de distancias mínimas:" << endl;
    for (int i = 0; i < resultado2.matriz.size(); ++i) {
        for (int j = 0; j < resultado2.matriz[i].size(); ++j) {
            if (resultado2.matriz[i][j] == 9999)
                cout << "INF" << "\t";
            else
                cout << resultado2.matriz[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Camino de ida: " << resultado2.camino_ida << endl;
    cout << "Camino de vuelta: " << resultado2.camino_vuelta << endl;
    cout << "Peso mínimo del recorrido: " << resultado2.peso_minimo << endl;
    cout << "----------------------------------------" << endl;
    return 0;
}
