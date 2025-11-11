#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm> // Para sort y para min

using namespace std;

float closestPair(vector<pair<int, int>> puntos) {
    // Implementación del algoritmo para encontrar el par de puntos más cercanos
    int n = puntos.size();
    sort(puntos.begin(), puntos.end()); // Ordenar puntos por coordenada x
    int x_min = puntos[0].first; // Primera coordenada x
    int x_max = puntos[n-1].first; // Última coordenada x
    int mid_x = (x_min + x_max) / 2; // Coordenada x media
    float d1 = 9999; // Distancia mínima inicial alta para la mitad izquierda
    float d2 = 9999; // Distancia mínima inicial alta para la mitad derecha
    vector<pair<int, int>> left_half;
    vector<pair<int, int>> right_half;
    for (int i = 0; i < n; i++) { // Metemos los puntos en sus respectivas mitades
        if (puntos[i].first <= mid_x) {
            left_half.push_back(puntos[i]);
        } else {
            right_half.push_back(puntos[i]);
        }
    }
    // Establecemos casos base y casos especiales aquí
    if (n <= 3) { // Si no hay más de dos puntos o hay un solo punto.
        return abs(sqrt(pow(puntos[0].first - puntos[1].first, 2) + pow(puntos[0].second - puntos[1].second, 2)));
    }
    else {
        for (int i = 0; i < left_half.size(); i++) {
            for (int j = i + 1; j < left_half.size(); j++) { // Calcular distancia entre puntos en la mitad izquierda
                float dist = abs(sqrt(pow(left_half[i].first - left_half[j].first, 2) + pow(left_half[i].second - left_half[j].second, 2)));
                if (dist < d1) {
                    d1 = dist;
                }
            }
        }
        for (int i = 0; i < right_half.size(); i++) { // Repetimos para la mitad derecha
            for (int j = i + 1; j < right_half.size(); j++) { // Calcular distancia entre puntos en la mitad derecha
                float dist = abs(sqrt(pow(right_half[i].first - right_half[j].first, 2) + pow(right_half[i].second - right_half[j].second, 2)));
                if (dist < d2) {
                    d2 = dist;
                }
            }
        }
    }
    float d = min(d1, d2); // Distancia mínima entre las dos mitades
    pair<int, int> max_x_left = left_half.back(); // Ultimo par de coordenadas en la mitad izquierda
    pair<int, int> min_x_right = right_half.front(); // Primer par de coordenadas en la mitad derecha
    float d_mid = abs(sqrt(pow(max_x_left.first - min_x_right.first, 2) + pow(max_x_left.second - min_x_right.second, 2)));
    return min(d, d_mid);
}   

int main() {
    vector<pair<int, int>> puntos = {{1,1}, {2,4}, {2,2}, {3,1}};
    float distancia_minima = closestPair(puntos);
    cout << "La distancia mínima entre el par de puntos más cercanos es: " << distancia_minima << endl;
    return 0;
}