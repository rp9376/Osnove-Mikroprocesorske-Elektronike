/*
 * graphics.c
 *
 *  Created on: 10 May 2022
 *      Author: Gasper
 */





/* **************** MODULE DESCRIPTION *************************

This module implements functions for displaying various objects
via the GUI (i.e. the LCD screen).

// NOTE: all coordinates (x,y) (if not specified otherwise), represent
// the top left corner of objects (i.e. the x_min, y_min).

// We can use different types of coordinate systems:
//
//	1) the absolute coordinate system with the origin at the top left corner of the display ("_abs" suffix )
//
//	2) the image coordinate system with the origin at the top left corner of the image  ("_img" suffix )


************************************************************* */





// ----------- Include other modules (for private) -------------


// ------ Standard C libraries -----

#include <stdlib.h>		// support for dynamic memory allocation
#include <math.h>		// support for math basic functions



// -------- System level modules -------

#include "kbd.h"		// for demo



// ------ System level modules ---------



// ------ Application level modules ---------
#include "graphics.h"
#include "objects.h"
#include "images.h"






// ---------------------- Private definitions ------------------


// an uxiliary graphic object is used as a partial frame buffer
graphic_object_t	partial_frame_buffer;








// ------------- Public function implementations --------------






// ----------- IMAGE RELATED FUNCTIONALITY ------------



void GFX_display_image_array(uint16_t *img_array, int16_t x, int16_t y, uint16_t size_x, uint16_t size_y)
{
	ILI9341_SetDisplayWindow( x, y, size_x, size_y);
	ILI9341_SendData((LCD_IO_Data_t *) img_array, size_x*size_y );
}



void GFX_display_image_object(image_object_t *image, int16_t x, int16_t y)
{
	ILI9341_SetDisplayWindow( x, y, image->size_x, image->size_y);
	ILI9341_SendData((LCD_IO_Data_t *) image->image_array, image->size );
}



// coordinates (x_img,y_img) are given in the image coordinate system
uint16_t GFX_get_image_pixel(image_object_t *img, int16_t x_img, int16_t y_img)
{
	uint32_t i;

	// coordinates (x_img,y_img) are from image coordinate system
	if ( ( (x_img>=0) && (x_img < img->size_x) ) && ( (y_img>=0) && (y_img < img->size_y) ) )
	{

		// calculate the "linear index" of the pixel at (x, y) coordinate
		i = y_img * img->size_x + x_img;

		// return the pixel at that index from the image array
		return img->image_array[i];
	}

	else
	{
		// return transparent pixel if pixel location lies outside the image
		return IMG_TRANSPARENT_COLOR_CODE;
	}

}



void GFX_get_image_part(image_object_t *img, int16_t x, int16_t y, uint16_t size_x, uint16_t size_y, uint16_t *sub_image_array)
{
	uint32_t i = 0;


	// make sure image part lies inside the image
	if(y + size_y > img->size_y)
		return;

	if(x + size_x > img->size_x)
		return;


	// go over all required rows
	for( uint16_t row = y; row < (y + size_y); row++ )
	{
		// for each row, go over all required columns
		for(uint16_t column = x; column < (x + size_x); column++ )
		{

			sub_image_array[i] = GFX_get_image_pixel(img, column, row);
			i++;
		}

	}

}







uint16_t* GFX_allocate_image_buffer(uint32_t size_px)
{
	return ( (uint16_t *) malloc(size_px * sizeof(uint16_t) ) );
}


void GFX_deallocate_image_buffer(uint16_t *ptr)
{
	free(ptr);
}









// ----------- GRAPHICAL OBJECT RELATED FUNCTIONALITY ---------





void GFX_draw_gfx_object(graphic_object_t *gfx_object)
{

	ILI9341_SetDisplayWindow( gfx_object->location.x_min, gfx_object->location.y_min, gfx_object->image.size_x, gfx_object->image.size_y);

	ILI9341_SendData((LCD_IO_Data_t *) gfx_object->image.image_array, gfx_object->image.size );
}





void GFX_save_gfx_object_location(graphic_object_t *gfx_object)
{
	gfx_object->location_old.x_min = gfx_object->location.x_min;
	gfx_object->location_old.y_min = gfx_object->location.y_min;

	gfx_object->location_old.x_max = gfx_object->location.x_max;
	gfx_object->location_old.y_max = gfx_object->location.y_max;

	gfx_object->location_old.x_center = gfx_object->location.x_center;
	gfx_object->location_old.y_center = gfx_object->location.y_center;

}



