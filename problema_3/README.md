# Implementar un reconocimiento de cadenas, expresiones notación científica, ip, correo electrónico.
### Programa desarrollado en C++ que reconoce cuando una cadena de texto es uan ipv4, una expresion cientifica, un correo electronico. En caso contrario si no es una de estas tres opciones, entonces arroja un mensaje de que es cadena de texto normal y corriente

## Requisitos / dependencias
 - Un compilador c++ moderno:
  - linux / macos: gcc o clang
windows: mingw gcc o msvc cl
 - **(opcional)** make si quieres usar un makefile.
 - **(opcional)** valgrind para detectar fugas de memoria en linux/macos:
  - ubuntu/debian: sudo apt install valgrind
  - macos (homebrew): brew install --cask valgrind (puede requerir ajustes)
no hay librerías externas: solo la librería estándar de c++ 

# Instalación (Windows)
## 🛠️ Compilación del código

---

### Con MinGW (MSYS2):

 - i. Instala **MSYS2** y el paquete `mingw-w64-x86_64-gcc`.

- ii. En la consola MinGW:

```bash```

`gcc -std=c11 -Wall -Wextra -o ejecutable.exe main.cpp`

##O puede usar

`make run`

`./ejecutable.exe`

# Resultado del programa:

## Salida si se una IPv4
![Image](https://github.com/user-attachments/assets/f832d82d-ce82-4fef-83fe-64310585c2fc)

## Salida si es un correo electrónico
![Image](https://github.com/user-attachments/assets/38c56546-57af-42f0-bbb6-0b3a45213d7a)

## Salida si es una expresión científica
![Image](https://github.com/user-attachments/assets/0f2cf19c-c24a-4563-a941-6d8aa7fab8c1)

## Salida si ninguna de las anteriores cumple
![Image](https://github.com/user-attachments/assets/9df7fbb1-e700-4de3-ba3a-75e7c5998942)
