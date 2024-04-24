/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

//static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int best_profit(BakeryProductTable a) //calcula la mayor ganancia que puede obtener una tienda
{
    unsigned int max_profit = 0u; //almacena la ganancia obtenida hasta el momento
    //COMPLETAR
    for(unsigned int city = 0u; city < CITIES; city++){ //itera sobre cada ciudad y temporada
        for(unsigned int season = 0u; season < SEASONS; season++){
            //para cada ciudad y temporada, calcula el costo total de produccion (sumando harina
            // levadura y manteca mult por su cant resp y su precio resp)
            unsigned int cost = a[city][season].flour_cant * a[city][season].flour_price +
                                a[city][season]. yeast_cant * a[city][season].yeast_price +
                                a[city][season].butter_cant * a[city][season].butter_price;
            
            //calcula la ganancia para esta ciudad y temporada restando el costo total de prod del valor de venta
            unsigned int profit = a[city][season].sale_value - cost;
            //Compara esta ganancia con la ganancia máxima registrada (max_profit) hasta ahora y,
            // si es mayor, actualiza max_profit con el nuevo valor de ganancia.
            if(profit > max_profit){
                max_profit = profit;
            }

        }
    }
    return max_profit; //devuelve la ganancia maxima
}

void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    int city, season; //var para almacenar la ciudad y temporada
    //var para alamacenar los datos de produccion y venta
    unsigned int flour_cant, flour_price, yeast_cant, yeast_price, butter_cant, butter_price, sale_value;
    //lee los datos del archivo linea por linea en el formato especifiado(por eunciado)
    while (fscanf(file, "##%d??%d (%u,%u) (%u,%u) (%u,%u) %u\n",
                  &city, &season,
                  &flour_cant, &flour_price,
                  &yeast_cant, &yeast_price,
                  &butter_cant, &butter_price,
                  &sale_value) == 9)
    { //verifica si la ciudad y temporada estan dentro del rango valido
        if (city >= 0 && city < CITIES && season >= 0 && season < SEASONS)
        {
            //almacena los datos en la estruc bakeryproducttable en la posicion correspondiente
            array[city][season].flour_cant = flour_cant;
            array[city][season].flour_price = flour_price;
            array[city][season].yeast_cant = yeast_cant;
            array[city][season].yeast_price = yeast_price;
            array[city][season].butter_cant = butter_cant;
            array[city][season].butter_price = butter_price;
            array[city][season].sale_value = sale_value;
        }
        else //si la ciudad o temporada estan fuera del rango valido
        {
            fprintf(stderr, "Invalid city or season.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}
