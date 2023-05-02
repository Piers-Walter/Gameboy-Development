#include <gb/gb.h>
#include <stdio.h>
#include "GameSprites.c"
#include "GameCharacter.c"
#include <stdlib.h>
#include <gbdk/console.h>
#include "heart.c"
#include "space.c"
#include <rand.h>

struct GameCharacter ship;
struct GameCharacter bug;
// struct GameCharacter bug;
uint8_t spriteSize = 8;

uint8_t tileOrder[] = {0,2,1,3};

BYTE checkCollisions(struct GameCharacter* one, struct GameCharacter* two){
    if( one->x < two->x+two->width && one->x+one->width > two->x){
        if( one->y < two->y+two->height && one->y+one->height > two->y){
        //collision happened
            return TRUE;
        }
    }

    return FALSE;
}

void showLives(uint8_t lives){
    SHOW_WIN;
    set_win_data(1,1,heart);

    // set 0x9000 to 0x900F to 0 to reset background tile to transparent
    uint16_t * pointer = (uint16_t *)0x9000;
    while(pointer < 0x900F){
        *pointer = 0x00;
        *pointer++;
    }


    for(uint8_t i=0; i<160/8; i++){
        set_win_tile_xy(i,0,0);
    }
    for(uint8_t i=0; i<lives; i++){
        set_win_tile_xy(i,0,1);
    }
    move_win(7,136);
}

void drawSpace(){
    SHOW_BKG;
    set_bkg_data(2,1,space); // Load regs 2 with space

    for(uint8_t x=0; x<DEVICE_SCREEN_WIDTH; x++){
        for(uint8_t y = 0; y<32; y++){
            set_bkg_tile_xy(x,y,2);
        }
    }
}

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
    while(1){
        uint8_t lives = 3;
        setupBug();
        setupShip();

        drawSpace();
        showLives(lives);

        SHOW_SPRITES;
        DISPLAY_ON;

        while(lives>0){
            scroll_bkg(0,-1);
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

            performantdelay(2);
            if(checkCollisions(&ship, &bug)){
                lives--;
                bug.y = 0;
                showLives(lives);
            }
            moveGameCharacter(&bug);
            moveGameCharacter(&ship);
        };

        HIDE_WIN;
        gotoxy(0,SCY_REG/8);
        printf("\n\n\n\n\n === GAME OVER ===\n    Press Start");
        set_bkg_data(0,1,space);

        while(! (joypad() & J_START)){
            performantdelay(1);
        }
        for(int x =0; x < 20; x++){
            for(int y = 0; y < 18; y++){
                set_bkg_tile_xy(x,y,0);
            }
        };

    }


    
}