#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <math.h>

//Window
const int SCREEN_WIDTH  = 2560;
const int SCREEN_HEIGHT = 1536;
const int SCREEN_FPS = 25;

//Color key surface
const SDL_Color BLACK = {0, 0, 0};
const SDL_Color WHITE = {0xFF, 0xFF, 0xFF};
const SDL_Color DEMO = {0, 64, 128};
const SDL_Color RED = {255, 0, 0};
const int RENDER_DRAW_COLOR = 0xFF;

//Screen effect
const int ALPHA_BLEND_RANGE = 80;
const int FADING_DELAY_TIME = 50;

//Elementary function
const float PI = 3.14159;
const float EPSILON_SIN = 0.00001;
const float SIN_FACTOR_K = 200.0;
const float SIN_FACTOR_A = 0.01;
const float SIN_FACTOR_B = 1.5*PI;
const float SIN_FACTOR_C = 400.0;

const float EPSILON_COS = 0.00001;
const float COS_FACTOR_K = 200.0;
const float COS_FACTOR_A = 0.01;
const float COS_FACTOR_B = 0.0;
const float COS_FACTOR_C = 1100.0;

//Rect
const SDL_Rect TOTAL_SCREEN = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
const SDL_Rect HALVED_SCREEN = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

//Font
const int FONT_SIZE = 30;
const int FONT_SIZE_2 = 40;

//Main
const int PLAYER_MAX_FALL_SPEED  = 10;
const int PLAYER_GRAVITY_VELOCITY = 1;
const int PLAYER_VELOCITY = 20;
const int PLAYER_JUMP_VAL = 25;
const int PLAYER_FRAME_NUM = 16;
const int PLAYER_START_FALL_Y_POS = 800;
const int PLAYER_TOTAL_LIVES = 3;
const int PLAYER_ADD_VELOCITY = 20;

//Bullet
const int BULLET_VELOCITY_X_VAL = 50;
const int BULLET_VELOCITY_Y_VAL = 25;
const int BULLET_MARGINS_X_VAL = 40;
const int BULLET_MARGINS_Y_VAL = 20;

//Threat
const int THREAT_GRAVITY_VELOCITY = 1;
const int THREAT_VELOCITY = 10;
const int THREAT_MAX_FALL_VELOCITY = 10;
const int THREAT_FRAME_NUM = 8;
const int THREAT_MAX_PATROL = 128*4;
const int THREAT_TOTAL_NUM_EACH_TYPE = 2;
const int THREAT_START_FALL_Y_POS = 700;

const int THREAT_BULLET_MARGINS_X_VAL = 30;
const int THREAT_BULLET_MARGINS_Y_VAL = 30;
const int THREAT_BULLET_VELOCITY = 15;
const int THREAT_BULLET_MAX_RANGED = 128*4;

//Fairy
const int FAIRY_FRAME_NUM = 20;
const int FAIRY_VELOCITY_X_VAL = 20;
const int FAIRY_VELOCITY_Y_VAL = 20;
const int FAIRY_CONVO_NUM = 10;

//Text
const int TEXT_MARGINS_X_VAL = 80;
const int TEXT_MARGINS_Y_VAL = 200;
const int TEXT_SPACING = 150;

//Delay
const int FRAME_TEXT_DELAY = 0;
const int NORMAL_TYPING_DELAY_TIME = 100;
const int SKIP_TYPING_DELAY_TIME = 30;
const int EACH_CONVO_DELAY_TIME = 1000;

//Map
const int MAX_MAP_X = 50;
const int MAX_MAP_Y = 12;
const int MAX_MAP_X_SCREEN = 20;
const int MAX_MAP_Y_SCREEN = 12;
const int EPSILON = 1; //Sai so de xu ly va cham voi tile map
const int TILE_SIZE = 128; //kich thuoc 1 tile la 128x128

//Tile
const int MAX_TILES = 60;
const int BLANK_TILE = 0;
const int SPELL_BOOK = 25;
const int SPELL_BOOK_FRAME = 4;
const int HP_POTION = 50;
const int HASTE_POTION = 51;
const int INVUL_POTION = 52;
const int POWER_POTION = 53;
const int GOLD_COIN = 55;
const int GOLD_COIN_FRAME = 4;

//Time
const int TIME_ONE_STAGE = 300; //5p

//Draft
const int STATE_MONEY = MAX_TILES + 1;

//Cac bien do hoa
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Event g_event;

//Cac bien font text
extern TTF_Font* g_font_text;
extern TTF_Font* g_font_text_2;

//Cac tai nguyen cua game
const std::string game_name = "TheMageRunner";
const std::string g_name_menu = "resource//Tilemap//menu//menu.png";
const std::string g_name_back_ground_1 = "resource//Tilemap//bkg_12800x1536//bkg1_12800x1536.png";
const std::string g_name_back_ground_2 = "resource//Tilemap//bkg_12800x1536//bkg2_12800x1536.png";
const std::string g_name_back_ground_3 = "resource//Tilemap//bkg_12800x1536//bkg3_12800x1536.png";
const std::string g_name_font_text = "resource//Font//dlxfont_.ttf";
const std::string g_name_font_text_2 = "resource//Font//joystix_monospace.ttf";
const std::string g_name_map_tile = "resource//Tilemap//map03.txt";
const std::string g_name_tile_directory = "resource//Tilemap//tile_128x128//";
const std::string g_name_skull = "resource//Item//skull//1.png";

const std::string g_name_map_tile_tutorial_1 = "resource//Tilemap//map_tutorial_1.txt";
const std::string g_name_map_tile_tutorial_2 = "resource//Tilemap//map_tutorial_2.txt";
const std::string g_name_map_tile_tutorial_3 = "resource//Tilemap//map_tutorial_3.txt";