void GFX_restore_gfx_object_old_location(graphic_object_t *gfx_object)
{
	gfx_object->location.x_min = gfx_object->location_old.x_min;
	gfx_object->location.y_min = gfx_object->location_old.y_min;

	gfx_object->location.x_max = gfx_object->location_old.x_max;
	gfx_object->location.y_max = gfx_object->location_old.y_max;

	gfx_object->location.x_center = gfx_object->location_old.x_center;
	gfx_object->location.y_center = gfx_object->location_old.y_center;


}



// the limiting values are still allowed
void GFX_init_location_restrictions(graphic_object_t *gfx_object, canvas_location_t *canvas_location)
{
	// top left corner restrictions
	gfx_object->top_left_limits.X_MIN = canvas_location->x_min;
	gfx_object->top_left_limits.Y_MIN = canvas_location->y_min;

	gfx_object->top_left_limits.X_MAX = canvas_location->x_max - gfx_object->image.size_x;
	gfx_object->top_left_limits.Y_MAX = canvas_location->y_max - gfx_object->image.size_y;



	// center point restrictions
	gfx_object->center_limits.X_MIN = canvas_location->x_min + ceil( gfx_object->image.size_x / 2 );
	gfx_object->center_limits.Y_MIN = canvas_location->y_min + ceil( gfx_object->image.size_y / 2 );

	gfx_object->center_limits.X_MAX = canvas_location->x_max - ceil( gfx_object->image.size_x / 2 );
	gfx_object->center_limits.Y_MAX = canvas_location->y_max - ceil( gfx_object->image.size_y / 2 );

}








uint8_t GFX_set_gfx_object_location(graphic_object_t *gfx_object, int16_t x, int16_t y)
{

	// check if the new location is within restrictions
	if( ( x >= gfx_object->top_left_limits.X_MIN ) &&
		( x <= gfx_object->top_left_limits.X_MAX ) &&
		( y >= gfx_object->top_left_limits.Y_MIN ) &&
		( y <= gfx_object->top_left_limits.Y_MAX )
	  )
	{
		// within restrictions -> object can be placed

		// set the new object location
		gfx_object->location.x_min = x;
		gfx_object->location.y_min = y;


		gfx_object->location.x_max = gfx_object->location.x_min + gfx_object->image.size_x;
		gfx_object->location.y_max = gfx_object->location.y_min + gfx_object->image.size_y;


		gfx_object->location.x_center = gfx_object->location.x_min + gfx_object->image.size_x / 2;
		gfx_object->location.y_center = gfx_object->location.y_min + gfx_object->image.size_y / 2;


		return 1;	// placement successful
	}
	else
	{
		// new location is outside the restrictions -> object will not be placed

		return 0;	// placement successful
	}


}




uint8_t GFX_init_gfx_object_location(graphic_object_t *gfx_object, int16_t x, int16_t y)
{
	uint8_t return_value;

	return_value = GFX_set_gfx_object_location(gfx_object, x, y);

	if( return_value  )
	{
		// remember the initial object location
		GFX_save_gfx_object_location(gfx_object);
	}

	return return_value;

}




uint8_t GFX_set_gfx_object_center_location(graphic_object_t *gfx_object, int16_t x, int16_t y)
{
	// check if the new location is within restrictions
	if( ( x >= gfx_object->center_limits.X_MIN ) &&
		( x <= gfx_object->center_limits.X_MAX ) &&
		( y >= gfx_object->center_limits.Y_MIN ) &&
		( y <= gfx_object->center_limits.Y_MAX )
	  )
	{
		// within restrictions -> object can be placed

		// set the new object location
		gfx_object->location.x_center = x;
		gfx_object->location.y_center = y;


		gfx_object->location.x_min = gfx_object->location.x_center - gfx_object->image.size_x/2;
		gfx_object->location.y_min = gfx_object->location.y_center - gfx_object->image.size_y/2;

		gfx_object->location.x_max = gfx_object->location.x_min +  gfx_object->image.size_x;
		gfx_object->location.y_max = gfx_object->location.y_min +  gfx_object->image.size_y;

		return 1;	// placement successful

	}
	else
	{
		// new location is outside the restrictions -> object will not be placed

		return 0;	// placement successful
	}
}



