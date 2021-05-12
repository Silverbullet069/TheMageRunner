
#include "MainObject.h"

MainObject::MainObject()
{
   frame_ = 0;
   x_pos_ = 0;
   y_pos_ = PLAYER_START_FALL_Y_POS;
   x_val_ = 0;
   y_val_ = 0;
   width_frame_ = 0;
   height_frame_ = 0;
   status_ = IDLE_RIGHT;
   skill_type_ = FIRE_BALL;
   input_type_.idle_ = 1; //Khoi tao ban dau
   input_type_.left_ = 0;
   input_type_.right_ = 0;
   input_type_.up_ = 0;
   input_type_.down_ = 0;
   input_type_.jump_ = 0;
   on_ground_ = false;
   is_ice_shard_learned_ = false;
   map_x_ = 0;
   map_y_ = 0;
   come_back_time_ = 0;
   invul_time_ = 0;
   ko_time_ = 0;
   toggle_bullet_ = BulletObject::MAIN_FIRE_BALL_RIGHT;
   money_count_ = 0;

   txt_player_idle_left_ = NULL;
   txt_player_idle_right_ = NULL;
   txt_player_walk_left_ = NULL;
   txt_player_walk_right_ = NULL;
   txt_player_jump_left_ = NULL;
   txt_player_jump_right_ = NULL;
   txt_player_take_hit_left_ = NULL;
   txt_player_take_hit_right_ = NULL;
   txt_player_ko_left_ = NULL;
   txt_player_ko_right_ = NULL;
}

MainObject::~MainObject()
{
   if(txt_player_idle_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_idle_left_);
      txt_player_idle_left_ = NULL;
   }
   if(txt_player_idle_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_idle_right_);
      txt_player_idle_right_ = NULL;
   }
   if(txt_player_walk_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_walk_left_);
      txt_player_walk_left_ = NULL;
   }
   if(txt_player_walk_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_walk_right_);
      txt_player_walk_right_ = NULL;
   }
   if(txt_player_jump_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_jump_left_);
      txt_player_jump_left_ = NULL;
   }
   if(txt_player_jump_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_jump_right_);
      txt_player_jump_right_ = NULL;
   }
   if(txt_player_take_hit_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_take_hit_left_);
      txt_player_take_hit_left_ = NULL;
   }
   if(txt_player_take_hit_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_take_hit_right_);
      txt_player_take_hit_right_ = NULL;
   }
   if(txt_player_ko_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_ko_left_);
      txt_player_ko_left_ = NULL;
   }
   if(txt_player_ko_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_ko_right_);
      txt_player_ko_right_ = NULL;
   }
}

void MainObject::LoadAllPlayerAction(SDL_Renderer* des)
{
   txt_player_idle_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_idle_left, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_player_idle_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_idle_right, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_player_walk_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_walk_left, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_player_walk_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_walk_right, des,
                                                           rect_, SDL_FALSE, WHITE);
   txt_player_jump_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_jump_left, des,
                                                           rect_, SDL_FALSE, WHITE);
   txt_player_jump_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_jump_right, des,
                                                           rect_, SDL_FALSE, WHITE);
   txt_player_take_hit_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_take_hit_left, des,
                                                              rect_, SDL_FALSE, WHITE);
   txt_player_take_hit_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_take_hit_right, des,
                                                              rect_, SDL_FALSE, WHITE);
   txt_player_ko_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_ko_left, des,
                                                         rect_, SDL_FALSE, WHITE);
   txt_player_ko_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_ko_right, des,
                                                         rect_, SDL_FALSE, WHITE);
   /** LUU Y : RECT_ la chung cho tat ca cac action,
   RECT_ duoc su dung boi action duoc khoi tao SAU CUNG` **/
   //width_frame_ = rect_.w/PLAYER_FRAME_NUM;
   width_frame_ = rect_.w;
   height_frame_ = rect_.h;
}

