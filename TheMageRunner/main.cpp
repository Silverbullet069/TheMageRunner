#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include "ExpObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "ScreenEffect.h"
#include "BossObject.h"
#include "TypingScene.h"
#include "FairyObject.h"
#include "ElementaryFunctions.h"

//Khoi tao cac threats
std::vector<ThreatObject*> MakeThreatList()
{
   std::vector<ThreatObject*> list_threats;

   ThreatObject* fire_wisp = new ThreatObject[THREAT_TOTAL_NUM_EACH_TYPE];

   for(int i = 0 ; i < THREAT_TOTAL_NUM_EACH_TYPE ; ++i)
   {
      ThreatObject* p_threat = (fire_wisp + i);
      if(p_threat != NULL)
      {
         p_threat->LoadAllThreatAction(g_renderer);
         p_threat->set_clips();
         p_threat->set_type_move(ThreatObject::MOVE_LEFT);
         p_threat->set_type_element(ThreatObject::FIRE);

         //Set vi tri xuat hien tren tile map cho ke thu (ngau nhien)
         //p_threat->set_x_pos(SDLCommonFunction::GenerateRandomNumber(1, TILE_SIZE*MAX_MAP_X));

         if(i == 0)
         {
             p_threat->set_x_pos(3500); //28*128
             p_threat->set_y_pos(896);
         }
         else
         {
             p_threat->set_x_pos(5120); //40*128
             p_threat->set_y_pos(THREAT_START_FALL_Y_POS);
         }

         int pos1 = p_threat->get_x_pos() - THREAT_MAX_PATROL;
         int pos2 = p_threat->get_x_pos() + THREAT_MAX_PATROL;
         p_threat->SetAnimationPos(pos1, pos2);

         //Tao ra 1 vien dan
         BulletObject* p_bullet = new BulletObject();
         p_bullet->set_bullet_type(BulletObject::WISP_FIRE_BALL_LEFT);
         p_threat->InitBullet(p_bullet, g_renderer);

         list_threats.push_back(p_threat);
      }
   }

   return list_threats;
}

