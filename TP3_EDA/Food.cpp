#include <time.h>
#include <stdlib.h>
#include "Food.h"
#include "const.h"

/****************************************************************
FOODRAND:
->Descripcion:funcion ,interna de respawn_food,  que les da posiciones aleatorias a food
    Recibe:
        1. int i: recibe un indice que se utiliza en la semilla del rand

    Retorna: void
****************************************************************/
void Food::foodRand(int i)
{
    srand(time(NULL) * i *1000);
    foodPos.x = (double)(rand() % DISPLAYWIDTH);           //checkear los maximos valores que puede obtener
    foodPos.y = (double)(rand() % DISPLAYHEIGHT);
}


/****************************************************************
RESPAWN_FOOD:
->Descripcion: funcion que comprueba el arreglo de food, buscando a los comidos y una vez que los encontro los hace reaparecer
    Recibe:
        1. Food foods[]: recibe un arreglo de foods
        2. unsigned int foodCount: recibe la cantidad de comida elegida por el usuario

    Retorna: void
****************************************************************/
//funcion que comprueba el arreglo de cfood , buscando a los comidos y los hace aparecer de nuevo.
void respawn_food(Food foods[], unsigned int foodCount) {
    for (int i = 0; i < foodCount; i++)
    {
        if (foods[i].isAlive == false) {
            foods[i].foodRand(i);
            foods[i].isAlive = true;
        }
    }
}
