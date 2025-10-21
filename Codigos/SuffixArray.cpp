#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void suffixArray(string s) {
    int n = s.size();
    if (n == 0 || s[n-1] != '$') {
        s += '$'; // Asegurarse de que la cadena termine con un carácter único
    }
    n = s.size();
    vector<pair<string, int>> suffixes; // Vector para almacenar sufijos y sus índices
    for (int i = n-1; i > 0; --i) { // Guarda el número del indice donde se encuentra el sufijo
        string temp;
        for (int j = i; j < n; ++j) { // Construir el sufijo desde la posición i hasta el final
            temp += s[j];
        }
        suffixes.push_back({temp, i + 1}); // Guardar el sufijo y su índice original
    }
    suffixes.push_back({s, 1}); // Añadir el sufijo completo con índice 0
    
    vector<pair<string, int>> sortedSuffixes;
    sortedSuffixes = suffixes;
    sort(sortedSuffixes.begin(), sortedSuffixes.end());
    // Para imprimir ambos resultados
    cout << "Sufijos originales y sus índices:" << endl;
    for (int i = 0; i < suffixes.size(); i++) {
        cout << suffixes[i].first << " - " << suffixes[i].second << endl;
    }
    cout << "\nSufijos ordenados y sus índices:" << endl;
    for (int i = 0; i < sortedSuffixes.size(); i++) {
        cout << sortedSuffixes[i].first << " - " << sortedSuffixes[i].second << endl;
    }
}

int main() {
    string str = "ababcabcabababd";
    suffixArray(str);
    return 0;
}