#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "ImpTimer.h"

int main(int argc, char* argv[])
{
   //Khoi tao Timer
      ImpTimer fps_timer;

   //Khoi tao SDL
      if(!SDLCommonFunction::Init())
      {
         printf( "Failed to initialize!" );
         return 0;
      }

   //SET MAIN LOOP FLAG
      bool is_quit = false;

   //Make BaseObject
      BaseObject back_ground_1;
      BaseObject back_ground_2;
      BaseObject back_ground_3;

   //SET LOADING FLAG
      bool ret;

   //Khai bao BaseObject
      ret = back_ground_1.LoadImg(g_name_back_ground_1, g_renderer);
      if(!ret)  { printf("Failed to load background 1!"); return 0;}

      ret = back_ground_2.LoadImg(g_name_back_ground_2, g_renderer);
      if(!ret)  { printf("Failed to load background 2!"); return 0;}

      ret = back_ground_3.LoadImg(g_name_back_ground_3, g_renderer);
      if(!ret)  { printf("Failed to load background 3!"); return 0;}

   //Khai bao GameMap
      GameMap game_map;
      game_map.LoadMap("map03.txt");
      game_map.LoadTiles(g_renderer);

   //Trong khi chuong trinh dang chay
      while(!is_quit)
      {
         //Bat dau chay dong ho
         fps_timer.start();

         //Xu ly event tren queue
         while(SDL_PollEvent(&g_event))
         {
            //Quit game
            if(g_event.type == SDL_QUIT )
            {
               is_quit = true;
               break;
            }

         }

      //Clear screen
         SDL_RenderClear(g_renderer);

      //In background ra truoc
         back_ground_3.Render(g_renderer);
         back_ground_2.Render(g_renderer);
         back_ground_1.Render(g_renderer);

      //Xu ly tile map
         game_map.DrawMap(g_renderer); //Ve lai game_map

      //In ra man hinh
         SDL_RenderPresent(g_renderer);

      //Thiet ke FPS thu cong
         int real_imp_time = fps_timer.get_ticks();
         int time_one_frame = 1000/SCREEN_FPS;
         if (real_imp_time < time_one_frame)
         {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
               SDL_Delay(delay_time);
         }
      }

      SDLCommonFunction::Close();

      return 0; //Ham nay giai tru bo nho cua ca MainObject()
}
