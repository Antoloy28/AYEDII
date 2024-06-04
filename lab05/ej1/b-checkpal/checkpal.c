#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

#define MAX_LENGTH 100

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered = NULL;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    
    if (fgets(user_input, MAX_LENGTH, stdin) != NULL) {
        // Eliminar el '\n' al final de la cadena, si existe
        size_t length = string_length(user_input);
        if (length > 0 && user_input[length - 1] == '\n') {
            user_input[length - 1] = '\0';
        }

        // Filtrar caracteres no deseados
        filtered = string_filter(user_input, ignore_chars[0]);
        for (unsigned int i = 1; i < SIZEOF_ARRAY(ignore_chars); i++) {
            char *temp = string_filter(filtered, ignore_chars[i]);
            free(filtered);
            filtered = temp;
        }

        // Verificar si la cadena filtrada es un palíndromo
        printf("El texto:\n\n"
               "\"%s\" \n\n"
               "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es" : "NO es");

        free(filtered); // Liberar memoria asignada
    } else {
        fprintf(stderr, "Error al leer la entrada.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