int main(int argc, char* argv[])
{
   //Khoi tao Timer
      ImpTimer fps_timer;

   //Init SDL
      if(!SDLCommonFunction::Init())
      {
         printf( "Failed to initialize!" );
         return 0;
      }
      if(!SDLCommonFunction::LoadFontText())
      {
         printf( "Failed to load font text!" );
         return 0;
      }

/***********************************************MENU*****************************************************/
    SDL_Rect screen = TOTAL_SCREEN;
    SDL_Texture* menu = SDLCommonFunction::LoadTexture(g_name_menu, g_renderer, screen);
    if(SDLCommonFunction::CreateGameMenu(menu, g_font_text_2, g_renderer) == 1)
    {
        return 0;
    }
    SDL_DestroyTexture(menu);
    menu = nullptr;

/*********************************************BACKSTORY*****************************************************/

   ScreenEffect::RenderRectangle(g_renderer, TOTAL_SCREEN, BLACK);
   SDL_RenderPresent(g_renderer);

   TypingScene back_story;
   back_story.InitBackStory(g_renderer, g_event);

/*****************************************FAIRY'S INTRODUCE*************************************************/

   FairyObject guide_fairy;
   guide_fairy.LoadAllFairyAction(g_renderer);
   guide_fairy.SetClipsEachAction();
   guide_fairy.InitFairyIntro();
   while(guide_fairy.get_is_active() == true)
   {
      //Bat dau chay dong ho
      fps_timer.start();

      while(SDL_PollEvent(&g_event))
      {
         //Quit game
         if(g_event.type == SDL_QUIT )
         {
            return 0;
         }
         guide_fairy.HandleInputAction(g_event);
      }

      guide_fairy.RenderClear(g_renderer);
      guide_fairy.HandleMove();
      guide_fairy.Show(g_renderer);
      guide_fairy.HandleConvoIntro(g_renderer);

      //Thiet ke FPS thu cong
         int real_imp_time = fps_timer.get_ticks();
         int time_one_frame = 1000/SCREEN_FPS;
         if (real_imp_time < time_one_frame)
         {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
               SDL_Delay(delay_time);
         }
      SDL_RenderPresent(g_renderer);
   }
   ScreenEffect::FadeOutScreenNoClick(g_renderer);

/*********************************************TUTORIAL***************************************************/


    bool is_begin_tutorial_1 = guide_fairy.get_selected_yes();

    //Init GameMap for tutorial
        GameMap game_map_tutorial;
        game_map_tutorial.set_is_size_screen(true);
        game_map_tutorial.LoadMap(g_name_map_tile_tutorial_1);
        game_map_tutorial.LoadTiles(g_renderer);
        Map map_data_tutorial = game_map_tutorial.GetMap();

    //Render all tile map into 1 texture
        SDL_Texture* p_txt_tutorial_map = SDL_CreateTexture(g_renderer,
                                                       SDL_PIXELFORMAT_RGBA8888,
                                                       SDL_TEXTUREACCESS_TARGET,
                                                       SCREEN_WIDTH, SCREEN_HEIGHT);
    //Set render target to p_txt_tutorial_map, not window
        SDL_SetRenderTarget(g_renderer, p_txt_tutorial_map);
    //Render everything to p_txt_tutorial_map
        game_map_tutorial.DrawMap(g_renderer);
    //Set render target back to screen
        SDL_SetRenderTarget(g_renderer, NULL);
    //Fade in texture
        ScreenEffect::FadeInScreenNoClick(g_renderer, p_txt_tutorial_map);

        MainObject player_tutorial;
        player_tutorial.LoadAllPlayerAction(g_renderer);
        player_tutorial.set_clips();
        player_tutorial.SetMapXY(0, 0);
        player_tutorial.set_is_center_on_map(false);
        player_tutorial.InitPlayer();

        FairyObject guide_tut_fairy;
        guide_tut_fairy.LoadAllFairyAction(g_renderer);
        guide_tut_fairy.SetClipsEachAction();
        guide_tut_fairy.InitFairyTutorial();

   while(is_begin_tutorial_1)
   {
      //Bat dau chay dong ho
      fps_timer.start();

      while(SDL_PollEvent(&g_event))
      {
         //Quit game
         if(g_event.type == SDL_QUIT )
         {
            return 0;
         }

         if(guide_tut_fairy.get_convo_run() == false)
         {
            player_tutorial.HandleInputAction(g_event, g_renderer);
         }
      }

      if(guide_tut_fairy.get_convo_run() == false)
      {
         SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0xFF);
         SDL_RenderClear(g_renderer); //black screen

         game_map_tutorial.DrawMap(g_renderer);

         player_tutorial.HandleBullet(g_renderer);
         player_tutorial.HandleExplosion(g_renderer);
         player_tutorial.DoPlayer(map_data_tutorial);
         player_tutorial.UpdateImagePlayer(g_renderer);
         player_tutorial.Show(g_renderer);
      }

      guide_tut_fairy.HandleConvoTutorial(g_renderer);
      guide_tut_fairy.SetBreakBetweenConvo();

      static bool show_convo_1 = false;
      static int delay_time_ = 60;
      if(delay_time_ > 0)
      {
         delay_time_--;
      }
      else
      {
         if(show_convo_1 == false)
         {
            guide_tut_fairy.FreezeScreenToConvo(g_renderer);
            player_tutorial.Show(g_renderer);
            show_convo_1 = true;
         }
      }

      static bool show_convo_2 = false;
      if(player_tutorial.get_x_pos() < 6*TILE_SIZE && show_convo_1 == true)
      {

         if(show_convo_2 == false)
         {
            guide_tut_fairy.FreezeScreenToConvo(g_renderer);
            player_tutorial.Show(g_renderer);
            show_convo_2 = true;
         }
      }

      static bool show_convo_3 = false;
      if(player_tutorial.get_x_pos() > 14*TILE_SIZE && show_convo_2 == true)
      {

         if(show_convo_3 == false)
         {
            guide_tut_fairy.FreezeScreenToConvo(g_renderer);
            player_tutorial.Show(g_renderer);
            show_convo_3 = true;
         }
      }

      if(player_tutorial.get_x_pos() < 10*TILE_SIZE && show_convo_3 == true)
      {
         is_begin_tutorial_1 = false;
         ScreenEffect::FadeOutScreenNoClick(g_renderer);
      }

      //Thiet ke FPS thu cong
         int real_imp_time = fps_timer.get_ticks();
         int time_one_frame = 1000/SCREEN_FPS;
         if (real_imp_time < time_one_frame)
         {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
               SDL_Delay(delay_time);
         }

      SDL_RenderPresent(g_renderer);
   }

