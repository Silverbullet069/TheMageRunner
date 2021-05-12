#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>

//Window
const int SCREEN_WIDTH  = 2560;
const int SCREEN_HEIGHT = 1536;
const int SCREEN_FPS = 30;
//Black
const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 0;
const int COLOR_KEY_B = 0;
const int RENDER_DRAW_COLOR = 0xFF;

//Cac bien do hoa
extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Event g_event;

//Cac tai nguyen cua game
const std::string game_name = "TestTile";
const std::string g_name_back_ground_1 = "Tile_numbering//bk_2560x1536//bg1_2560x1536.png";
const std::string g_name_back_ground_2 = "Tile_numbering//bk_2560x1536//bg2_2560x1536.png";
const std::string g_name_back_ground_3 = "Tile_numbering//bk_2560x1536//bg3_2560x1536.png";

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
   //Load img va set rect cua img do
      SDL_Rect LoadRect(const std::string file_path);
   //Kiem tra va cham giua 2 object
      bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
   //Kiem tra toa do cua 1 diem voi 1 rect_
      bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
   //Don dep bo nho
      void Close();
}


#define TILE_SIZE 128 //kich thuoc 1 tile la 128x128
#define EPSILON 1 //Sai so de xu ly va cham tile map

//width co 10 o, height co 10 o
#define MAX_MAP_X 100
#define MAX_MAP_Y 12

struct Input
{
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
