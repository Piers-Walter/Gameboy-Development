#include <gb/gb.h>
#include <stdbool.h>
#include <stdio.h>

// Smiler Bird
#include "SmilerSprites.c"

// Background
#include "Background/Background.h"
#include "Background/Tile.h"

const uint8_t MIN_HEIGHT = 130;
const uint8_t MAX_HEIGHT = 20;
const uint8_t START_HEIGHT = 80;
const uint8_t X_POS = 20;
const int8_t Y_UPLIFT = -5;

void initialise_sprite(uint8_t *y_pos) {
  // Load the tiles 0 & 1 with the values from Smiler
  set_sprite_data(0, 2, Smiler);
  // Set GB Memory Sprite 0 to Sprite 0 in from above
  set_sprite_tile(0, 0);
  // Move sprite 0 to X and Y position
  move_sprite(0, X_POS, *y_pos);
  SHOW_SPRITES;
}

void intitalise_background(void) {
  set_bkg_data(0, Background_TILECOUNT, BackgroundTiles);
  set_bkg_tiles(0, 0, Background_WIDTH, Background_HEIGHT, BackgroundMap);
  SHOW_BKG;
}

void update_bkg_position(void) { scroll_bkg(1, 0); }

void main(void) {
  uint8_t frameLoop = 0;
  int8_t y_speed = 0;
  uint8_t y_pos = START_HEIGHT;
  initialise_sprite(&y_pos);
  intitalise_background();

  bool a_released = TRUE;

  while (1) {
    frameLoop++;
    update_bkg_position();

    // See if a is pressed and has been relased
    uint8_t buttons = joypad();
    if (buttons & J_A && a_released) {
      y_speed = Y_UPLIFT;
      a_released = FALSE;
    }

    if (!(buttons & J_A)) {
      a_released = TRUE;
    }

    // Apply Gravity every other frame
    if (frameLoop % 2) {
      y_speed += 1;
    }

    // Update sprite location
    y_pos += y_speed;

    if (y_pos < MAX_HEIGHT) {
      y_pos = MAX_HEIGHT;
    }

    // Make sure sprite doesn't go below MIN_HEIGHT
    if (y_pos > MIN_HEIGHT) {
      y_pos = 130;
      y_speed = 0;
    }

    move_sprite(0, X_POS, y_pos);
    vsync();
  }
}