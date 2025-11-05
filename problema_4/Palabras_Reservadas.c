
#include <stdio.h>

/* Comentario multilínea con palabras reservadas:
   int return if else for
*/

int suma(int a, int b) {
    return a + b; 
}

int main(void) {
    int contador = 0;
    char ch = 'i'; /* literal de carácter con i */

    // Comentario línea: if else int return for

    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            printf("i = %d es par\n", i);
        } else {
            printf("i = %d es impar\n", i);
        }
    }

    int integration = 10; 
    contador = suma(integration, 5);

    return contador;
}
