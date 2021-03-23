#ifndef CONST
#define CONST
/*****************************************************************************************
 *                                       Constantes y Enum
 ****************************************************************************************/
#define MAXBLOBS    1000
#define MAXFOOD     30
#define VEL_DEF		10
#define SEC_PER_TICK 0.15
#define TICKS_PER_DEATH 8

#define DISPLAYHEIGHT   470
#define DISPLAYWIDTH    900
#define SON_DIST        20
#define BABY_IMG_SIZE	40
#define GROWN_IMG_SIZE	45
#define OLD_IMG_SIZE	80
#define FOOD_IMG_SIZE	20

 // Constantes del parser
#define CANT_PARAM  10  // Cantidad de parametros que permite la estructura.
#define LENG_PARAM  20  // Cantidad de caracteres de cada parametro.


enum AGES { BABY = 1, GROWN, OLD };
enum FOODS { OLDFULL = 3, GROWNFULL, BABYFULL };

#define PI 3.14159265

#endif // CONST