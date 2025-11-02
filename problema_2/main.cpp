/*
2) Dado un número entero no negativo n, a) genere los coeficientes del polinomio (x+1) n
,muestre el resultado del polinomio y b) muestre por pasos el cálculo para x dado, f(x) = (x+1)n ,según el
polinomio generado. Implemente el algoritmo utilizando memoria dinamica. Para generar los polinomios de (x+1)n
 utilice el triangulo de pascal
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<long long>> generarTrianguloPascal(int n) {
    if (n < 0 || n > 30) { 
        cerr << "Error: n debe ser un entero no negativo y razonablemente pequeño." << endl;
        return {}; 
    }
    
    // Almacena todas las filas del triángulo.
    vector<vector<long long>> triangulo;

    // Genera la fila 0: (x+1)^0 = 1
    if (n >= 0) {
        triangulo.push_back({1});
    }

    // Genera las filas 1 a n
    for (int i = 1; i <= n; ++i) {
        // La fila anterior (i-1)
        const vector<long long>& filaAnterior = triangulo.back();
        
        // La nueva fila (i) tendrá i + 1 coeficientes
        vector<long long> nuevaFila(i + 1);
        
        // El primer y último coeficiente siempre son 1
        nuevaFila[0] = 1;
        nuevaFila[i] = 1; 

        // Calcula los coeficientes intermedios sumando los de la fila anterior
        // C(i, j) = C(i-1, j-1) + C(i-1, j)
        for (int j = 1; j < i; ++j) {
            nuevaFila[j] = filaAnterior[j - 1] + filaAnterior[j];
        }

        triangulo.push_back(nuevaFila);
    }

    return triangulo;
}

// Función para mostrar el polinomio y sus coeficientes en formato Triángulo de Pascal.
void mostrarPolinomioTriangulo(const vector<vector<long long>>& triangulo, int n) {
    if (triangulo.empty()) return;

    cout << "\na) Coeficientes y Polinomio Resultante (Triángulo de Pascal):" << endl;

    for (int grado = 0; grado <= n; ++grado) {
        const vector<long long>& coef = triangulo[grado];
        
        cout << "   (x+1)^" << grado << " = "; 

        for (int i = grado; i >= 0; --i) {
            long long c = coef[grado - i]; 
           
            if (i < grado) {
                cout << "+";
            }
            
            if (i == 0) {  
                cout << c;
            } else if (c == 1) {
                cout << "x";
            } else {
                cout << c << "x"; 
            }
          
            if (i > 1) {
                cout << "^" << i;
            }
        }
        cout << endl;
    }

    cout << "\n   Coeficientes de (x+1)^" << n << " (de x^" << n << " a x^0): ";
    const vector<long long>& coef_final = triangulo.back();
    for (size_t i = 0; i < coef_final.size(); ++i) {
        cout << coef_final[i] << (i == coef_final.size() - 1 ? "" : ", ");
    }
    cout << endl;
}

// Función para evaluar el polinomio f(x) = (x+1)^n usando el Algoritmo de Horner (por pasos)
void evaluarPolinomioPasos(const vector<long long>& coef, int n, double x) {
    if (coef.empty()) return;

    cout << "\nb) Cálculo por pasos para f(" << x << ") = (x+1)^" << n << ":" << endl;
    

    cout.setf(ios::fixed);
    cout.precision(4);

    double valor_polinomio = 0.0;
    cout << "   f(" << x << ") = ";

 
    for (int i = n; i >= 0; --i) {
        long long c = coef[n - i]; 
        double x_pow_i = pow(x, i); 
        double termino = c * x_pow_i;
        
        valor_polinomio += termino;

        // Muestra el paso: c * x^i
        cout << "(" << c << " * " << x << "^" << i << ")";
        
        if (i > 0) {
            cout << " + ";
        }
    }
    cout << endl;

    cout << "   Suma de términos = " << valor_polinomio << endl;

    double verificacion = pow(x + 1, n);
    cout << "   Verificación (x+1)^n = (" << x << "+1)^" << n << " = " << verificacion << endl;

    cout << "\n   [Nota: El método óptimo para evaluar un polinomio es el Algoritmo de Horner.]" << endl;
}

int main() {
    int n;
    double x;

    cout << "Ingrese el exponente n (para (x+1)^n): ";
    cin >> n;

    vector<vector<long long>> triangulo = generarTrianguloPascal(n);

    if (triangulo.empty()) {
        return 1; 
    }

    // Parte a) Muestra coeficientes y polinomio en formato Triángulo
    mostrarPolinomioTriangulo(triangulo, n);

    // Pide el valor de x para la evaluación
    cout << "\nIngrese el valor de x para evaluar f(x): ";
    cin >> x;


    const vector<long long>& coeficientes_n = triangulo.back();

    // Parte b) Muestra la evaluación por pasos
    evaluarPolinomioPasos(coeficientes_n, n, x);

    return 0;
}