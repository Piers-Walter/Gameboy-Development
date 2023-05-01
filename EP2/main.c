#include <gb/gb.h>
#include <stdio.h>
#include "SmilerSprintes.c"

void main(){
    uint8_t currentspriteindex = FALSE;
    set_sprite_data(0,2, Smiler);
    set_sprite_tile(0,0);
    move_sprite(0,88,78);
    SHOW_SPRITES;

    while(1){
        currentspriteindex++;
        set_sprite_tile(0, currentspriteindex % 2);
        delay(1000);
        scroll_sprite(0, 10,10);
    }
}