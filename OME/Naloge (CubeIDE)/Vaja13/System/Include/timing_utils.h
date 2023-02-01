/*
 * timing_utils.h
 *
 *  Created on: 12.4.2022
 *      Author: Rok Plesko
 */


#ifndef INCLUDE_TIMING_UTILS_H_
#define INCLUDE_TIMING_UTILS_H_



// Pri implementaciji modula z orodji za merjenje časa bomo potrebovali sledeče HAL funkcije:
//
//    HAL_GetTick()
//    LL_TIM_EnableCounter (TIM_TypeDef * TIMx)
//    LL_TIM_EnableIT_UPDATE (TIM_TypeDef * TIMx)
//    LL_TIM_DisableIT_UPDATE (TIM_TypeDef * TIMx)
//    LL_TIM_IsEnabledIT_UPDATE (TIM_TypeDef * TIMx)
//    LL_TIM_IsActiveFlag_UPDATE (TIM_TypeDef * TIMx)
//    LL_TIM_ClearFlag_UPDATE (TIM_TypeDef * TIMx)
//




// ----------- Include other modules (for public) -------------


#include "stdint.h"		// za podporo definicijam celoštevilskih tipov (npr. uint8_t)


////////	PROBLEMI    /////////////////////////
// preglej timer nastavitve
//pejd skoz cubemx errorje popravt


// -------------------- Public definitions --------------------

// Na tem mestu "javno" definiramo "handle" strukturo, s pomočjo katere
// bomo lahko ustvarili funkcionalnost ure štoparice in tako merili čas.
typedef struct
{
	uint32_t	time_mark;
	uint32_t	elapsed_time;

} stopwatch_handle_t;






// ---------------- Public function prototypes ----------------


// Funkcije za delo z uro štoparico.
void TIMUT_stopwatch_set_time_mark(stopwatch_handle_t *stopwatch);
void TIMUT_stopwatch_update(stopwatch_handle_t *stopwatch);
uint8_t TIMUT_stopwatch_has_X_ms_passed(stopwatch_handle_t *stopwatch, uint32_t x);
uint8_t TIMUT_stopwatch_has_another_X_ms_passed(stopwatch_handle_t *stopwatch, uint32_t x);
uint32_t TIMUT_get_stopwatch_elapsed_time(stopwatch_handle_t *stopwatch);

// Demo testne funkcije.
void TIMUT_stopwatch_demo(void);




#endif /* INCLUDE_TIMING_UTILS_H_ */
