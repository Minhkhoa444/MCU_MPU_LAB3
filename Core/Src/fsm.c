/*
 * fsm_mod_mode.c
 *
 *  Created on: Oct 24, 2023
 *      Author: ADMIN
 */

#include "fsm.h"

#ifndef INTERNAL_LINKAGE
#define INTERNAL_LINKAGE static
#endif

INTERNAL_LINKAGE const int32_t interrupt_period = 10;

INTERNAL_LINKAGE uint8_t seven_seg_index = 0;

INTERNAL_LINKAGE int32_t red_light_duration = 5;
INTERNAL_LINKAGE int32_t yellow_light_duration = 1;
INTERNAL_LINKAGE int32_t green_light_duration = 4;

typedef enum state_t {
    INIT,
    RED_GREEN,
    RED_YELLOW,
    GREEN_RED,
    YELLOW_RED,
    MAN_RED,
    MAN_YELLOW,
    MAN_GREEN
} state_t;

INTERNAL_LINKAGE state_t state = INIT;

typedef struct buffer_wrapper_t {
    int32_t buffer[4];    //  N, E, S, W
} buffer_wrapper_t;

INTERNAL_LINKAGE void buffer_decrement(buffer_wrapper_t *buffer) {
    buffer->buffer[0] -= 1;
    buffer->buffer[1] -= 1;
    buffer->buffer[2] -= 1;
    buffer->buffer[3] -= 1;
}
INTERNAL_LINKAGE buffer_wrapper_t seven_seg_buffer = {{0, 0, 0, 0}};

INTERNAL_LINKAGE void auto_redgreen(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    if(timer1_flag) {
        setTimer1(timer_scaler(yellow_light_duration * 1000, interrupt_period));
        setTimer2(timer_scaler(1000, interrupt_period));
        setTimer3(timer_scaler(250, interrupt_period));
        state = RED_YELLOW;
        seven_seg_buffer = (buffer_wrapper_t){{yellow_light_duration, yellow_light_duration, yellow_light_duration, yellow_light_duration}};
    }
    if(timer2_flag) {
        setTimer2(timer_scaler(1000, interrupt_period));
        buffer_decrement(&seven_seg_buffer);
    }
    if(timer3_flag) {
        setTimer3(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        state = MAN_RED;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    }
}

INTERNAL_LINKAGE void auto_redyellow() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);
    if(timer1_flag) {
        setTimer1(timer_scaler(green_light_duration * 1000, interrupt_period));
        setTimer2(timer_scaler(1000, interrupt_period));
        setTimer3(timer_scaler(250, interrupt_period));
        state = GREEN_RED;
        seven_seg_buffer = (buffer_wrapper_t){{green_light_duration, red_light_duration, green_light_duration, red_light_duration}};
    }
    if(timer2_flag) {
        setTimer2(timer_scaler(1000, interrupt_period));
        buffer_decrement(&seven_seg_buffer);
    }
    if(timer3_flag) {
        setTimer3(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        state = MAN_RED;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    }
}

INTERNAL_LINKAGE void auto_greenred() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    if(timer1_flag) {
        setTimer1(timer_scaler(yellow_light_duration * 1000, interrupt_period));
        setTimer2(timer_scaler(1000, interrupt_period));
        setTimer3(timer_scaler(250, interrupt_period));
        state = YELLOW_RED;
        seven_seg_buffer = (buffer_wrapper_t){{yellow_light_duration, yellow_light_duration, yellow_light_duration, yellow_light_duration}};
    }
    if(timer2_flag) {
        setTimer2(timer_scaler(1000, interrupt_period));
        buffer_decrement(&seven_seg_buffer);
    }
    if(timer3_flag) {
        setTimer3(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        state = MAN_RED;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    }
}

INTERNAL_LINKAGE void auto_yellowred(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5, GPIO_PIN_SET);
    if(timer1_flag) {
        setTimer1(timer_scaler(green_light_duration * 1000, interrupt_period));
        setTimer2(timer_scaler(1000, interrupt_period));
        setTimer3(timer_scaler(250, interrupt_period));
        state = RED_GREEN;
        seven_seg_buffer = (buffer_wrapper_t){{red_light_duration, green_light_duration, red_light_duration, green_light_duration}};
    }
    if(timer2_flag) {
        setTimer2(timer_scaler(1000, interrupt_period));
        buffer_decrement(&seven_seg_buffer);
    }
    if(timer3_flag) {
        setTimer3(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        state = MAN_RED;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    }
}

