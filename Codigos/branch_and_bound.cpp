#include <iostream>

/*
  Julio César Rodríguez Figueroa - A01029680
  Jin Sik Yoon - A01026630
  Algoritmo de branch and bound (Asignación de Trabajos)
*/

using namespace std;

const int N = 4;   // 4 trabajadores, 4 trabajos

// Matriz de costos del ejemplo
int cost[N][N] = {
    {5, 9, 10, 3},      // Trabajador 1
    {2, 6, 12, 1},      // Trabajador 2
    {7, 4, 4, 8},       // Trabajador 3
    {11, 16, 2, 14}     // Trabajador 4
};

int mejorCosto = 10000;       // mejor costo encontrado predefinido
int mejorAsignacion[N];       // mejor asignación
int asignacionActual[N];      // asignación actual
bool trabajoUsado[N] = {false, false, false, false}; // trabajos ya usados

// trabajador = índice del trabajador actual (0 a 3)
// costoActual = costo acumulado hasta ahora
void asignarTrabajos(int trabajador, int costoActual) {
    // Si ya asignamos a todos los trabajadores
    if (trabajador == N) {
        if (costoActual < mejorCosto) { // encontramos mejor costo
            mejorCosto = costoActual;
            for (int i = 0; i < N; i++) {
                mejorAsignacion[i] = asignacionActual[i];
            }
        }
        return;
    }

    // Branch and bound:
    // Si el costo actual ya excede el mejor costo encontrado, cortar esta rama
    if (costoActual >= mejorCosto) {
        return;
    }

    // Probar todos los trabajos para este trabajador
    for (int j = 0; j < N; j++) {
        if (!trabajoUsado[j]) {                 // si el trabajo está libre
            trabajoUsado[j] = true;             // lo marcamos como usado
            asignacionActual[trabajador] = j;   // asignamos trabajo j al trabajador
            asignarTrabajos(trabajador + 1,
                           costoActual + cost[trabajador][j]);

            trabajoUsado[j] = false;            // deshacemos (backtracking)
        }
    }
}

int main() {
    asignarTrabajos(0, 0);

    cout << "Mejor costo total: " << mejorCosto << endl;
    cout << "Asignacion (Trabajador -> trabajo):" << endl;
    for (int i = 0; i < N; i++) {
        cout << "  Trabajador " << (i + 1)
             << " -> Trabajo " << (mejorAsignacion[i] + 1) << endl;
    }
    return 0;
}