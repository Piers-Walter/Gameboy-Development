#include <gb/gb.h>
#include <stdio.h>

void main(){
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    while(1){
        UBYTE joypad_state = joypad();

        if(joypad_state){
            NR10_REG = 0b00010110;

            NR11_REG = 0b01000000;

            NR12_REG = 0b01110011;

            NR13_REG = 0b00000000;

            NR14_REG = 0b11000100;

            delay(1000);
        }
    }
}