/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3;

Flight flight_from_file(FILE* file)
{
    Flight flight;

    int res = fscanf(file, "%u %u %u %c", &flight.hour, &flight.delay, &flight.passengers_amount, &flight.code);
    if (res != AMOUNT_OF_FLIGHT_VARS) {
        fprintf(stderr, "Invalid flight format.\n");
        exit(EXIT_FAILURE);
    }

    // Determinar el tipo de vuelo según el formato del archivo
    if (flight.hour == 0) {
        flight.type = last_mile;
    } else {
        flight.type = layover;
    }

    return flight;
}