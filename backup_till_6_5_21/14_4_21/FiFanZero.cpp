#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TextObject.h"

/**
! Luu y :
SDL_BlitSurface = SDL_RenderCopy
SDL_Flip = SDL_RenderPresent
**/

int main(int argc, char* argv[])
{
   //Khoi tao SDL
      if(!SDLCommonFunction::Init())
      {
         printf( "Failed to initialize!" );
         return 0;
      }

   //Khoi tao audio
      if(!SDLCommonFunction::LoadAudio())
      {
         printf( "Failed to load audio!");
         return 0;
      }

   //Khoi tao font chu
      if(!SDLCommonFunction::LoadFontText())
      {
         printf( "Failed to load font text");
         return 0;
      }

   bool is_run_screen = true;
   int bkgn_x = 0;
   SDL_Rect rect_bkgn;

   //Main loop flag
      bool is_quit = false;

   //Make PlayerPower
   PlayerPower player_power;
   player_power.Init();

   //Make TextObject
   TextObject mark_game;
   mark_game.SetColor(TextObject::WHITE_TEXT);

   TextObject time_game;
   time_game.SetColor(TextObject::WHITE_TEXT);

   //Load texture background 600
   //g_background2 = SDLCommonFunction::LoadImage("bg600.png");

   //Load texture background 4800
      g_background = SDLCommonFunction::LoadImage(g_name_back_ground);

      if(g_background == NULL)
      {
         printf("Failed to load background");
         return 0;
      }

   //Set texture flag
         bool ret;

   //Khai bao MainObject
         MainObject plane_object;
      //Load texture cua MainObject
         ret = plane_object.LoadImg(g_name_main_obj);
         if(!ret) {  return 0; }
      //Dat vi tri xuat hien ban dau cua MainObject
         plane_object.SetRect(POS_X_START_MAIN, POS_Y_START_MAIN);

   //Khai bao ExplosionObject
      //ExplosionObject khi MainObject no
         ExplosionObject exp_main;
         ret = exp_main.LoadImg(g_name_exp_main);
         exp_main.set_clip();
         if(!ret) {  return 0;  }

      //ExplosionObject khi ThreatObject no
         ExplosionObject exp_threat;
         ret = exp_threat.LoadImg(g_name_exp_threat);
         exp_threat.set_clip();
         if(!ret) {  return 0;  }

   //Khai bao nhieu ThreatObject
         ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
         for(int t = 0 ; t < NUM_THREATS ; ++t)
         {
            //Xu ly lan lan luot tung ThreatObject
               ThreatObject* p_threat = (p_threats + t);

               if(p_threat != NULL)
               {
                  //Load texture cua ThreatObject
                     ret = p_threat->LoadImg(g_name_threat_obj);
                     if(!ret) {
                        delete [] p_threats; //Ham nay chay ~ThreatObject()
                        SDLCommonFunction::Close();
                        return 0;
                     }

                  //Generate ngau nhien vi tri theo phuong y cua ThreatObject
                     int rand_y = SDLCommonFunction::MakeRandValue();
                  //Dat vi tri xuat hien ban dau cua ThreatObject, phuong y ngau nhien, phuong x theo thu tu lan luot
                     p_threat->SetRect(SCREEN_WIDTH + t*VAL_OFFSET_START_POST_THREAT, rand_y);
                  //Set van toc theo phuong x cua ThreatObject
                     p_threat->set_x_val(VELOCITY_THREAT);
                  //Tao ra 1 vien dan/1 threat
                     AmoObject* p_amo = new AmoObject();
                  //Khoi tao cac trang thai cua vien dan vua duoc tao ra
                     p_threat->InitAmo(p_amo);
               }
            }

      //Thiet lap so lan chet
      unsigned int die_number = 0;

      //Thiet lap diem so
      unsigned int mark_value = 0;

      //Thiet lap thoi gian game
      Uint32 time_value = 0;

      int ret_menu = SDLCommonFunction::ShowMenu(g_font_menu);
      if(ret_menu == 1) //1 la chi so exit
      {
         is_quit = true;
      }

      //Trong khi chuong trinh dang chay
      while(!is_quit)
      {
         //Xu ly event tren queue
         while(SDL_PollEvent(&g_event))
         {
            //Quit game
            if(g_event.type == SDL_QUIT )
            {
               is_quit = true;
               break;
            }

            plane_object.HandleInputAction(g_event);
         }

         //Clear screen
            SDL_RenderClear(g_renderer);


         //Lam background di chuyen
/**
         Cach 1
            bkgn_x -= 2;
         //Copy background 1
            rect_bkgn = {bkgn_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(g_renderer, g_background, NULL, &rect_bkgn);
         //Copy background 2
            rect_bkgn = {bkgn_x + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(g_renderer, g_background, NULL, &rect_bkgn);
            if(bkgn_x <= -SCREEN_WIDTH)
            {
                  bkgn_x = 0;
            }

**/

         //Cach 2
         if(is_run_screen == true)
         {
            bkgn_x -= SCREEN_VELOCITY;
            if(bkgn_x <= (SCREEN_WIDTH - BACKGROUND_WIDTH))
            {
               is_run_screen = false;
            }
            else
            {
               rect_bkgn = {bkgn_x, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
               SDL_RenderCopy(g_renderer, g_background, NULL, &rect_bkgn);
            }
         }
         else
         {
            rect_bkgn = {bkgn_x, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
            SDL_RenderCopy(g_renderer, g_background, NULL, &rect_bkgn);
         }

/**
            Improve cach 2
            if(is_run_screen == true)
            {
                  bkgn_x -= 2;
                  rect_bkgn = {bkgn_x, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
                  SDL_RenderCopy(g_renderer, g_background, NULL, &rect_bkgn);
                  if(bkgn_x <= -BACKGROUND_WIDTH)
                  {
                        is_run_screen = false;
                  }
                  else if(bkgn_x <= (SCREEN_WIDTH - BACKGROUND_WIDTH))
                  {
                        rect_bkgn = {bkgn_x + BACKGROUND_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                        SDL_RenderCopy(g_renderer, g_background2, NULL, &rect_bkgn);

                  }
            }
            else
            {
                  rect_bkgn = {bkgn_x + BACKGROUND_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
                  SDL_RenderCopy(g_renderer, g_background2, NULL, &rect_bkgn);
            }
**/


      //Show PlayerPower
            player_power.Render();

      //Xu ly MainObject
      //Xu ly di chuyen cua MainObject
            plane_object.HandleMove();
      //Copy MainObject ra man hinh
            plane_object.Show();
      //Trang thai cac vien dan hien co cua MainObject
            plane_object.MakeAmo();

      //Xu ly cac ThreatObject
            for (int tt = 0 ; tt < NUM_THREATS ; ++tt)
            {
               ThreatObject* p_threat = (p_threats + tt);
               if(p_threat != NULL)
               {
                  //Xu ly ThreatObject
                  //Xu ly di chuyen cua ThreatObject
                     p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                  //Copy ThreatObject ra man hinh
                     p_threat->Show();
                  //Trang thai cac vien dan hien co cua ThreatObject
                     p_threat->MakeAmo(SCREEN_WIDTH, SCREEN_HEIGHT);

                  //Set flag va cham giua cac vien dan cua Threats va Main
                  bool is_col_1 = false;
                  //Bang dan cua ThreatObject
                     std::vector<AmoObject*> amo_arr = p_threat->GetAmoList(); //amo_arr de phan biet voi amo_list
                     for(int am = 0 ; am < amo_arr.size() ; ++am)
                     {
                        //Vien dan cua ThreatObject
                        AmoObject* p_amo = amo_arr.at(am);
                        if(p_amo != NULL)
                        {
                           //Kiem tra va cham giua cac vien dan cua Threats va Main
                           is_col_1 = SDLCommonFunction::CheckCollision(plane_object.GetRect(), p_amo->GetRect());
                           if(is_col_1)
                           {
                              p_threat->ResetAmo(p_amo);
                              break;
                           }
                        }
                     }

                  //Kiem tra va cham giua Main va Threats
                  bool is_col_2 = SDLCommonFunction::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
                  if(is_col_1 || is_col_2)
                  {
                     //Thiet lap vu no xay ra khi va cham giua Main va Threat
                     for(int ex = 0 ; ex < 4 ; ++ex)
                     {
                        //Dat vi tri xay ra vu no, vu no tai tam cua may bay
                           int x_pos = plane_object.GetRect().x + plane_object.GetRect().w*0.5 - EXPLOSION_WIDTH*0.5;
                           int y_pos = plane_object.GetRect().y + plane_object.GetRect().h*0.5 - EXPLOSION_HEIGHT*0.5;

                        //Set frame cua vu no
                           exp_main.set_frame(ex);
                        //Set toa do cua vu no
                           exp_main.SetRect(x_pos, y_pos);
                        //Copy vu no vao renderer
                           exp_main.ShowEx();
                        //Thiet lap delay 0.005s giua cac frame
                           SDL_Delay(50);
                        //In ra vu no truoc khi chuong trinh dung
                           SDL_RenderPresent(g_renderer);
                     }
                        //Set audio vu no
                           Mix_PlayChannel(-1, g_sound_explosion_main, 0);

                        //Xu ly PlayerPower
                           die_number++;
                           if(die_number <= 2)
                           {
                              //Delay 1s
                              SDL_Delay(1000);
                              //Hoi sinh may bay
                              plane_object.SetRect(POS_X_START_MAIN, POS_Y_START_MAIN);
                              //Giam di 1 mang
                              player_power.Decrease();
                              //Copy hinh anh mang song con lai ra man hinh
                              player_power.Render();
                           }
                           else
                           {
                              //Hien 1 message box bao hieu tro choi ket thuc
                              if(MessageBox(NULL, "Game Over!", "Info", MB_OK) == IDOK)
                              {
                                 //Don dep
                                 delete [] p_threats; //Ham nay chay ~ThreatObject()
                                 SDLCommonFunction::Close();
                                 return 0;
                              }
                           }
                  }

                  //Bang dan cua MainObject
                  std::vector<AmoObject*> amo_list = plane_object.GetAmoList();
                  for(int im = 0 ; im < amo_list.size() ; ++im)
                  {
                     //Vien dan cua MainObject
                     AmoObject* p_amo = amo_list.at(im);
                     if(p_amo != NULL)
                     {
                        //Kiem tra va cham giua dan cua Main voi Threat
                        bool is_col = SDLCommonFunction::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
                        if(is_col)
                        {
                           //Cong them 1 diem/threat ban trung
                           mark_value++;

                           //Vu no xay ra khi va cham giua dan cua Main va Threats
                           for(int tx = 0 ; tx < 4 ; ++tx)
                           {
                              //Dat vi tri xay ra vu no, vu no tai tam cua ThreatObject
                                 int x_pos = p_threat->GetRect().x + p_threat->GetRect().w*0.5 - EXPLOSION_WIDTH*0.5;
                                 int y_pos = p_threat->GetRect().y + p_threat->GetRect().h*0.5 - EXPLOSION_HEIGHT*0.5;

                              //Set frame cua vu no
                                 exp_threat.set_frame(tx);
                              //Set toa do cua vu no
                                 exp_threat.SetRect(x_pos, y_pos);
                              //Copy vu no vao renderer
                                 exp_threat.ShowEx();

                              //Khong the render 4 frame cung 1 luc vi no se lam chuong trinh lag
                           }
                              //Reset lai vi tri cua Threat
                                 p_threat->Reset(SCREEN_WIDTH + tt*VAL_OFFSET_START_POST_THREAT);
                              //Xoa vien dan da ban trung Threat
                                 plane_object.RemoveAmo(im);
                              //Set audio vu no
                                 Mix_PlayChannel(-1, g_sound_explosion_threat, 0);

                        }

                     }

                  }

               }

            }

            //Xu ly time_game
            std::string str_time = "Time : ";
            time_value = SDL_GetTicks()/1000;
            std::string val_str_time = std::to_string(time_value);
            str_time += val_str_time;
            time_game.SetText(str_time);
            time_game.SetRect(SCREEN_WIDTH - 200, 10);
            time_game.CreateGameText(g_font_text);

            //Xu ly mark_game
            std::string val_str_mark = std::to_string(mark_value);
            std::string str_mark = "Mark : ";
            str_mark += val_str_mark;
            mark_game.SetText(str_mark);
            mark_game.SetRect(500, 10);
            mark_game.CreateGameText(g_font_text);

            //Tranh bug 1 vien dan/1 renderer/1 frame => Correct : sum dan/1 renderer/1 frame
            SDL_RenderPresent(g_renderer);
      }
      delete [] p_threats; //Ham nay chay ~ThreatObject()
      SDLCommonFunction::Close();
      return 0; //Ham nay giai tru bo nho cua ca MainObject()
}