//Main
const std::string main_directory = "resource//Main//Real wizard//Tile//128x128//";
const std::string g_name_main_obj_walk_left = "resource//Main//Real wizard//Tile//128x128//png 16fr//walk_left_16fr.png";
const std::string g_name_main_obj_walk_right = "resource//Main//Real wizard//Tile//128x128//png 16fr//walk_right_16fr.png";
const std::string g_name_main_obj_idle_left = "resource//Main//Real wizard//Tile//128x128//png 16fr//idle_left_16fr.png";
const std::string g_name_main_obj_idle_right = "resource//Main//Real wizard//Tile//128x128//png 16fr//idle_right_16fr.png";
const std::string g_name_main_obj_jump_left = "resource//Main//Real wizard//Tile//128x128//png 1fr//jump_left_1fr.png";
const std::string g_name_main_obj_jump_right = "resource//Main//Real wizard//Tile//128x128//png 1fr//jump_right_1fr.png";
const std::string g_name_main_obj_take_hit_left = "resource//Main//Real wizard//Tile//128x128//png 16fr//take_hit_left_16fr.png";
const std::string g_name_main_obj_take_hit_right = "resource//Main//Real wizard//Tile//128x128//png 16fr//take_hit_right_16fr.png";
const std::string g_name_main_obj_ko_left = "resource//Main//Real wizard//Tile//128x128//png 1fr//die_left_1fr.png";
const std::string g_name_main_obj_ko_right = "resource//Main//Real wizard//Tile//128x128//png 1fr//die_right_1fr.png";

const std::string g_name_skill_main_fire_ball_right = "resource//Main//Real wizard//Fireball//64x64//Right//Fireball.png";
const std::string g_name_skill_main_fire_ball_left = "resource//Main//Real wizard//Fireball//64x64//Left//Fireball.png";
const std::string g_name_skill_main_ice_shard_right = "resource//Main//Real wizard//Iceshard//64x64//Right//7.png";
const std::string g_name_skill_main_ice_shard_left = "resource//Main//Real wizard//Iceshard//64x64//Left//7.png";
const std::string g_name_skill_main_magic_barrier = "resource//Main//Real wizard//Magic barrier//150x150//Shield.png";

const std::string g_name_icon_live = "resource//Icon//Live//pixel_heart.png";
const std::string g_name_icon_skill = "resource//Icon//Skill//sprite_icon.png";
const std::string g_name_icon_buff = "resource//Icon//Buff//buff_sprite.png";
const std::string g_name_icon_coin = "resource//Icon//Coin//gold_coin.png";
const std::string g_name_icon_hour_glass = "resource//Icon//Hourglass//hourglass.png";

//Threat
const std::string g_name_threat_fire_wisp_move_left = "resource//Threat//Elemental wisp//Fire wisp//128x128//move_left.png";
const std::string g_name_threat_fire_wisp_move_right = "resource//Threat//Elemental wisp//Fire wisp//128x128//move_right.png";
const std::string g_name_threat_fire_wisp_die_left = "resource//Threat//Elemental wisp//Fire wisp//128x128//die_left.png";
const std::string g_name_threat_fire_wisp_die_right = "resource//Threat//Elemental wisp//Fire wisp//128x128//die_right.png";

const std::string g_name_skill_wisp_fire_ball_left = "resource//Threat//Elemental wisp//Fire wisp//Projectile//fire_ball_left.png";
const std::string g_name_skill_wisp_fire_ball_right = "resource//Threat//Elemental wisp//Fire wisp//Projectile//fire_ball_right.png";

//Fairy
const std::string fairy_directory = "resource//NPC//Fairy Pixel Art//";
const std::string g_name_fairy_fly_left = fairy_directory + "192and128//Fairy_fly_left_20fr.png";
const std::string g_name_fairy_fly_right = fairy_directory + "192and128//Fairy_fly_right_20fr.png";
const std::string g_name_fairy_fly_forward = fairy_directory + "192and128//Fairy_fly_forward_20fr.png";
const std::string g_name_fairy_vanish_forward = fairy_directory + "192and128//Fairy_vanish_forward_20fr.png";
const std::string g_name_fairy_idle_forward = fairy_directory + "192and128//Fairy_idle_forward_1fr.png";

//Khai bao cac bien co ban
namespace SDLCommonFunction
{
   //Tim min, max cua 2 so nguyen
      int FindMin(const int& a, const int& b);
      int FindMax(const int& a, const int& b);
   //Khoi tao SDL
      bool Init();
   //Load img, set color key, set rect va luu duoi dang texture
      SDL_Texture* LoadTexture(const std::string& file_path, SDL_Renderer* des, SDL_Rect& rect,
                               int color_flag = SDL_FALSE, SDL_Color color = BLACK);
   //Load font text
      bool LoadFontText();
   //Load audio
      bool LoadAudio();
   //Kiem tra va cham giua 2 object
      bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
   //Kiem tra toa do cua 1 diem voi 1 rect_
      bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
   //Tao so nguyen ngau nhien trong khoang min, max
      int GenerateRandomNumber(const int& min_, const int& max_);
   //Tao. 1 menu don? gian?
      int CreateGameMenu(SDL_Texture* menu, TTF_Font* font, SDL_Renderer* des);
   //Tao. 1 game over screen don? gian?
      int CreateGameOver(TTF_Font* font, SDL_Renderer* des);
   //Don dep bo nho
      void Close();
}

struct Input
{
   int idle_; //Dung yen
   int left_; //Di chuyen sang phai
   int right_; //Di chuyen sang trai
   int up_; //Huong len tren
   int down_; //Ngoi xuong
   int jump_; //Nhay len
   int die_; //Chet
};

#endif
