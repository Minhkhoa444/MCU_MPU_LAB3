/*
 * seven_seg.c
 *
 *  Created on: Oct 24, 2023
 *      Author: ADMIN
 */

#include "seven_seg.h"

void display7SEG(uint8_t num) {
    if(num > 9) num = 9;
    uint16_t led_on_pins = GPIO_PIN_9, led_off_pins = GPIO_PIN_9;
    switch(num) {
    case 0:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
        led_off_pins = GPIO_PIN_15;
        break;
    case 1:
        led_on_pins = GPIO_PIN_10 | GPIO_PIN_11;
        led_off_pins = GPIO_PIN_9 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        break;
    case 2:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
        led_off_pins = GPIO_PIN_11 | GPIO_PIN_14;
        break;
    case 3:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_15;
        led_off_pins = GPIO_PIN_13 | GPIO_PIN_14;
        break;
    case 4:
        led_on_pins = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_14 | GPIO_PIN_15;
        led_off_pins = GPIO_PIN_9 | GPIO_PIN_12 | GPIO_PIN_13;
        break;
    case 5:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
        led_off_pins = GPIO_PIN_10 | GPIO_PIN_13;
        break;
    case 6:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        led_off_pins = GPIO_PIN_10;
        break;
    case 7:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
        led_off_pins = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        break;
    case 8:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        break;
    case 9:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
        led_off_pins = GPIO_PIN_13;
        break;
    default:
        led_on_pins = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    }
    HAL_GPIO_WritePin(GPIOB, led_on_pins, GPIO_PIN_RESET);
    if(num != 8) HAL_GPIO_WritePin(GPIOB, led_off_pins, GPIO_PIN_SET);
}

void update7SEG(uint8_t index, int32_t *led_buffer) {
    display7SEG(led_buffer[index]);
    switch(index) {
    case 0:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6, GPIO_PIN_SET);
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
        break;
    default:
        break;
    }
}