#include <gb/gb.h>
#include "backgroundtiles.c"
#include "simple_background_map.c"

void main(){
    set_bkg_data(0,7,backgroundtiles);
    set_bkg_tiles(0,0,40,18,backgroundmap);
    
    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        scroll_bkg(1,0);
        delay(50);
    }
}