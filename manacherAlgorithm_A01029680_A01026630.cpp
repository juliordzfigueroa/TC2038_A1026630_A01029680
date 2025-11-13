#include <iostream>
#include <vector>
using namespace std;

/*
Implementación del algoritmo de Manacher para encontrar el palíndromo más largo en una cadena.
Jin Sik Joon A01026630
Julio Cesar Rodriguez Figueroa A01029680
*/

void manacher(string S) {
    string Sm = "$"; // Cadena modificada con caracteres especiales
    vector<int> nums = {}; // Vector para almacenar los radios de los palíndromos
    int indice = {}; // Indice del centro del palíndromo más largo
    int i = 0, j = 0; // i para recorrer S, j para recorrer Sm
    while (i < S.length()) { // Se recorre la cadena original y se inserta un caracter especial entre cada caracter y al inicio y final
        if (Sm[j] == '$'){
            Sm.push_back(S[i]);
            i++;
            j++;
        } else {
            Sm.push_back('$');
            j++;
        }
    }
    Sm.push_back('$'); // Caracter especial al final

    for (int i = 0; i < Sm.length(); i++) { // Se recorre la cadena modificada para encontrar los palíndromos
        int space = 1; // Radio de comparación desde el centro
        int temp = 0; // Varaible temporal para contar el radio del palíndromo
        while (true){
            if (Sm[i - space] == Sm[i + space]){
                temp += 1;
                space += 1;
            } else {
                break;
            }
            if (i - space < 0 || i + space >= Sm.length()){
                break;
            }
        }
        nums.push_back(temp);
    }

    int greater = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > greater) 
        {
            greater = nums[i];
            indice = {i};
        }
        else if (nums[i] == greater) continue;
    }

    string palindromo = "";
    for (int i = indice - greater; i < indice + greater; i++) {
        if (Sm[i] != '$') {
            palindromo += Sm[i];
        }
    }
    cout << endl;

    // Para encontar en la cadena original
    int start = 0; // Variable para almacenar el índice de inicio
    for (int i = 0; i < S.length(); i++) { 
        if (S[i] == palindromo[0]) {
            bool match = true;
            for (int j = 0; j < palindromo.length(); j++) { // Al encontrar el primer caracter, se compara el resto para ver si coincide el palindromo
                if (S[i + j] != palindromo[j]) { // Si no coincide, se rompe el ciclo y se sigue buscando
                    match = false;
                    break;
                }
            }
            if (match) { // Si coincide, se guarda el índice de inicio y se rompe el ciclo
                start = i;
                break;
            }
        }
    }
    cout << "El palíndromo más largo es: " << palindromo << endl;
    cout << "Y se encuentra en la cadena original desde el índice " << start + 1 << " hasta el índice " << start + palindromo.length()  << endl;
}

int main() {
    string S = "XABCABXBBC";
    manacher(S);
    return 0;
};