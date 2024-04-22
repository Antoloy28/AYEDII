/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

//lee los datos de archivo y crea una escructura de tipo flight
Flight flight_from_file(FILE* file, char code, item_t type)
{
    Flight flight;
    flight.code = code;
    flight.type = type;

    /* COMPLETAR */
    //lee los dostos del arch file segun el formato esperado en expectd.. espera dos valores, la hora de vuelo y cant de items
    int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &flight.hour, &flight.items_amount);
    //comprueba si fscaf no pudo leer el num esperado de var
    if(res < AMOUNT_OF_FLIGHT_VARS){
        fprintf(stderr, "Invalid file format: flight code %c", code);
        exit(EXIT_FAILURE);
    }

    return flight; //devuelve la estructura flight creada con la info del vuelo leida del arch
}