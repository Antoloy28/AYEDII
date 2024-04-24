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

#define MAX_ALLOWED_BOXES 75
#define MAX_ALLOWED_LETTERS 150
#define BOX_PENALTY 10
#define LETTER_PENALTY 2

typedef Flight DeliveryTable [TYPE][HOURS];

/**
 * @brief Write the content of the array 'a' into stdout.
 * @param[in] a array to dump in stdout
 */
void array_dump(DeliveryTable a);

/**
 * @brief calcula la tarifa adicional que debe pagar la empresa
 * @param[in] a array
 * @param[in] hour un valor entre 0 y 23 que representa la hora
 *                 calcular el costo de la tarifa de espacio adicional
 * @details
 *   cuenta los articulos llegados hasta la`hour` (inclusive).
 *   por cada caja extra se suma BOX_PENALTY a la tarifa
 *   por cada letra extra se suma LETTER_PENALTY ta la tarifa
 */
unsigned int extra_space_fee_cost(DeliveryTable a, unsigned int hour);


/**
 * @brief reads an array of layover information from file
 * @details
 *
 *  Each element is read from the file located at 'filepath'.
 *  The file must exist in disk and must have its contents in a sequence of
 *  lines, each with the following format:
 *
 *   <flight_code> <hour> <type> <boxes> <type> <letters>
 *
 *   Those elements are copied into the multidimensional array 'a'.
 *   The dimensions of the array are given by the macros noted above.
 *
 * @param a array which will contain read file
 * @param filepath file with layover data
 */
void array_from_file(DeliveryTable a, const char *filepath);

#endif