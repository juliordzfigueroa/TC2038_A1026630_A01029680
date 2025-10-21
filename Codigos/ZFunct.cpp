#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void zFunction(string s, string pattern){ // Recibe 2 valores, la cadena a analizar y el patron a buscar
    int length_p = pattern.length();
    if (pattern[length_p - 1] != '$' ) { // Asegurarse de que el patrón termine con un carácter único
        pattern += '$';
    }
    s = pattern + s; // Concatenar patrón y cadena
    cout << "Cadena a analizar: " << s << endl;
    int i = 0, j = 1, cont = 0;
    vector<int> Z; // Vector para almacenar los valores Z
    Z.push_back(0); // Valor para iniciar el vector
    while (j <= s.length()) { // Mientras j no se pase del tamaño de la cadena
        if (s[i] == s[j]) {
            i++;
            j++;
            cont++;
        } 
        else {
            Z.push_back(cont);
            cont = 0;
            i = 0;  
            j = Z.size() - 1; // Actualizar j al último índice del vector Z
        }
    }
    Z.pop_back(); // Eliminar el último valor extra añadido al principio del vector
    cout << "Valores Z: ";
    for (int k = 1; k < Z.size(); k++) {
        cout << Z[k] << " ";
    }
    cout << endl;
    cout << "Patrón encontrado en las posiciones: ";
    for (int k = 1; k <= Z.size(); k++) {
        if (Z[k] == length_p) { // Si el valor Z es igual a la longitud del patró
            cout << k - length_p - 1<< " "; // Imprimir la posición donde se encontró el patrón
        }
    }
}

int main() {
    string str = "xabcabxabcabcx";
    string pattern = "abcabc";
    zFunction(str, pattern);
    return 0;
}