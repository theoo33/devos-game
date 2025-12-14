#ifndef SPRITE_H
#define SPRITE_H

// Généré par png_to_c_with_palette.py à partir de 'pixel-32x32.png'
#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT 32
#define SPRITE_PLAYER_WIDTH 32
#define SPRITE_PLAYER_HEIGHT 32
#define SPRITE_NUMBER_WIDTH 64
#define SPRITE_NUMBER_HEIGHT 64

extern unsigned char palette_vga[256][3];
extern unsigned char palette_numbers[256][3];
extern unsigned char sprite_data[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_door_data[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_ball_data[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_player_red_right[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_red_left[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];

// numbers
extern unsigned char zeroB_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char zeroR_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char oneB_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char oneR_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char twoB_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char twoR_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char threeB_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char threeR_data[SPRITE_NUMBER_WIDTH*SPRITE_NUMBER_HEIGHT];
extern unsigned char scoreBoard_data[246*143];

#endif