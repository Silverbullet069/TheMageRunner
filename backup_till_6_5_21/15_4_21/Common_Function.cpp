#include "Common_Function.h"
#include "BaseObject.h"
#include "TextObject.h" //Chi khoi tao trong file cpp

//Khoi tao cac bien toan cuc
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Texture* g_background = NULL;
//SDL_Texture* g_background2 = NULL;
SDL_Texture* g_menu = NULL;
SDL_Event g_event;
TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;

//Khoi tao cac bien audio
Mix_Chunk* g_sound_bullet_laser = NULL;
Mix_Chunk* g_sound_bullet_sphere = NULL;
Mix_Chunk* g_sound_explosion_main = NULL;
Mix_Chunk* g_sound_explosion_threat = NULL;

//Dinh nghia ham tim max min cua 2 so nguyen
int SDLCommonFunction::FindMin(const int& a, const int& b) {if(a<b) return a; return b;}
int SDLCommonFunction::FindMax(const int& a, const int& b) {if(a>b) return a; return b;}

//Dinh nghia ham khoi tao SDL
bool SDLCommonFunction::Init()
{
   //Tao flag khoi tao
   bool success = true;

   //Khoi tao SDL
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) // Co the dung SDL_INIT_EVERYTHING < 0
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
                                                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

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

				//Khoi tao load anh JPG
				int imgFlagsJPG = IMG_INIT_JPG;
				if( !( IMG_Init( imgFlagsJPG ) & imgFlagsJPG ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Khoi tao audio
				if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 )
            {
               printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
SDL_Surface* SDLCommonFunction::LoadImage(const std::string file_path)
{
   //Load image vao surface tai 1 dia chi cu the
   SDL_Surface* loaded_surface = IMG_Load(file_path.c_str());

   //Neu surface load khong duoc
   if(loaded_surface == NULL)
   {
      printf( "Unable to load image %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError() );
   }
   else
   {
      //Xoa phong
		SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) ); //cyan
   }

   return loaded_surface;
}

SDL_Texture* SDLCommonFunction::LoadTexture(const std::string file_path, SDL_Renderer* des)
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
      SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
      new_texture = SDL_CreateTextureFromSurface(des, loaded_surface);
      if(new_texture == NULL)
      {
         printf( "Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError() );
      }
      //Viet them ham lay width va height o day
      //Huy surface cu
         SDL_FreeSurface(loaded_surface);
   }

   return new_texture;
}

