#include <cmath> // Para usar pow
#include <iostream>
#include <string> // Para manerjar cadenas

using namespace std;


int p = 31;                // Tamaño del adecedario (incluye ñ)
long long m = (pow(10, 9)) + 9; // Tamaño del módulo

string alfabeto = "abcdefghijklmnñopqrstuvwxyz"; // Alfabeto español en minúsculas

void hashS(string a) {
  long long suma = 0, temp;
  for (int i = 0; i < a.length(); i++) {
    for (int j = 0; j < alfabeto.length(); j++) {
      if (a[i] == alfabeto[j]) {
        temp = (j + 1) * long(pow(p, i));
        suma += temp;
        break;
      }
    }
  }
  cout << "Suma sin módulo: " << suma << endl;
  cout << "Aplicando % m:  " << suma % m << endl;

}


  int main() {
    setlocale(LC_ALL, "spanish");
    string str = "ababcabcabababd";
    hashS(str);
    return 0;
  };