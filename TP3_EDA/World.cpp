#include "World.h"

void World::initWorld()
{
    for (unsigned int i = 0; i < blobCounter; i++)      //constructor de Class Blobs
    {
        nBlobs[i].blobRand(velMax * 100, i, modo, muertePorcentage);              // REVISAR
    }
    for (unsigned int i = 0; i < foodTotal; i++)
    {
        nFood[i].foodRand(i);               // Randomiza los parametros de la Food.
    }
}