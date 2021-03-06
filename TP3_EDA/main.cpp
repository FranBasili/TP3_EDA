#include <iostream>
#include "World.h"
#include "Food.h"
#include "Blob.h"
#include "const.h"
#include "parser.h"
#include "grafica.h"
#include <time.h>


int parseCallback(char* key, char* value, void* userData);
void delay(float number_of_seconds);

int main(int argc, char* argv[]) {
    World mundo;                
    initializeAllegro();                                // Inicializamos allegro.
    parseCmdLine(argc, argv, parseCallback, &mundo);    // Parseamos los comandos de la consola.            
    mundo.initWorld();                                  // Iniciamos el mundo dandole param. a los blobs y a las foods.
    drawWorld(mundo);                                   // Mostramos el estado inicial de la simulación.
    
    while (mundo.running) {
        redirigir(mundo.nBlobs, mundo.nFood, mundo.blobCounter, mundo.foodTotal, mundo.smellRadius);    // Los blob apuntan a la comida visible mas cercan.
        movimiento(mundo.nBlobs, mundo.blobCounter, mundo.velPorcentage);                               // Los blobs se mueven.
        comer(mundo.nBlobs, mundo.nFood, mundo.blobCounter, mundo.foodTotal);                           // Si pueden comer, comen.
        fusionar(mundo.nBlobs, mundo.blobCounter, mundo.randomJiggleLimit);                             // si tienen que fusionarse, se fusionan.
        nacer(mundo.nBlobs, mundo.blobCounter);                                                         // Hago los nacimientos en los casos necesarios.
        mundo.running = morir(mundo.nBlobs, mundo.blobCounter, mundo.muertePorcentage);                 // Mato a los blobs que le toque.
        drawWorld(mundo);                                                                               // Muestro en pantalla la simulación y analizo los parametros de simulacion.
        delay(SEC_PER_TICK);                                                                            // Esperamos el tiempo de un tick.
    }

    shutdownAllegro();  // Una vez finalizada la simulación, destruimos todo lo de allegro.
    return 0;


    /*
        Resumen del main:

        Inicializar Back.
        Inicializar arreglo.

        Bucle:
        1. Verificar si alguno puede comer.
        2. Verificar si se pueden Mergear
        3. Actualizar direcciones
        4. Mover
        5. Determinar nacimientos
        6. Determinar muertes
        7. Revisar eventos allegro
        8. Mostrar en Allegro

        Destruir recursos.
    */
}




/*****************************************************************************************
 * CALLBACK
 *  Funci�n que guarda en el campo KEY de la estructura userData el value.
 *  Retorna 0 si hay error y 1 no hay error.
 * **************************************************************************************/
int parseCallback(char* key, char* value, void* userData)
{
    World* Data = (World*) userData;   // "Casteamos" el puntero al formato de nuestra
                                       // estructura.

     float tempf = atof(value);     // Transformamos el value a float.
     int tempi = atoi(value);       // Transformamos el value a entero.

    if (!strcmp(key, "vM"))         // Dependiendo de la key ingresada, guardamos el dato 
    {                               //ingresado en un campo distinto.

        if (tempf > 0)                  // Si el valor no cumple alguna condicion logica del
            Data->velMax = tempf;    //campo, retornamos error.

        else
            return  ERROR_CALLBACK;
    }
    else if (!strcmp(key, "vP"))
    {
        
        if (tempf > 0 && tempf <= 1)
            Data->velPorcentage = tempf;

        else
            return  ERROR_CALLBACK;
    }
    else if (!strcmp(key, "bC"))
    {
        if (tempi > 0)
            Data->blobCounter = tempi;

        else
            return  ERROR_CALLBACK;
    }

    else if (!strcmp(key, "fC"))
    {
        if (tempi > 0)
            Data->foodTotal = tempi;

        else
            return  ERROR_CALLBACK;
    }
    else if (!strcmp(key, "modo"))
    {
        if (tempi == 1 || tempi == 2)
            Data->modo = tempi;

        else
            return  ERROR_CALLBACK;
    }

    else if (!strcmp(key, "sR"))
    {
        if (tempi > 0)
            Data->smellRadius = tempi;

        else
            return  ERROR_CALLBACK;
    }

    else if (!strcmp(key, "rJL"))
    {
        if (tempi > 0 && tempi <= 360)
            Data->randomJiggleLimit = tempi;

        else
            return  ERROR_CALLBACK;
    }
    else if (!strcmp(key, "mBaby"))
    {
        if (tempf > 0 && tempf < 1)
            (Data->muertePorcentage)[0] = tempf;

        else
            return  ERROR_CALLBACK;
    }
    else if (!strcmp(key, "mGrown"))
    {
        if (tempf > 0 && tempf < 1)
            (Data->muertePorcentage)[1] = tempf;

        else
            return  ERROR_CALLBACK;
    }
    else if (!strcmp(key, "mOld"))
    {
        if (tempf > 0 && tempf < 1)
            (Data->muertePorcentage)[2] = tempf;

        else
            return  ERROR_CALLBACK;
    }
    else {
        return ERROR_CALLBACK;          // Si no reconozco la Key, retorno error.
    }

    return OK;
}

void delay(float number_of_seconds)
{
    // Convertimos a milis 
    float milli_seconds = 1000 * number_of_seconds;

    // Guardamos el tiempo 
    clock_t start_time = clock();

    // Congelamos el codigo hasta que se cumpla el tiempo 
    while (clock() < start_time + milli_seconds)
        ;
}
