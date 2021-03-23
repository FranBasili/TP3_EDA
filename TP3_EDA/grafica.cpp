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
        cout << "Failed to load arial.ttf" << endl;
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

void drawWorld(World& world) {
    al_start_timer(timer);

    al_draw_bitmap(bitmapBackground, 0.0, 0.0, 0);

    for (unsigned int i = 0; i < world.blobCounter; i++) {
        switch (world.nBlobs[i].age) {
        case BABY:
            al_draw_rotated_bitmap(bitmapBabyBlob, BABY_IMG_SIZE / 2, BABY_IMG_SIZE / 2, world.nBlobs[i].blobPos.x, world.nBlobs[i].blobPos.y, angleAllegro(world.nBlobs[i].angle), 0);
            break;
        case GROWN:
            al_draw_rotated_bitmap(bitmapGrownBlob, GROWN_IMG_SIZE / 2, GROWN_IMG_SIZE / 2, world.nBlobs[i].blobPos.x, world.nBlobs[i].blobPos.y, angleAllegro(world.nBlobs[i].angle), 0);
            break;
        case OLD:
            al_draw_rotated_bitmap(bitmapGoodOldBlob, OLD_IMG_SIZE / 2, OLD_IMG_SIZE / 2, world.nBlobs[i].blobPos.x, world.nBlobs[i].blobPos.y, angleAllegro(world.nBlobs[i].angle), 0);
            break;
        }
    }

    for (unsigned int j = 0; j < world.foodTotal; j++) {
        al_draw_bitmap(bitmapFood, world.nFood[j].foodPos.x, world.nFood[j].foodPos.y, 0);
    }

    char temp[50];
    char traslate[10];

    /*itoa(world.velPorcentage, traslate, 5);
    sprintf_s(temp, "Vel Porcentage: %s", traslate);
    al_draw_text(font, al_color_name("black"), DISPLAYWIDTH /7 , DISPLAYHEIGHT- 50, ALLEGRO_ALIGN_CENTER, temp);*/


    al_flip_display();

    /*al_wait_for_event(queue, &event);
    al_get_keyboard_state(&keyState);
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || al_key_down(&keyState, ALLEGRO_KEY_Q)) {
        running = false;
    }
    }*/

}

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

double angleAllegro(double angleFromNorth) { // recibe un angulo medido del norte
    return  (angleFromNorth * (ALLEGRO_PI / 180)); 
    //  return  (-ALLEGRO_PI / 2) + (angleFromNorth * (ALLEGRO_PI / 180)); //lo convierte al
}