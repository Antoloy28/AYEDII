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
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a) {
  /* COMPLETAR */
  unsigned int total = 0u; //para almacenar el costo total por exceso de espacio

  // Ver cuanto va al deposito ese dia
  unsigned int total_boxes = 0u; //cant total de cajas
  unsigned int total_letters = 0u; //cant total de cartas
  // Asumo que para la hora h, el indice es h-1
  //se verif si hay envios de cartas y cajas en cada hora, si hay envios se duma respectivamente
  for(unsigned int i=0u; i<=FEE_CLOSE_HOUR; i++) {
    if(a[boxes][i].items_amount > 0) {
      total_boxes += a[boxes][i].items_amount;
    }
    if(a[letters][i].items_amount > 0) {
      total_letters += a[letters][i].items_amount;
    }
  }

  // Calcular penalty total
  //se calcula el costo toal por exceso de espacio
  //restando la cant maxima permitida de cajas y cartas a la cantidad totales de cartas y
  // cajas multip por las tarifas de penalizacion
  
  total = BOX_PENALTY*(total_boxes - MAX_ALLOWED_BOXES) + LETTER_PENALTY*(total_letters - MAX_ALLOWED_LETTERS);

  return total;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  /* COMPLETAR: lectura completa de todos los datos (dentro del while complete)*/
  while (i < HOURS && !feof(file)) {
    /* COMPLETAR: lectura de codigo de vuelo  (complete lo de fscanf)*/
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
    Flight flight_boxes = flight_from_file(file, code, boxes);
    array[boxes][flight_boxes.hour-1] = flight_boxes;
    Flight flight_letters = flight_from_file(file, code, letters);
    array[letters][flight_letters.hour-1] = flight_letters;
    i++;
  }
  fclose(file);
}