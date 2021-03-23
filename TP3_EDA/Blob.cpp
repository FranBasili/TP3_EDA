#include "Blob.h"
#include <time.h>       
#include <math.h>
#include "const.h"
#include <stdlib.h>
#include <iostream>


//PROTOTIPOS//
void swap(Blob objeto[], int i, int blobCounter);
int intersection_check(Position	pos1, Position pos2, int obj1, int obj2);


/****************************************************************
BLOBRAND:
->Descripcion:funcion que asigna valores aleatorios a campos determinados(posicion,age y angle)
    Recibe:
        1. int velMax: donde se espera  velMax; default: 10
        2. int i: recibe un indice que sirve para multiplicar la semilla del rand; defaul:1
        3. int modo: recibe el modo del juego; default:1

    Retorna: void
****************************************************************/
void Blob::blobRand(int velMax_, int i, int modo, float muertesPorcentaje[])
{
    blobPos.x = (double)(rand() % DISPLAYWIDTH);           //checkear los maximos valores que puede obtener
    blobPos.y = (double)(rand() % DISPLAYHEIGHT);
    age = (int)(1 + rand() % 3);                                //se asigna una edad aleatoria, va de 1 a 3
    tickAlive = muertesPorcentaje[age - 1];
    angle = rand() % 360;

    if (modo == 2)
    {
        velMax = rand() % velMax_;
        velMax /= 100;
    }
    else if (modo == 1)
    {
        velMax = velMax_;
        velMax /= 100;
    }
}



/****************************************************************
BLOBLOCATE:
->Descripcion:funcion ,interna de blobRand,que modifica la posicion del blob
    Recibe:
        1. double posx: recibe la coordenada x del blob
        2. double posy: recibe la coordenada y del blob

    Retorna: void
****************************************************************/
void Blob::blobLocate(double posx, double posy)
{
    blobPos.x = posx;
    blobPos.y = posy;
}



/****************************************************************
NACER:
->Descripcion:funcion que lee foodcount y genera un hijo si es necesario
    Recibe:
        1. Blob objeto[]: recibe un arreglo de blobs
        2. int&blobCounter: recibe una referencia de la cantidad de blob en el mundo

    Retorna: void
****************************************************************/
void nacer(Blob objeto[], unsigned int& blobCounter)            //FUNCION a discutir,como recibe world o como le informe el crecimento de un nuevo blob
{
    for (int i = 0; i < blobCounter; i++)
    {
        if ((objeto[i].age == BABY && objeto[i].foodCount >= BABYFULL) ||
            (objeto[i].age == GROWN && objeto[i].foodCount >= GROWNFULL) ||
            (objeto[i].age == OLD && objeto[i].foodCount >= OLDFULL))
        {
            objeto[i].foodCount = 0;                                        //se reinicia el contador de alimentos xq pario un hijo
            objeto[blobCounter].blobLocate(objeto[i].blobPos.x + SON_DIST, objeto[i].blobPos.y + SON_DIST);  //se le asigna la posicion al hijo
            objeto[blobCounter].nacimiento(objeto[i]);
            blobCounter++;
        }
    }
}




/****************************************************************
NACIMIENTO:
->Descripcion:funcion interna de nacer, configura los campos del hijo
    Recibe:
        1. Blob objeto: recibe un blob

    Retorna: void
****************************************************************/
void Blob::nacimiento(Blob objeto) {
    age = 1;
    foodCount = 0;
    isAlive = true;
    tickAlive = objeto.tickAlive;
    velMax = objeto.velMax;
    angle = (rand() % 360);
}




/****************************************************************
MOVIMIENTO:
->Descripcion:funcion que va a mover todos los blobs del juego
    Recibe:
        1. Blob objeto[]: recibe un arreglo de blobs
        2. unsigned int blobCounter: recibe una referencia de la cantidad de blob en el mundo
        3. double velPorcentage: recibe el porcentage de velocidad

    Retorna: void
****************************************************************/
void movimiento(Blob blobs[], unsigned int blobCounter, double velPorcentaje)
{
    for (unsigned int i = 0; i < blobCounter; i++)
    {
        blobs[i].moverBlob(velPorcentaje);
    }
}




/****************************************************************
MOVERBLOB:
->Descripcion:funcion que mueve el blob , accediendo a los campos de posicion
    Recibe:
        1. Blob objeto[]: recibe un arreglo de blobs
        2. int&blobCounter: recibe una referencia de la cantidad de blob en el mundo

    Retorna: void
****************************************************************/
void Blob::moverBlob(double velPorcentaje)
{
    blobPos.x += velMax * velPorcentaje * cos(angle * PI /180);
    blobPos.y += velMax * velPorcentaje * sin(angle * PI / 180);

    if (blobPos.x >= DISPLAYWIDTH)
    {
        blobPos.x = blobPos.x - DISPLAYWIDTH;
    }
    else if (blobPos.x < 0)
    {
        blobPos.x += DISPLAYWIDTH;
    }
    if (blobPos.y >= DISPLAYHEIGHT)
    {
        blobPos.y = blobPos.y - DISPLAYHEIGHT;
    }
    else if (blobPos.y < 0)
    {
        blobPos.y += DISPLAYHEIGHT;
    }
}




