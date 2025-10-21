#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> knapsack(vector<int> w, vector<int> v, int mW) {
    if (w.size() != v.size()) return {}; // Si los tamaños de los valores y pesos no coinciden no se realiza el
    int n = w.size(); // Número de elementos 
    vector<vector<int>> dp(n + 1, vector<int>(mW + 1, 0));

    // Llenar la matriz dp con los valores máximos que se pueden obtener en cada fila iterando sobre los elementos
    for (int i = 1; i <= n; i++) { 
        for (int j = 0; j <= mW; j++) {
            if (w[i - 1] <= j) { // Si el peso del elemento actual es menor o igual a la capacidad actual
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
            } else { // Si el peso del elemento actual es mayor a la capacidad actual
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Imprimir los elementos que se incluyen en la mochila (la matriz dp)
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= mW; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp;
}

int main() {
    vector<int> weights = {6, 3, 4, 2}; // Pesos de los elementos
    vector<int> values = {30, 14, 16, 9};  // Valores de los elementos
    int maxWeight = 10; // Capacidad máxima de la mochila

   vector<vector<int>> result = knapsack(weights, values, maxWeight);

    return 0;
}
