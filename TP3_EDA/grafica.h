
#ifndef GRAFICA
#define GRAFICA

#include "World.h"

#define CANT_OPCIONES   8
#define OFFSETX     0
#define OFFSETY     5
#define POS(x)      ( ((x)+0.5) * DISPLAYWIDTH / CANT_OPCIONES + OFFSETX)   
#define ANGLEALLEGRO(x)		((x) * PI / 180)

void initializeAllegro();
void drawWorld(World&);
void shutdownAllegro(void);

#endif //GRAFICA
