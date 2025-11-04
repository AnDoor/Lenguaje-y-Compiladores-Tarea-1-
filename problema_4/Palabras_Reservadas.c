/* test_input.c
 *
 * Archivo de prueba para el traductor sencillo (translator_student.c).
 * Contiene las palabras reservadas: int, return, if, else, for
 * en código, en strings y en comentarios para verificar el comportamiento.
 */

#include <stdio.h>

/* Comentario multilínea con palabras reservadas:
   int return if else for
*/

int suma(int a, int b) {
    return a + b; // return aquí debería traducirse fuera de strings/comentarios
}

int main(void) {
    int contador = 0;
    char *texto = "En este string aparecen: int if for return else (no traducir)";
    char ch = 'i'; /* literal de carácter con i */

    // Comentario línea: if else int return for (no traducir)
    printf("Texto: %s\n", texto);

    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            printf("i = %d es par\n", i);
        } else {
            printf("i = %d es impar\n", i);
        }
    }

    int integration = 10; // identifier que contiene 'int' no debe cambiarse
    contador = suma(integration, 5);

    return contador;
}