//Cach cu~
bool MainObject::LoadImg(const std::string file_path, SDL_Renderer* des)
{
   bool ret = BaseObject::LoadImg(file_path, des, SDL_TRUE, DEMO);
   if(!ret) { printf("Unable to load main object!"); }
   else
   {
      width_frame_ = rect_.w/PLAYER_FRAME_NUM;
      height_frame_ = rect_.h;
   }
   return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
   SDL_Rect rect_tmp = {0, 0, 0, 0};
   rect_tmp.x = rect_.x;
   rect_tmp.y = rect_.y;
   rect_tmp.w = width_frame_;
   rect_tmp.h = height_frame_;
   return rect_tmp;
}

void MainObject::set_clips()
{
   if(width_frame_ > 0 && height_frame_ > 0)
   {
      for(int i = 0 ; i < PLAYER_FRAME_NUM ; ++i)
      {
         frame_clip_[i].x = i*width_frame_;
         frame_clip_[i].y = 0;
         frame_clip_[i].w = width_frame_;
         frame_clip_[i].h = height_frame_;
      }
   }
}

void MainObject::Show(SDL_Renderer* des)
{
   //Xu ly trang thai ghi nhan
   //Nhan vat dang di chuyen sang trai, phai, hoac dung yen
   if((input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.idle_ == 1)
      && (status_ != JUMP_LEFT && status_ != JUMP_RIGHT))
      /** SU DUNG STATUS O DAY vi input_type_.jump_ la NHAN 1 LAN, khong phai GIU~
      vay nen khi nhan' Space 1 lan va nha Space ngay sau do, input_type.jump_ ngay lap tuc ve 0
      trong khi ham` nay` nhan input_type_ lien tuc nen khong the dung input_type_.jump_ */
   {
      frame_ ++; //Tang frame
   }
   else //input_type_.jump_ == 1
   {
      frame_ = 0;
   }

   //Quay vong` lai frame
   if(frame_ >= PLAYER_FRAME_NUM)
   {
      frame_ = 0;
      //Ket' thuc' 1 vong` khi trang thai' dang la dinh' dan => RESET lai status_
      if(status_ == TAKE_HIT_LEFT)
      {
         status_ = IDLE_LEFT;
      }
      else if(status_ == TAKE_HIT_RIGHT)
      {
         status_ = IDLE_RIGHT;
      }
   }

   //Giam duoc cong viec xu ly khi dang delay time de hoi sinh nhan vat
   if(come_back_time_ == 0)
   {
      //x_pos_ la vi tri cua nhan vat tren toan bo map
      //map_x la vi tri mep khung hinh tren toan bo map
      //rect_.x la vi tri cua nhan vat tren khung hinh
      //Sau khi nhan vat xuat hien o 1/2 khung hinh, rect_.x = const
      //Vi x_pos_ va map_x_ tang dong` thoi
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_ - map_y_;

      //Lay rect cua frame hien tai
      SDL_Rect* current_clip = &frame_clip_[frame_];

      SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

      SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
   }
}

