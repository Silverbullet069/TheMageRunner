#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <windows.h>

//Window
const int BACKGROUND_WIDTH   = 4800;
const int BACKGROUND_HEIGHT  = 600;
const int UNDER_LIMIT        = 100;
const int SCREEN_WIDTH       = 1200;
const int SCREEN_HEIGHT      = 600;
const int SCREEN_VELOCITY    = 2;

//Main
const int POS_X_START_MAIN      = 100;
const int POS_Y_START_MAIN      = 200;
const int VELOCITY_MAIN         = 10;
const int VELOCITY_BULLET_MAIN  = 20;

//Threat
const int NUM_THREATS             = 3;
const int VELOCITY_THREAT         = 5;
const int VELOCITY_BULLET_THREAT  = 10;
const int VAL_OFFSET_START_POST_THREAT = 400;

//Cac bien do hoa
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Texture* g_background;
//extern SDL_Texture* g_background_2;
extern SDL_Texture* g_menu;
extern SDL_Event g_event;
extern TTF_Font* g_font_text;
extern TTF_Font* g_font_menu;

//Cac bien audio
extern Mix_Chunk* g_sound_bullet_laser;
extern Mix_Chunk* g_sound_bullet_sphere;
extern Mix_Chunk* g_sound_explosion_main;
extern Mix_Chunk* g_sound_explosion_threat;

//Cac tai nguyen cua game
const std::string game_name = "FiFanZero";
const std::string g_name_back_ground = "bg4800.png";
const std::string g_name_main_obj = "plane_fly.png";
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

const std::string g_name_font_text = "lazy.ttf";

//Khai bao cac bien co ban
namespace SDLCommonFunction
{
   //Tim min, max cua 2 so nguyen
      int FindMin(const int& a, const int& b);
      int FindMax(const int& a, const int& b);
   //Khoi tao SDL
      bool Init();
   //Load img va luu duoi dang texture
      SDL_Texture* LoadImage(const std::string file_path);
   //Load width va height cua mot Image
      SDL_Rect LoadWidthHeight(const std::string file_path);
   //Load audio
      bool LoadAudio();
   //Load text
      bool LoadFontText();
   //Copy texture vao renderer va in ra man hinh
      void ShowTexture(SDL_Texture* final_texture = NULL);
   //Set rand value
      int MakeRandValue(const int& div_val = 400);
   //Kiem tra va cham giua 2 object
      bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
   //Kiem tra toa do cua 1 diem voi 1 rect_
      bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
   //Tao Menu
      int ShowMenu(TTF_Font* font); //font chu cac nut trong Menu
   //Don dep bo nho
      void Close();
}

#endif
