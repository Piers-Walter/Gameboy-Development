#include <gb/gb.h>
#include <stdio.h>
#include "GameSprites.c"
#include "GameCharacter.c"
#include <stdlib.h>

struct GameCharacter ship;
struct GameCharacter bug;
// struct GameCharacter bug;
uint8_t spriteSize = 8;

uint8_t tileOrder[] = {0,2,1,3};

void moveGameCharacter(struct GameCharacter* character){
    move_sprite(character->spriteIDs[0], character->x, character->y);
    move_sprite(character->spriteIDs[1], character->x + spriteSize, character->y);
    move_sprite(character->spriteIDs[2], character->x, character->y + spriteSize);
    move_sprite(character->spriteIDs[3], character->x + spriteSize, character->y + spriteSize);
}

void performantdelay(uint8_t numloops){
    uint8_t i;
    for(i=0; i<numloops; i++){
        wait_vbl_done();
    }
}

void setupShip(){
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    uint8_t vramStartIndex = 0;
    set_sprite_data(0,4,shipTiles); // Load sprite into slots 0-3 in vram
    for(uint8_t i = vramStartIndex; i < vramStartIndex + 4; i++){
        set_sprite_tile(i,tileOrder[i]); // Set tile 0 to use vram 0 etc
        ship.spriteIDs[i] = i; // add reference to tile in ship struct
    }

    moveGameCharacter(&ship);
}

void setupBug(){
    bug.x = 8;
    bug.y = 8;
    bug.width = 16;
    bug.height = 16;

    uint8_t vramStartIndex = 4;
    set_sprite_data(vramStartIndex,4,bugTiles); // Load sprite into slots 4-7 in vram

    for(uint8_t i = vramStartIndex; i < (vramStartIndex + 4); i++){
        set_sprite_tile(i, tileOrder[i%4]+vramStartIndex); // Set tile 4 to use vram 4 etc
        bug.spriteIDs[i % vramStartIndex] = i; // add reference to tile in bug struct
    }

    moveGameCharacter(&bug);
}

void main(){
    setupBug();
    setupShip();

    SHOW_SPRITES;
    DISPLAY_ON;

    while(1){
        if(joypad() & J_LEFT){
            if(ship.x > 8)
                ship.x -= 1;
        }
        if(joypad() & J_RIGHT){
            if(ship.x < SCREENWIDTH-8)
                ship.x += 1;
        }

        bug.y += 3;
        if(bug.y > SCREENHEIGHT + spriteSize*2){
            bug.y = 0;
            bug.x = ship.x;
        }

        moveGameCharacter(&bug);
        moveGameCharacter(&ship);

        performantdelay(2);
    }
}