bool SDLCommonFunction::LoadAudio()
{
   bool success = true;

   g_sound_bullet_laser = Mix_LoadWAV(g_name_audio_bullet_main_laser.c_str());
   if(g_sound_bullet_laser == NULL)
   {
      printf( "Failed to load laser bullet sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
      success = false;
   }

   g_sound_bullet_sphere = Mix_LoadWAV(g_name_audio_bullet_main_sphere.c_str());
   if(g_sound_bullet_laser == NULL)
   {
      printf( "Failed to load sphere bullet sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
      success = false;
   }

   g_sound_explosion_main = Mix_LoadWAV(g_name_audio_exp_main.c_str());
   if(g_sound_explosion_main == NULL)
   {
      printf( "Failed to load main explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
      success = false;
   }

   g_sound_explosion_threat = Mix_LoadWAV(g_name_audio_exp_threat.c_str());
   if(g_sound_explosion_threat == NULL)
   {
      printf( "Failed to load threat explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
      success = false;
   }

   return success;
}

bool SDLCommonFunction::LoadFontText()
{
   bool success = true;
   g_font_text = TTF_OpenFont( g_name_font_text.c_str(), 20 );
   if(g_font_text == NULL)
   {
      printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
   }

   g_font_menu = TTF_OpenFont( g_name_font_text.c_str(), 40);
   if(g_font_menu == NULL)
   {
      printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
   }

   return success;
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

int SDLCommonFunction::ShowMenu(SDL_Texture* menu, TTF_Font* font, SDL_Renderer* des)
{
   const int kMenuItemNum = 2;
   SDL_Rect pos_arr[kMenuItemNum];
   pos_arr[0].x = 200;
   pos_arr[0].y = 400;
   pos_arr[1].x = 200;
   pos_arr[1].y = 500;

   TextObject text_menu[kMenuItemNum];

   text_menu[0].SetText("Play Game");
   text_menu[0].SetColor(TextObject::BLACK_TEXT);
   text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

   text_menu[1].SetText("Exit");
   text_menu[1].SetColor(TextObject::BLACK_TEXT);
   text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

   //Trang thai cua tung nut
   bool selected[kMenuItemNum] = {0, 0};
   SDL_Event m_event;
   //Toa do cua con tro chuot
   int x_mouse = 0;
   int y_mouse = 0;

   while(true)
   {
      SDL_RenderCopy(des, menu, NULL, NULL);

      //In ra cac nut cua menu voi font truyen vao
      for(int i = 0 ; i < kMenuItemNum ; ++i)
      {
         text_menu[i].CreateGameText(font, des);
      }

      //Xu ly input cua chuot
      while(SDL_PollEvent(&m_event))
      {
         switch(m_event.type)
         {
         case SDL_QUIT:
            return 1;

         case SDL_MOUSEMOTION :
            {
               //Lay toa do cua con tro chuot
               x_mouse = m_event.motion.x;
               y_mouse = m_event.motion.y;

               for(int i = 0 ; i < kMenuItemNum ; ++i)
               {
                  //Neu con tro chuot nam ben trong
                  if(CheckFocusWithRect(x_mouse, y_mouse, text_menu[i].GetRect()))
                  {
                     //Neu truoc do, nam ben trong, bo qua
                     //Neu truoc do, nam ben ngoai
                     if(selected[i] == false)
                     {
                        //Set lai trang thai - nam trong
                        selected[i] = 1;
                        text_menu[i].SetColor(TextObject::RED_TEXT);
                     }
                  }
                  else //con tro chuot nam ben ngoai
                  {
                     //Neu truoc do nam ben ngoai, bo qua
                     //Neu truoc do nam ben trong
                     if(selected[i] == true)
                     {
                        //Set lai trang thai - nam ngoai
                        selected[i] = 0;
                        text_menu[i].SetColor(TextObject::BLACK_TEXT);
                     }
                  }
               }
            }
            break;

         case SDL_MOUSEBUTTONDOWN :
         {
            //Lay toa do cua con tro chuot
            x_mouse = m_event.motion.x;
            y_mouse = m_event.motion.y;

            for(int i = 0 ; i < kMenuItemNum ; ++i)
            {
               if(CheckFocusWithRect(x_mouse, y_mouse, text_menu[i].GetRect()))
               {
                  return i; //Return nut
               }
            }
         }

         case SDL_KEYDOWN :
            if(m_event.key.keysym.sym == SDLK_ESCAPE)
            {
               return 1;
            }
         default:
            break;
         }
      }
      SDL_RenderPresent(des); // Update lien tuc Menu
   }
   return 1;
}

int SDLCommonFunction::MakeRandValue(const int& div_val /*400*/)
{
  int rand_y = rand()%div_val;
  if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT)
  {
    rand_y = SCREEN_HEIGHT*0.3;
  }
  return rand_y;
}

void SDLCommonFunction::Close()
{
   //Don dep audio
   Mix_FreeChunk(g_sound_bullet_laser);
   Mix_FreeChunk(g_sound_bullet_sphere);
   Mix_FreeChunk(g_sound_explosion_main);
   Mix_FreeChunk(g_sound_explosion_threat);
   g_sound_bullet_laser = NULL;
   g_sound_bullet_sphere = NULL;
   g_sound_explosion_main = NULL;
   g_sound_explosion_threat = NULL;

   //Don dep window, renderer, background
   SDL_DestroyWindow(g_window);
   SDL_DestroyRenderer(g_renderer);
	g_window = NULL;
	g_renderer = NULL;

	//Tat chuong trinh ngam va chuong trinh chinh cua SDL
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

/**
CheckCollision :

      // Case 1: size object 1 < size object 2
      if (left_a > left_b && left_a < right_b)
      {
            if (top_a > top_b && top_a < bottom_b)
            {
                  return true;
            }
      }

      if (left_a > left_b && left_a < right_b)
      {
            if (bottom_a > top_b && bottom_a < bottom_b)
            {
                  return true;
            }
      }

      if (right_a > left_b && right_a < right_b)
      {
            if (top_a > top_b && top_a < bottom_b)
            {
                  return true;
            }
      }

      if (right_a > left_b && right_a < right_b)
      {
            if (bottom_a > top_b && bottom_a < bottom_b)
            {
                  return true;
            }
      }

      // Case 2: size object 1 < size object 2
      if (left_b > left_a && left_b < right_a)
      {
            if (top_b > top_a && top_b < bottom_a)
            {
                  return true;
            }
      }

      if (left_b > left_a && left_b < right_a)
      {
            if (bottom_b > top_a && bottom_b < bottom_a)
            {
                  return true;
            }
      }

      if (right_b > left_a && right_b < right_a)
      {
            if (top_b > top_a && top_b < bottom_a)
            {
                  return true;
            }
      }

      if (right_b > left_a && right_b < right_a)
      {
            if (bottom_b > top_a && bottom_b < bottom_a)
            {
                  return true;
            }
      }

      // Case 3: size object 1 = size object 2
      if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
      {
            return true;
      }

      return false;
**/
