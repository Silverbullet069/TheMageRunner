
#include <vector>
#include "CommonFunction.h"
#include "BaseObject.h"

//Khoi tao cac bien toan cuc
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Event g_event;

//Khoi tao font text
TTF_Font* g_font_text = NULL;

//Dinh nghia ham tim max min cua 2 so nguyen
int SDLCommonFunction::FindMin(const int& a, const int& b) {if(a<b) return a; return b;}
int SDLCommonFunction::FindMax(const int& a, const int& b) {if(a>b) return a; return b;}
int SDLCommonFunction::GenerateRandomNumber(const int& min_, const int& max_) { return min_ + rand() % (max_ + 1 - min_); }

//Dinh nghia ham khoi tao SDL
bool SDLCommonFunction::Init()
{
   //Tao flag khoi tao
   bool success = true;

   //Khoi tao SDL
   if (SDL_Init(SDL_INIT_VIDEO) < 0) // Co the dung SDL_INIT_EVERYTHING < 0
   {
      printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
      success = false;
   }
   else
   {
      //Texture filtering chuyen thanh duong thang
      if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
      {
         printf( "Warning: Linear texture filtering not enabled!" );
      }

      //Khoi tao window o bien global
      g_window = SDL_CreateWindow(game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

      //Khoi tao window khong thanh
      if(g_window == NULL)
      {
         printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
         success = false;
      }
      else
      {
         //Tao renderer o bien global, su dung GPU de tang toc va VSYNC de dong bo voi FPS cua man hinh
         g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

         //Khoi tao renderer khong thanh
         if(g_renderer == NULL)
         {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
         }
         else
         {
            //Khoi tao mau cho renderer
            SDL_SetRenderDrawColor( g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR ); //white

				//Khoi tao load anh PNG
				int imgFlagsPNG = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlagsPNG ) & imgFlagsPNG ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

            //Khoi tao font
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
         }
      }
   }

   return success;
}

//Dinh nghia ham load anh (chung cho toan bo chuong trinh)
//Khong can dinh nghia bool, bool cho ham ben trong BaseObject
SDL_Texture* SDLCommonFunction::LoadTexture(const std::string& file_path, SDL_Renderer* des,
                                           SDL_Rect& rect, const int& color_flag, const SDL_Color& color)
{
   //Khoi tao texture rong~
   SDL_Texture* new_texture = NULL;

   //Load image vao surface tai 1 dia chi cu the
   SDL_Surface* loaded_surface = IMG_Load(file_path.c_str());

   //Neu surface load khong duoc
   if(loaded_surface == NULL)
   {
      printf( "Unable to load image %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError() );
   }
   else
   {
      //Color key
      SDL_SetColorKey(loaded_surface, color_flag, SDL_MapRGB(loaded_surface->format, color.r, color.g, color.b));

      new_texture = SDL_CreateTextureFromSurface(des, loaded_surface);

      if(new_texture == NULL)
      {
         printf( "Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError() );
      }
      else
      {
         rect.w = loaded_surface->w;
         rect.h = loaded_surface->h;
      }
      //Huy surface cu
         SDL_FreeSurface(loaded_surface);
   }

   return new_texture;
}

bool SDLCommonFunction::LoadFontText()
{
   bool success = true;

   g_font_text = TTF_OpenFont( g_name_font_text.c_str(), FONT_SIZE);
   if(g_font_text == NULL)
   {
      printf( "Failed to load font game! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
   }

   return success;
}

bool SDLCommonFunction::LoadAudio()
{
   //
}

bool SDLCommonFunction::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
      int left_a = object1.x;
      int right_a = object1.x + object1.w;
      int top_a = object1.y;
      int bottom_a = object1.y + object1.h;

      int left_b = object2.x;
      int right_b = object2.x + object2.w;
      int top_b = object2.y;
      int bottom_b = object2.y + object2.h;

      int left = SDLCommonFunction::FindMax(left_a, left_b);
      int right = SDLCommonFunction::FindMin(right_a, right_b);
      int top = SDLCommonFunction::FindMax(top_a, top_b);
      int bottom = SDLCommonFunction::FindMin(bottom_a, bottom_b);

      if( (right - left <= 0) || (bottom - top <= 0) )
            return false;
      return true;
}

bool SDLCommonFunction::CheckFocusWithRect(const int& x, const int &y, const SDL_Rect& rect)
{
   if( (rect.x <= x && x <= rect.x + rect.w) && ( rect.y <= y && y <= rect.y + rect.h ))
      return true;
   return false;
}

void SDLCommonFunction::Close()
{
   //Don dep window, renderer, background
   SDL_DestroyWindow(g_window);
   SDL_DestroyRenderer(g_renderer);
	g_window = NULL;
	g_renderer = NULL;

	//Tat chuong trinh ngam va chuong trinh chinh cua SDL
	IMG_Quit();
	SDL_Quit();
}
