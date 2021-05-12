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

//Window
const int SCREEN_WIDTH  = 2560;
const int SCREEN_HEIGHT = 1536;
const int SCREEN_FPS = 25;

//Color key surface
const SDL_Color BLACK = {0, 0, 0};
const SDL_Color WHITE = {0xFF, 0xFF, 0xFF};
const SDL_Color DEMO = {167, 178, 180};
const int RENDER_DRAW_COLOR = 0xFF;

//Rect
const SDL_Rect TOTAL_SCREEN = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//Font
const int FONT_SIZE = 30;

//Main
const int PLAYER_MAX_FALL_SPEED  = 10;
const int PLAYER_GRAVITY_VELOCITY = 1;
const int PLAYER_VELOCITY = 20;
const int PLAYER_JUMP_VAL = 20;
const int PLAYER_FRAME_NUM = 16;
const int PLAYER_START_FALL_Y_POS = 700;
const int PLAYER_TOTAL_LIVES = 3;

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
const int THREAT_TOTAL_NUM_EACH_TYPE = 1;
const int THREAT_START_FALL_Y_POS = 700;

const int THREAT_BULLET_MARGINS_X_VAL = 30;
const int THREAT_BULLET_MARGINS_Y_VAL = 30;
const int THREAT_BULLET_VELOCITY = 15;
const int THREAT_BULLET_MAX_RANGED = 128*4;

//Text
const int NORMAL_TYPING_DELAY_TIME = 200;
const int SKIP_TYPING_DELAY_TIME = 50;

//Cac bien do hoa
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Event g_event;

//Cac bien font text
extern TTF_Font* g_font_text;

//Cac tai nguyen cua game
const std::string game_name = "TheMageRunner";
const std::string g_name_back_ground_1 = "resource//Tilemap//bk_2560x1536//bg1_2560x1536.png";
const std::string g_name_back_ground_2 = "resource//Tilemap//bk_2560x1536//bg2_2560x1536.png";
const std::string g_name_back_ground_3 = "resource//Tilemap//bk_2560x1536//bg3_2560x1536.png";
const std::string g_name_font_text = "resource//Font//dlxfont_.ttf";
const std::string g_name_map_tile = "resource//Tilemap//map03.txt";
const std::string g_name_tile_directory = "resource//Tilemap//tile_128x128//";

//Main
const std::string g_name_icon_main_live = "resource//Main//Real wizard//Tile//128x128//Icon//Live_icon_1fr.png";
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

//Threat
const std::string g_name_threat_fire_wisp_move_left = "resource//Threat//Elemental wisp//Fire wisp//128x128//move_left.png";
const std::string g_name_threat_fire_wisp_move_right = "resource//Threat//Elemental wisp//Fire wisp//128x128//move_right.png";
const std::string g_name_threat_fire_wisp_die_left = "resource//Threat//Elemental wisp//Fire wisp//128x128//die_left.png";
const std::string g_name_threat_fire_wisp_die_right = "resource//Threat//Elemental wisp//Fire wisp//128x128//die_right.png";

const std::string g_name_skill_wisp_fire_ball_left = "resource//Threat//Elemental wisp//Fire wisp//Projectile//fire_ball_left.png";
const std::string g_name_skill_wisp_fire_ball_right = "resource//Threat//Elemental wisp//Fire wisp//Projectile//fire_ball_right.png";

//Draft
const std::string g_name_exp_main = "exp_main.png";
const std::string g_name_bullet_main_laser = "laser.png";
const std::string g_name_bullet_main_sphere = "sphere.png";
const std::string g_name_audio_bullet_main_laser = "Laser.wav";
const std::string g_name_audio_bullet_main_sphere = "Sphere.wav";
const std::string g_name_audio_exp_main = "exp_main.wav";

const std::string g_name_threat_obj = "af1.png";
const std::string g_name_exp_threat = "exp_threat.png";
const std::string g_name_bullet_threat = "sphere2.png";
const std::string g_name_audio_bullet_threat = "";
const std::string g_name_audio_exp_threat = "exp_threat.wav";

const std::string g_name_menu = "start_menu.png";
const std::string g_name_life = "Heart.png";

//Khai bao cac bien co ban
namespace SDLCommonFunction
{
   //Tim min, max cua 2 so nguyen
      int FindMin(const int& a, const int& b);
      int FindMax(const int& a, const int& b);
   //Khoi tao SDL
      bool Init();
   //Load img, set color key, set rect va luu duoi dang texture
      SDL_Texture* LoadTexture(const std::string& file_path, SDL_Renderer* des,
                               SDL_Rect& rect, const int& color_flag, const SDL_Color& color);
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
   //Don dep bo nho
      void Close();
}

#define MAX_TILES 50 //tong so tile su dung trong tile map
#define TILE_SIZE 128 //kich thuoc 1 tile la 128x128
#define EPSILON 1 //Sai so de xu ly va cham tile map

//width co 100 o, height co 12 o
#define MAX_MAP_X 100
#define MAX_MAP_Y 12

//Chi so tile rong~ la 0
#define BLANK_TILE 0
//Chi so tien vang la 4
#define STATE_MONEY 51
#define SPELL_BOOK 25
#define SPELL_BOOK_FRAME 4

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

//Khai bao kieu du lieu Map
struct Map
{
   //Luu vi tri mep trai ban do
   int start_x_;
   int start_y_;
   int max_x_; //So luong o toi da theo phuong x
   int max_y_; //So luong o toi da theo phuong y
   int tile[MAX_MAP_Y][MAX_MAP_X]; //Gia tri cua tung o tile theo toa do[y][x]
   std::string file_name_; //Ten cua file .dat tile map
};

#endif
