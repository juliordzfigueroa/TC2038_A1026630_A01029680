#include <iostream>
#include <vector>
using namespace std;

int fibonacci(int n) { // Función recursiva para calcular el n-ésimo número de Fibonacci sin programación dinamica
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacciMemo(int n) { // Programación dinamica usando recursion
    vector<int> memo = {0,1};
    if (n < memo.size()){
        return memo[n];
    } 
    else{
        int f = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
        memo.push_back(f);
        return f;
    }
}

int fibonacciIterativo (int n){ // Programación dinamica usando ciclos
    vector<int> f(n);
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}

int fibonacciIterativo2 (int n){
    if (n <= 1) return n;

    else{
        int n1 = 0, n2 = 1, f;
        for (int i = 2; i <= n; i++) {
            f = n1 + n2;
            n1 = n2;
            n2 = f;
        }
        return f;
    }
}

int fibonacciMemo2(int n){ // Función que hace la suma de fibonacci sin vector de manera recursiva
    if (n <= 1) return n; // Caso base
    else {
        int n1 = fibonacciMemo2(n - 1), n2 = fibonacciMemo2(n - 2), f; // Se establecen las variables temporales para almacenar los datos de programación dinámica
        f = n1 + n2; // Último número de Fibonacci calculado
        n1 = n2; // Se actualizan las variables temporales
        n2 = f;
        return f; // Se regresa el último número de Fibonacci calculado
    }
}

int main() {
    int n = 40; // Cambia este valor para calcular otros números de Fibonacci
    cout << "Fibonacci de " << n << " es " << fibonacciMemo2(n) << endl;
    cout << "Fibonacci de " << n << " es " << fibonacciIterativo2(n) << endl;
    return 0;
}