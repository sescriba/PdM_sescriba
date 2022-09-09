/**
  ******************************************************************************
  * @file    API_delay.c
  * @author  MCD Application Team
  * @brief   Delay driver file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Time initialization
  * @param  delay_t * delay, tick_t duration
  * @retval Void
  */
void delayInit(delay_t * delay, tick_t duration ){
	if(delay ==0 || duration <= 0 || duration > MAX_DElAY) return;
	delay->startTime = 0;
	delay->duration = duration;
	delay->running = false;
	return;
}

/**
  * @brief  Time control
  * @param  delay_t * delay
  * @retval bool_t end
  */
bool_t delayRead(delay_t * delay ){
	uint32_t time = 0;
	bool_t end = false;
	if(delay->running == false){	//Initialization check
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else{
		time = HAL_GetTick() - (delay->startTime);		//Get difference
		if(time >= delay->duration){		//Time control
			delay->running = false;
			end = true;
			return end;
		}
	}
	end = false;
	return end;
}

/**
  * @brief  Time reassignation
  * @param  delay_t * delay
  * @retval bool_t end
  */
void delayWrite(delay_t * delay, tick_t duration ){
	if(duration <= 0) return;
	delay->duration = duration;
	return;
}
