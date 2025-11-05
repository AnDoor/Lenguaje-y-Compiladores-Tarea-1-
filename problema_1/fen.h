#ifndef FEN_H
#define FEN_H

#include <stdbool.h>

/*
 * is_valid_fen:
 *  - Entrada: una cadena C con la posible notación FEN (puede contener espacios/trailing newline).
 *  - Salida: true si la cadena es un FEN válido según las reglas básicas de FEN (6 campos),
 *            false en caso contrario.
 *
 * Documentación:
 *  La función valida los seis campos de FEN:
 *   1) disposición de piezas (8 filas separadas por '/', cada fila suma 8 casillas)
 *   2) color activo ('w' o 'b')
 *   3) disponibilidad de enroque (combinación de 'KQkq' o '-')
 *   4) casilla posible de en passant (archivo a-h y fila 3 o 6, o '-')
 *   5) contador de medio-movimiento (entero >= 0)
 *   6) número de movimiento (entero > 0)
 *
 *  Acepta una cadena con espacios; internamente se recorta (trim) antes de validar.
 */
bool is_valid_fen(const char *fen);

#endif /* FEN_H */
