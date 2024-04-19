#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

int main(int argc, char *argv[]) { //complete los parametros
    FILE *file; //declara un puntero a un archivo
    unsigned int indexes[MAX_SIZE]; //arr para guardar int
    char letters[MAX_SIZE]; //arr para guardar letras
    char sorted[MAX_SIZE]; // arr ordenado resultante
    unsigned int length = 0; //inicia la long del arr en 0 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo 
    
 unsigned int index; //var para almacenar el indice del arr leido del arch 

   if (argc != 2){ //verif si el prog se ejecuto con un argum (nombre del arch de entrada) si no imprime error
        printf("EXPECTED UN FILE AS ARGUMENT \nCORRECT USE: ./ejecutable ./file.in\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r"); //abre el archivo de entrada en modo lectura
    while(!feof(file) && length <MAX_SIZE){ // lee el arch y alamcena los indices y letras en los arr
        fscanf(file, "%u -> *%c* ", &index, &letters[length]); //correspondientes hasta alcanzar el tam max
        if(index >= MAX_SIZE){ //o el final del arch
            printf("INDEX MAXIMO ALCANZADO, INVALID FILE\n");
        }
        indexes[length] = index;
    }
    fclose(file); //cierra el arch desp de leer
    for(unsigned int i = 0; i < length; i++){ //utiliza los indices leidos para organizar en un nuevo ar "sorted"
        sorted[indexes[i]] = letters[i];
    }

    dump(sorted, length); //imprime el arr ordenado usando la func dump

    return EXIT_SUCCESS;
}


