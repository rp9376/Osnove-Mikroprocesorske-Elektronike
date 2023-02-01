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

graphic_object_t	splash_screen;
graphic_object_t	background;
graphic_object_t	game_over_sprite;
graphic_object_t	press_any_key_sprite;

graphic_object_t	digit_1_sprite;
graphic_object_t	digit_2_sprite;
graphic_object_t	digit_3_sprite;

progress_bar_t	timeout_bar;



// ------- Compound objects -------

arduino_object_t	arduino[NUM_OF_ARDUINO_TYPES];
crosshair_object_t	crosshair;




// ----- Text objects ------

text_object_t	score_box_title;
text_object_t	score_text;

text_object_t	time_box_title;







// ------------- Public function implementations --------------

// init all the objects
void OBJ_init(void)
{
	// init settings
	OBJ_init_canvas();

	// full screen images
	OBJ_init_splash_screen();
	OBJ_init_background();

	// sprites
	OBJ_init_game_over_sprite();
	OBJ_init_press_any_key_sprite();
	OBJ_init_arduinos();
	OBJ_init_crosshair();
	OBJ_init_digit_sprites();


	// text boxes
	OBJ_init_score_box_title();
	OBJ_init_score_text();

	OBJ_init_time_box_title();


	// init progress bar
	OBJ_init_timeout_bar();


}






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



	// above ground area
		canvas.above_ground.x_min = 0;
		canvas.above_ground.y_min = 0;

		canvas.above_ground.x_max = DISPLAY_SIZE_X;
		canvas.above_ground.y_max = 200;

		canvas.above_ground.x_center = DISPLAY_CENTER_X;
		canvas.above_ground.y_center = canvas.above_ground.y_max/2;


	// below ground area
		canvas.below_ground.x_min = 0;
		canvas.below_ground.y_min = canvas.above_ground.y_max + 1;

		canvas.below_ground.x_max = DISPLAY_SIZE_X;
		canvas.below_ground.y_max = DISPLAY_SIZE_Y;

		canvas.below_ground.x_center = DISPLAY_CENTER_X;
		canvas.below_ground.y_center = (canvas.below_ground.y_max - canvas.below_ground.y_min) / 2;
}









// ------------------ FULL SCREEN IMAGES ----------------------


// object "constructor"
void OBJ_init_splash_screen(void)
{
	// init graphic object

		// init image
		splash_screen.image.image_array = (uint16_t*) splash_screen_img;

		splash_screen.image.size_x = 320;
		splash_screen.image.size_y = 240;
		splash_screen.image.size = splash_screen.image.size_x * splash_screen.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions (&splash_screen, &canvas.whole_area );
		GFX_init_gfx_object_location( &splash_screen, 0, 0);


		// set the initial object velocity
		GFX_set_gfx_object_velocity(&splash_screen, 0, 0);


}



