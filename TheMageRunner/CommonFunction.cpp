
#include "CommonFunction.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "ScreenEffect.h"

//Khoi tao cac bien toan cuc
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Event g_event;

//Khoi tao font text
TTF_Font* g_font_text = NULL;
TTF_Font* g_font_text_2 = NULL;

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
                                                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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
SDL_Texture* SDLCommonFunction::LoadTexture(const std::string& file_path, SDL_Renderer* des, SDL_Rect& rect,
                                            int color_flag, SDL_Color color)
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

   g_font_text_2 = TTF_OpenFont( g_name_font_text.c_str(), FONT_SIZE_2);

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

int SDLCommonFunction::CreateGameMenu(SDL_Texture* menu, TTF_Font* font, SDL_Renderer* des)
{
   const int kMenuItemNum = 2;
   TextObject text_menu[kMenuItemNum];

   text_menu[0].SetTextType("Play Game");
   text_menu[0].SetColor(BLACK);
   text_menu[0].SetPosXY(1200, 1180);

   text_menu[1].SetTextType("Exit");
   text_menu[1].SetColor(BLACK);
   text_menu[1].SetPosXY(900,280);

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
         text_menu[i].LoadTextureTextType(font, des);
         if(i == 0) //Play Game
         {
             text_menu[i].RenderText(des, nullptr, -40);
         }
         else
         {
             text_menu[i].RenderText(des, nullptr, 37);
         }
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
                  if(CheckFocusWithRect(x_mouse, y_mouse, text_menu[i].GetRectType()))
                  {
                     //Neu truoc do, nam ben trong, bo qua
                     //Neu truoc do, nam ben ngoai
                     if(selected[i] == false)
                     {
                        //Set lai trang thai - nam trong
                        selected[i] = 1;
                        text_menu[i].SetColor(RED);
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
                        text_menu[i].SetColor(BLACK);
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
               if(CheckFocusWithRect(x_mouse, y_mouse, text_menu[i].GetRectType()))
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

int SDLCommonFunction::CreateGameOver(TTF_Font* font, SDL_Renderer* des)
{
    ScreenEffect::BlurScreenNoClick(des);

    const int kGameOverItemNum = 3;
    TextObject text_game_over[kGameOverItemNum];

    text_game_over[0].SetTextType("Retry Again");
    text_game_over[0].SetColor(BLACK);
    text_game_over[0].SetPosXY(1000, 800);

    text_game_over[1].SetTextType("Exit to Menu");
    text_game_over[1].SetColor(BLACK);
    text_game_over[1].SetPosXY(1000, 900);

    text_game_over[2].SetTextType("Exit to Windows");
    text_game_over[2].SetColor(BLACK);
    text_game_over[2].SetPosXY(1000, 1000);

   //Trang thai cua tung nut
   bool selected[kGameOverItemNum] = {0, 0};

   SDL_Event m_event;

   //Toa do cua con tro chuot
   int x_mouse = 0;
   int y_mouse = 0;

    BaseObject skull;
    skull.LoadImg(g_name_skull.c_str(), des, SDL_FALSE, WHITE);
    skull.SetRect((SCREEN_WIDTH - skull.GetRect().w)/2, (SCREEN_HEIGHT - skull.GetRect().h)/2 - 250);

    TextObject text_gover;
    text_gover.SetTextType("Game Over! Ha Ha Ha !");
    text_gover.SetColor(BLACK);
    text_gover.SetPosXY(880, 650);
    text_gover.LoadTextureTextType(font, des);

    SDL_Rect halv_screen = HALVED_SCREEN;
    SDL_Color color_data = {180, 180, 180};
    ScreenEffect::RenderRectangle(des, halv_screen, color_data);

    SDL_Rect outline_halv =  {halv_screen.x + 1, halv_screen.y + 1, halv_screen.w - 1, halv_screen.h - 1};
    ScreenEffect::RenderOutline(des, outline_halv, WHITE);

    skull.Render(des);
    text_gover.RenderText(des);

    while(true)
    {
        //In ra cac nut cua menu voi font truyen vao
      for(int i = 0 ; i < kGameOverItemNum ; ++i)
      {
         text_game_over[i].LoadTextureTextType(font, des);
         text_game_over[i].RenderText(des);
      }

      //Xu ly input cua chuot
      while(SDL_PollEvent(&m_event))
      {
         switch(m_event.type)
         {
         case SDL_QUIT:
            return 2;

         case SDL_MOUSEMOTION :
            {
               //Lay toa do cua con tro chuot
               x_mouse = m_event.motion.x;
               y_mouse = m_event.motion.y;

               for(int i = 0 ; i < kGameOverItemNum ; ++i)
               {
                  //Neu con tro chuot nam ben trong
                  if(CheckFocusWithRect(x_mouse, y_mouse, text_game_over[i].GetRectType()))
                  {
                     //Neu truoc do, nam ben trong, bo qua
                     //Neu truoc do, nam ben ngoai
                     if(selected[i] == false)
                     {
                        //Set lai trang thai - nam trong
                        selected[i] = 1;
                        text_game_over[i].SetColor(RED);
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
                        text_game_over[i].SetColor(BLACK);
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

            for(int i = 0 ; i < kGameOverItemNum ; ++i)
            {
               if(CheckFocusWithRect(x_mouse, y_mouse, text_game_over[i].GetRectType()))
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
