#include <fstream>
#include <iostream>
#include <vector>

/*
  Julio César Rodríguez Figueroa - A01029680
  Jin Sik Yoon - A01026630
  Algoritmo de Kruskal
*/

using namespace std;

// Estructuras utilizadas
struct Edge {
  int u; // Nodo 1
  int v; // Nodo 2
  int w; // Peso de la arista
};

// Funciones para leer archivo
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

// Funciones de Merge Sort. Mezcla dos mitades ya ordenadas [low..mid] y
// [mid+1..high] por w ascendente
void mergeEdges(vector<Edge> &v, int low, int mid, int high) {
  int a = mid - low + 1;
  int b = high - mid;

  vector<Edge> lowVector(a);
  vector<Edge> highVector(b); // Copias temporales

  // Copiar la mitad izquierda
  for (int i = 0; i < a; i++) {
    lowVector[i] = v[low + i];
  }
  // Copiar la mitad derecha
  for (int j = 0; j < b; j++) {
    highVector[j] = v[mid + 1 + j];
  }

  int i = 0;   // índice en lowVector
  int j = 0;   // índice en highVector
  int k = low; // índice en v

  // Mezclar comparando por peso (w) en orden ascendente
  while (i < a && j < b) {
    if (lowVector[i].w <= highVector[j].w) {
      v[k] = lowVector[i];
      i++;
    } else {
      v[k] = highVector[j];
      j++;
    }
    k++;
  }

  // Copiar remanentes
  while (i < a) {
    v[k] = lowVector[i];
    i++;
    k++;
  }
  while (j < b) {
    v[k] = highVector[j];
    j++;
    k++;
  }
}

// Ordena en forma ascendente por peso (w) el vector de aristas v
void ordenaMerge(vector<Edge> &v, int low, int high) {
  if (high <= low)
    return;

  int mid = low + (high - low) / 2; // Encuentra el medio del arreglo
  ordenaMerge(v, low, mid);
  ordenaMerge(v, mid + 1, high); // Divide hasta elementos individuales
  mergeEdges(v, low, mid, high); // Junta las mitades ya ordenadas
}

// Funciones para Kruskal
bool contiene(const vector<int> &v, int x) {
  for (size_t i = 0; i < v.size(); i++)
    if (v[i] == x)
      return true;
  return false;
}

// Retorna true si s y t están conectados en resp
bool estanConectados(int s, int t, const vector<Edge> &resp) {
  if (s == t)
    return true;
  vector<int> stack;
  vector<int> visitados;

  stack.push_back(s);
  visitados.push_back(s);

  while (!stack.empty()) {
    int x = stack.back();
    stack.pop_back();

    // Explorar vecinos de x mirando todas las aristas seleccionadas
    for (size_t i = 0; i < resp.size(); i++) {
      int a = resp[i].u, b = resp[i].v;

      if (a == x) {
        if (b == t)
          return true;
        if (!contiene(visitados, b)) {
          visitados.push_back(b);
          stack.push_back(b);
        }
      }
      if (b == x) {
        if (a == t)
          return true;
        if (!contiene(visitados, a)) {
          visitados.push_back(a);
          stack.push_back(a);
        }
      }
    }
  }
  return false;
}

// Aplica la lógica de selección por extremos para encontrar el MST
void seleccionPorExtremos(const vector<Edge> &edges) {
  vector<Edge> resp;
  long long total = 0;

  for (size_t i = 0; i < edges.size(); i++) {
    int u = edges[i].u, v = edges[i].v, w = edges[i].w;

    // Si u y v NO están conectados todavía en 'resp', agregamos esta arista
    if (!estanConectados(u, v, resp)) {
      resp.push_back(edges[i]);
      total += w;
    }
    // Si ya están conectados, ignoramos para evitar ciclos
  }

  // Imprime los datos de la solución
  cout << "Conexiones usadas: ";
  if (resp.empty()) {
    cout << ". ";
  } else {
    for (size_t i = 0; i < resp.size(); i++) {
      cout << "[" << resp[i].u << "," << resp[i].v << "," << resp[i].w << "]";
      if (i + 1 < resp.size())
        cout << ", ";
      else
        cout << ". " << endl;
    }
  }
  cout << "Peso final: " << total << endl;
}

/*
------------------------------
 Instrucciones para el usuario
------------------------------
Para ejecutar el programa, se debe tener un archivo de texto con el nombre, de
preferencia en el mismo espacio de trabajo. En nuestro caso, el archivo se llama
"Krustal.txt". Si su archivo tiene un nombre diferente, se debe cambiar el
nombre en la variable "filename" en la función main. Adicional a esto, se
requiere que el archivo tenga el formato de aristas en el siguiente orden:
nodo1, nodo2, peso, separado por un espacio.
*/

int main() {
  string filename = "Krustal.txt";

  vector<Edge> edges;
  if (!readEdges(filename, edges)) {
    cout << "No se pudo abrir el archivo: " << filename << "\n";
    return 1;
  }

  ordenaMerge(edges, 0, edges.size() - 1);
  seleccionPorExtremos(edges);

  return 0;
}
