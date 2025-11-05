#include "fen.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define FEN_BUF_SIZE 1024

/*
 * trim:
 *  - Quita espacios en blanco iniciales y finales de s (in-place).
 */
static void trim(char *s) {
    char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != s) memmove(s, start, strlen(start) + 1);

    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[len - 1] = '\0';
        len--;
    }
}

/*
 * is_piece_letter:
 *  - True si c es una letra válida de pieza (PNBRQKpnbrqk).
 */
static bool is_piece_letter(char c) {
    return (c == 'P' || c == 'N' || c == 'B' || c == 'R' || c == 'Q' || c == 'K' ||
            c == 'p' || c == 'n' || c == 'b' || c == 'r' || c == 'q' || c == 'k');
}

/*
 * is_valid_placement:
 *  - Valida el primer campo (colocación): exactamente 8 filas separadas por '/',
 *    y cada fila suma exactamente 8 casillas (las cifras 1..8 cuentan huecos).
 */

static bool is_valid_placement(const char *s) {
    if (s == NULL || *s == '\0') return false;

    int ranks = 0;
    const char *p = s;
    while (*p) {
        ranks++;
        int squares = 0;

        /* procesar una fila hasta '/' o fin */
        while (*p && *p != '/') {
            if (isdigit((unsigned char)*p)) {
                int v = *p - '0';
                if (v < 1 || v > 8) return false;
                squares += v;
            } else if (is_piece_letter(*p)) {
                squares += 1;
            } else {
                return false;
            }
            if (squares > 8) return false;
            p++;
        }

        if (squares != 8) return false;

        if (*p == '/') p++; /* saltar '/' y continuar */
    }

    return (ranks == 8);
}

/*
 * is_valid_active_color:
 *  - Segundo campo: 'w' o 'b'.
 */
static bool is_valid_active_color(const char *s) {
    return (s && (strcmp(s, "w") == 0 || strcmp(s, "b") == 0));
}

/*
 * is_valid_castling:
 *  - Tercer campo: combinación sin repetición de K Q k q, o '-' si no hay enroques.
 */
static bool is_valid_castling(const char *s) {
    if (s == NULL) return false;
    if (strcmp(s, "-") == 0) return true;

    bool seenK = false, seenQ = false, seenk = false, seenq = false;
    for (const char *p = s; *p; ++p) {
        if (*p == 'K') {
            if (seenK) return false;
            seenK = true;
        } else if (*p == 'Q') {
            if (seenQ) return false;
            seenQ = true;
        } else if (*p == 'k') {
            if (seenk) return false;
            seenk = true;
        } else if (*p == 'q') {
            if (seenq) return false;
            seenq = true;
        } else {
            return false;
        }
    }
    return true;
}

/*
 * is_valid_en_passant:
 *  - Cuarto campo: '-' o una casilla válida a-h + fila 3 o 6.
 */
static bool is_valid_en_passant(const char *s) {
    if (s == NULL) return false;
    if (strcmp(s, "-") == 0) return true;
    if (strlen(s) != 2) return false;

    char file = s[0];
    char rank = s[1];
    if (file < 'a' || file > 'h') return false;
    if (rank != '3' && rank != '6') return false;
    return true;
}

/*
 * is_nonnegative_integer:
 *  - Cadena que representa un entero >= 0 (al menos un dígito, solo dígitos).
 */
static bool is_nonnegative_integer(const char *s) {
    if (s == NULL || *s == '\0') return false;
    for (const char *p = s; *p; ++p) {
        if (!isdigit((unsigned char)*p)) return false;
    }
    return true;
}

/*
 * is_positive_integer:
 *  - Cadena que representa un entero > 0.
 */
static bool is_positive_integer(const char *s) {
    if (!is_nonnegative_integer(s)) return false;

    /* verificar que no sea "0", "00", ... */
    for (const char *p = s; *p; ++p) {
        if (*p != '0') return true;
    }
    return false; /* todos ceros -> no es positivo */
}

/*
 * is_valid_fen:
 *  - Valida una cadena FEN completa. Se esperan exactamente 6 campos separados por espacios.
 *  - Uso: simplificado para ser legible y directo.
 */
bool is_valid_fen(const char *fen) {
    if (fen == NULL) return false;

    char buf[FEN_BUF_SIZE];
    if (strlen(fen) >= sizeof(buf)) return false;
    strcpy(buf, fen);
    trim(buf);
    if (buf[0] == '\0') return false;

    /* Separar en exactamente 6 campos (modificando buf in-place) */
    char *parts[6] = {0};
    int idx = 0;
    char *p = buf;

    /* saltar espacios iniciales por si acaso */
    while (*p && isspace((unsigned char)*p)) p++;

    while (*p && idx < 6) {
        parts[idx++] = p;
        /* avanzar hasta el siguiente espacio */
        while (*p && !isspace((unsigned char)*p)) p++;
        if (*p) {
            *p = '\0'; /* separar token */
            p++;
            while (*p && isspace((unsigned char)*p)) p++; /* saltar espacios consecutivos */
        }
    }

    /* si no conseguimos 6 campos, o hay texto extra después -> inválido */
    if (idx != 6) return false;
    if (*p != '\0') return false;

    /* validar cada campo */
    if (!is_valid_placement(parts[0])) return false;
    if (!is_valid_active_color(parts[1])) return false;
    if (!is_valid_castling(parts[2])) return false;
    if (!is_valid_en_passant(parts[3])) return false;
    if (!is_nonnegative_integer(parts[4])) return false;
    if (!is_positive_integer(parts[5])) return false;

    return true;
}
