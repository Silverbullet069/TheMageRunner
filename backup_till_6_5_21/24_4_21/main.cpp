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
#include "Geometric.h"
#include "BossObject.h"

//Khoi tao cac threats
std::vector<ThreatObject*> MakeThreatList()
{
   std::vector<ThreatObject*> list_threats;

   ThreatObject* dynamic_threats = new ThreatObject[20];

   for(int i = 0 ; i < 20 ; ++i)
   {
      ThreatObject* p_threat = (dynamic_threats + i);
      if(p_threat != NULL)
      {
         //Viet them
         p_threat->LoadThreatLeftImg(g_renderer);
         p_threat->LoadThreatRightImg(g_renderer);
         //p_threat->LoadImg("threat_left.png", g_renderer);
         p_threat->set_clips();
         p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE);
         p_threat->set_x_pos(500 + i*500);
         p_threat->set_y_pos(100);

         int pos1 = p_threat->get_x_pos() - 60;
         int pos2 = p_threat->get_x_pos() + 60;
         p_threat->SetAnimationPos(pos1, pos2);
         p_threat->set_input_left(1);

         list_threats.push_back(p_threat);
      }
   }

   ThreatObject* static_threats = new ThreatObject[20];

   for(int i = 0 ; i < 20 ; ++i)
   {
      ThreatObject* p_threat = (static_threats + i);
      if(p_threat != NULL)
      {
         //Viet them
         p_threat->LoadThreatStaticImg(g_renderer);
         //p_threat->LoadImg("threat_level.png", g_renderer);
         p_threat->set_clips();
         p_threat->set_x_pos(700 + i*1200);
         p_threat->set_y_pos(250);
         p_threat->set_type_move(ThreatObject::STATIC_THREAT);
         p_threat->set_input_left(0);

         //DAN CUA THREAT duoc tao ra ben ngoai InitBullet => 1 threat/ 1 bullet
         BulletObject* p_bullet = new BulletObject();
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

   //Khoi tao SDL
      if(!SDLCommonFunction::Init())
      {
         printf( "Failed to initialize!" );
         return 0;
      }

   //Khoi tao font
      if(!SDLCommonFunction::LoadFontText())
      {
         printf( "Failed to load font text!" );
         return 0;
      }

      bool is_run_screen = true;
      int bkgn_x = 0;
      SDL_Rect rect_bkgn;

   //SET MAIN LOOP FLAG
      bool is_quit = false;

   //SET LOADING FLAG
      bool ret;

   //Khai bao BaseObject
      BaseObject back_ground;
      ret = back_ground.LoadImg(g_name_back_ground, g_renderer);
      if(!ret)  { printf("Failed to load background!"); return 0;}

   //Khai bao GameMap
      GameMap game_map;
      game_map.LoadMap("map01.dat");
      game_map.LoadTiles(g_renderer);

   //Khai bao MainObject
      MainObject p_player;
      p_player.LoadPlayerWalkLeftImg(g_renderer); //Load san~ txt, rect
      p_player.LoadPlayerWalkRightImg(g_renderer); //Load san~ txt, rect
      p_player.LoadPlayerIdleImg(g_renderer); //Trong ham` co set_width_frame va set_width_height
      p_player.set_clips(DISTANCE_FRAME_IDLE);

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
   time_game.SetColorType(TextObject::WHITE_TEXT);

   //Khai bao mark text
   TextObject mark_game;
   mark_game.SetColorType(TextObject::WHITE_TEXT);
   Uint8 mark_value = 0; //255

   //Khai bao money count
   TextObject money_game;
   money_game.SetColorType(TextObject::WHITE_TEXT);

   //Khai bao so mang luc dau
   int num_die = 0;

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

            p_player.HandleInputAction(g_event, g_renderer);
         }

      //Clear screen
         SDL_RenderClear(g_renderer);
      //In background ra truoc
         back_ground.Render(g_renderer);
      //Khoi tao map_data, lam trung gian cho game_map
         Map map_data = game_map.GetMap();

      /**Xu ly nhan vat **/

         //Xu ly bang dan cua nhan vat
         p_player.HandleBullet(g_renderer);
         //Xu ly vu no tao ra boi DAN cua nhan vat
         p_player.HandleExplosion(g_renderer);

         //Set lai start_x_, y sau khi bi bien dong truoc do
         p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
         p_player.DoPlayer(map_data); //start_x_, start_y_ bat dau bien dong
         p_player.Show(g_renderer); //In ra nhan vat

      /** Xu ly tile map */

         game_map.SetMap(map_data); //Tinh lai game_map voi start_x_, start_y_ moi
         game_map.DrawMap(g_renderer); //Ve lai game_map

      /** Xu ly hinh hoc */

         GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
         ColorData color_data(0, 64, 128);
         Geometric::RenderRectangle(rectangle_size, color_data, g_renderer);

         GeometricFormat outline_size(1, 1, SCREEN_WIDTH - 1, 38);
         ColorData color_data2(255, 255, 255);
         Geometric::RenderOutline(outline_size, color_data2, g_renderer);

      //Show PlayerPower
         player_power.Show(g_renderer);
      //Show PlayerMoney
         player_money.Show(g_renderer);

      //Xu ly ke thu voi tile map
         for(int i = 0 ; i  < threats_list.size() ; ++i)
         {
            ThreatObject* p_threat = threats_list.at(i);
            if(p_threat != NULL)
            {
               p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
               p_threat->ImpMoveType(g_renderer);
               p_threat->DoThreat(map_data);
               p_threat->MakeBullet(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
               p_threat->Show(g_renderer);

               SDL_Rect rect_player = p_player.GetRectFrame();

               bool bCol1 = false;

               //Check tung vien dan cua THREAT
               std::vector<BulletObject*> t_bullet_list = p_threat->get_bullet_list();
               for(int tb = 0 ; tb < t_bullet_list.size() ; ++tb)
               {
                  BulletObject* pt_bullet = t_bullet_list.at(tb);
                  if(pt_bullet != NULL)
                  {
                     //Check va cham giua DAN CUA THREAT voi PLAYER
                     bCol1 = SDLCommonFunction::CheckCollision(pt_bullet->GetRect(), rect_player);
                     if(bCol1 == true)
                     {
                        p_threat-> RemoveBullet(tb);
                        break;
                     }
                  }
               }

               //Check va cham giua THREAT va PLAYER
               SDL_Rect rect_threat = p_threat->GetRectFrame();
               bool bCol2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat);

               //Neu 1 trong 2 TH va cham xay ra
               if(bCol1 == true || bCol2 == true)
               {
                  //Xu ly chi so sinh menh cua nhan vat
                  num_die++;
                  if(num_die <= 3)
                  {
                     p_player.SetRect(0, 0);
                     p_player.set_come_back_time(60);
                     SDL_Delay(500); // 1 sec
                     player_power.DecreaseNum();
                     player_power.Show(g_renderer);
                     continue;
                  }
                  else
                  {
                     if(MessageBox (NULL, "Game Over", "Info", MB_OK | MB_ICONSTOP) == IDOK)
                     {
                        p_threat->Free();
                        SDLCommonFunction::Close();
                        return 0;
                     }
                  }
               }
            }
         }

      /*
         int frame_exp_width = exp_threat.get_frame_width();
         int frame_exp_height = exp_threat.get_frame_height();
      */

      //Check va cham giua BULLET CUA MAIN va THREAT
         std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
         for(int r = 0 ; r < bullet_arr.size() ; ++r )
         {
            BulletObject* p_bullet = bullet_arr.at(r);
            if(p_bullet != NULL)
            {
               for(int t = 0 ; t < threats_list.size() ; ++t)
               {
                  ThreatObject* threat_obj = threats_list.at(t);
                  if(threat_obj != NULL)
                  {
                     SDL_Rect tRect;
                     tRect.x = threat_obj->GetRect().x;
                     tRect.y = threat_obj->GetRect().y;
                     tRect.w = threat_obj->get_width_frame();
                     tRect.h = threat_obj->get_height_frame();

                     SDL_Rect bRect = p_bullet->GetRect();

                     bool bCol = SDLCommonFunction::CheckCollision(bRect, tRect);

                     //Neu xay ra va cham
                     if(bCol)
                     {
                        mark_value++; //Tang them 1 diem cho moi threat tieu diet
                        //Ham khoi tao vu no
                        p_player.InitExplosion(ExpObject::EXP_THREAT,
                                               p_bullet->GetRect().x,
                                               p_bullet->GetRect().y, g_renderer);

                        /**

                        //Init Explosion
                        std::vector<ExpObject*> exp_arr = p_player.get_exp_list();
                        ExpObject* exp_obj = new ExpObject();
                        exp_obj->set_exp_type(ExpObject::EXP_THREAT);
                        exp_obj->LoadImgExp(g_renderer);
                        exp_obj->set_clips();
                        int x_pos = p_bullet->GetRect().x - exp_obj->get_frame_width()*0.5;
                        int y_pos = p_bullet->GetRect().y - exp_obj->get_frame_height()*0.5;
                        exp_obj->SetRect(x_pos, y_pos);
                        //SetRect theo cach nay se lam vu no di chuyen khi nhan vat di chuyen
                        //Vi rect la quy chieu' giua pos va map
                        //Tuy nhien do toc do di chuyen cua nhan vat khong dang ke
                        //Tam thoi bo qua
                        exp_obj->set_is_exp(true);
                        exp_arr.push_back(exp_obj);
                        p_player.set_exp_list(exp_arr);
                        **/

                        /*

                        for(int ex = 0 ; ex < EXP_NUM_FRAME ; ++ex)
                        {
                           int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                           int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
                           exp_threat.set_frame(ex);
                           exp_threat.SetRect(x_pos, y_pos);
                           exp_threat.Show(g_renderer);
                        }

                        */
                        p_player.RemoveBullet(r);
                        threat_obj->Free();
                        threats_list.erase(threats_list.begin() + t);
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

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(g_font_text, g_renderer);
            time_game.RenderText(g_renderer, SCREEN_WIDTH - 200, 15);
         }

         //Show mark game
         std::string val_str_mark = std::to_string(mark_value);
         std::string str_mark = "Mark : ";
         str_mark += val_str_mark;

         mark_game.SetText(str_mark);;
         mark_game.LoadFromRenderText(g_font_text, g_renderer);
         mark_game.RenderText(g_renderer, SCREEN_WIDTH*0.5 - 50, 15);

         //Show money count
         int money_count = p_player.GetMoney();
         std::string money_str = std::to_string(money_count);
         money_game.SetText(money_str);
         money_game.LoadFromRenderText(g_font_text, g_renderer);
         money_game.RenderText(g_renderer, SCREEN_WIDTH*0.5 - 250, 15);

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
