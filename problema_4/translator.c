/* translator_student.c
 *
 * Programa simple (estilo estudiante) que lee todo un archivo C en memoria
 * dinámica y reemplaza hasta 5 palabras reservadas por su equivalente en español.
 *
 * Compilar:
 *   gcc -std=c11 -o translator_student translator_student.c
 *
 * Uso:
 *   ./translator_student archivo.c > archivo_trad.c
 *
 * Nota: código intencionalmente simple, no profesional. Maneja strings,
 * caracteres y comentarios de forma básica para evitar reemplazar dentro de ellos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Lista corta de palabras reservadas (máx 5) y sus traducciones */
struct Map { const char *kw; const char *es; };
struct Map map[] = {
    {"int", "entero"},
    {"return", "retornar"},
    {"if", "si"},
    {"else", "sino"},
    {"for", "para"},
    {NULL, NULL}
};

/* lee todo el archivo en memoria dinámica, devuelve buffer (nulo-terminado) */
char *read_all(FILE *f) {
    size_t cap = 4096;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char *n = realloc(buf, cap);
            if (!n) { free(buf); return NULL; }
            buf = n;
        }
        buf[len++] = (char)c;
    }
    buf[len] = '\0';
    return buf;
}

/* devuelve traducción o NULL */
const char *lookup(const char *tok) {
    for (int i = 0; map[i].kw; ++i) {
        if (strcmp(map[i].kw, tok) == 0) return map[i].es;
    }
    return NULL;
}

int main(int argc, char **argv) {
    FILE *f = stdin;
    if (argc >= 2) {
        f = fopen(argv[1], "rb");
        if (!f) { perror("fopen"); return 1; }
    }

    char *s = read_all(f);
    if (f != stdin) fclose(f);
    if (!s) { fprintf(stderr, "Error leyendo entrada\n"); return 1; }

    int i = 0;
    int in_str = 0, in_char = 0, in_slc = 0, in_mlc = 0;

    while (s[i]) {
        char c = s[i];

        /* manejar comentarios y literales de forma simple */
        if (in_str) {
            putchar(c);
            if (c == '\\') { if (s[i+1]) putchar(s[++i]); } /* escape */
            else if (c == '"') in_str = 0;
            i++; continue;
        }
        if (in_char) {
            putchar(c);
            if (c == '\\') { if (s[i+1]) putchar(s[++i]); }
            else if (c == '\'') in_char = 0;
            i++; continue;
        }
        if (in_slc) {
            putchar(c);
            if (c == '\n') in_slc = 0;
            i++; continue;
        }
        if (in_mlc) {
            putchar(c);
            if (c == '*' && s[i+1] == '/') { putchar(s[++i]); in_mlc = 0; }
            i++; continue;
        }

        /* detectar inicios */
        if (c == '"') { in_str = 1; putchar(c); i++; continue; }
        if (c == '\'') { in_char = 1; putchar(c); i++; continue; }
        if (c == '/' && s[i+1] == '/') { in_slc = 1; putchar(c); putchar(s[++i]); i++; continue; }
        if (c == '/' && s[i+1] == '*') { in_mlc = 1; putchar(c); putchar(s[++i]); i++; continue; }

        /* detectar token (identificador/keyword) */
        if (isalpha((unsigned char)c) || c == '_') {
            int start = i;
            while (isalpha((unsigned char)s[i]) || isdigit((unsigned char)s[i]) || s[i] == '_') i++;
            int len = i - start;
            char *tok = malloc(len + 1);
            if (!tok) { free(s); fprintf(stderr, "malloc\n"); return 1; }
            memcpy(tok, s + start, len);
            tok[len] = '\0';
            const char *tr = lookup(tok);
            if (tr) {
                fputs(tr, stdout);
            } else {
                fputs(tok, stdout);
            }
            free(tok);
            continue;
        }

        /* por defecto copiar caracter */
        putchar(c);
        i++;
    }

    free(s);
    return 0;
}
