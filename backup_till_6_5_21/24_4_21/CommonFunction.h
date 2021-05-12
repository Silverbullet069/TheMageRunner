#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <vector>

//Window
const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_FPS = 30;

//Color key surface
const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 0;
const int COLOR_KEY_B = 0;//black
const int RENDER_DRAW_COLOR = 0xFF;

//Font
const int FONT_SIZE = 15;

//Main
const int PLAYER_MAX_FALL_SPEED  = 10;
const int PLAYER_GRAVITY_VELOCITY = 1;
const int PLAYER_VELOCITY = 8;
const int PLAYER_JUMP_VAL = 20;
const int PLAYER_FRAME_NUM = 8;
const int DISTANCE_FRAME_MOVE = 100; //Thu cong
const int DISTANCE_FRAME_IDLE = 110;

//Bullet
const int BULLET_VELOCITY_X_VAL = 25;
const int BULLET_VELOCITY_Y_VAL = 25;
const int BULLET_MARGINS_X_VAL = 20;
const int BULLET_MARGINS_Y_VAL = 50;


//Cac bien do hoa
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Event g_event;

//Cac bien font text
extern TTF_Font* g_font_text;

//Bien tru~ object texture truoc khi su dung ham SDLCommonFunction::GetObject
extern SDL_Texture* g_tmp_texture;

//Cac tai nguyen cua game
const std::string game_name = "TheMageRunner";
const std::string g_name_back_ground = "background.png";
const std::string g_name_font_text = "dlxfont_.ttf";

//Main
const std::string g_name_main_obj_move_left = "resource//Main//Evil Wizard//Sprites//move_left.png";
const std::string g_name_main_obj_move_right = "resource//Main//Evil Wizard//Sprites//move_right.png";
const std::string g_name_main_obj_idle = "resource//Main//Evil Wizard//Sprites//idle.png";
const std::string g_name_skll_main_fire_ball = "resource//Main//Fireball//FB004.png";
const std::string g_name_skill_main_ice_shard = "resource//Main//Ice Shard//I5050-7.png";

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
   //Load img va luu duoi dang surface
      SDL_Surface* LoadImage(const std::string file_path);
   //Load img va luu duoi dang texture
      SDL_Texture* LoadTexture(const std::string file_path, SDL_Renderer* des);
   //Load font text
      bool LoadFontText();
   //Load audio
      bool LoadAudio();
   //Load img va set rect cua img do
      SDL_Rect LoadRect(const std::string file_path);
   //Kiem tra va cham giua 2 object
      bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
   //Kiem tra toa do cua 1 diem voi 1 rect_
      bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
   //Don dep bo nho
      void Close();
}


#define TILE_SIZE 64 //kich thuoc 1 tile la 64x64
#define EPSILON 1 //Sai so de xu ly va cham tile map
#define EPSILON_Y 6 // Sai so rieng de de xu ly va cham mat dat

//width co 400 o, height co 10 o
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

//Chi so tile rong~ la 0
#define BLANK_TILE 0
//Chi so tien vang la 4
#define STATE_MONEY 4

struct Input
{
   int idle_; //Dung yen
   int left_; //Di chuyen sang phai
   int right_; //Di chuyen sang trai
   int up_; //Huong len tren
   int down_; //Ngoi xuong
   int jump_; //Nhay len
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