INTERNAL_LINKAGE void mode_2(void) {
    static int32_t red_light_duration_temp = 1;
    seven_seg_buffer = (buffer_wrapper_t){{red_light_duration_temp / 10, 2, red_light_duration_temp % 10, 2}};
    if(timer4_flag) {
        setTimer4(timer_scaler(500, interrupt_period));
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    }
    if(timer5_flag) {
        setTimer5(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);
        state = MAN_YELLOW;
    }
    if(is_button_pressed(1)) {
        red_light_duration_temp += 1;
        if(red_light_duration_temp > 99) red_light_duration_temp = 1;
    }
    if(is_button_pressed(2)) {
        red_light_duration = red_light_duration_temp;
        green_light_duration = red_light_duration - yellow_light_duration;
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);
        state = MAN_YELLOW;
    }
}

INTERNAL_LINKAGE void mode_3(void) {
    static int32_t yellow_light_duration_temp = 1;
    seven_seg_buffer = (buffer_wrapper_t){{yellow_light_duration_temp / 10, 3, yellow_light_duration_temp % 10, 3}};
    if(timer4_flag) {
        setTimer4(timer_scaler(500, interrupt_period));
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);
    }
    if(timer5_flag) {
        setTimer5(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
        state = MAN_GREEN;
    }
    if(is_button_pressed(1)) {
        yellow_light_duration_temp += 1;
        if(yellow_light_duration_temp > 99) yellow_light_duration_temp = 1;
    }
    if(is_button_pressed(2)) {
        yellow_light_duration = yellow_light_duration_temp;
        green_light_duration = red_light_duration - yellow_light_duration;
        setTimer4(timer_scaler(500, interrupt_period));
        setTimer5(timer_scaler(250, interrupt_period));
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
        state = MAN_GREEN;
    }
}

INTERNAL_LINKAGE void mode_4(void) {
    static int32_t green_light_duration_temp = 1;
    seven_seg_buffer = (buffer_wrapper_t){{green_light_duration_temp / 10, 4, green_light_duration_temp % 10, 4}};
    if(timer4_flag) {
        setTimer4(timer_scaler(500, interrupt_period));
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
    }
    if(timer5_flag) {
        setTimer5(timer_scaler(250, interrupt_period));
        update7SEG(seven_seg_index, seven_seg_buffer.buffer);
        seven_seg_index += 1;
        if(seven_seg_index >= 4) {
            seven_seg_index = 0;
        }
    }
    if(is_button_pressed(0)) {
        state = INIT;
    }
    if(is_button_pressed(1)) {
        green_light_duration_temp += 1;
        if(green_light_duration_temp > 99) green_light_duration_temp = 1;
    }
    if(is_button_pressed(2)) {
        green_light_duration = green_light_duration_temp;
        red_light_duration = green_light_duration + yellow_light_duration;
        state = INIT;
    }
}


void mode_switch_fsm(void) {
    switch(state) {
    case INIT:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
        state = RED_GREEN;
        setTimer1(timer_scaler(green_light_duration * 1000, interrupt_period));
        setTimer2(timer_scaler(1000, interrupt_period));
        setTimer3(timer_scaler(200, interrupt_period));
        seven_seg_buffer = (buffer_wrapper_t){{red_light_duration, green_light_duration, red_light_duration, green_light_duration}};
        break;
    case RED_GREEN:
        auto_redgreen();
        break;
    case RED_YELLOW:
        auto_redyellow();
        break;
    case GREEN_RED:
        auto_greenred();
        break;
    case YELLOW_RED:
        auto_yellowred();
        break;
    case MAN_RED:
        mode_2();
        break;
    case MAN_YELLOW:
        mode_3();
        break;
    case MAN_GREEN:
        mode_4();
        break;
    default:
        break;
    }
}
