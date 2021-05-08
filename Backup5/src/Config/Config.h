
#ifndef CONFIG_H
#define CONFIG_H

//Screen
const int SCREEN_WIDTH = 2560;
const int SCREEN_HEIGHT = 1536;

//Player
const float PLAYER_START_X_POS = 100.0f;
const float PLAYER_START_Y_POS = 200.0f;
const int PLAYER_WIDTH_FRAME = 500;
const int PLAYER_HEIGHT_FRAME = 500;

const float PLAYER_SPEED = 0.8f;
const int PLAYER_SPRITE_ROW = 1;
const int PLAYER_SPRITE_JUMP_FALL_ROW = 2;
const int PLAYER_SPRITE_FRAME = 8;
const int PLAYER_ANIMATION_SPEED = 100;

const float PLAYER_RIGID_BODY_GRAVITY_ACCEL = 3.0f;
const float PLAYER_JUMP_TIME = 15.0f;
const float PLAYER_JUMP_FORCE = 10.0f;
const int PLAYER_RUN_FORCE = 10;

const int PLAYER_BUFFER_X_POS = -200;
const int PLAYER_BUFFER_Y_POS = -150;
const int PLAYER_BUFFER_W_POS = 360;
const int PLAYER_BUFFER_H_POS = 320;

//Background
const int BKG_MAP_START_X_POS = 0;
const int BKG_MAP_START_Y_POS = 0;
const int BKG_MAP_WIDTH = 3840;
const int BKG_MAP_HEIGHT = 1536;
const float BKG_LAYER_LAST_SPEED = 0.6f;
const float BKG_LAYER_MID_SPEED = 0.7f;
const float BKG_LAYER_FIRST_SPEED = 0.8f;

//Tile
const int TILE_SIZE = 128;
const int TILE_MAP_ROW_COUNT = 12;
const int TILE_MAP_COL_COUNT = 30;

#endif // CONFIG_H
