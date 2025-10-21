#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
  int u; // Nodo 1 
  int v; // Nodo 2
  int w; // Peso de la arista
};

// Estructura para almacenar el recorrido de Dijkstra
struct Recorrido {
  int u; // Nodo 1 
  int v; // Nodo 2
  int w; // Peso de la arista
  int pos; // Lugar en el que recorremos esta arista 
};

// ------------------------------
// Función para leer archivo
// ------------------------------

bool readEdges(const string &filename, vector<Edge> &edges) {
  ifstream in(filename);
  if (!in.is_open())
    return false;

  Edge e;
  while (in >> e.u >> e.v >> e.w) { // lee 3 enteros por línea
    edges.push_back(e);
  }
  return true;
}

// ------------------------------
// Funciones para Dijkstra
// ------------------------------

bool contiene(const vector<int> &v, int x) {
  for (size_t i = 0; i < v.size(); i++)
    if (v[i] == x)
      return true;
  return false;
}

void dijkstra(int nodoI, vector<Edge> &edges) {
    vector<Recorrido> resp;
    vector<Edge> caminosPosibles; // Aristas que conectan con el nodo actual
    vector<int> nodosVisitados (nodoI); // Hace la función de la cola para ver cuales nodos han sido visitados
    int total = 0; // Peso total del recorrido
    int cont = 1; // Contador de nodos visitados
    for (size_t i = 0; i < edges.size(); i++) {
        if (edges[i].u == nodoI || edges[i].v == nodoI) { // Si la arista conecta con el nodo inicial
            caminosPosibles.push_back(edges[i]); // Agrega la arista a los caminos posibles
        }
    }
    // Buscar la arista de menor peso en caminosPosibles
    if (!caminosPosibles.empty()) {
        int minIdx = 0;
        for (size_t i = 1; i < caminosPosibles.size(); i++) {
            if (caminosPosibles[i].w < caminosPosibles[minIdx].w) {
                minIdx = i;
            }
        }
        total = caminosPosibles[minIdx].w; // Inicializa el total con el peso mínimo
        Recorrido r;
        r.u = caminosPosibles[minIdx].u;
        r.v = caminosPosibles[minIdx].v;
        r.w = caminosPosibles[minIdx].w;
        r.pos = minIdx;
        resp.push_back(r); // Agrega la arista con el peso mínimo al recorrido
    }
    // Imprimir el recorrido
    cout << "Aristas en el recorrido de Dijkstra desde el nodo " << nodoI << ":\n";
    for (size_t i = 0; i < resp.size(); i++) {
        cout << resp[i].u << " -- " << resp[i].v << " (Peso: " << resp[i].w << ")\n";
    }
}

int main () {
  vector<Edge> edges = {{0, 1, 8}, {0, 2, 12}};
  if (!readEdges("graph.txt", edges) && edges.empty()) {
    cout << "Error al abrir el archivo." << endl;
    return 1;
  }



  int nodoInicial = 0; // Nodo desde el cual iniciar Dijkstra
  dijkstra(nodoInicial, edges);

  return 0;
}