/*******************************************STORY_STAGE***************************************************/

   //SET LOADING FLAG
      bool ret;

   //BaseObject
      BaseObject back_ground_1;
      BaseObject back_ground_2;
      BaseObject back_ground_3;
      ret = back_ground_1.LoadImg(g_name_back_ground_1, g_renderer, SDL_FALSE, BLACK);
      if(!ret)  { printf("Failed to load background 1!"); return 0;}
      ret = back_ground_2.LoadImg(g_name_back_ground_2, g_renderer, SDL_FALSE, BLACK);
      if(!ret)  { printf("Failed to load background 2!"); return 0;}
      ret = back_ground_3.LoadImg(g_name_back_ground_3, g_renderer, SDL_FALSE, BLACK);
      if(!ret)  { printf("Failed to load background 3!"); return 0;}

   //GameMap
      GameMap game_map;
      game_map.LoadMap(g_name_map_tile);
      game_map.LoadTiles(g_renderer);

   //MainObject
      MainObject p_player;
      p_player.LoadAllPlayerAction(g_renderer);
      p_player.set_clips();
      p_player.set_is_center_on_map(true);
      static bool ko = false;

   //ThreatObject
      std::vector<ThreatObject*> threats_list = MakeThreatList();

    //PlayerLive
        PlayerLive player_live;
        player_live.Init(g_renderer);

    //PlayerScore
        PlayerScore player_score;
        player_score.Init(g_renderer);

    //PlayerSkill
        PlayerSkill player_skill;
        player_skill.Init(g_renderer);

    //PlayerMoney
        PlayerMoney player_money;
        player_money.Init(g_renderer);

    //PlayerBuff
        PlayerBuff player_buff;
        player_buff.Init(g_renderer);

   //PlayerTime
      PlayerTime player_time;
      player_time.Init(g_renderer);

