#include "grafica.h"
#include "const.h"
#include "Blob.h"
#include "Food.h"
#include "Position.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <stdio.h>

enum PARAMS {MODO, VP, VM, FC, MBABY, MGROWN, MOLD, SR, RJL};
static ALLEGRO_DISPLAY* display;
static ALLEGRO_EVENT_QUEUE* queue;
static ALLEGRO_TIMER* timer;
static ALLEGRO_FONT* font;
static ALLEGRO_BITMAP* bitmapBackground;
static ALLEGRO_BITMAP* bitmapBabyBlob;
static ALLEGRO_BITMAP* bitmapGrownBlob;
static ALLEGRO_BITMAP* bitmapGoodOldBlob;
static ALLEGRO_BITMAP* bitmapFood;

static ALLEGRO_EVENT event;
static ALLEGRO_KEYBOARD_STATE keyState;

using namespace std;

/*****************************************************************************************
*                                       Prototipos
****************************************************************************************/
void printVar(int pointer, World& world);
void printBlobs(World& world);
void printFood(World& world);
void checkVar(int& pointer, World& world);

/****************************************************************
INITIALIZEALLEGRO:
->Descripcion:inicializa todo lo relacionado allegro, carga los bitmaps , los eventos y controla que los mismos esten correctamente cargados
        void

    Retorna:
        void
****************************************************************/
void initializeAllegro() 
{
    if (! al_init() ) 
    {
        fprintf(stderr, "failed to initialize allegro!\n");
    }

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    queue = al_create_event_queue();
    display = al_create_display(DISPLAYWIDTH, DISPLAYHEIGHT);
    timer = al_create_timer(1.0 / 60.0);
    font = al_load_ttf_font("DelaGothicOne-Regular.ttf", 12, 0);
    bitmapBackground = al_load_bitmap("background.jpg");
    bitmapBabyBlob = al_load_bitmap("babyblob.png");
    bitmapGrownBlob = al_load_bitmap("grownblob.png");
    bitmapGoodOldBlob = al_load_bitmap("goodoldblob.png");
    bitmapFood = al_load_bitmap("food.png");


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    if (font == NULL) {
        cout << "Failed to load .ttf" << endl;
    }

    if (bitmapBackground == NULL) {
        cout << "Failed to load background.jpg" << endl;
    }
    if (bitmapBabyBlob == NULL) {
        cout << "Failed to load babyblob.png" << endl;
    }
    if (bitmapGrownBlob == NULL) {
        cout << "Failed to load grownblob.png" << endl;
    }
    if (bitmapGoodOldBlob == NULL) {
        cout << "Failed to load goodoldblob.png" << endl;
    }
    if (bitmapFood == NULL) {
        cout << "Failed to load food.png" << endl;
    }
}

/****************************************************************
DRAWWORLD:
->Descripcion:funcion que va renderizar todo lo propio a las clases de world, blob, food y sus correspondientes funciones
        1. World &: recibe una referencia a world ,que es una clase que contiene toda la informacion del mundo

    Retorna:
        void
****************************************************************/
void drawWorld(World& world) {
    static int pointer = 0;
    static bool keys[4] = { false, false, false, false };
    al_start_timer(timer);

    al_draw_bitmap(bitmapBackground, 0.0, 0.0, 0);
    printBlobs(world);
    printFood(world);
    printVar(pointer, world);
    checkVar(pointer, world);
    al_flip_display();
}

/****************************************************************
SHUTDOWNALLEGRO:
->Descripcion: funcion que destruye todos los recursos usados para renderizar el programa
        void

    Retorna:
        void
****************************************************************/
void shutdownAllegro(void) {

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(bitmapBackground);
    al_destroy_bitmap(bitmapBabyBlob);
    al_destroy_bitmap(bitmapGrownBlob);
    al_destroy_bitmap(bitmapGoodOldBlob);
    al_destroy_bitmap(bitmapFood);
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();

}