void MainObject::HandleInputAction(SDL_Event& events, SDL_Renderer* des)
{
   if(status_ == TAKE_HIT_LEFT || status_ == TAKE_HIT_RIGHT
      || status_ == RESPAWN || status_ == KO_LEFT || status_ == KO_RIGHT)
      return;

   //Ban phim
   if(events.type == SDL_KEYDOWN)
   {
      switch(events.key.keysym.sym)
      {
      case SDLK_a : /** LEFT **/
         {
            if(on_ground_ == true)
            {
               status_ = WALK_LEFT;

               input_type_.left_ = 1;
               input_type_.idle_ = 0;
               input_type_.right_ = 0;
               input_type_.jump_ = 0;
            }
            else //on_ground_ == false
            {
               status_ = JUMP_LEFT;
               input_type_.left_ = 1;
            }
         }
         break;
      case SDLK_d : /** RIGHT **/
         {
            if(on_ground_ == true)
            {
               status_ = WALK_RIGHT;
               input_type_.right_ = 1;
               input_type_.idle_ = 0;
               input_type_.left_ = 0;
               input_type_.jump_ = 0;
            }
            else //on_ground_ == false
            {
               status_ = JUMP_RIGHT;
               input_type_.right_ = 1;
            }
         }
         break;
      case SDLK_SPACE :
         {
            if(status_ == JUMP_LEFT || status_ == JUMP_RIGHT)
            {
               break; //Khi dang trong khong trung, huy bam' Space => khong render lai hinh`
            }
            input_type_.jump_ = 1;
            /** input_type_.idle_ KHONG PHAN BIET DUOC TRAI PHAI => DUNG status_ o day */
            if(input_type_.left_ == 1 || status_ == IDLE_LEFT)
            {
               status_ = JUMP_LEFT;
            }
            else if(input_type_.right_ == 1 || status_ == IDLE_RIGHT)
            {
               status_ = JUMP_RIGHT;
            }
         }
         break;
      case SDLK_1 :
         {
            if(status_ == WALK_LEFT || status_ == IDLE_LEFT || status_ == JUMP_LEFT)
            {
               skill_type_ = FIRE_BALL;
               toggle_bullet_ = BulletObject::MAIN_FIRE_BALL_LEFT;
            }
            else if(status_ == WALK_RIGHT || status_ == IDLE_RIGHT || status_ == JUMP_RIGHT)
            {
               skill_type_ = FIRE_BALL;
               toggle_bullet_ = BulletObject::MAIN_FIRE_BALL_RIGHT;
            }
         }
         break;
      case SDLK_2 :
         {
            if(is_ice_shard_learned_ == true)
            {
               if(status_ == WALK_LEFT || status_ == IDLE_LEFT || status_ == JUMP_LEFT)
               {
                  skill_type_ = ICE_SHARD;
                  toggle_bullet_ = BulletObject::MAIN_ICE_SHARD_LEFT;
               }
               else if(status_ == WALK_RIGHT || status_ == IDLE_RIGHT || status_ == JUMP_RIGHT)
               {
                  skill_type_ = ICE_SHARD;
                  toggle_bullet_ = BulletObject::MAIN_ICE_SHARD_RIGHT;
               }
            }
         }
         break;
      }
   }
   else if (events.type == SDL_KEYUP)
   {
      switch(events.key.keysym.sym)
      {
         case SDLK_a :
         {
            if(on_ground_ == true)
            {
               input_type_.left_ = 0;

      /** NOI KI HON VE TRUONG HOP NAY

      Gia su : PHIM A dang duoc nhan', ngay lap tuc nhan' PHIM D, roi moi nha PHIM A
      (k noi den trg hop nha PHIM A truoc roi moi nhan PHIM D)
      Giai thich: neu ngay lap tuc nhan' phim' D sau phim' A, idle = 0, right = 1,
      status = W_R, nhung sau do' nha phim' A, khien cho idle = 1, status = I_L
      =>Tao bug
      =>Giai quyet : Chi khi nao right = 0 (tuc la khong co trang thai' right = 1
      truoc khi nha PHIM A) thi moi cho phep' idle = 1.

      */
               if(input_type_.right_ == 0)
               {
                  status_ = IDLE_LEFT;
                  input_type_.idle_ = 1;
               }
            }
            else
            {
               input_type_.left_ = 0;
               input_type_.idle_ = 1;
            }

         }
         break;
         case SDLK_d :
         {
            if(on_ground_ == true)
            {
               input_type_.right_ = 0;
               if(input_type_.left_ == 0)
               {
                  status_ = IDLE_RIGHT;
                  input_type_.idle_ = 1;
               }
            }
            else
            {
               input_type_.right_ = 0;
               input_type_.idle_ = 1;
            }
         }
         break;
         case SDLK_SPACE :
         {
            input_type_.jump_ = 0;
         }
         break;
      }
   }

   //Set loai. dan. theo loai. skill va trang thai di chuyen cua nv
   if(status_ == WALK_LEFT || status_ == IDLE_LEFT || status_ == JUMP_LEFT)
   {
      if(skill_type_ == FIRE_BALL)
      {
         toggle_bullet_ = BulletObject::MAIN_FIRE_BALL_LEFT;
      }
      else if(skill_type_ == ICE_SHARD)
      {
         toggle_bullet_ = BulletObject::MAIN_ICE_SHARD_LEFT;
      }
   }
   else if(status_ == WALK_RIGHT || status_ == IDLE_RIGHT || status_ == JUMP_RIGHT)
   {
      if(skill_type_ == FIRE_BALL)
      {
         toggle_bullet_ = BulletObject::MAIN_FIRE_BALL_RIGHT;
      }
      else if(skill_type_ == ICE_SHARD)
      {
         toggle_bullet_ = BulletObject::MAIN_ICE_SHARD_RIGHT;
      }
   }

   //Bam chuot
   if(events.type == SDL_MOUSEBUTTONDOWN)
   {
      if(events.button.button == SDL_BUTTON_LEFT)
      {
         BulletObject* p_bullet = new BulletObject();

      //Set loai dan
         p_bullet->set_bullet_type(toggle_bullet_);
      //Set flag di chuyen cua vien dan
         p_bullet->set_is_move(true);

      //Load img cua loai dan tuong ung
         p_bullet->LoadImgBullet(des);

         if(status_ == WALK_LEFT || status_ == IDLE_LEFT || status_ == JUMP_LEFT)
         {
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(this->rect_.x,
                              this->rect_.y - BULLET_MARGINS_Y_VAL);
            p_bullet->set_x_pos(this->x_pos_);
            p_bullet->set_y_pos(this->y_pos_- BULLET_MARGINS_Y_VAL);
         }
         else if(status_ == WALK_RIGHT || status_ == IDLE_RIGHT || status_ == JUMP_RIGHT)
         {
            p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
            p_bullet->SetRect(this->rect_.x + this->width_frame_ - BULLET_MARGINS_X_VAL,
                              this->rect_.y - BULLET_MARGINS_Y_VAL);
            p_bullet->set_x_pos(this->x_pos_ + this->width_frame_ - BULLET_MARGINS_X_VAL);
            p_bullet->set_y_pos(this->y_pos_ - BULLET_MARGINS_Y_VAL);
         }

      //Set van toc cua vien dan
      //Van toc <0 hay >0 phu thuoc vao huong' dan
         p_bullet->set_x_val(BULLET_VELOCITY_X_VAL);
         p_bullet->set_y_val(BULLET_VELOCITY_Y_VAL);

         p_bullet_list_.push_back(p_bullet);
      }
   }
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
   /** status_ k quy dinh boi on_ground_ **/
   if(status_ == TAKE_HIT_LEFT)
   {
      BaseObject::SetObject(txt_player_take_hit_left_);
   }
   else if(status_ == TAKE_HIT_RIGHT)
   {
      BaseObject::SetObject(txt_player_take_hit_right_);
   }
   else if(status_ == RESPAWN)
   {
      //
   }
   else if(status_ == KO_LEFT)
   {
      BaseObject::SetObject(txt_player_ko_left_);
   }
   else if(status_ == KO_RIGHT)
   {
      BaseObject::SetObject(txt_player_ko_right_);
   }

   /** status_ quy dinh boi on_ground_ **/
   if(on_ground_ == true)
   {
      /** Phan biet giua status va input.
      Su dung input co the lay duoc trang thai, nhung khi nha phim/chuot ra, input se mat.
      Status luu trang thai, cho du co nha phim/chuot, status van giu nguyen **/
      if(status_ == WALK_LEFT)
      {
         BaseObject::SetObject(txt_player_walk_left_);
      }
      else if (status_ == WALK_RIGHT)
      {
         BaseObject::SetObject(txt_player_walk_right_);
      }
      else if (status_ == IDLE_LEFT)
      {
         BaseObject::SetObject(txt_player_idle_left_);
      }
      else if(status_ == IDLE_RIGHT)
      {
         BaseObject::SetObject(txt_player_idle_right_);
      }
   }
   else // dang nhay hoac dang roi tu do
   {
      if(status_ == JUMP_LEFT)
      {
         BaseObject::SetObject(txt_player_jump_left_);
      }
      else if (status_ == JUMP_RIGHT)
      {
         BaseObject::SetObject(txt_player_jump_right_);
      }
   }
}

