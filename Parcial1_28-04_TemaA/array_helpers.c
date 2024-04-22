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
* @brief returns true when reach last entry in flight table
* @return True when is the last entry of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(LayoverTable a) { //calcula cuantos pasajeros estan esperando un vuelo 
  for (unsigned int hour = 0u; hour < HOURS; ++hour) { //itera sobre cada hora (fila)
    for (unsigned int type = 0u; type < TYPE; ++type) { //itera sobre cada tipo (columna)
      Flight f = a[hour][type];
      fprintf(stdout, "%c: %s at %u:00 with %u passengers", f.code, f.type == 0 ? "arrives" : "departs", f.hour - 1, f.passengers_amount);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int passengers_amount_in_airport (LayoverTable a, unsigned int h) {
  /* COMPLETAR */
  int total = 0; //para almacenar la suma total de pasaj en el aerop
  for (unsigned int i = 0; i < h-1; i++){ //bucle q itera sobre las horas
    total += a[i][0].passengers_amount; //suma la cantidad de pasajeros que llegan al aerop
    total -= a[i][1].passengers_amount; //resta la cant de pasajeros que salen del aerop
  }
  total += a[h][0].passengers_amount; //suma la cant de pasaje que llegan al aerop en la hora h

  return total; //devuelve los pasajeros en la hora h
}


void array_from_file(LayoverTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i=0; //para recorrer las horas en la tabla
  /* COMPLETAR: lectura completa de todos los datos */ /*(habia q completar dentro del while)*/
  while (!feof(file)) {
    /* COMPLETAR: lectura de codigo de vuelo (habia q coml el fscanf)*/
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    i++; //agregue yo
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    //complete el renglon de abajo
    Flight flight_arrival =  flight_from_file(file, code);
    array[flight_arrival.hour-1][flight_arrival.type] = flight_arrival; //agregue esta linea completa
    //comlete la  linea de abajo
    Flight flight_departure = flight_from_file(file, code);
    array[flight_departure.hour-1][flight_departure.type] = flight_departure;
  }
  fclose(file);
}