/****************************************************************
PRINTVAR:
->Descripcion:funcion que imprime el valor de las variables pasadas por el usuario
        1. int pointer: recibe un int que contiene el parametro
        2. World &: recibe una referencia a world ,que es una clase que contiene toda la informacion del mundo

    Retorna:
        void
****************************************************************/
void printVar(int pointer, World& world)
{
    char temp[30];

    if (pointer == MODO)
        sprintf_s(temp, "-> Modo: %d", world.modo);
    else
        sprintf_s(temp, "Modo: %d", world.modo);
    al_draw_text(font, FONT_COLOR, POS(MODO), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);


    if (pointer == VP)
        sprintf_s(temp, "-> V.Porc: %.2f", world.velPorcentage);
    else
        sprintf_s(temp, "V.Porc: %.2f", world.velPorcentage);
    al_draw_text(font, FONT_COLOR, POS(VP), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);

    if (pointer == VM)
        sprintf_s(temp, "-> V.Max: %.2f", world.velMax);
    else
        sprintf_s(temp, "V.Max: %.2f", world.velMax);
    al_draw_text(font, FONT_COLOR, POS(VM), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);


    if (pointer == FC)
        sprintf_s(temp, "-> Comida: %d", world.foodTotal);
    else
        sprintf_s(temp, "Comida: %d", world.foodTotal);
    al_draw_text(font, FONT_COLOR, POS(FC), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);


    if (pointer == MBABY)
        sprintf_s(temp, "-> Baby: %.2f", world.muertePorcentage[0]);
    else
        sprintf_s(temp, "Baby: %.2f", world.muertePorcentage[0]);
    al_draw_text(font, FONT_COLOR, POS(MBABY), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);


    if (pointer == MGROWN)
        sprintf_s(temp, "-> Grown: %.2f", world.muertePorcentage[1]);
    else
        sprintf_s(temp, "Grown: %.2f", world.muertePorcentage[1]);
    al_draw_text(font, FONT_COLOR, POS(MGROWN), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);


    if (pointer == MOLD)
        sprintf_s(temp, "-> Old: %.2f", world.muertePorcentage[2]);
    else
        sprintf_s(temp, "Old: %.2f", world.muertePorcentage[2]);
    al_draw_text(font, FONT_COLOR, POS(MOLD), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);


    if (pointer == SR)
        sprintf_s(temp, "-> Smell: %d", world.smellRadius);
    else
        sprintf_s(temp, "Smell: %d", world.smellRadius);
    al_draw_text(font, FONT_COLOR, POS(SR), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);

    if (pointer == RJL)
        sprintf_s(temp, "-> RJL: %d", world.randomJiggleLimit);
    else
        sprintf_s(temp, "RJL: %d", world.randomJiggleLimit);
    al_draw_text(font, FONT_COLOR, POS(RJL), OFFSETY, ALLEGRO_ALIGN_CENTER, temp);
}

/****************************************************************
PRINTBLOBS:
->Descripcion: funcion que grafica los blobs con su debida rotacion
        1.World& world: recbe toda la informacon necesaria en la clase world para graficar el blob

    Retorna:
        void
****************************************************************/
void printBlobs(World& world)
{
    for (unsigned int i = 0; i < world.blobCounter; i++) {
        switch (world.nBlobs[i].age) {
        case BABY:
            al_draw_rotated_bitmap(bitmapBabyBlob, BABY_IMG_SIZE / 2, BABY_IMG_SIZE / 2, world.nBlobs[i].blobPos.x, world.nBlobs[i].blobPos.y, ANGLEALLEGRO(world.nBlobs[i].angle), 0);
            break;
        case GROWN:
            al_draw_rotated_bitmap(bitmapGrownBlob, GROWN_IMG_SIZE / 2, GROWN_IMG_SIZE / 2, world.nBlobs[i].blobPos.x, world.nBlobs[i].blobPos.y, ANGLEALLEGRO(world.nBlobs[i].angle), 0);
            break;
        case OLD:
            al_draw_rotated_bitmap(bitmapGoodOldBlob, OLD_IMG_SIZE / 2, OLD_IMG_SIZE / 2, world.nBlobs[i].blobPos.x, world.nBlobs[i].blobPos.y, ANGLEALLEGRO(world.nBlobs[i].angle), 0);
            break;
        }
    }

}

