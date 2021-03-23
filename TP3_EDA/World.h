#ifndef _WORLD_
#define _WORLD_
/*****************************************************************************************
 *                                       Bibliotecas
 ****************************************************************************************/
#include "Food.h"
#include "Blob.h"
#include "const.h"
 /*****************************************************************************************
  *                                       Clase
  ****************************************************************************************/
class World {
public:
    Blob nBlobs[MAXBLOBS];
    Food nFood[MAXFOOD];
    double velPorcentage;
    float velMax;
    unsigned int blobCounter;
    unsigned int foodTotal;
    int modo;
    int smellRadius; //Radio de detecci�n de la comida desde el centro del Blob.
    int randomJiggleLimit;//Valor aleatorio a sumar para el c�lculo de la direcci�n. 
    int muertePorcentage[3];

    World() {                        //me crea y me construye a todas las clases incluidas en el mundo

        blobCounter = 10;
        velPorcentage = 50;
        velMax = 20;
        foodTotal = 10;
        modo = 1;
        smellRadius = 20;
        randomJiggleLimit = 90;
        muertePorcentage[0] = 25;
        muertePorcentage[1] = 50;
        muertePorcentage[2] = 75;

    }
    void initWorld();
};

#endif // !WORLD

