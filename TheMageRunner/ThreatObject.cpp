
#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
   width_frame_ = 0;
   height_frame_ = 0;
   map_x_ = 0;
   map_y_ = 0;
   x_pos_ = 0;
   y_pos_ = 0;
   x_val_ = 0;
   y_val_ = 0;
   on_ground_ = false;
   come_back_time_ = 0;
   width_frame_ = 0;
   height_frame_ = 0;
   frame_ = 0;
   type_move_ = STATIC_THREAT;
   type_element_ = FIRE;
   animation_a_ = 0;
   animation_b_ = 0;
   hidden_live_ = 3;

   txt_threat_move_left_ = NULL;
   txt_threat_move_right_ = NULL;
   txt_threat_die_left_ = NULL;
   txt_threat_die_right_ = NULL;
}

ThreatObject::~ThreatObject()
{
   if(txt_threat_move_left_ != NULL)
   {
      SDL_DestroyTexture(txt_threat_move_left_);
      txt_threat_move_left_ = NULL;
   }
   if(txt_threat_move_right_ != NULL)
   {
      SDL_DestroyTexture(txt_threat_move_right_);
      txt_threat_move_right_ = NULL;
   }
   if(txt_threat_die_left_ != NULL)
   {
      SDL_DestroyTexture(txt_threat_die_left_);
      txt_threat_die_left_ = NULL;
   }
   if(txt_threat_die_right_ != NULL)
   {
      SDL_DestroyTexture(txt_threat_die_right_);
      txt_threat_die_right_ = NULL;
   }
}

