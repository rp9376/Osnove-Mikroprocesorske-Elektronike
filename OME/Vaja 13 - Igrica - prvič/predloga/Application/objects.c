/*
 * objects.c
 *
 *  Created on: 10 May 2022
 *      Author: Gasper
 */



/* **************** MODULE DESCRIPTION *************************

This module defines application objects and functions that manipulate
the object parameters.


************************************************************* */





// ----------- Include other modules (for private) -------------



// -------- Application level modules -------

#include "objects.h"






// ---------------------- Private definitions ------------------


// ----- Object for defining settings ------

canvas_t	canvas;



// --- Graphical objects ----

graphic_object_t	background;
graphic_object_t	sprite;

progress_bar_t		progress_bar;


// ----- Text objects ------

text_object_t  text_object;





// ------------- Public function implementations --------------





// ---------------- OBJECTS for SETTINGS ----------------


// object "constructor"
void OBJ_init_canvas(void)
{
	// whole area
		canvas.whole_area.x_min = 0;
		canvas.whole_area.y_min = 0;

		canvas.whole_area.x_max = DISPLAY_SIZE_X;
		canvas.whole_area.y_max = DISPLAY_SIZE_Y;

		canvas.whole_area.x_center = DISPLAY_CENTER_X;
		canvas.whole_area.y_center = DISPLAY_CENTER_Y;


}









// ------------------ FULL SCREEN IMAGES ----------------------


// object "constructor"
void OBJ_init_background(void)
{
	// init graphic object

		// init image

		// nastavimo kazalec na RGB565 sliko v pomnilniku
		background.image.image_array = (uint16_t*) background_img;

		// nastavimo parametre slike
		background.image.size_x = 320;
		background.image.size_y = 240;
		background.image.size = background.image.size_x * background.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions (&background, &canvas.whole_area );
		GFX_init_gfx_object_location( &background, 0, 0);

		// set the initial object velocity
		GFX_set_gfx_object_velocity(&background, 0, 0);
}









// ------------------ SPRITES ----------------------



// In computer graphics, a sprite is a two-dimensional bitmap that is
// integrated into a larger scene, most often in a 2D video game.

// object "constructor"
void OBJ_init_sprite(void)
{
	// init graphic object

		// init image
		// nastavimo kazalec na RGB565 sliko v pomnilniku
		sprite.image.image_array = (uint16_t*) sprite_img;

		// nastavimo parametre slike
		sprite.image.size_x = 56;
		sprite.image.size_y = 100;
		sprite.image.size = sprite.image.size_x * sprite.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions ( &sprite, &canvas.whole_area );
		GFX_init_gfx_object_location( &sprite, 70, 112 );



		// set the initial object velocity
		GFX_set_gfx_object_velocity(&sprite, 0, 0);
}






// ------------ TEXT OBJECTS -------------



void OBJ_init_text_object(void)
{
	static char str[]= "HEALTH";

	text_object.text = str;

	text_object.x_min = 11;
	text_object.y_min = 11;

	text_object.fore_color = C_WHITE;
	text_object.back_color = 0x5CBF;

	text_object.font = (UG_FONT*) &FONT_8X12;
}







// ---- progress bar ------


void OBJ_init_progress_bar(void)
{
	progress_bar.value_percent = 100;
	progress_bar.full_length_px = 100;


	progress_bar.bar.x_min = 70;
	progress_bar.bar.y_min = 11;

	progress_bar.bar.length = progress_bar.full_length_px;
	progress_bar.bar.height = 10;

	progress_bar.bar.x_max = progress_bar.bar.x_min + progress_bar.bar.length;
	progress_bar.bar.y_max = progress_bar.bar.y_min + progress_bar.bar.height;

	progress_bar.bar.color = C_RED;

	progress_bar.background_color = C_BLACK;

}




void OBJ_set_progress_bar_value(uint8_t value)
{
	if (value <= 100 )
	{
		progress_bar.value_percent = value;

		progress_bar.bar.length = (progress_bar.full_length_px * progress_bar.value_percent) / 100;

		progress_bar.bar.x_max = progress_bar.bar.x_min + progress_bar.bar.length;

	}
}









// ------- Test functions ---------


// -------------- Private function implementations -------------


