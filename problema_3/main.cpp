/*
 Implemente reconocimiento de cadenas, expresiones notación científica, ip, correo electrónico.
*/

#include <iostream>
#include <string>
#include <regex>

using namespace std;

/* funciona para poder verificar el match entre la cadena y los patrones de regex*/
bool verificar_patron(const string& cadena, const regex& patron) {

    return regex_match(cadena, patron);
}

int main() {
    //patrones regex para identificar patrones de textos
    const regex regexCientifica("^[+-]?(\\d+(\\.\\d*)?|\\.\\d+)[eE][+-]?\\d+$");
    const regex regexIP("^(\\d{1,3}\\.){3}\\d{1,3}$");
    const regex regexCorreo("^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    string test;


    cout << "--- PRUEBAS DE RECONOCIMIENTO DE CADENAS ---\n\n";
    cout<<"Introduzca una cadena de texto"<<endl;
   getline(cin,test);
  
    if (verificar_patron(test, regexCientifica)) {
        cout << "La cadena es una expresion cientifica\n";
    } else if (verificar_patron(test, regexIP)){
        cout << "La cadena es un protocolo de internet (IPv4) \n";
    }else if  (verificar_patron(test, regexCorreo)){
         cout << "La cadena de texto es un correo electronico\n";
    }else{
         cout << "Es una cadena de texto normal \n";
    }
    cout << "\n--- FIN DE PRUEBAS ---\n";

    return EXIT_SUCCESS;

}