uint8_t GFX_init_gfx_object_center_location(graphic_object_t *gfx_object, int16_t x, int16_t y)
{
	uint8_t return_value;

	return_value = GFX_set_gfx_object_center_location(gfx_object, x, y);

	if ( return_value )
	{
		// remember the initial object location
		GFX_save_gfx_object_location(gfx_object);
	}

	return return_value;
}







void GFX_set_gfx_object_velocity(graphic_object_t *gfx_object, int8_t velocity_x, int8_t velocity_y)
{
	gfx_object->velocity.x = velocity_x;
	gfx_object->velocity.y = velocity_y;
}



uint8_t GFX_update_gfx_object_location(graphic_object_t *gfx_object)
{


	uint16_t x_new, y_new;

	// remember the current object location
	GFX_save_gfx_object_location(gfx_object);


	// calculate the new object location according to the object velocity
	// simplified for now
	x_new =  gfx_object->location.x_min + gfx_object->velocity.x;
	y_new =  gfx_object->location.y_min + gfx_object->velocity.y;


	// set the new object location
	return GFX_set_gfx_object_location(gfx_object, x_new, y_new);

}



void GFX_get_object_movement_area(graphic_object_t *gfx_object, object_location_t *object_movement_area)
{
	object_movement_area->x_min = (gfx_object->location.x_min < gfx_object->location_old.x_min) ? gfx_object->location.x_min : gfx_object->location_old.x_min;
	object_movement_area->y_min = (gfx_object->location.y_min < gfx_object->location_old.y_min) ? gfx_object->location.y_min : gfx_object->location_old.y_min;

	object_movement_area->x_max = (gfx_object->location.x_max > gfx_object->location_old.x_max) ? gfx_object->location.x_max : gfx_object->location_old.x_max;
	object_movement_area->y_max = (gfx_object->location.y_max > gfx_object->location_old.y_max) ? gfx_object->location.y_max : gfx_object->location_old.y_max;


	object_movement_area->x_center = (object_movement_area->x_max - object_movement_area->x_min) / 2;
	object_movement_area->y_center = (object_movement_area->y_max - object_movement_area->y_min) / 2;
}








void GFX_absolute_coordinates_to_object_coordinates(graphic_object_t *object, int16_t x_abs, int16_t y_abs, int16_t *x_obj, int16_t *y_obj)
{

	*x_obj = x_abs - object->location.x_min;
	*y_obj = y_abs - object->location.y_min;
}




uint8_t GFX_are_gfx_objects_overlapping(graphic_object_t *object_A, graphic_object_t *object_B)
{

	if ( 	(object_A->location.x_min > object_B->location.x_max) ||	// Cond1. If A's left edge is to the right of the B's right edge, - then A is Totally to right Of B
			(object_A->location.x_max < object_B->location.x_min) ||	// Cond2. If A's right edge is to the left of the B's left edge, - then A is Totally to left Of B
			(object_A->location.y_max < object_B->location.y_min) ||	// Cond3. If A's top edge is below B's bottom edge, - then A is Totally below B
			(object_A->location.y_min > object_B->location.y_max) )		// Cond4. If A's bottom edge is above B's top edge, - then A is Totally above B
	{
		return 0;	// not overlapping
	}
	else
		return 1;	// overlapping

}














