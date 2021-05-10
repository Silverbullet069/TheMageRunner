
#ifndef CONFIG_H
#define CONFIG_H

//Screen
const int SCREEN_WIDTH = 2560;
const int SCREEN_HEIGHT = 1536;

//Player
const float PLAYER_START_X_POS = 100.0f;
const float PLAYER_START_Y_POS = 200.0f;
const int PLAYER_WIDTH_FRAME   = 500;
const int PLAYER_HEIGHT_FRAME  = 500;

const float PLAYER_SPEED = 0.8f;

const int PLAYER_SPRITE_COMMON_ROW   = 0;
const int PLAYER_SPRITE_COMMON_FRAME = 8;
const int PLAYER_SPRITE_JUMP_FRAME   = 2;
const int PLAYER_SPRITE_FALL_FRAME   = 2;

const int PLAYER_ANIME_IDLE_SPEED   = 100;
const int PLAYER_ANIME_RUN_SPEED    = 100;
const int PLAYER_ANIME_CROUCH_SPEED = 200;
const int PLAYER_ANIME_JUMP_SPEED   = 200;
const int PLAYER_ANIME_FALL_SPEED   = 300;
const int PLAYER_ANIME_ATTACK_SPEED = 100;

const float PLAYER_RIGID_BODY_GRAVITY_ACCEL = 3.0f;
const float PLAYER_JUMP_TIME = 15.0f;
const float PLAYER_JUMP_FORCE = 10.0f;
const int PLAYER_RUN_FORCE = 10;

const int PLAYER_BUFFER_X_POS = -220;
const int PLAYER_BUFFER_Y_POS = -220;
const int PLAYER_BUFFER_W_POS = 420;
const int PLAYER_BUFFER_H_POS = 400;

//Enemy
const float ENEMY_RIGID_BODY_GRAVITY_ACCEL = 3.5f;

//Background
const int BKG_MAP_START_X_POS = 0;
const int BKG_MAP_START_Y_POS = 0;
const int BKG_MAP_WIDTH = 3840;
const int BKG_MAP_HEIGHT = 1536;
const float BKG_LAYER_LAST_SPEED = 0.6f;
const float BKG_LAYER_MID_SPEED = 0.7f;
const float BKG_LAYER_FIRST_SPEED = 0.8f;

//Tile (dung` de? set bien' local trong CollisionHandler)
const int TILE_SIZE = 128;
const int TILE_MAP_ROW_COUNT = 12;
const int TILE_MAP_COL_COUNT = 30;

#endif // CONFIG_H
