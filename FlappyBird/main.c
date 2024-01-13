#include <gb/gb.h>
#include <stdio.h>
#include "SmilerSprites.c"
#include <stdbool.h>

const uint8_t MIN_HEIGHT = 130;
const uint8_t X_POS = 20;
const uint8_t Y_UPLIFT = 6;

void main(void)
{
    uint8_t y_speed = 0;
    uint8_t y_pos = MIN_HEIGHT;
    bool a_released = TRUE;

    set_sprite_data(0, 2, Smiler);
    set_sprite_tile(0, 0);
    move_sprite(0, X_POS, y_pos);
    SHOW_SPRITES;

    while (1)
    {
        uint8_t keys = joypad();
        if (keys & J_A && a_released)
        {
            y_speed = Y_UPLIFT;
            a_released = FALSE;
        }
        if (!(keys & J_A))
        {
            a_released = TRUE;
        }

        y_pos -= y_speed;

        if (y_pos > MIN_HEIGHT)
        {
            y_pos = MIN_HEIGHT;
        }
        else
        {
            y_speed -= 1;
        }

        move_sprite(0, X_POS, y_pos);
        vsync();
    }
}