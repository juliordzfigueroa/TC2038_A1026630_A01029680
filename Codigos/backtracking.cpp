#include <iostream>
#include <vector>

/*
  Julio César Rodríguez Figueroa - A01029680
  Jin Sik Yoon - A01026630
  Algoritmo de backtracking (Suma de subsets)
*/

using namespace std;

int C[] = {2, 3, 7, 9};         // conjunto
int E = 4;                      // tamaño del conjunto
int T = 9;                      // objetivo de suma

// Función recursiva para buscar subconjuntos
void buscar(int i, int suma, vector<int> actual) {
    // Si la suma es exactamente T, imprimimos el subconjunto
    if (suma == T) {
        cout << "{ ";
        for (int k = 0; k < actual.size(); k++) {
            cout << actual[k] << " ";
        }
        cout << "}" << endl;
        
        return;
    }

    // Si se han considerado todos los elementos o la suma excede T, terminamos
    if (i == E || suma > T) {
        return;
    }

    // Incluir C[i] en el subconjunto
    actual.push_back(C[i]);
    buscar(i + 1, suma + C[i], actual);
    actual.pop_back(); // deshacer
    buscar(i + 1, suma, actual);
}

int main() {
    vector<int> actual;
    cout << "Subconjuntos que suman " << T << endl;
    buscar(0, 0, actual);
    return 0;
}