// object "constructor"
void OBJ_init_background(void)
{
	// init graphic object

		// init image
		background.image.image_array = (uint16_t*) background_img;

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
void OBJ_init_game_over_sprite(void)
{
	// init graphic object

		// init image
		game_over_sprite.image.image_array = (uint16_t*) game_over_img;

		game_over_sprite.image.size_x = 242;
		game_over_sprite.image.size_y = 81;
		game_over_sprite.image.size = game_over_sprite.image.size_x * game_over_sprite.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions ( &game_over_sprite, &canvas.whole_area );
		GFX_init_gfx_object_location( &game_over_sprite, 39, 53 );



		// set the initial object velocity
		GFX_set_gfx_object_velocity(&game_over_sprite, 0, 0);
}




// object "constructor"
void OBJ_init_press_any_key_sprite(void)
{
	// init graphic object

		// init image
		press_any_key_sprite.image.image_array = (uint16_t*) press_any_key_img;

		press_any_key_sprite.image.size_x = 260;
		press_any_key_sprite.image.size_y = 23;
		press_any_key_sprite.image.size = press_any_key_sprite.image.size_x * press_any_key_sprite.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions (&press_any_key_sprite, &canvas.whole_area );
		GFX_init_gfx_object_location( &press_any_key_sprite, 30, 150);


		// set the initial object velocity
		GFX_set_gfx_object_velocity(&press_any_key_sprite, 0, 0);
}




// object "constructor"
void OBJ_init_digit_sprites(void)
{
	// init graphic object

		// init image
		digit_1_sprite.image.image_array = (uint16_t*) digit_1_img;

		digit_1_sprite.image.size_x = 33;
		digit_1_sprite.image.size_y = 70;
		digit_1_sprite.image.size = digit_1_sprite.image.size_x * digit_1_sprite.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions (&digit_1_sprite, &canvas.whole_area );
		GFX_init_gfx_object_center_location( &digit_1_sprite, canvas.above_ground.x_center, canvas.above_ground.y_center);


		// set the initial object velocity
		GFX_set_gfx_object_velocity(&digit_1_sprite, 0, 0);





		// init graphic object

			// init image
			digit_2_sprite.image.image_array = (uint16_t*) digit_2_img;

			digit_2_sprite.image.size_x = 70;
			digit_2_sprite.image.size_y = 70;
			digit_2_sprite.image.size = digit_2_sprite.image.size_x * digit_2_sprite.image.size_y;

			// init the graphic object location
			GFX_init_location_restrictions (&digit_2_sprite, &canvas.whole_area );
			GFX_init_gfx_object_center_location( &digit_2_sprite, canvas.above_ground.x_center, canvas.above_ground.y_center);


			// set the initial object velocity
			GFX_set_gfx_object_velocity(&digit_2_sprite, 0, 0);


		// init graphic object

			// init image
			digit_3_sprite.image.image_array = (uint16_t*) digit_3_img;

			digit_3_sprite.image.size_x = 69;
			digit_3_sprite.image.size_y = 70;
			digit_3_sprite.image.size = digit_3_sprite.image.size_x * digit_3_sprite.image.size_y;

			// init the graphic object location
			GFX_init_location_restrictions (&digit_3_sprite, &canvas.whole_area );
			GFX_init_gfx_object_center_location( &digit_3_sprite, canvas.above_ground.x_center, canvas.above_ground.y_center);


			// set the initial object velocity
			GFX_set_gfx_object_velocity(&digit_3_sprite, 0, 0);


}









void OBJ_init_arduinos(void)
{
	// --- arduino UNO ---

		// init graphic object

			// init image
			arduino[UNO].gfx_object.image.image_array = (uint16_t*) arduino_uno_img;

			arduino[UNO].gfx_object.image.size_x = 60;
			arduino[UNO].gfx_object.image.size_y = 42;
			arduino[UNO].gfx_object.image.size = arduino[UNO].gfx_object.image.size_x * arduino[UNO].gfx_object.image.size_y;

			// init the graphic object location
			GFX_init_location_restrictions(&arduino[UNO].gfx_object, &canvas.above_ground );
			GFX_init_gfx_object_center_location(&arduino[UNO].gfx_object, canvas.above_ground.x_center, canvas.above_ground.y_center);

			// set the initial object velocity
			GFX_set_gfx_object_velocity(&arduino[UNO].gfx_object, 0, 0);


		// init arduino specific parameters
			arduino[UNO].points = 100;
			arduino[UNO].health = 1;
			arduino[UNO].show_time_ms = 5000;





	// --- arduino MEGA ---

		// init graphic object

			// init image
			arduino[MEGA].gfx_object.image.image_array = (uint16_t*) arduino_mega_img;

			arduino[MEGA].gfx_object.image.size_x = 70;
			arduino[MEGA].gfx_object.image.size_y = 34;
			arduino[MEGA].gfx_object.image.size =  arduino[MEGA].gfx_object.image.size_x * arduino[MEGA].gfx_object.image.size_y;

			// init the graphic object location
			GFX_init_location_restrictions(&arduino[MEGA].gfx_object, &canvas.above_ground );
			GFX_init_gfx_object_center_location(&arduino[MEGA].gfx_object, canvas.above_ground.x_center, canvas.above_ground.y_center);



			// set the initial object velocity
			GFX_set_gfx_object_velocity(&arduino[MEGA].gfx_object, 0, 0);



		// init arduino specific parameters
			arduino[MEGA].points = 200;
			arduino[MEGA].health = 1;
			arduino[MEGA].show_time_ms = 5000;



	// --- arduino NANO ---

		// init graphic object

			// init image
			arduino[NANO].gfx_object.image.image_array = (uint16_t*) arduino_nano_img;

			arduino[NANO].gfx_object.image.size_x = 70;
			arduino[NANO].gfx_object.image.size_y = 28;
			arduino[NANO].gfx_object.image.size =  arduino[NANO].gfx_object.image.size_x * arduino[NANO].gfx_object.image.size_y;

			// init the graphic object location
			GFX_init_location_restrictions (&arduino[NANO].gfx_object, &canvas.above_ground );
			GFX_init_gfx_object_center_location(&arduino[NANO].gfx_object, canvas.above_ground.x_center, canvas.above_ground.y_center);



			// set the initial object velocity
			GFX_set_gfx_object_velocity(&arduino[NANO].gfx_object, 0, 0);



		// init arduino specific parameters
			arduino[NANO].points = 50;
			arduino[NANO].health = 1;
			arduino[NANO].show_time_ms = 5000;

}






// object "constructor"
void OBJ_init_crosshair(void)
{
	// init graphic object

		// init image
		crosshair.gfx_object.image.image_array = (uint16_t*) crosshair_img;

		crosshair.gfx_object.image.size_x = 45;
		crosshair.gfx_object.image.size_y = 45;
		crosshair.gfx_object.image.size = crosshair.gfx_object.image.size_x * crosshair.gfx_object.image.size_y;

		// init the graphic object location
		GFX_init_location_restrictions (&crosshair.gfx_object, &canvas.above_ground );
		GFX_init_gfx_object_center_location(&crosshair.gfx_object, canvas.above_ground.x_center, canvas.above_ground.y_center);

		// set the initial object velocity
		GFX_set_gfx_object_velocity(&crosshair.gfx_object, 0, 0);


	// init crosshair specific parameters
		crosshair.distance_to_target_center = 320;	// todo

}






// ------------ TEXT OBJECTS -------------


// ------- Score text --------

void OBJ_init_score_box_title(void)
{
	static char str[]= "SCORE";

	score_box_title.text = str;

	score_box_title.x_min = 243;
	score_box_title.y_min = 205;

	score_box_title.fore_color = C_WHITE;
	score_box_title.back_color = C_BLACK;

	score_box_title.font = (UG_FONT*) &FONT_7X12;
}



void OBJ_set_score_text_value(uint16_t score)
{
	static char str[6];

	sprintf(str, "%5d", score);
	score_text.text = str;

}


void OBJ_init_score_text(void)
{
	OBJ_set_score_text_value(1150);

	score_text.x_min = 242;
	score_text.y_min = 219;

	score_text.fore_color = C_WHITE;
	score_text.back_color = C_BLACK;

	score_text.font = (UG_FONT*) &FONT_8X8;
}





// ---- Time box text ------


void OBJ_init_time_box_title(void)
{
	static char str[]= "TIME";

	time_box_title.text = str;

	time_box_title.x_min = 57;
	time_box_title.y_min = score_box_title.y_min;

	time_box_title.fore_color = C_WHITE;
	time_box_title.back_color = C_BLACK;

	time_box_title.font = (UG_FONT*) &FONT_7X12;
}





// ---- Timeout progress bar ------


void OBJ_init_timeout_bar(void)
{
	timeout_bar.value_percent = 100;
	timeout_bar.full_length_px = 137;


	timeout_bar.bar.x_min = 54;
	timeout_bar.bar.y_min = 217;

	timeout_bar.bar.length = timeout_bar.full_length_px;
	timeout_bar.bar.height = 10;

	timeout_bar.bar.x_max = timeout_bar.bar.x_min + timeout_bar.bar.length;
	timeout_bar.bar.y_max = timeout_bar.bar.y_min + timeout_bar.bar.height;

	timeout_bar.bar.color = C_RED;

	timeout_bar.background_color = C_BLACK;

}




void OBJ_set_timeout_bar_value(uint8_t value)
{
	if (value <= 100 )
	{
		timeout_bar.value_percent = value;

		timeout_bar.bar.length = (timeout_bar.full_length_px * timeout_bar.value_percent) / 100;

		timeout_bar.bar.x_max = timeout_bar.bar.x_min + timeout_bar.bar.length;

	}
}









// ------- Test functions ---------


// -------------- Private function implementations -------------


