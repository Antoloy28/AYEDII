/*
  @file array_helpers.h
  @brief defines array helpers methods. These methods operates over multidimensional array of layover
*/
#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>
#include "flight.h"

#define HOURS 24
#define TYPE 2

typedef Flight LayoverTable [HOURS][TYPE];

/**
 * @brief Write the content of the array 'a' into stdout.
 * @param[in] a array to dump in stdout
 */
void array_dump(LayoverTable a);

/**
 * @brief calcula cuantos pasajero estan esperando un vuelo
 * @param[in] a matriz con datos
 * @param[in] hour un valor entre 0 y 23 que representa la hoea a calcular *la cantidad de pasajeros en espera
 */
unsigned int passengers_amount_in_airport(LayoverTable a, unsigned int hour);


/**
 * @brief lee una serie de info de escala del archivo
 * @details
 *
 *  cada elem se lee del arch ubicado en 'filepath'.
 *  el arch debe existir en el disco y debe tener su contenido en una sec de lineas, cada con el sig formato
 *
 *   <flight_code> <type> <hour> <passengers> <type> <hour> <passengers>
 *
 *   esos elem se copian se la matriz multidimensional 'a'.
 *   las dim de la matriz vienen dadas por las macros mencionadas anteriormente
 *
 * @param a array which will contain read file
 * @param filepath file with layover data
 */
void array_from_file(LayoverTable a, const char *filepath);

#endif