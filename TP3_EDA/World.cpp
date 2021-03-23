#include "World.h"
#include <iostream>

void World::initWorld()
{
    for (unsigned int i = 0; i < blobCounter; i++)      //constructor de Class Blobs
    {
        nBlobs[i].blobRand(muertePorcentage);              // REVISAR
        nBlobs[i].setVel(velMax * 100, modo);
    }
    for (unsigned int i = 0; i < foodTotal; i++)
    {
        nFood[i].foodRand(i);               // Randomiza los parametros de la Food.
    }
}