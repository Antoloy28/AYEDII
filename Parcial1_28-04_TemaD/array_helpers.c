/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last line in flight file
* @return True when is the last line of the file, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DelayTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: %s flight with %u passengers arrived at %u:00, with %u delay",
        f.code,
        f.type == 0 ? "last_mile" : "layover",
        f.passengers_amount,
        f.hour - 1,
        f.delay
      );
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int compensation_cost(DelayTable a, unsigned int hour) {
    unsigned int total_compensation = 0;

    // Inicializar la demora total para cada tipo de vuelo
    unsigned int total_last_mile_delay = 0;
    unsigned int total_layover_delay = 0;

    // Iterar sobre las horas hasta las 6pm
    for (unsigned int i = 0; i <= hour && i < HOURS && i < 18; i++) {
        // Sumar la demora de cada vuelo en la hora actual
        total_last_mile_delay += a[last_mile][i].delay * a[last_mile][i].passengers_amount;
        total_layover_delay += a[layover][i].delay * a[layover][i].passengers_amount;
    }

    // Calcular la compensación para cada tipo de vuelo si excede el límite permitido
    if (total_last_mile_delay > MAX_LM_DELAY_ALLOWED) {
        total_compensation += (total_last_mile_delay - MAX_LM_DELAY_ALLOWED) * COMPENSATION_PER_MINUTE;
    }
    if (total_layover_delay > MAX_LAYOVER_DELAY_ALLOWED) {
        total_compensation += (total_layover_delay - MAX_LAYOVER_DELAY_ALLOWED) * COMPENSATION_PER_MINUTE;
    }

    return total_compensation;
}

void array_from_file(DelayTable array, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    char code;
    unsigned int hour, delay, passengers_amount;

    while (fscanf(file, "%u %u %u %u %u %u %c", &hour, &delay, &passengers_amount, &hour, &delay, &passengers_amount, &code) == 7) {
        // Asegurarse de que la hora esté dentro del rango
        if (hour >= 1 && hour <= HOURS) {
            // Leer y almacenar datos de vuelo para last_mile
            Flight last_mile_flight = { code, last_mile, hour, delay, passengers_amount };
            array[last_mile][hour - 1] = last_mile_flight;

            // Leer y almacenar datos de vuelo para layover
            Flight layover_flight = { code, layover, hour, delay, passengers_amount };
            array[layover][hour - 1] = layover_flight;
        }
    }

    fclose(file);
}