#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) { //devuelve la long de la cadena guardada en el parametro s
    /* COMPLETAR */
    unsigned int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}

bool fstring_eq(fixstring s1, fixstring s2) { //indica si la cadena s1 y s2 son iguales 
    /*COMPLETAR*/
    unsigned int length = fstring_length (s1);
    if (length != fstring_length(s2)){
        return false;
    }else{
        for (unsigned int i = 0; i < length; i++){
            if (s1[i] != s2[i]){
                return false;
            }
        }
    }
    return true;
}

bool fstring_less_eq(fixstring s1, fixstring s2) { //indica si la cadena guardada en s1 es menor o igual que la guardada en s2 en el snetido del orden alfab
    /*COMPLETAR*/
    unsigned int length = fstring_length(s1);
    unsigned int i = 0;
    while(i < length){
        if (s1[i] < s2[i]){
            return true;
        }else if (s1[i] > s2[i]){
            return false;
        }
        i++;
    }
    return true; 
}