/****************************************************************
REDIRIGIR:
->Descripcion:barre el arreglo de blobs, derivandolos a redireccion
    Recibe:
        1. Blob objeto[]: recibe un arreglo de blobs
        2. Food foods[]:recibe un arreglo de foods
        3. int blobCounter: recibe  la cantidad de blob en el mundo
        4. int cantFood: recibe la cantidad de food que hay en le mundo
        5. int smellRandius: recibe el radio de busqueda de comida de los blobs

    Retorna: void
****************************************************************/
void redirigir(Blob blobs[], Food foods[], int blobCounter, int cantFood, int smellRadius)
{
    for (int i = 0; i < blobCounter; i++)
    {
        blobs[i].redireccion(foods, cantFood, smellRadius);
    }
}





/****************************************************************
REDIRECCION:
->Descripcion:funcion interna de redirigir,busca la comida mas cercana y "apunta" el blob hacia ella
    Recibe:
        1. Food foods[]:recibe un arreglo de foods
        2. int cantFood: recibe la cantidad de food que hay en le mundo
        3. int smellRandius: recibe el radio de busqueda de comida de los blobs

    Retorna: void
****************************************************************/
void Blob::redireccion(Food food[], int cantFood, int smellRadius)
{
    double distMin = sqrt(pow(DISPLAYHEIGHT, 2) + pow(DISPLAYWIDTH, 2));
    double dist = 0;
    int food_index = 0;

    for (int i = 0; i < cantFood; i++)
    {
        dist = sqrt(pow((food[i].foodPos.x - blobPos.x), 2) + pow((food[i].foodPos.y - blobPos.y), 2));

        if (dist < distMin)
        {
            distMin = dist;
            food_index = i;
        }
    }

    if (distMin <= smellRadius)
    {
        angle = 180 * atan2(food[food_index].foodPos.y - blobPos.y, food[food_index].foodPos.x - blobPos.x) / PI;
    }
}





/****************************************************************
COMER:
->Descripcion:funcion que hace comer al blob, un alimento en el caso especifico que se crucen
    Recibe:
        1. Blob objeto[]: recibe un arreglo de blobs
        2. Food foods[]:recibe un arreglo de foods
        3. int blobCounter: recibe  la cantidad de blob en el mundo
        4. int cantFood: recibe la cantidad de food que hay en le mundo

    Retorna: void
****************************************************************/
void comer(Blob blobs[], Food foods[], int blobCounter, int cantFood)
{
    for (int i = 0; i < blobCounter; i++)
    {
        
        for (int j = 0, comiendo = false; j < cantFood && comiendo == false; j++)
        {
            if ( (intersection_check(foods[j].foodPos, blobs[i].blobPos, 0 , blobs[i].age)) && (foods[j].isAlive == true) )
            {
                blobs[i].foodCount++;
                foods[j].isAlive = false;
                comiendo = true;
            }
        }
    }

    respawn_food(foods, cantFood);
}



/****************************************************************
FUSIONAR:
->Descripcion:funcion que va a fusionar a dos blobs en el caso de que se crucen y sean si o si de la misma edad(no aplica a OLD)
    Recibe:
        1. Blob objeto[]: recibe un arreglo de blobs
        2. int& blobCounter: recibe una referencia a la cantidad de blob en el mundo
        3. int randomJinggleLimit:recibe un valor aleatorio a sumar para el c�lculo de la direcci�n.

    Retorna: void
****************************************************************/
void fusionar(Blob blobs[], unsigned int& blobCounter, int randomJiggleLimit)
{
    for (unsigned int i = 0; i < blobCounter; i++)
    {
        if (blobs[i].age != OLD)
        {
            for (unsigned int j = i + 1; j < blobCounter; j++)
                if (intersection_check(blobs[i].blobPos, blobs[j].blobPos, blobs[i].age, blobs[j].age) && (blobs[j].age == blobs[i].age))
                {
                    blobs[i].fusion(blobs[j], j, blobCounter, randomJiggleLimit);
                    blobs[j].isAlive = false;
                    swap(blobs, j, blobCounter);
                    blobCounter--;
                }
        }
    }
}




