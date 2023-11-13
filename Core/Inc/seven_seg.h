/*
 * seven_seg.h
 *
 *  Created on: Oct 27, 2023
 *      Author: ADMIN
 */

#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

#include <stdint.h>
#include "main.h"

void display7SEG(uint8_t num);

void update7SEG(uint8_t index, int32_t *led_buffer);

#endif /* INC_SEVEN_SEG_H_ */
