//borre algunas cosas y func por pedido del enunciado (borre dond habia filepath)


/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int array_from_file(int array[], unsigned int max_size) {
    //your code here!!!
    FILE *archivo = stdin; //abre un arch filepath en modo lectura 'r'
    unsigned int length;
    fscanf(archivo, "%u", &length); //lee un num sin sign y lo almacena en la var length
    assert(length <= max_size); //verif que el array legth no exceda el max permitido max_size
    for(unsigned int i = 0; i < length; i++){ //recorre cada elem del array
        fscanf(archivo, "%i", &array[i]);//lee un entero desde el arch y lo amacena en el elem correp del array
        if(feof(archivo)){ //verif si se alcanzo el final del arch
            printf("ERROR!!!\n");
            exit(EXIT_FAILURE);

        }
    }
    fclose(archivo);
    return length;
}

void array_dump(int a[], unsigned int length) { //imprime el array, con los corchetes y separado
    //your code here!!!
    if(!length == 0u){ //verif q length no sea igual a 0 
        printf("[");
        for(unsigned int i = 0; i < length-1u;i++){ //empieza la iteracion hasta el ultimo elem
        printf("%i, ", a[i]);// se imprime cada elem, seguido de una coma

    }
    printf("%i]\n", a[length-1u]);
    }

}


int main() { //se van los argumentos por enunciado
    //char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    //filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}