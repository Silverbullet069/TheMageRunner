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
         p_threat->set_x_pos(1500);
         p_threat->set_y_pos(THREAT_START_FALL_Y_POS);

         int pos1 = p_threat->get_x_pos() - THREAT_MAX_PATROL;
         int pos2 = p_threat->get_x_pos() + THREAT_MAX_PATROL;
         p_threat->SetAnimationPos(pos1, pos2);

         //Tao ra 1 vien dan
         BulletObject* p_bullet = new BulletObject();
         p_bullet->set_bullet_type(BulletObject::WISP_FIRE_BALL_LEFT);
         int type = p_bullet->get_bullet_type();
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

   /** INIT SDL **/
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

   /** INIT BACKSTORY **/

   /**
   ScreenEffect::RenderRectangle(g_renderer, TOTAL_SCREEN, BLACK);
   SDL_RenderPresent(g_renderer);

   TypingScene back_story;
   back_story.InitBackStory(g_renderer, g_event);
   **/

   /** INIT FAIRY'S INTRODUCT **/

   FairyObject guide_fairy;
   guide_fairy.LoadAllFairyAction(g_renderer);
   guide_fairy.SetClipsEachAction();
   guide_fairy.InitFairy();
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
         guide_fairy.get_convo().HandleInputActionByFrame(g_event);
      }

      guide_fairy.RenderClear(g_renderer);
      guide_fairy.HandleMove();
      guide_fairy.Show(g_renderer);
      guide_fairy.HandleConvo(g_renderer);

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

   ScreenEffect::FadeOutScreenNoClick(g_renderer, TOTAL_SCREEN, BLACK);

   /** INIT TUTORIAL **/

   GameMap game_map_tutorial;
   game_map_tutorial.LoadTiles(g_renderer);
   game_map_tutorial.LoadMap(g_name_map_tile_tutorial_1);

   MainObject player_tutorial;
   player_tutorial.LoadAllPlayerAction(g_renderer);
   player_tutorial.set_clips();

   bool is_done_tutorial_1 = false;
   while(!is_done_tutorial_1)
   {
      while(SDL_PollEvent(&g_event))
      {
         //Quit game
         if(g_event.type == SDL_QUIT )
         {
            break;
         }

         player_tutorial.HandleInputAction(g_event, g_renderer);
      }

      player_tutorial.HandleBullet(g_renderer);
      player_tutorial.HandleExplosion(g_renderer);

      player_tutorial.SetMapXY(map_data.start_x_, map_data.start_y_);
      player_tutorial.DoPlayer(map_data);
      player_tutorial.UpdateImagePlayer(g_renderer);
      player_tutorial.Show(g_renderer);
   }

   return 0;

   //SET LOADING FLAG
      bool ret;

   //Khai bao BaseObject
      BaseObject back_ground_1;
      BaseObject back_ground_2;
      BaseObject back_ground_3;

      ret = back_ground_1.LoadImg(g_name_back_ground_1, g_renderer, SDL_FALSE, BLACK);
      if(!ret)  { printf("Failed to load background 1!"); return 0;}

      ret = back_ground_2.LoadImg(g_name_back_ground_2, g_renderer, SDL_FALSE, BLACK);
      if(!ret)  { printf("Failed to load background 2!"); return 0;}

      ret = back_ground_3.LoadImg(g_name_back_ground_3, g_renderer, SDL_FALSE, BLACK);
      if(!ret)  { printf("Failed to load background 3!"); return 0;}

   //Khai bao GameMap
      GameMap game_map;
      game_map.LoadMap(g_name_map_tile);
      game_map.LoadTiles(g_renderer);

   //Khai bao MainObject
      MainObject p_player;
      p_player.LoadAllPlayerAction(g_renderer);
      p_player.set_clips();

   //Khai bao PlayerPower
      PlayerPower player_power;
      player_power.Init(g_renderer);

   //Khai bao PlayerMoney
      PlayerMoney player_money;
      player_money.Init(g_renderer);

   //Khai bao ThreatObject
      std::vector<ThreatObject*> threats_list = MakeThreatList();

   //Khai bao BossThreat
      BossObject boss_object;
      boss_object.LoadImg("boss_object.png", g_renderer);
      boss_object.set_clips();
      boss_object.set_x_pos(MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6);
      boss_object.set_y_pos(10);

   /*

   //Khai bao ExpObject
      ExpObject exp_threat;
      ret = exp_threat.LoadImg("exp3.png", g_renderer);
      if(!ret) { return 0;}
      else
      {
         exp_threat.set_clips();
      }

   */

   //Khai bao time text
   TextObject time_game;
   time_game.SetColor(WHITE);

   //Khai bao mark text
   TextObject mark_game;
   mark_game.SetColor(WHITE);
   Uint8 mark_value = 0; //255

   //Khai bao money count
   TextObject money_game;
   money_game.SetColor(WHITE);

   //Khai bao so mang luc dau
   int num_die = 0;

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
      //In background ra truoc
         back_ground_3.Render(g_renderer);
         back_ground_2.Render(g_renderer);
         back_ground_1.Render(g_renderer);

      //Khoi tao map_data, lam trung gian cho game_map
         Map map_data = game_map.GetMap();

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

      /** Xu ly hinh hoc

         GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 80);
         ColorData color_data(0, 64, 128);
         Geometric::RenderRectangle(rectangle_size, color_data, g_renderer);

         GeometricFormat outline_size(1, 1, SCREEN_WIDTH - 1, 79);
         ColorData color_data2(255, 255, 255);
         Geometric::RenderOutline(outline_size, color_data2, g_renderer);

       */

      /** Xu ly game texture */

      //Show PlayerPower
         player_power.Show(g_renderer);
      //Show PlayerMoney
         player_money.Show(g_renderer);

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
               if((bCol1 == true || bCol2 == true) && p_player.get_invul_time() == 0)
               {
                  //Xu ly chi so sinh menh cua nhan vat
                  num_die++;
                  if(num_die <= PLAYER_TOTAL_LIVES)
                  {
                     /**
                     p_player.SetRect(0, PLAYER_START_FALL_Y_POS);
                     p_player.set_come_back_time(3*SCREEN_FPS); //Sau khi set come_back_time_, nv se bien mat
                     SDL_Delay(500); // 0.5 sec
                     **/

                     p_player.set_invul_time(3*SCREEN_FPS); //3s
                     p_player.set_frame(0);

                     player_power.DecreaseNum();
                     player_power.Show(g_renderer);
                     continue;
                  }
                  else //num_die qua' 3 mang
                  {
                     p_player.set_ko_time(2*SCREEN_FPS); //2s
                     is_quit = true;
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
                        mark_value++; //Tang them 1 diem cho moi threat tieu diet

                        //Threat bi tieu diet voi loai dan tuong ung
                        if((p_bullet->get_bullet_type() == BulletObject::MAIN_ICE_SHARD_LEFT
                          || p_bullet->get_bullet_type() == BulletObject::MAIN_ICE_SHARD_RIGHT)
                          && threat_obj->get_type_element() == ThreatObject::FIRE)
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

         //Show Boss
         int val = MAX_MAP_X*TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);
         if(val <= SCREEN_WIDTH)
         {
            boss_object.SetMapXY(map_data.start_x_, map_data.start_y_);
            boss_object.DoBoss(map_data);
            boss_object.MakeBullet(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            boss_object.Show(g_renderer);
         }

      /** XU LY CHI SO PHU TRO CHO GAME

      /**
         //Show game time
         std::string str_time = "Time : ";
         Uint32 time_val = SDL_GetTicks()/1000;
         Uint32 val_time = 300 - time_val;
         if(val_time <= 0)
         {
            if(MessageBox (NULL, "Game Over", "Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
               is_quit = true;
               break;
            }

         }
         else
         {
            std::string str_val = std::to_string(val_time);
            str_time+=str_val;

            time_game.SetTextType(str_time);
            time_game.LoadFromRenderText(g_font_text, g_renderer);
            time_game.RenderText(g_renderer, SCREEN_WIDTH - 200, 15);
         }

         //Show mark game
         std::string val_str_mark = std::to_string(mark_value);
         std::string str_mark = "Mark : ";
         str_mark += val_str_mark;

         mark_game.SetTextType(str_mark);;
         mark_game.LoadFromRenderText(g_font_text, g_renderer);
         mark_game.RenderText(g_renderer, SCREEN_WIDTH*0.5 - 50, 15);

         //Show money count
         int money_count = p_player.GetMoney();
         std::string money_str = std::to_string(money_count);
         money_game.SetTextType(money_str);
         money_game.LoadFromRenderText(g_font_text, g_renderer);
         money_game.RenderText(g_renderer, SCREEN_WIDTH*0.5 - 250, 15);
      **/

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
