#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> prefixFunct(string s){
    int n = s.size();
    vector<int> pi(n, 0); // Vector para almacenar los valores de la función prefijo
    for (int i = 1; i < n; i++) { // Iterar desde el segundo carácter hasta el final
        int j = pi[i - 1]; // Longitud del prefijo más largo que es también sufijo para el prefijo que termina en i-1
        while (j > 0 && s[i] != s[j]) { // Retroceder hasta encontrar un prefijo coincidente o llegar a 0
            j = pi[j - 1];
        }
        if (s[i] == s[j]) { // Si hay coincidencia, incrementar la longitud del prefijo
            j++;
        }
        pi[i] = j; // Asignar la longitud del prefijo más largo que es también sufijo para el prefijo que termina en i
    }
    // Imprimir los valores de la función prefijo
    cout << "Función prefijo (pi array):" << endl;
    for (int i = 0; i < n; i++) {
        cout << pi[i] << " ";
    }
    cout << endl;

    return pi;
}

void kmpSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> pi = prefixFunct(pattern); // Obtener la función prefijo para el patrón
    int j = 0; // Índice para el patrón
    for (int i = 0; i < n; i++) { // Iterar sobre cada carácter del texto
        while (j > 0 && text[i] != pattern[j]) { // Retroceder en el patrón si hay una discrepancia
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) { // Si hay coincidencia, avanzar en el patrón
            j++;
        }
        if (j == m) { // Si se ha encontrado una coincidencia completa del patrón
            cout << "Patrón encontrado en el índice: " << i - m + 1 << endl;
            j = pi[j - 1]; // Continuar buscando más coincidencias
        }
    }
}

int main() {
    string str = "ababcabcabababd";
    vector<int> pi = prefixFunct(str);
    kmpSearch("ababcabcabababd", "ababd");
    return 0;
}