void ThreatObject::LoadAllThreatAction(SDL_Renderer* des)
{
   txt_threat_move_left_ = SDLCommonFunction::LoadTexture(g_name_threat_fire_wisp_move_left, des,
                                                          rect_, SDL_FALSE, BLACK);
   txt_threat_move_right_ = SDLCommonFunction::LoadTexture(g_name_threat_fire_wisp_move_right, des,
                                                          rect_, SDL_FALSE, BLACK);
   txt_threat_die_left_ = SDLCommonFunction::LoadTexture(g_name_threat_fire_wisp_die_left, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_threat_die_right_ = SDLCommonFunction::LoadTexture(g_name_threat_fire_wisp_die_right, des,
                                                          rect_, SDL_FALSE, WHITE);
   width_frame_ = rect_.w/THREAT_FRAME_NUM;
   height_frame_ = rect_.h;
}

/**
bool ThreatObject::LoadImg(const std::string file_path, SDL_Renderer* des,
                           const int& color_flag, const SDL_Color& color)
{
   bool ret = BaseObject::LoadImg(file_path, des, );

   if(!ret) { printf("Unable to load threat object!"); }
   else
   {
      width_frame_ = rect_.w/THREAT_FRAME_NUM;
      //Vi rect_.w la chieu dai cua 1 sprite gom 8 frame
      height_frame_ = rect_.h;
   }

   return ret;
}
*/

SDL_Rect ThreatObject::GetRectFrame()
{
   SDL_Rect rect_tmp = {0, 0, 0, 0};
   rect_tmp.x = rect_.x;
   rect_tmp.y = rect_.y;
   rect_tmp.w = width_frame_;
   rect_tmp.h = height_frame_;
   return rect_tmp;
}

void ThreatObject::set_clips()
{
   if(width_frame_ > 0 && height_frame_ > 0)
   {
      for(int i = 0 ; i < THREAT_FRAME_NUM ; ++i)
      {
         frame_clip_[i].x = i*width_frame_;
         frame_clip_[i].y = 0;
         frame_clip_[i].w = width_frame_;
         frame_clip_[i].h = height_frame_;
      }
   }
}

void ThreatObject::Show(SDL_Renderer* des)
{
   //Khong nam trong pham vi delay time giua 2 mang
   if(come_back_time_ == 0)
   {
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_ - map_y_;

      frame_++; //Tang lien tuc, vi khong co xu ly trang thai input

      if(frame_ >= THREAT_FRAME_NUM)
      {
         frame_ = 0;
      }

      SDL_Rect* current_clip = &frame_clip_[frame_];

      SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

      //De phong
      if(current_clip != NULL)
      {
         renderQuad.w = current_clip->w;
         renderQuad.h = current_clip->h;
      }

      SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
   }
}

void ThreatObject::DoThreat(Map& map_data)
{
   if(come_back_time_ == 0)
   {
      x_val_ = 0;
      y_val_ += THREAT_GRAVITY_VELOCITY;
      if(y_val_ >= THREAT_MAX_FALL_VELOCITY)
      {
         y_val_ = THREAT_MAX_FALL_VELOCITY;
      }

      if(type_move_ == ThreatObject::MOVE_LEFT)
      {
         x_val_ -= THREAT_VELOCITY;
      }
      else if(type_move_ == ThreatObject::MOVE_RIGHT)
      {
         x_val_ += THREAT_VELOCITY;
      }
      else if(type_move_ == ThreatObject::DIE_LEFT)
      {
         //
      }
      else if(type_move_ == ThreatObject::DIE_RIGHT)
      {
         //
      }

      CheckToMap(map_data);
   }
   else if(come_back_time_ > 0) //Ke thu dang trong delay time de hoi sinh
   {
      come_back_time_--; //Giam thoi gian (tinh theo frame)
      if(come_back_time_ == 0)
      {
         InitThreat();
      }
   }
}

void ThreatObject::InitThreat()
{
   x_val_ = 0;
   y_val_ = 0;
   if(x_pos_ > 4*TILE_SIZE) //Gia su: ke thu xuat hien lui` lai. de tranh vuc
   {
      x_pos_ -= 4*TILE_SIZE; //Lui lai vi tri xuat hien tiep theo
      animation_a_ -= 4*TILE_SIZE; //Lui lai bien trai
      animation_b_ -= 4*TILE_SIZE; //Lui lai bien phai
   }
   else
   {
      x_pos_ = 0;
   }
   y_pos_ = THREAT_START_FALL_Y_POS;
   come_back_time_ = 0;
   type_move_ = ThreatObject::MOVE_LEFT;
   type_element_ = ThreatObject::FIRE;
}

void ThreatObject::CheckToMap(Map& map_data)
{
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
   y2 = (y_pos_ + height_min - EPSILON) / TILE_SIZE;

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
      if(x_val_ > 0) //Move right
      {
         //Check collision with coins
         int val1 = map_data.tile[y1][x2];
         int val2 = map_data.tile[y2][x2];

         if((val1 != BLANK_TILE && val1 != STATE_MONEY)||(val2 != BLANK_TILE && val2 != STATE_MONEY))
         //Check o ben phai, va o ben duoi cua no
         {
            x_pos_ = x2*TILE_SIZE;
            x_pos_ -= (width_frame_ + EPSILON);
            this->SetAnimationPos(animation_a_, x_pos_ - EPSILON);
            x_val_ = 0;
         }
      }
      else if(x_val_ < 0) //Move left
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y2][x1];

         if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
         //Check o ben trai, va o ben duoi cua no
         {
            x_pos_ = (x1 + EPSILON)*TILE_SIZE;
            this->SetAnimationPos(x_pos_ + EPSILON, animation_b_);
            x_val_ = 0;
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

         if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
         {
            y_pos_ = y2*TILE_SIZE;
            y_pos_ -= (height_frame_ + EPSILON);
            y_val_ = 0;
            on_ground_ = true;
            //Neu nhu luc bat dau khong bam chuot/ban phim, set trang thai cua nhan vat la RIGHT
         }
      }
      else if(y_val_ < 0) //Jump
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y1][x2];

         if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
         {
            y_pos_ = (y1 + EPSILON)*TILE_SIZE;
            y_val_ = 0;
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

void ThreatObject::ImpMoveType(SDL_Renderer* des)
{
   if(type_move_ == STATIC_THREAT)
   {
      BaseObject::SetObject(txt_threat_move_left_);
   }
   else
   {
      if(type_move_ == ThreatObject::DIE_LEFT)
         {
            BaseObject::SetObject(txt_threat_die_left_);
         }
      else if(type_move_ == ThreatObject::DIE_RIGHT)
         {
            BaseObject::SetObject(txt_threat_die_right_);
         }

      if(on_ground_ == true) //ke thu` duoi mat dat
      {
         if(x_pos_ > animation_b_)
         {
            type_move_ = ThreatObject::MOVE_LEFT;
            BaseObject::SetObject(txt_threat_move_left_);
            this->ResetBullet(des);
         }
         else if(x_pos_ < animation_a_)
         {
            type_move_ = ThreatObject::MOVE_RIGHT;
            BaseObject::SetObject(txt_threat_move_right_);
            this->ResetBullet(des);
         }
         else if(type_move_ == ThreatObject::DIE_LEFT)
         {
            BaseObject::SetObject(txt_threat_die_left_);
         }
         else if(type_move_ == ThreatObject::DIE_RIGHT)
         {
            BaseObject::SetObject(txt_threat_die_right_);
         }

      }
      else //Ke thu tren khong trung (luc khoi tao hoac hoi sinh sau khi roi xuong vuc)
      {
         if(type_move_ = ThreatObject::MOVE_LEFT)
         {
            BaseObject::SetObject(txt_threat_move_left_);
         }
      }
   }
}

void ThreatObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* des)
{
   if(p_bullet != NULL)
   {
      bool ret = p_bullet->LoadImgBullet(des);
      if(!ret) printf("Unable to load bullet threat!");
      else
      {
         p_bullet->set_is_move(true);
         //Set DIR_LEFT vi ke thu duoc khoi tao ban dau di chuyen ben trai
         p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
         //KHONG CO + THREAT_BULLET_MARGINS_X_VAL
         p_bullet->SetRect(this->x_pos_, this->y_pos_ + THREAT_BULLET_MARGINS_Y_VAL);
         //x_pos_ la vi tri cua threat tren tile map
         //Set theo x_pos_ vi rect_.x cua ThreatObject chua duoc tinh'
         p_bullet->set_x_val(THREAT_BULLET_VELOCITY);

         bullet_list_.push_back(p_bullet);
      }
   }
}

