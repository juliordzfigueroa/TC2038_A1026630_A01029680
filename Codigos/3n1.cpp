#include <iostream>

using namespace std;

int main(){
    int i, j;
    cin >> i >> j;
    if ((i <= 0 || j <= 0) || (i > 10000 || j > 10000)){
        return 0; 
    }
    else {
    int max = 0;  // Variable que cuenta el mayor número de pasos.
    int cont;  // Variable que lleva la cuenta de pasos en cada ciclo.
    int n;
    if (j < i){
        for (int k = i; k >= j; k--){
            cont = 1;
            n = k;
            while (n != 1){
                if (n % 2 == 0){ // Si es par
                    cont ++;
                    n = n/2;
                }
                else{ // Si es impar
                    cont ++;
                    n = (3*n)+1;
                }
            }
            if (max < cont){
                max = cont;  
            }
        }
    } else {
        for (int k = j; k >= i; k--){
            cont = 1;
            n = k;
            while (n != 1){
                if (n % 2 == 0){ // Si es par
                    cont ++;
                    n = n/2;
                }
                else{ // Si es impar
                    cont ++;
                    n = (3*n)+1;
                }
            }
            if (max < cont){
                max = cont;  
            }
        }
        }
    }
    cout << i << " " << j << " " << max << endl;
    return 0;
}