/**
   //BossThreat
      BossObject boss_object;
      boss_object.LoadImg("boss_object.png", g_renderer);
      boss_object.set_clips();
      boss_object.set_x_pos(MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6);
      boss_object.set_y_pos(10);

   //ExpObject
      ExpObject exp_threat;
      ret = exp_threat.LoadImg("exp3.png", g_renderer);
      if(!ret) { return 0;}
      else
      {
         exp_threat.set_clips();
      }
**/

   //SET MAIN LOOP FLAG
   bool is_quit = false;

   //PROGRAM RUNNING
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

            p_player.HandleInputAction(g_event, g_renderer);
         }

      //Clear screen
         SDL_RenderClear(g_renderer);

      //Lay' map_data tu` trong GameMap da~ duoc^. cap^. nhat^.
         Map map_data = game_map.GetMap();

      //Init fade in screen when enter game
         static bool begin_once = false;
         SDL_Texture* p_txt_story_map;
         if(begin_once == false)
         {
            //Render all tile map into 1 texture
            p_txt_story_map = SDL_CreateTexture(g_renderer,
                                                SDL_PIXELFORMAT_RGBA8888,
                                                SDL_TEXTUREACCESS_TARGET,
                                                SCREEN_WIDTH, SCREEN_HEIGHT);
            //Set render target to p_txt_story_map, not window
            SDL_SetRenderTarget(g_renderer, p_txt_story_map);
            begin_once = true;
         }

      //Tao. hieu^. ung' parallex cho background
      if(p_player.get_x_pos() > SCREEN_WIDTH/2)
      {
         back_ground_3.SetRect(-map_data.start_x_*0.6, 0);
         back_ground_2.SetRect(-map_data.start_x_*0.7, 0);
         back_ground_1.SetRect(-map_data.start_x_*0.8, 0);
      }
         back_ground_3.Render(g_renderer);
         back_ground_2.Render(g_renderer);
         back_ground_1.Render(g_renderer);


      /**Xu ly nhan vat */

         //Xu ly bang dan cua nhan vat
         p_player.HandleBullet(g_renderer);
         //Xu ly vu no tao ra boi DAN cua nhan vat
         p_player.HandleExplosion(g_renderer);

         p_player.SetMapXY(map_data.start_x_, map_data.start_y_); //Set lai start_x_, y da bi bien dong truoc do
         p_player.DoPlayer(map_data); //start_x_, start_y_ bat dau bien dong
         p_player.UpdateImagePlayer(g_renderer); // Set lai trang. thai' cua nhan^ vat.
         p_player.Show(g_renderer); //In ra nhan vat

      /** Xu ly tile map */

         game_map.SetMap(map_data); //Tinh lai game_map voi start_x_, start_y_ moi
         game_map.DrawMap(g_renderer); //Ve lai game_map

      /** Xu? ly' hinh` hoc. **/

         SDL_Rect rectangle_size = {0, 0, SCREEN_WIDTH, 2*TILE_SIZE};
         ScreenEffect::RenderRectangle(g_renderer, rectangle_size, DEMO);

         SDL_Rect outline_size = {1, 1, SCREEN_WIDTH - 1, 2*TILE_SIZE - 1};
         ScreenEffect::RenderOutline(g_renderer, outline_size, WHITE);

      /** Bat dau xu ly ke dich */

         for(int i = 0 ; i  < threats_list.size() ; ++i)
         {
            ThreatObject* p_threat = threats_list.at(i);
            if(p_threat != NULL)
            {
               p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
               p_threat->ImpMoveType(g_renderer);
               p_threat->DoThreat(map_data);
               p_threat->MakeBullet(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT,
                                    p_player.get_x_pos(), p_player.get_status());
               p_threat->Show(g_renderer);

            //Lay vi tri cua nhan vat va ke thu
               SDL_Rect rect_player = p_player.GetRectFrame();
               SDL_Rect rect_threat = p_threat->GetRectFrame();

            /** Xu ly va cham giua DAN CUA THREAT voi PLAYER */

               bool bCol1 = false;

               std::vector<BulletObject*> t_bullet_list = p_threat->get_bullet_list();
               for(int tb = 0 ; tb < t_bullet_list.size() ; ++tb)
               {
                  BulletObject* pt_bullet = t_bullet_list.at(tb);
                  if(pt_bullet != NULL)
                  {
                     SDL_Rect tmp = pt_bullet->GetRect();
                     bCol1 = SDLCommonFunction::CheckCollision(pt_bullet->GetRect(), rect_player);
                     if(bCol1 == true)
                     {
                        //p_threat->RemoveBullet(tb);
                        break;
                     }
                  }
               }

            /** Xu ly va cham giua THREAT voi PLAYER */

               bool bCol2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat);

            /** Neu 1 trong 2 TH va cham xay ra VA DONG THOI player dang k trong thoi gian bat' tu, player mat 1 mang */
               if((bCol1 == true || bCol2 == true) && p_player.get_invul_time() == 0 && p_player.get_invin_time() == 0)
               {
                  p_player.DecreaseLive();
                  if(p_player.GetNumLive() >= 0)
                  {
                     p_player.set_invul_time(2*SCREEN_FPS); //3s
                     p_player.set_frame(0);
                     continue;
                  }
                  else //num_die qua' 3 mang
                  {
                     p_player.set_ko_time(5*SCREEN_FPS); //5s
                     ko = true;
                  }
               }
            }
            //Threat da bi gan' trang thai' die va check load het cac frame
               if(p_threat->get_frame() == THREAT_FRAME_NUM - 1 &&
                  (p_threat->get_type_move() == ThreatObject::DIE_RIGHT) ||
                  (p_threat->get_type_move() == ThreatObject::DIE_LEFT)  )
               {
                  p_threat->Free();
                  threats_list.erase(threats_list.begin() + i);
               }
         }

      /** Ket thuc xu ly ke dich */

      /** Check va cham giua BULLET CUA MAIN (dong thoi voi THREAT va TILE MAP) */

         std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
         for(int r = 0 ; r < bullet_arr.size() ; ++r )
         {
            BulletObject* p_bullet = bullet_arr.at(r);
            if(p_bullet != NULL)
            {
               /** Check va cham voi TILE MAP, set is_move_ ve false */
               p_bullet->CheckToMap(map_data);

               /** Check va cham voi threat */
               for(int t = 0 ; t < threats_list.size() ; ++t)
               {
                  ThreatObject* threat_obj = threats_list.at(t);
                  if(threat_obj != NULL)
                  {
                     SDL_Rect tRect = threat_obj->GetRectFrame();
                     SDL_Rect bRect = p_bullet->GetRect();

                     bool bCol = SDLCommonFunction::CheckCollision(bRect, tRect);

                     //Neu xay ra va cham
                     if(bCol)
                     {
                        //Threat bi tieu diet voi loai dan tuong ung
                        if((p_bullet->get_bullet_type() == BulletObject::MAIN_ICE_SHARD_LEFT
                          || p_bullet->get_bullet_type() == BulletObject::MAIN_ICE_SHARD_RIGHT)
                          && threat_obj->get_type_element() == ThreatObject::FIRE)
                        {
                            if(p_player.get_pwup_time() > 0)
                            {
                                threat_obj->set_hidden_live(0);
                            }
                            else
                            {
                                threat_obj->DecreaseLive();
                            }

                            if(threat_obj->get_hidden_live() == 0)
                            {
                                if(threat_obj->get_type_move() == ThreatObject::MOVE_LEFT)
                                {
                                    threat_obj->set_type_move(ThreatObject::DIE_LEFT);
                                    threat_obj->set_frame(0); //Set lai frame cua threat ve 0
                                }
                                else if(threat_obj->get_type_move() == ThreatObject::MOVE_RIGHT)
                                {
                                    threat_obj->set_type_move(ThreatObject::DIE_RIGHT);
                                    threat_obj->set_frame(0); //Set lai frame cua threat ve 0
                                }

                                p_player.IncreaseScore();
                            }
                        }

                        /**
                        //Ham khoi tao vu no
                        //Cach ngan'
                        p_player.InitExplosion(ExpObject::EXP_THREAT,
                                               p_bullet->GetRect().x,
                                               p_bullet->GetRect().y, g_renderer);
                        **/

                        //Huy vien dan sau khi ban' trung'
                        p_player.RemoveBullet(r);
                     }
                  }
               }
            }
         }

         if(ko == true && p_player.get_ko_time() == 0)
         {
            if(SDLCommonFunction::CreateGameOver(g_font_text_2, g_renderer) == 2)
            {
                return 0;
            }
         }

         /** Xu? ly' game texture **/
         player_live.SetNumLive(p_player.GetNumLive());
         player_live.Show(g_renderer);

         player_score.SetNumScore(p_player.GetNumScore());
         player_score.Show(g_renderer);

         player_money.SetNumMoney(p_player.GetNumMoney());
         player_money.Show(g_renderer);

         player_skill.SetNumSkill(p_player.GetNumSkill());
         player_skill.Show(g_renderer);

         player_buff.ImpBuffType(PlayerBuff::HASTE, p_player.GetHasteTime());
         player_buff.ImpBuffType(PlayerBuff::INVIN, p_player.GetInvinTime());
         player_buff.ImpBuffType(PlayerBuff::POWER_UP, p_player.GetPwupTime());
         player_buff.Show(g_renderer);

      //Show PlayerTime
         Uint32 time_val = SDL_GetTicks()/1000;
         Uint32 val_time = TIME_ONE_STAGE - time_val;
         player_time.SetTimeCount(val_time);
         player_time.Show(g_renderer);

       //Bat' dau` fade in screen = p_txt_story_map
            static bool end_once = false;
            if(end_once == false)
            {
                //Set render target back to screen
                SDL_SetRenderTarget(g_renderer, NULL);

                //Fade in texture
                ScreenEffect::FadeInScreenNoClick(g_renderer, p_txt_story_map);
                end_once = true;
            }

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

      //Giai phong bo nho cua cac threat
      for(int i = 0 ; i < threats_list.size() ; ++i)
      {
         ThreatObject* p_threat = threats_list.at(i);
         if(p_threat != NULL)
         {
            p_threat->Free();
            p_threat = NULL;
         }
      }
      threats_list.clear();

      SDLCommonFunction::Close();
      return 0; //Ham nay giai tru bo nho cua ca MainObject()
}
