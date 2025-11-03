#include <stdio.h>
#include <stdlib.h>
#include "fen.h"

int main(void) {
    char line[1024];
    
    printf("Ingresar la cadena FEN y presionar enter:\n");
    fflush(stdout);

    /* Leer una línea desde stdin (por ejemplo: "rnbqkbnr/... 0 1\n") */
    if (fgets(line, sizeof(line), stdin) == NULL) {
        /* Si no hay entrada, informamos por stderr y salimos con código 1 */
        fprintf(stderr, "Error: no se recibió entrada\n");
        return 1;
    }

    /* Llamar al módulo de validación FEN */
    if (is_valid_fen(line)) {
        printf("FEN válida\n");
        return 0;
    } else {
        printf("FEN inválida\n");
        return 2;
    }
}
