# Validador FEN en C

Descripción
-----------
Programa en C que valida cadenas en notación FEN (Forsyth–Edwards Notation).  
Verifica las seis partes de la FEN: disposición del tablero, color activo, enroque, casilla de en-passant, contador de medio-movimiento y número de movimiento.  

Requisitos / dependencias
------------------------
- Un compilador C moderno:
  - Linux / macOS: `gcc` o `clang`
  - Windows: MinGW `gcc` o MSVC `cl`
- (Opcional) `make` si quieres usar un Makefile.
- (Opcional) `valgrind` para detectar fugas de memoria en Linux/macOS:
  - Ubuntu/Debian: `sudo apt install valgrind`
  - macOS (Homebrew): `brew install --cask valgrind` (puede requerir ajustes)

No hay librerías externas: solo la librería estándar de C.

Instalación (Linux / macOS)
---------------------------
1. Asegúrate de tener `gcc` o `clang` instalado:
   - Ubuntu/Debian: `sudo apt update && sudo apt install build-essential`
   - macOS (Xcode tools): `xcode-select --install`

2. Compilar:
```sh
gcc -std=c11 -Wall -Wextra -o fen main.c fen.c
```

Instalación (Windows)
---------------------
- Con MinGW (MSYS2):
  1. Instala MSYS2 y el paquete `mingw-w64-x86_64-gcc`.
  2. En la consola MinGW:
```sh
gcc -std=c11 -Wall -Wextra -o fen.exe main.c fen.c
```
- Con Visual Studio (Developer Command Prompt):
```bat
cl /W4 /std:c11 /O2 main.c fen.c
```
(ajusta flags según tu versión de MSVC)

Códigos de salida
-----------------
- 0  -> FEN válida
- 1  -> Error de entrada (p. ej. no se leyó nada)
- 2  -> FEN inválida

Ejemplos (válidos / inválidos)
------------------------------
- Válida (posición inicial):
```
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
```
- Inválida (activo no válido):
```
... wronfield ... x KQkq - 0 1
```
- Inválida (menos de 6 campos o más de 6 campos): el validador exige exactamente 6 campos separados por espacios.

Notas de compilacion
-----------------------------------------

- Ya se encuentra creado un Makefile para la compilacion de los archivos del problema, solamente debe escribir en
la terminal make run y generara un ejecutable actualizado 

# Ejecutar el programa exportado
------------------------------

- Para iniciar el ejecutable creado por el make file llamado "ejecutable" ubicar la ruta de la terminal
en esta carpeta correspondiente al problema y escribir ./ejecutable para iniciar el programa. Este
archivo exportado se compilo en un sistema Linux, si tiene error se recomienda ejecutar make file para
compilar de acuerdo a su sistema operativo. 