void GFX_draw_one_gfx_object_on_background(graphic_object_t *object, graphic_object_t *bckgnd)
{
	uint32_t i = 0;

	int16_t x_obj;
	int16_t y_obj;

	uint16_t pixel;


	// specify the frame buffer graphic object parameters
	// consider that the object can be moving! -> the buffer area must
	// contain both old object area and new object area!
	GFX_get_object_movement_area(object, &partial_frame_buffer.location );


	// prepare the partial frame image buffer for the entire movement area of the object
		partial_frame_buffer.image.size_x = partial_frame_buffer.location.x_max - partial_frame_buffer.location.x_min;
		partial_frame_buffer.image.size_y = partial_frame_buffer.location.y_max - partial_frame_buffer.location.y_min;
		partial_frame_buffer.image.size = partial_frame_buffer.image.size_x * partial_frame_buffer.image.size_y;

		// allocate memory for the part of the frame, i.e. prepare the image buffer
		partial_frame_buffer.image.image_array = GFX_allocate_image_buffer(partial_frame_buffer.image.size);




	// copy the appropriate part of the background image to the buffer
	GFX_get_image_part( &bckgnd->image, partial_frame_buffer.location.x_min, partial_frame_buffer.location.y_min, partial_frame_buffer.image.size_x, partial_frame_buffer.image.size_y, partial_frame_buffer.image.image_array);


	// overlay the graphical object image over the part of the background image
	// go over all the required rows of the background image part
	for( uint16_t y_abs = partial_frame_buffer.location.y_min; y_abs < partial_frame_buffer.location.y_max; y_abs++ )
	{
		// for each row, go over all required columns
		for( uint16_t x_abs = partial_frame_buffer.location.x_min; x_abs < partial_frame_buffer.location.x_max; x_abs++ )
		{
			// overlay the object pixel

				// get the graphical object image pixel at this current (column, row)
				GFX_absolute_coordinates_to_object_coordinates(object, x_abs, y_abs, &x_obj, &y_obj);
				pixel = GFX_get_image_pixel( &object->image, x_obj, y_obj);

				// overlay the pixel only if it is not transparent
				if ( pixel != IMG_TRANSPARENT_COLOR_CODE)
					partial_frame_buffer.image.image_array[i] = pixel;

			// update the buffer linear index
			i++;
		}
	}


	// display the partial frame buffer
	GFX_draw_gfx_object(&partial_frame_buffer);


	// de-allocate memory for the partial frame buffer
	GFX_deallocate_image_buffer(partial_frame_buffer.image.image_array);


}















void GFX_draw_two_gfx_objects_on_background(graphic_object_t *front_object, graphic_object_t *middle_object, graphic_object_t *bckgnd)
{
	uint32_t i = 0;

	int16_t x_obj;
	int16_t y_obj;

	uint16_t pixel;


	// if front two objects are not overlapping
	if ( ! GFX_are_gfx_objects_overlapping(front_object, middle_object) )
	{
		// display these two objects on the background separately
		GFX_draw_one_gfx_object_on_background(front_object, bckgnd);

		GFX_draw_one_gfx_object_on_background(middle_object, bckgnd);

	}
	else
	{
		// objects are overlapping

		// determine the outer dimension of front and middle object movement areas

			object_location_t	front_object_movement_area;
			object_location_t	middle_object_movement_area;

			// determine movement areas for each object
			GFX_get_object_movement_area( front_object, &front_object_movement_area);
			GFX_get_object_movement_area( middle_object, &middle_object_movement_area);

			// the partial frame should contain both movement areas!
			partial_frame_buffer.location.x_min = (front_object_movement_area.x_min < middle_object_movement_area.x_min) ? front_object_movement_area.x_min : middle_object_movement_area.x_min;
			partial_frame_buffer.location.y_min = (front_object_movement_area.y_min < middle_object_movement_area.y_min) ? front_object_movement_area.y_min : middle_object_movement_area.y_min;

			partial_frame_buffer.location.x_max = (front_object_movement_area.x_max > middle_object_movement_area.x_max) ? front_object_movement_area.x_max : middle_object_movement_area.x_max;
			partial_frame_buffer.location.y_max = (front_object_movement_area.y_max > middle_object_movement_area.y_max) ? front_object_movement_area.y_max : middle_object_movement_area.y_max;



		// prepare the partial frame image buffer for the combined movement area of both objects
			partial_frame_buffer.image.size_x = partial_frame_buffer.location.x_max - partial_frame_buffer.location.x_min;
			partial_frame_buffer.image.size_y = partial_frame_buffer.location.y_max - partial_frame_buffer.location.y_min;
			partial_frame_buffer.image.size = partial_frame_buffer.image.size_x * partial_frame_buffer.image.size_y;


			// allocate memory for the part of the frame, i.e. prepare the image buffer
			partial_frame_buffer.image.image_array = GFX_allocate_image_buffer(partial_frame_buffer.image.size);



		// copy the appropriate part of the background image to the buffer
		GFX_get_image_part( &bckgnd->image, partial_frame_buffer.location.x_min, partial_frame_buffer.location.y_min, partial_frame_buffer.image.size_x, partial_frame_buffer.image.size_y, partial_frame_buffer.image.image_array);


		// overlay the images of the two graphical objects over the part of the background image
		// go over all the required rows of the background image part
		for( uint16_t y_abs = partial_frame_buffer.location.y_min; y_abs < partial_frame_buffer.location.y_max; y_abs++ )
		{
			// for each row, go over all required columns
			for( uint16_t x_abs = partial_frame_buffer.location.x_min; x_abs < partial_frame_buffer.location.x_max; x_abs++ )
			{
				// overlay the middle object pixel

					// get the graphical object image pixel at this current (column, row)
					GFX_absolute_coordinates_to_object_coordinates(middle_object, x_abs, y_abs, &x_obj, &y_obj);
					pixel = GFX_get_image_pixel( &middle_object->image, x_obj, y_obj);

					// overlay the pixel only if it is not transparent
					if ( pixel != IMG_TRANSPARENT_COLOR_CODE)
						partial_frame_buffer.image.image_array[i] = pixel;


				// overlay the front object pixel

					// get the graphical object image pixel at this current (column, row)
					GFX_absolute_coordinates_to_object_coordinates(front_object, x_abs, y_abs, &x_obj, &y_obj);
					pixel = GFX_get_image_pixel( &front_object->image, x_obj, y_obj);

					// overlay the pixel only if it is not transparent
					if ( pixel != IMG_TRANSPARENT_COLOR_CODE)
						partial_frame_buffer.image.image_array[i] = pixel;


				// update the buffer linear index
				i++;
			}

		}


		// display the partial frame buffer
		GFX_draw_gfx_object(&partial_frame_buffer);



		// de-allocate the partial image frame buffer
		GFX_deallocate_image_buffer(partial_frame_buffer.image.image_array);


	}

}