void MainObject::DoPlayer(Map& map_data)
{
   if(come_back_time_ == 0)
   {
      x_val_ = 0;
      //Xu ly nhan vat roi tu tu xuong
      y_val_ += PLAYER_GRAVITY_VELOCITY; //Toc do roi

      //Gioi han van toc roi
      if(y_val_ >= PLAYER_MAX_FALL_SPEED)
      {
         y_val_ = PLAYER_MAX_FALL_SPEED;
      }

      if(input_type_.jump_ == 1) //nv nhay len
      {
         if(on_ground_ == true) //neu nv dung duoi mat dat
         {
            /**K hong dung -= vi muon nhay nhanh **/
            y_val_ = -PLAYER_JUMP_VAL;
         }
         on_ground_ = false; //Set nv hien tai dang khong nam duoi dat

         //input_type_.jump_ = 0; //Ngay tu luc nhay len, set truoc flag dap xuong mat dat
         //Neu khong set, ngay sau khi dap xuong, nv tiep tuc nhay len vi flag van bang 1
      }
      /** LUU Y : O DAY KHONG SU DUNG else if, vi` nhan vat co the vua nhay? vua di chuyen sang phai/trai **/
      if(input_type_.left_ == 1) //nv di chuyen sang trai
      {
         x_val_ -= PLAYER_VELOCITY; //Tang toc do di chuyen len trai
      }
      if(input_type_.right_ == 1) // nv di chuyen sang phai
      {
         x_val_ += PLAYER_VELOCITY; //Tang toc do di chuyen len phai
      }
      if(input_type_.idle_ == 1)
      {
         //
      }
      //Ham kiem tra va cham voi tilemap, ham` nay` lam` thay doi x_pos_ va y_pos_
      CheckToMap(map_data);
      //Ham lam tile map chay theo nhan vat, ham` nay` lam` thay doi map_data.start_x_ (hay map_x_ cua nhan vat) theo x_pos_ moi'
      CenterEntityOnMap(map_data);
   }

   //Xu ly delay time giua 2 mang
   if(come_back_time_ > 0)
   {
      come_back_time_ --;
      if(come_back_time_ == 0)
      {
         InitPlayer(); //RESET lai nhan vat, roi tu tren cao xuong
      }
   }

   //Xu ly time bat' tu khi dinh dan.
   if(invul_time_ > 0)
   {
      invul_time_--;
      static bool reset_sts = true; //Khoi tao bien static bool chi so lan` reset status con` lai.

      //Set lai status ngay sau khi invul_time_ duoc khoi tao, ham` chi chay. 1 lan
      if((status_ == WALK_LEFT || status_ == IDLE_LEFT || status_ == JUMP_LEFT) && reset_sts == true)
      {
         status_ = TAKE_HIT_LEFT;
         reset_sts = false;
         //reset status = false, sau khi chay. het' 1 vong` frame, nv set lai status = idle
         //Khi do status se khong reset lai = take hit
         input_type_.left_ = 0;
         input_type_.idle_ = 1; // dung de chay. frame
         //Dung` di chuyen khi dinh' dan.
      }
      else if((status_ == WALK_RIGHT || status_ == IDLE_RIGHT || status_ == JUMP_RIGHT) && reset_sts == true)
      {
         status_ = TAKE_HIT_RIGHT;
         reset_sts = false;
         //reset status = false, sau khi chay. het' 1 vong` frame, nv set lai status = idle
         //Khi do status se khong reset lai = take hit
         input_type_.right_ = 0;
         input_type_.idle_ = 1; // dung de chay. frame
         //Dung` di chuyen khi dinh' dan.
      }

      if(invul_time_ == 0)
      {
         reset_sts = true;
         //Set lai reset status = true sau khi het' thoi gian bat' tu, de su dung trong lan` tiep theo dinh' dan.
      }
   }

   //Xu ly time cho den luc ket thuc chuong trinh
   if(ko_time_ > 0)
   {
      ko_time_--;

      static bool reset_sts = true;
      //Set lai status ngay sau khi invul_time_ duoc khoi tao, ham` chi chay. 1 lan
      if((status_ == WALK_LEFT || status_ == IDLE_LEFT || status_ == JUMP_LEFT) && reset_sts == true)
      {
         status_ = KO_LEFT;
         reset_sts = false;
         input_type_.left_ = 0;
         input_type_.idle_ = 0; //dung` de const frame
         //Dung` di chuyen khi chuan bi KO
      }
      else if((status_ == WALK_RIGHT || status_ == IDLE_RIGHT || status_ == JUMP_RIGHT) && reset_sts == true)
      {
         status_ = KO_RIGHT;
         reset_sts = false;
         input_type_.right_ = 0;
         input_type_.idle_ = 0; //dung` de const frame
         //Dung` di chuyen khi chuan bi KO
      }

      if(ko_time_ == 0)
      {
         reset_sts = true;
         /** BO SUNG : continue sub-menu **/
      }
   }
}

