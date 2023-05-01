#include <gb/gb.h>
#include <stdio.h>
#include "bloke.c"


int8_t playerlocation[2];
BOOLEAN jumping = FALSE;
int8_t gravity = -2;
int8_t currentspeedY = 0;
uint8_t floorYPosition = 139;

typedef struct SpriteLocation {
    uint8_t x;
    int8_t y;
};

typedef struct Player {
    uint8_t spriteId;
    struct SpriteLocation playerLocation;
};

void performantdelay(uint8_t numloops){
    uint8_t i;
    for(i=0; i<numloops; i++){
        wait_vbl_done();
    }
}

int8_t wouldhitsurface(uint8_t projectedYPosition) {
    if(projectedYPosition >= floorYPosition){
        return floorYPosition;
    }
    return -1;
}

void jump(uint8_t spriteid, struct SpriteLocation *spriteLocation){
    int8_t possiblesurfaceY = 0;

    if(!jumping){
        jumping = TRUE;
        currentspeedY = 10;
    }

    currentspeedY = currentspeedY + gravity;

    spriteLocation->y = spriteLocation->y - currentspeedY;

    possiblesurfaceY = wouldhitsurface(spriteLocation->y);

    if(possiblesurfaceY != -1){
        jumping = FALSE;
        move_sprite(spriteid,spriteLocation->x, possiblesurfaceY);
    }else{
        move_sprite(spriteid,spriteLocation->x, spriteLocation->y);
    }
   
}

void main(){
    struct Player player = {
        .spriteId = 0,
        .playerLocation = {
            .x = 10,
            .y = floorYPosition
        }
    };

    set_sprite_data(0, 8, bloke); // Load the first 8 sprite tiles from bloke into VRAM
    set_sprite_tile(0,player.spriteId); // Set first sprite to tile 0 from VRAM

    move_sprite(0,player.playerLocation.x, player.playerLocation.y); // Move the sprite tile onscreen

    DISPLAY_ON;
    SHOW_SPRITES;

    while(1){
        if(joypad() & J_LEFT){
            player.playerLocation.x -= 2;
            move_sprite(0, player.playerLocation.x, player.playerLocation.y);
        }
        if(joypad() & J_RIGHT){
            player.playerLocation.x += 2;
            move_sprite(0, player.playerLocation.x, player.playerLocation.y);
        }

        if((joypad() & J_A) || jumping){
            jump(player.spriteId, & player.playerLocation);
        }
        
        performantdelay(5);

    }
}