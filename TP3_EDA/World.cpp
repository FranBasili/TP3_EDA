#include "World.h"
#include <iostream>

void World::initWorld()
{
    std::cout << "PRE INIT" << std::endl;
    std::cout << muertePorcentage[0] << "\t" <<muertePorcentage[1] << "\t" << muertePorcentage[2] << std::endl;
    for (unsigned int i = 0; i < blobCounter; i++)      //constructor de Class Blobs
    {
        nBlobs[i].blobRand(velMax * 100, i, modo, muertePorcentage);              // REVISAR
    }
    for (unsigned int i = 0; i < foodTotal; i++)
    {
        nFood[i].foodRand(i);               // Randomiza los parametros de la Food.
    }
}