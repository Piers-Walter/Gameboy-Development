#include <gb/gb.h>
#include "backgroundtiles.c"
#include "simple_background_map.c"
#include <gbdk/font.h>
#include "window_map.c"

void main(){
    font_t min_font;
    
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    set_bkg_data(37,7,backgroundtiles);
    set_bkg_tiles(0,0,40,18,backgroundmap);
    
    set_win_tiles(0,0,5,1,windowmap);
    move_win(7, 128);
    SHOW_WIN;


    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        scroll_bkg(1,0);
        delay(50);
    }
}