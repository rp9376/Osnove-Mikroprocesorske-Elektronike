/*
 * objects.h
 *
 *  Created on: 10 May 2022
 *      Author: Gasper
 */

#ifndef INCLUDE_OBJECTS_H_
#define INCLUDE_OBJECTS_H_






// ----------- Include other modules (for public) -------------




// ------ Standard C libraries -----

#include "stdint.h"		// support for data type definitions
#include <stdio.h>		// add sprintf() functionality




// -------- Application level modules -------

#include "images.h"			// definitions for image objects
#include "graphics.h"		// support for graphic objects









// -------------------- Public definitions --------------------




// canvas object (parameters about area where graphics is drawn)
typedef struct
{
	canvas_location_t	whole_area;
	canvas_location_t	above_ground;
	canvas_location_t	below_ground;

} canvas_t;





// ------ COMPOUND OBJECTS TYPE DEFINITIONS ---------


// ---- Arduino object type definitions ----
typedef enum {UNO, MEGA, NANO,    NUM_OF_ARDUINO_TYPES} arduino_types_enum_t;

typedef struct
{
	// graphic object
	graphic_object_t	gfx_object;


	// arduino specific parameters
	uint8_t 		points;				// points earned when destroyed
	uint16_t		show_time_ms;		// time in ms that arduino is shown before it disappears

	uint8_t 		health;				// health points; zero means it is destroyed


} arduino_object_t;




// ---- Crosshair object type definitions ----

typedef struct
{
	// graphic object
	graphic_object_t	gfx_object;

	// crosshair specific parameters
	uint16_t	distance_to_target_center;		// distance in pixels

} crosshair_object_t;















// ------------- OBJECT ARE EXTERNAL GLOBAL VARIABLES  -----------

// This simplifies inter-module data transfer at the risk of exposing data.

extern canvas_t	canvas;


extern graphic_object_t	splash_screen;
extern graphic_object_t	background;

extern graphic_object_t	game_over_sprite;
extern graphic_object_t	press_any_key_sprite;

extern graphic_object_t	digit_1_sprite;
extern graphic_object_t	digit_2_sprite;
extern graphic_object_t	digit_3_sprite;



extern arduino_object_t		arduino[NUM_OF_ARDUINO_TYPES];
extern crosshair_object_t	crosshair;


extern text_object_t	score_box_title;
extern text_object_t	score_text;

extern text_object_t	time_box_title;
extern progress_bar_t	timeout_bar;








// ---------------- Public function prototypes ----------------

void OBJ_init(void);


void OBJ_init_canvas(void);

void OBJ_init_splash_screen(void);
void OBJ_init_background(void);

void OBJ_init_game_over_sprite(void);
void OBJ_init_press_any_key_sprite(void);
void OBJ_init_digit_sprites(void);

void OBJ_init_arduinos(void);
void OBJ_init_crosshair(void);


void OBJ_init_score_box_title(void);
void OBJ_init_score_text(void);
void OBJ_set_score_text_value(uint16_t score);

void OBJ_init_time_box_title(void);
void OBJ_init_timeout_bar(void);
void OBJ_set_timeout_bar_value(uint8_t value);



#endif /* INCLUDE_OBJECTS_H_ */
