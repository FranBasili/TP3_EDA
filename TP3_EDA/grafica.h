
#ifndef GRAFICA
#define GRAFICA

#include "World.h"

#define CANT_OPCIONES   8
#define OFFSETX     0
#define OFFSETY     5
#define POS(x)      ( ((x)+0.5) * DISPLAYWIDTH / CANT_OPCIONES + OFFSETX)   
#define ANGLEALLEGRO(x)		((x) * PI / 180)
#define FONT_RED     15 
#define FONT_GREEN   74 
#define FONT_BLUE    8
#define FONT_COLOR	al_map_rgb(FONT_RED, FONT_GREEN, FONT_BLUE)

void initializeAllegro();
void drawWorld(World&);
void shutdownAllegro(void);

#endif //GRAFICA
