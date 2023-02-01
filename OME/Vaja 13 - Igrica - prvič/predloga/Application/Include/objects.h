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

} canvas_t;











// ------------- OBJECT ARE EXTERNAL GLOBAL VARIABLES  -----------

// This simplifies inter-module data transfer at the risk of exposing data.


// Graphic objects

extern canvas_t	canvas;
extern graphic_object_t	background;
extern graphic_object_t	sprite;

extern progress_bar_t		progress_bar;


// Text objects

extern text_object_t  text_object;






// ---------------- Public function prototypes ----------------


void OBJ_init_canvas(void);

void OBJ_init_background(void);

void OBJ_init_sprite(void);

void OBJ_init_text_object(void);

void OBJ_init_progress_bar(void);
void OBJ_set_progress_bar_value(uint8_t value);



#endif /* INCLUDE_OBJECTS_H_ */