void MainObject::InitPlayer()
{
   //Neu vi tri nhan vat theo phuong x vuot qua 4 o tile
   if(x_pos_ >= 4*TILE_SIZE)
   {
      x_pos_ -= 4*TILE_SIZE;
   }
   else //x_pos < 4*TILE_SIZE (Nv dang o vi tri xuat phat)
   {
      x_pos_ = 0;
   }
   y_pos_ = PLAYER_START_FALL_Y_POS;
   x_val_ = 0;
   y_val_ = 0;
   on_ground_ = false;
   status_ = JUMP_RIGHT;
}

void MainObject::CheckToMap(Map& map_data)
{
   //Cach kiem tra nay chi chuan xac, neu tat ca cac tile deu la 64x64

   //x1x2y1y2 tinh theo o tiles, KHONG PHAI PIXEL
   //Gioi han kiem tra tu a => b theo phuong x
   int x1 = 0;
   int x2 = 0;

   //Gioi han kiem tra tu a => b theo phuong y
   int y1 = 0;
   int y2 = 0;

   //Kiem tra theo phuong ngang
   int height_min = (height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE);

   //Tim` xem nhan^ vat. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_ + x_val_) / TILE_SIZE;
   //De ma duong` bien cua nhan vat co the trung voi bien cua TILE_MAP
   //Ta tru di 1 luong EPSILON la sai so de check chuan xac hon
   x2 = (x_pos_ + x_val_ + width_frame_ - EPSILON) / TILE_SIZE;

   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong y
   y1 = (y_pos_) / TILE_SIZE; //Khong cong them y_val_
   y2 = (y_pos_ + height_min - EPSILON) / TILE_SIZE; /** LUU Y : DAT EPSILON_Y O DAY FIX TEXTURE NON 128x128 */

   /**

           x1,y1 ********* x2,y1 * *
           *               *
           *               *
           *               *
           *               *
           *               *
           x1,y2 ********* x2,y2 * *
           *               *
           *               *

   **/

   //Nam trong vung ban do tile map
   if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
   {
      if(x_val_ > 0) //Di chuyen sang phai
      {
         //Check va cham voi Item
         int val1 = map_data.tile[y1][x2];
         int val2 = map_data.tile[y2][x2];

         //Check va cham voi SPELL_BOOK
         if((SPELL_BOOK <= val1 && val1 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1)
          ||(SPELL_BOOK <= val2 && val2 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1))
         {
            //Set gia tri cua no = 0 => Lan render tiep theo se ra o tile blank
            map_data.tile[y1][x2] = 0;
            map_data.tile[y2][x2] = 0;
            is_ice_shard_learned_ = true;
         }
         else
         {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE )
            //Check o ben phai, va o ben duoi cua no
            {
               x_pos_ = x2*TILE_SIZE;
               x_pos_ -= (width_frame_ + EPSILON);
               x_val_ = 0;
            }
         }
      }
      else if(x_val_ < 0) //Move left
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y2][x1];

         if((SPELL_BOOK <= val1 && val1 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1)
          ||(SPELL_BOOK <= val2 && val2 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1))
         {
            map_data.tile[y1][x1] = 0;
            map_data.tile[y2][x1] = 0;
            is_ice_shard_learned_ = true;
         }
         else
         {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            //Check o ben trai, va o ben duoi cua no
            {
               x_pos_ = (x1 + EPSILON)*TILE_SIZE;
               x_val_ = 0;
            }
         }
      }
   }

   /**

           x1,y1 ********* x2,y1 ***
           *               *
           *               *
           *               *
           *               *
           *               *
           x1,y2 ********* x2,y2 ***
           *               *
           *               *

   **/


   //Check theo phuong thang dung
   int width_min = (width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE);

   //Tim` xem nhan^ vat. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_)/TILE_SIZE;
   x2 = (x_pos_ + width_min)/TILE_SIZE;

   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong y
   y1 = (y_pos_ + y_val_)/TILE_SIZE;
   y2 = (y_pos_ + y_val_ + height_frame_ - EPSILON) / TILE_SIZE;

   //Nam ben trong tile map
   if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
   {
      if(y_val_ > 0) //Idle
      {
         int val1 = map_data.tile[y2][x1];
         int val2 = map_data.tile[y2][x2];

         if((SPELL_BOOK <= val1 && val1 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1)
          ||(SPELL_BOOK <= val2 && val2 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1))
         {
            map_data.tile[y2][x1] = 0;
            map_data.tile[y2][x2] = 0;
            is_ice_shard_learned_ = true;
         }
         else
         {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
               y_pos_ = y2*TILE_SIZE;
               y_pos_ -= (height_frame_ + EPSILON);
               y_val_ = 0;
               on_ground_ = true;

               //Set lai status sau khi vua dap' xuong mat dat
               if(status_ == JUMP_LEFT)
               {
                  status_ = IDLE_LEFT;
               }
               else if(status_ == JUMP_RIGHT)
               {
                  status_ = IDLE_RIGHT;
               }
            }
         }
      }
      else if(y_val_ < 0) //Jump
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y1][x2];

         if((SPELL_BOOK <= val1 && val1 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1)
          ||(SPELL_BOOK <= val2 && val2 <= SPELL_BOOK + SPELL_BOOK_FRAME - 1))
         {
            map_data.tile[y1][x1] = 0;
            map_data.tile[y1][x2] = 0;
            is_ice_shard_learned_ = true;
         }
         else
         {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
               y_pos_ = (y1 + EPSILON)*TILE_SIZE;
               y_val_ = 0;
            }
         }
      }
   }

   //printf("%d\n", &on_ground_);

   //Neu khong phai TH dac biet, di chuyen nhan vat theo x_val_ va y_val_
   x_pos_ += x_val_;
   y_pos_ += y_val_;

   //Nhan vat di chuyen cham toi bien trai'
   if(x_pos_ < 0)
   {
      x_pos_ = 0;
   }
   else if(x_pos_ + width_frame_ > map_data.max_x_) //Nhan vat di chuyen cham toi bien phai?
   {
      x_pos_ = map_data.max_x_ - width_frame_ - EPSILON;
   }
   //Nhan vat di chuyen cham toi bien duoi (roi xuong vuc)
   if(y_pos_ > map_data.max_y_)
   {
      come_back_time_ = 60; //theo delay time giua 2 mang la (60 frame)
   }
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
   map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
   //Kiem tra luc o goc tile map ma nv xuat hien, chua di chuyen qua' 1/2 man hinh
   //thi chua cho tile map chay theo nv
   if(map_data.start_x_ < 0)
   {
      map_data.start_x_ = 0;
   }
   //Nhu tren, trg hop nay la goc tile map cuoi cung, con dung 1 goc tile map = man hinh
   //thi cung khong cho tile map chay theo nv nua
   else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) //max_x_ theo pixel
   {
      map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
   }

   //Kiem tra theo phuong y (danh cho Game di chuyen theo phuong thang dung)
   map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);

   if(map_data.start_y_ < 0)
   {
      map_data.start_y_ = 0;
   }
   else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) //max_y_ theo pixel
   {
      map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
   }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
   for(int i = 0 ; i < p_bullet_list_.size() ; ++i)
   {
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if(p_bullet != NULL)
      {
         if(p_bullet->get_is_move() == true)
         {
            p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_bullet->Render(des);
         }
         else
         {
            p_bullet_list_.erase(p_bullet_list_.begin() + i);
            if(p_bullet != NULL)
            {
               delete p_bullet;
               p_bullet = NULL;
            }
         }
      }
   }
}

