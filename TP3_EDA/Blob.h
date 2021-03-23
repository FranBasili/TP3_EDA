#ifndef BLOBS
#define BLOBS
/*****************************************************************************************
 *                                       Bibliotecas
 ****************************************************************************************/
#include "position.h"
#include "Food.h"
 /*****************************************************************************************
  *                                       Clase
  ****************************************************************************************/
class Blob {
public:

    Position blobPos;
    double angle;       // 0 hacia la derecha y aumenta en sentido horario
    unsigned int age;
    unsigned int foodCount;
    float tickAlive;
    float velMax;
    bool isAlive;

    Blob() {
        blobPos.x = 0;           //checkear los maximos valores que puede obtener
        blobPos.y = 0;
        angle = 0;
        age = 1;                                //se asigna una edad aleatoria, va de 1 a 3
        foodCount = 0;
        tickAlive = 0;
        isAlive = true;
        velMax = 0;
    };

    void blobRand(int velMax_, int i, int modo, int muertesPorcentaje[]);
    void blobLocate(double posx, double posy);
    void nacimiento(Blob objeto);
    void moverBlob(double velPorcentaje);
    void redireccion(Food food[], int cantFood, int smellRadius);
    void fusion(Blob blob2, int blob2Index, unsigned int& blobCounter, int randomJiggleLimit);
};

/*****************************************************************************************
 *                                       Prototipos
 ****************************************************************************************/

void nacer(Blob objeto[], unsigned int& blobCounter);
void redirigir(Blob blobs[], Food foods[], int blobCounter, int cantFood, int smellRadius);
void comer(Blob blobs[], Food foods[], int blobCounter, int cantFood);
void fusionar(Blob blobs[], unsigned int& blobCounter, int randomJiggleLimit);
void movimiento(Blob blobs[], unsigned int blobCounter, double velPorcentaje);
int morir(Blob objeto[], unsigned int& blobCounter);
#endif // BLOBS