/****************************************************************
PRINTFOOD:
->Descripcion: funcion que grafica los blobs con su debida rotacion
        1.World& world: recbe toda la informacon necesaria en la clase world para graficar el blob

    Retorna:
        void
****************************************************************/
void printFood (World& world)
{
    for (unsigned int j = 0; j < world.foodTotal; j++) 
    {
        al_draw_bitmap(bitmapFood, world.nFood[j].foodPos.x, world.nFood[j].foodPos.y, 0);
    }
}


/****************************************************************
CHECKVAR:
->Descripcion: funcion que grafica los blobs con su debida rotacion
        1.int& pointer: recibe una referencia a int que contiene el parametro
        2.World& world: recbe toda la informacon necesaria en la clase world para graficar el blob

    Retorna:
        void
****************************************************************/
void checkVar(int& pointer, World& world) {
    al_get_next_event(queue, &event);
    al_get_keyboard_state(&keyState);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || al_key_down(&keyState, ALLEGRO_KEY_Q) || al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
        world.running = false;

    else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
    {
        if (pointer == CANT_OPCIONES - 1)
            pointer = 0;
        else
            pointer++;
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
    {
        if (pointer == 0)
            pointer = CANT_OPCIONES - 1;
        else
            pointer--;
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
    {
        switch (pointer)
        {
        case VM:
            world.velMax += 5;
            break;

        case MODO:
            if (world.modo < 2)
            {
                world.modo++;
                for (int i = 0; i < world.blobCounter; i++)
                {
                    world.nBlobs[i].setVel(world.velMax*100, world.modo);
                }
            }    
            break;

        case VP:
            if (world.velPorcentage <= 0.95)
                world.velPorcentage += 0.05;
            else if (world.velPorcentage <= 1)
                world.velPorcentage =1;
            break;

        case FC:
            world.foodTotal++;
            break;

        case MBABY:
            if (world.muertePorcentage[0] <= 0.95)
                world.muertePorcentage[0] += 0.05;
            break;

        case MGROWN:
            if (world.muertePorcentage[1] <= 0.95)
                world.muertePorcentage[1] += 0.05;
            break;

        case MOLD:
            if (world.muertePorcentage[2] <= 0.95)
                world.muertePorcentage[2] += 0.05;
            break;

        case SR:
            world.smellRadius += 5;
            break;

        case RJL:
            if (world.randomJiggleLimit <= 350)
            {
                world.randomJiggleLimit+=10;
            }
        }
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
    {
        switch (pointer)
        {
        case VM:
            if(world.velMax>=5)
                world.velMax -= 5;
            break;

        case MODO:
            if (world.modo >= 2)
            {
                world.modo--;
                for (int i = 0; i < world.blobCounter; i++)
                {
                    world.nBlobs[i].setVel(world.velMax * 100, world.modo);
                }
            }
            break;

        case VP:
            if (world.velPorcentage >= 0.05)
            {
                world.velPorcentage -= 0.05;
            }
            else if (world.velPorcentage > 0)
            {
                world.velPorcentage = 0;
            }
            break;

        case FC:
            if (world.foodTotal > 0)
                world.foodTotal--;
            break;

        case MBABY:
            if (world.muertePorcentage[0] >= 0.05)
                world.muertePorcentage[0] -= 0.05;
            break;

        case MGROWN:
            if (world.muertePorcentage[1] >= 0.05)
                world.muertePorcentage[1] -= 0.05;
            break;

        case MOLD:
            if (world.muertePorcentage[2] >= 0.05)
                world.muertePorcentage[2] -= 0.05;
            break;

        case SR:
            if (world.smellRadius >= 5)
                world.smellRadius -= 5;
            break;

        case RJL:
            if (world.randomJiggleLimit >= 10)
            {
                world.randomJiggleLimit-=10;
            }
        }
    }
}