/****************************************************************
FUSION:
->Descripcion:funcion interna de fusionar que configura los campos del blob fusionado
    Recibe:
        1. Blob blob2: recibe un blobs
        2 .int blob2index: recibe un parametro que sirve para modificar la semilla del rand
        3. int& blobCounter: recibe una referencia a la cantidad de blob en el mundo
        3. int randomJinggleLimit:recibe un valor aleatorio a sumar para el cálculo de la direcci�n.

    Retorna: void
****************************************************************/
void Blob::fusion(Blob blob2, int blob2Index, unsigned int& blobCounter, int randomJiggleLimit)
{
    velMax = (velMax + blob2.velMax) / 2;                           // Calculamos el promedio de las velocidades.

    int randomJiggle = rand() % randomJiggleLimit;                  // Definimos el angulo aleatorio.
    double vx = cos(angle * PI / 180) + cos(blob2.angle * PI / 180) + cos(randomJiggle * PI / 180);  // Proyectamos los vectores sobre eje x.
    double vy = sin(angle * PI / 180) + sin(blob2.angle * PI / 180) + sin(randomJiggle * PI / 180);  // Proyectamos los vectores sobre eje y.
    angle = atan2(vy, vx) * 180 / PI;                                          // Con la suma de los vectores calculamos el �ngulo entre ellos.
    age++;      // Si el blob puede crecer, lo hacemos crecer.
}



/****************************************************************
MORIR:
->Descripcion:Revisar que la probabilidad de muerte que se pasa como parametro.
        1. Blob objeto[]: recibe un arreglo de blobs
        2. int& blobCounter: recibe una referencia a la cantidad de blob en el mundo

    Retorna:    0 si no hay blobs vivos.
                1 si hay algún blob vivo.
****************************************************************/
int morir(Blob objeto[], unsigned int& blobCounter) {

    static int contador = 0;

    if ((contador++) < TICKS_PER_DEATH)     // Si no pasaron la cantidad de ticks necesarios,
    {                                       //no asesinamos a nadie.
        return 1;                           
    }
    else
    {   
        contador = 0;
        for (unsigned int i = 0; i < blobCounter; i++) {
            if (objeto[i].isAlive == true) {
                float probabilidad = (float)(rand() % 100)/ (float)(100);
                std::cout << "Probabilidad: \t"  << probabilidad << "\t Tick:" << objeto[i].tickAlive;
                if (probabilidad <= objeto[i].tickAlive) {
                    objeto[i].isAlive = false;
                    swap(objeto, i, blobCounter);
                    blobCounter--;
                    std::cout << " \t MUERTO";
                }
                std::cout << std::endl;
            }
        }

        if (blobCounter == 0)       // Si no quedaron blobs vivos, retorno 0.
            return 0;
        else
            return 1;               // Si ha blobs vivos, sigo corriendo la simulacion
    }
}




/****************************************************************
SWAP:
->Descripcion:funcion interna, que apila a los blobs muertos en el final del arreglo.
        1. Blob objeto[]: recibe un arreglo de blobs
        2. int i: recibo posicion en el arreglo
        3. int blobCounter: recibe una referencia a la cantidad de blob en el mundo

    Retorna: void
****************************************************************/
void swap(Blob objeto[], int i, int blobCounter) {
    objeto[blobCounter] = objeto[blobCounter - 1];      //salvo al informacion del ultimo
    objeto[blobCounter - 1] = objeto[i];                //la informacion del muerto se la guarda al final del arreglo
    objeto[i] = objeto[blobCounter];                    //la informacion del ultima se guarda en la posicion del muerto
}

/****************************************************************
INTERSECTION_CHECK:
->Descripcion:funcion que comprueba los limites de los objetos ,confirmando o no si se cruzan.
        1. Position pos1: recibe la posicion del primer objeto en cuestion
        2. Position pos2: recibe la posicion del segundo objeto en cuestion
        3. int obj1: recibe el primer objeto en cuestion
        4. int obj2:recibe el segundo objeto en cuestion

    Retorna: void
****************************************************************/
int intersection_check(Position	pos1, Position pos2, int obj1, int obj2)
{
    // definimos un arreglo con los tama�os de las imagenes
    int margenes[4] = { FOOD_IMG_SIZE, BABY_IMG_SIZE, GROWN_IMG_SIZE, OLD_IMG_SIZE };

    // Calculamos los vertices del objeto 1.
    Position vertices1[5];
    vertices1[0] = { pos1.x - margenes[obj1] / 2, pos1.y - margenes[obj1] / 2 };
    vertices1[1] = { pos1.x - margenes[obj1] / 2, pos1.y + margenes[obj1] / 2 };
    vertices1[2] = { pos1.x + margenes[obj1] / 2, pos1.y - margenes[obj1] / 2 };
    vertices1[3] = { pos1.x + margenes[obj1] / 2, pos1.y + margenes[obj1] / 2 };
    vertices1[4] = { pos1.x                     , pos1.y                      };

    //Reviso si alguno de los 4 vertices del obj1 esta dentro del obj 2
    for (int i = 0; i < 5; i++)
    {
        if (vertices1[i].x < (pos2.x + margenes[obj2] / 2) && vertices1[i].x >(pos2.x - margenes[obj2] / 2) &&
            vertices1[i].y < (pos2.y + margenes[obj2] / 2) && vertices1[i].y >(pos2.y - margenes[obj2] / 2))
        {
            // Si uno de los 4 vertices esta adentro, determino que hay colision.
            return  1;
        }
    }

    // Si ninguno de los 4 vertices esta adentro, determino que no hay colisi�n.
    return 0;
}