void GFX_delete_area_on_background(int16_t x_min, int16_t y_min, int16_t x_max, int16_t y_max, graphic_object_t *bckgnd)
{
	// specify the frame buffer graphic object parameters
	// the buffer image dimensions is the same as current object dimensions
	partial_frame_buffer.location.x_min = x_min;
	partial_frame_buffer.location.y_min = y_min;

	partial_frame_buffer.location.x_max = x_max;
	partial_frame_buffer.location.y_max = y_max;


	// prepare the partial frame image buffer for the area of the current object
	partial_frame_buffer.image.size_x = partial_frame_buffer.location.x_max - partial_frame_buffer.location.x_min;
	partial_frame_buffer.image.size_y = partial_frame_buffer.location.y_max - partial_frame_buffer.location.y_min;
	partial_frame_buffer.image.size = partial_frame_buffer.image.size_x * partial_frame_buffer.image.size_y;



	// allocate memory for the part of the frame, i.e. prepare the image buffer
	partial_frame_buffer.image.image_array = GFX_allocate_image_buffer(partial_frame_buffer.image.size);



	// copy the appropriate part of the background image to the buffer
	GFX_get_image_part( &bckgnd->image, partial_frame_buffer.location.x_min, partial_frame_buffer.location.y_min, partial_frame_buffer.image.size_x, partial_frame_buffer.image.size_y, partial_frame_buffer.image.image_array);

	// display the partial frame buffer
	GFX_draw_gfx_object(&partial_frame_buffer);


	// de-allocate memory for the partial frame buffer
	GFX_deallocate_image_buffer(partial_frame_buffer.image.image_array);

}





void GFX_delete_gfx_object_on_background(graphic_object_t *object, graphic_object_t *bckgnd)
{

	// specify the frame buffer graphic object parameters
	// the buffer image dimensions is the same as current object dimensions
	partial_frame_buffer.location.x_min = object->location.x_min;
	partial_frame_buffer.location.y_min = object->location.y_min;

	partial_frame_buffer.location.x_max = object->location.x_max;
	partial_frame_buffer.location.y_max = object->location.y_max;


	// prepare the partial frame image buffer for the area of the current object
		partial_frame_buffer.image.size_x = partial_frame_buffer.location.x_max - partial_frame_buffer.location.x_min;
		partial_frame_buffer.image.size_y = partial_frame_buffer.location.y_max - partial_frame_buffer.location.y_min;
		partial_frame_buffer.image.size = partial_frame_buffer.image.size_x * partial_frame_buffer.image.size_y;

		// allocate memory for the part of the frame, i.e. prepare the image buffer
		partial_frame_buffer.image.image_array = GFX_allocate_image_buffer(partial_frame_buffer.image.size);



	// copy the appropriate part of the background image to the buffer
	GFX_get_image_part( &bckgnd->image, partial_frame_buffer.location.x_min, partial_frame_buffer.location.y_min, partial_frame_buffer.image.size_x, partial_frame_buffer.image.size_y, partial_frame_buffer.image.image_array);



	// display the partial frame buffer
	GFX_draw_gfx_object(&partial_frame_buffer);


	// de-allocate memory for the partial frame buffer
	GFX_deallocate_image_buffer(partial_frame_buffer.image.image_array);


}