void ThreatObject::ResetBullet(SDL_Renderer* des)
{
   for(int i = 0 ; i < bullet_list_.size() ; ++i)
   {
      BulletObject* p_bullet = bullet_list_.at(i);
      if(p_bullet != NULL)
      {
         p_bullet->SetRect(this->rect_.x + width_frame_ + EPSILON, y_pos_ + THREAT_BULLET_MARGINS_Y_VAL);

         if(type_move_ == ThreatObject::MOVE_RIGHT)
         {
            p_bullet->set_bullet_type(BulletObject::WISP_FIRE_BALL_RIGHT);
            p_bullet->LoadImgBullet(des);
         }
         else if(type_move_ == ThreatObject::MOVE_LEFT)
         {
            p_bullet->set_bullet_type(BulletObject::WISP_FIRE_BALL_LEFT);
            p_bullet->LoadImgBullet(des);
         }
      }
   }
}

void ThreatObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit,
                              const int& main_x_pos, const int& main_status)
{
   for(int i = 0 ; i < bullet_list_.size() ; ++i)
   {
      BulletObject* p_bullet = bullet_list_.at(i);
      if(p_bullet != NULL)
      {
         if(p_bullet->get_is_move() == true)
         {
            if(type_move_ == ThreatObject::MOVE_LEFT)
            {
               p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
               int bullet_distance = this->rect_.x + width_frame_ - p_bullet->GetRect().x;
               if(bullet_distance > 0 && bullet_distance < THREAT_BULLET_MAX_RANGED)
               {
                  p_bullet->HandleMove(x_limit, y_limit);
                  p_bullet->HandleWhileMainCenter(main_x_pos, main_status);
                  p_bullet->Render(des);
               }
               else //Vien dan di qua' pham vi patrol
               {
                  p_bullet->set_is_move(false);
               }
            }
            else if(type_move_ == ThreatObject::MOVE_RIGHT)
            {
               p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);

               int bullet_distance = p_bullet->GetRect().x + 20 - (this->rect_.x + width_frame_);
               if(bullet_distance > 0 && bullet_distance < THREAT_BULLET_MAX_RANGED)
               {
                  p_bullet->HandleMove(x_limit, y_limit);
                  p_bullet->HandleWhileMainCenter(main_x_pos, main_status);
                  p_bullet->Render(des);
               }
               else //Vien dan di qua' pham vi patrol
               {
                  p_bullet->set_is_move(false);
               }
            }
         }
         else //get_is_move() == false
         {
            p_bullet->set_is_move(true);

            if(type_move_ == ThreatObject::MOVE_RIGHT) //ke thu di chuyen sang phai
            {
               p_bullet->SetRect(this->rect_.x + width_frame_, y_pos_ + THREAT_BULLET_MARGINS_Y_VAL);
            }
            else if(type_move_ == ThreatObject::MOVE_LEFT) //ke thu di chuyen sang trai
            {
               p_bullet->SetRect(this->rect_.x, y_pos_ + THREAT_BULLET_MARGINS_Y_VAL);
            }
         }
      }
   }
}

void ThreatObject::RemoveBullet(const int& idx)
{
   int size_ = bullet_list_.size();
   if(size_ > 0 && idx < size_)
   {
      BulletObject* p_bullet = bullet_list_.at(idx);
      bullet_list_.erase(bullet_list_.begin() + idx);

      if(p_bullet != NULL)
      {
         delete p_bullet;
         p_bullet = NULL;
      }
   }
}