void MainObject::RemoveBullet(const int& idx)
{
   int size_ = p_bullet_list_.size();
   if(size_ > 0 && idx < size_)
   {
      BulletObject* p_bullet = p_bullet_list_.at(idx);
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);

      if(p_bullet != NULL)
      {
         delete p_bullet;
         p_bullet = NULL;
      }
   }
}

void MainObject::InitExplosion(const int& objType, const int& obj_x_pos, const int& obj_y_pos, SDL_Renderer* des)
{
   ExpObject* exp_obj = new ExpObject();
   exp_obj->set_exp_type(ExpObject::EXP_THREAT);
   exp_obj->LoadImgExp(g_renderer);
   exp_obj->set_clips();

   int exp_x_pos = obj_x_pos - exp_obj->get_frame_width()*0.5;
   int exp_y_pos = obj_y_pos - exp_obj->get_frame_height()*0.5;
   exp_obj->SetRect(exp_x_pos, exp_y_pos);
   exp_obj->set_is_exp(true);

   p_exp_list_.push_back(exp_obj);
}

void MainObject::HandleExplosion(SDL_Renderer* des)
{
   //Check tung vu no trong chuoi~ vu no
   for(int i = 0 ; i < p_exp_list_.size() ; ++i)
   {
      //Lay tung vu no ra
      ExpObject* p_exp = p_exp_list_.at(i);
      if(p_exp != NULL)
      {
         if(p_exp->get_is_exp() == true)
         {
            p_exp->Show(des);
         }
         else //get_is_exp() == false // frame_ > EXP_NUM_FRAME
         {
            p_exp_list_.erase(p_exp_list_.begin() + i);
            if(p_exp != NULL)
            {
               delete p_exp;
               p_exp = NULL;
            }
         }
      }
   }
}

//Chua dung den
void MainObject::RemoveExplosion(const int& idx)
{
   int size_ = p_exp_list_.size();
   if(size_ > 0 && idx < size_)
   {
      ExpObject* p_exp = p_exp_list_.at(idx);
      p_exp_list_.erase(p_exp_list_.begin() + idx);

      if(p_exp != NULL)
      {
         delete p_exp;
         p_exp = NULL;
      }
   }
}