void GFX_update_two_gfx_objects_on_background(graphic_object_t *front_object, graphic_object_t *middle_object, graphic_object_t *bckgnd)
{
	// move objects according to the velocity
	GFX_update_gfx_object_location(front_object);
	GFX_update_gfx_object_location(middle_object);


	// draw objects in their new location
	GFX_draw_two_gfx_objects_on_background(front_object, middle_object, bckgnd);

}






void GFX_display_text_object(text_object_t *txt_object)
{

	UG_FontSelect(txt_object->font);
	UG_SetForecolor(txt_object->fore_color);
	UG_SetBackcolor(txt_object->back_color);

	UG_PutString(txt_object->x_min, txt_object->y_min, txt_object->text );

}



void GFX_display_progress_bar(progress_bar_t *progress_bar)
{

	UG_FillFrame( progress_bar->bar.x_min, progress_bar->bar.y_min, progress_bar->bar.x_max, progress_bar->bar.y_max, progress_bar->bar.color );

	UG_FillFrame( progress_bar->bar.x_max, progress_bar->bar.y_min, progress_bar->bar.x_min + progress_bar->full_length_px, progress_bar->bar.y_max, progress_bar->background_color );
}










// ------------------ Demo functions -------------------






// Demonstracija ideje uporabe modulov objects.c in graphics.c.
// za izris stacionarnih objektov.
//
// V main() dodajte sledečo kodo:
//
/*
	  	GFX_demo();

		while (1)
		{
		}

*/
void GFX_demo(void)
{

	// ------- Izris ozadja --------

		// Najprej je potrebno objekt inicializirati s specifično OBJ_ funkcijo,
		// ki služi kot nekakšen konstruktor za objekt.
		// Inicializacija objektu nastavi vse parametre, da ga lahko pričnemo uporabljati.
		OBJ_init_background();

		// Sedaj pa ga lahko že izrišemo z GFX_ funkcijo za izris grafičnega objekta na zaslon.
		GFX_draw_gfx_object( &background );



	// ------ Dodamo "sprite" -------

		// Sedaj pa na ozadje dodamo "sprite".

		// Najprej je potrebno "sprite objekt" inicializirati s specifično OBJ_ funkcijo,
		// ki služi kot nekakšen konstruktor za objekt.
		// Inicializacija objektu nastavi vse parametre, da ga lahko pričnemo uporabljati.
		OBJ_init_sprite();

		// Sedaj pa ta "sprite objekt" izrišenmo NA OZADJE z GFX_ funkcijo.
		// Funkciji je potrebno posredovati dve informaciji:
		// sprednji objekt ter kateri objekt uporabljamo za ozadje.
		GFX_draw_one_gfx_object_on_background( &sprite, &background);




	// ----- Dodamo "progress bar" -----

		// Najprej je potrebno objekt inicializirati s specifično OBJ_ funkcijo,
		// ki služi kot nekakšen konstruktor za objekt.
		// Inicializacija objektu nastavi vse parametre, da ga lahko pričnemo uporabljati.
		OBJ_init_progress_bar();

		// In nato prikažemo ta objekt z _GFX funkcijo.
		GFX_display_progress_bar( &progress_bar );



	// ---- Dodamo še tekst ------

		// Najprej je potrebno objekt inicializirati s specifično OBJ_ funkcijo,
		// ki služi kot nekakšen konstruktor za objekt.
		// Inicializacija objektu nastavi vse parametre, da ga lahko pričnemo uporabljati.
		OBJ_init_text_object();

		// In nato prikažemo ta objekt z _GFX funkcijo.
		GFX_display_text_object( &text_object );




	// --- Čakamo na odziv uporabnika aplikacije ----


		while( KBD_get_pressed_key() == BTN_NONE );		// wait for button pressed




	// --- Se odzivamo na uporabnika -> manipuliramo z objektom -----


		// SPREMENIMO parametre objekta s pomočjo OBJ_ funkcije.
		OBJ_set_progress_bar_value(70);


		// In poskrbimo za osvežitev spremenjenega objekta na zaslonu s ponovnim izrisom.
		GFX_display_progress_bar( &progress_bar );



}

