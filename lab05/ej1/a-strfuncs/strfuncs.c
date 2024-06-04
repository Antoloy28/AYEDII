#include "strfuncs.h"

size_t string_length(const char *str){ //calcula la longitud de la cadena apuntada por str,
    if(str == NULL){
        return 0;
    }
    size_t length = 0; //var para contar la long d la cadena 
    while(str[length] != '\0'){//este bucle se ejecuta mientras mientras el caracter actual de la pos lenght no 
    // sea el nulo \0 q indica el final d la cadena 
        ++length;
    }
    return length;
}

//devuelve una nueva cadena en MEM DIN  q se obtiene tomando los caracteres de str que son distintos al caract c
char *string_filter(const char *str, char c) {
    unsigned int k = 0;
    // Asignar suficiente memoria para la nueva cadena filtrada
    // En el peor de los casos, la nueva cadena es igual de larga que la original
    char *filtered = (char *)malloc((string_length(str) + 1) * sizeof(char)); //strlen para obtener la long de str
    if (filtered == NULL) {
        return NULL; // Manejo de errores si malloc falla
    }

    for (unsigned int i = 0; i < string_length(str); i++) {//el bucle recorre str y copia los caracter distintos de c en
    // filtered
        if (str[i] != c) {
            filtered[k] = str[i];
            ++k;
        }
    }
    filtered[k] = '\0'; // Asegurar que la nueva cadena esté terminada en nulo

    return filtered;
}

//indica si la nueva cadena apuntada por str es simetrica en cuanto q el primer caracter coincide con el ultimo
//el segundo con el penultimo, etc 
bool string_is_symmetric(const char *str){
    if(str == NULL){
        return false;
    }
    size_t length = string_length(str); //obtener la longitud de la cadena y almacena el valor en lenght
    for(size_t i = 0; i < length/2; i++){//recorre la cadena desde el incio a la mitad
        if(str[i] != str[length - 1 - i]){ //si los caracteres no coinciden la cadena no es simetrica
            return false;
        }

    }
    return true; //si la cadena si es simetrica

}