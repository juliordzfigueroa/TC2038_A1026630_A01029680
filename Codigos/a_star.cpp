#include <iostream>
#include <vector>

using namespace std;


struct Nodo {
    int num; // Número del nodo
    int h; // Costo heurístico
};

struct Edge { // Estructura para representar una arista en el gráfo 
    Nodo n1; // Nodo 1
    Nodo n2; // Nodo 2
    int w;  // Peso
};


struct Estado{
    Nodo nodo_Actual; // Nodo actual
    int c_n; // Costo desde el nodo inicial hasta el nodo actual
    vector<pair<int,int>> recorrido; // Recorrido hasta el nodo actual (num, costo)
    vector<bool> visitados; // Nodos visitados
};

struct Path {
    vector<pair<int,int>> nodos; // Nodos en el camino (num, costo)
    int costoTotal; // Costo total del camino
};

Path a_star(Nodo nodoI, Nodo nodo_Obj, vector<Edge> aristas) { // Implementación del algoritmo A*
    Path mejor; // Variable que guarda la mejor solución encontrada hasta ahora
    mejor.costoTotal = 10000; // Inicializar con un valor alto
    mejor.nodos.clear(); 

    vector<Estado> pila; // Pila que simula el stack para backtracking

    // Estado inicial
    Estado inicial;
    inicial.nodo_Actual = nodoI; 
    inicial.c_n = 0;    // Costo acumulado inicial
    inicial.recorrido.push_back(make_pair(nodoI.num, nodoI.h)); // f = g + h = 0 + h
    pila.push_back(inicial);

    while (!pila.empty()) { // Mientras la pila no esté vacía
        Estado est = pila.back(); // Elemento de la pila (último estado)
        pila.pop_back(); // Sacar el último estado

        Nodo nodo_Actual = est.nodo_Actual; // Nodo actual
        int c_n = est.c_n; // Costo acumulado hasta el nodo actual
        vector<pair<int,int>> recorrido = est.recorrido; // Recorrido hasta el nodo actual

        // Caso base: llegamos al objetivo
        if (nodo_Actual.num == nodo_Obj.num) {
            if (c_n < mejor.costoTotal) {
                mejor.costoTotal = c_n;
                mejor.nodos = recorrido;
            }
            continue;
        }

        // Si ya es peor que lo mejor encontrado continuar
        if (c_n >= mejor.costoTotal) {
            continue;
        }

        // Buscar los caminos posibles desde el nodo actual
        vector<Edge> caminosPosibles;
        for (int i = 0; i < aristas.size(); ++i) {
            if (aristas[i].n1.num == nodo_Actual.num) {
                caminosPosibles.push_back(aristas[i]);
            }
        }

        // En vez de elegir solo el mejor, exploramos todos
        for (int j = 0; j < caminosPosibles.size(); ++j) {
            Edge e = caminosPosibles[j]; // Arista siguiente
            Nodo siguiente = e.n2; // Nodo siguiente

            int nuevo_c_n = c_n + e.w; // g nuevo
            int f = nuevo_c_n + siguiente.h; // f = g + h

            // Si ya es peor que lo mejor encontrado, continuar
            if (nuevo_c_n >= mejor.costoTotal) continue;

            Estado nuevoEst; // Nuevo estado
            nuevoEst.nodo_Actual = siguiente; // Nodo actual del nuevo estado
            nuevoEst.c_n = nuevo_c_n; // Costo acumulado hasta el nuevo nodo
            nuevoEst.recorrido = recorrido; // Recorrido hasta el nodo actual
            nuevoEst.recorrido.push_back(make_pair(siguiente.num, f)); // Agregar nuevo nodo al recorrido

            pila.push_back(nuevoEst); // Agregar nuevo estado a la pila
        }
    }

    return mejor;
}

int main(){
    // Ejemplo de uso del algoritmo A*
    Nodo nodoI = {1, 7}; // Nodo inicial
    Nodo nodo_Obj = {5, 0}; // Nodo objetivo

    vector<Edge> aristas = {
        {{1, 7}, {2, 6}, 2},
        {{1, 7}, {3, 2}, 4},
        {{2, 6}, {4, 1}, 3},
        {{3, 2}, {4, 1}, 1},
        {{4, 1}, {5, 0}, 2}
    };

    Path resultado = a_star(nodoI, nodo_Obj, aristas);
    cout << "Costo total del camino: " << resultado.costoTotal << endl;
    cout << "Nodos en el camino: ";
    for (int i = 0; i < resultado.nodos.size(); ++i) {
        cout << resultado.nodos[i].first << " ";
    }
    cout << endl;

    return 0;
}





