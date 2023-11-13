/*
 * input_reading.c
 *
 *  Created on: Oct 4, 2023
 *      Author: ADMIN
 */

#include "input_reading.h"

#ifndef INTERNAL_LINKAGE
#define INTERNAL_LINKAGE static
#endif
#define NO_OF_BUTTONS 3
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

INTERNAL_LINKAGE GPIO_PinState button_buffer[NO_OF_BUTTONS];
INTERNAL_LINKAGE GPIO_PinState debounce_button_buffer_0[NO_OF_BUTTONS];
INTERNAL_LINKAGE GPIO_PinState debounce_button_buffer_1[NO_OF_BUTTONS];
INTERNAL_LINKAGE GPIO_PinState debounce_button_buffer_2[NO_OF_BUTTONS];

INTERNAL_LINKAGE uint8_t debouce_counter[NO_OF_BUTTONS];
INTERNAL_LINKAGE uint8_t button_flag[NO_OF_BUTTONS];

void button_reading(void) {
    for(uint8_t i = 0; i < NO_OF_BUTTONS; ++i) {
        debounce_button_buffer_2[i] = debounce_button_buffer_1[i];
        debounce_button_buffer_1[i] = debounce_button_buffer_0[i];
        if(i == 0) debounce_button_buffer_0[i] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
        if(i == 1) debounce_button_buffer_0[i] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
        if(i == 2) debounce_button_buffer_0[i] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
        if(debounce_button_buffer_0[i] == debounce_button_buffer_1[i] && debounce_button_buffer_1[i] == debounce_button_buffer_2[i]) {
            if(button_buffer[i] != debounce_button_buffer_0[i]) {
                button_buffer[i] = debounce_button_buffer_0[i];
                if(button_buffer[i] == BUTTON_IS_PRESSED) {
                    debouce_counter[i] = 100;
                    button_flag[i] = 1;
                }
            }
            else {
                debouce_counter[i] -= 1;
                if(debouce_counter[i] == 0) {
                    if(button_buffer[i] == BUTTON_IS_PRESSED) {
                        debouce_counter[i] = 100;
                        button_flag[i] = 1;
                    }
                }
            }
        }
    }
}

uint8_t is_button_pressed(uint8_t index) {
    if(index >= NO_OF_BUTTONS) return 0;
    if(button_flag[index]) {
        button_flag[index] = 0;
        return 1;
    }
    else return 0;
}