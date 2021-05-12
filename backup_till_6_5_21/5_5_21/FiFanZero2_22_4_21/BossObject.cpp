
#include "BossObject.h"

BossObject::BossObject()
{
   x_pos_ = 0;
   y_pos_ = 0;
   x_val_ = 0;
   y_val_ = 0;
   map_x_ = 0;
   map_y_ = 0;
   input_type_.left_ = 0;
   input_type_.right_ = 0;
   input_type_.up_ = 0;
   input_type_.down_ = 0;
   input_type_.jump_ = 0;
   on_ground_ = false;
   frame_ = 0;
   width_frame_ = 0;
   height_frame_ = 0;
   think_time_ = 0;
}

BossObject::~BossObject()
{
   //
}

bool BossObject::LoadImg(const std::string file_path, SDL_Renderer* des)
{
   bool ret = BaseObject::LoadImg(file_path, des, SDL_TRUE, DEMO);

   if(!ret) { printf("Unable to load boss object!"); }
   else
   {
      width_frame_ = rect_.w/BOSS_FRAME_NUM; //rect_.w la chieu dai cua 1 sprite gom 8 frame
      height_frame_ = rect_.h;
   }

   return ret;
}

void BossObject::set_clips()
{
   if(width_frame_ > 0 && height_frame_ > 0)
   {
      for(int i = 0 ; i < BOSS_FRAME_NUM ; ++i)
      {
         frame_clip_[i].x = i*width_frame_;
         frame_clip_[i].y = 0;
         frame_clip_[i].w = width_frame_;
         frame_clip_[i].h = height_frame_;
      }
   }
}

void BossObject::Show(SDL_Renderer* des)
{
   //Khong nam trong pham vi delay time giua 2 mang
   if(think_time_ == 0)
   {
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_ - map_y_;

      frame_++; //Tang lien tuc, vi Boss khong co xu ly trang thai input

      if(frame_ >= BOSS_FRAME_NUM)
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

void BossObject::DoBoss(Map& map_data)
{
   if(think_time_ == 0)
   {
      //Xu ly Boss roi tu tu xuong
      x_val_ = 0;
      y_val_ += GRAVITY_SPEED; //Toc do roi

      //Gioi han van toc roi
      if(y_val_ >= MAX_FALL_SPEED)
      {
         y_val_ = MAX_FALL_SPEED;
      }

      //Boss di chuyen sang trai
      if(input_type_.left_ == 1)
      {
         //Tang toc do di chuyen sang trai
         x_val_ -= BOSS_SPEED;
      }
      // Boss di chuyen sang phai
      else if(input_type_.right_ == 1)
      {
         //Tang toc do di chuyen sang phai
         x_val_ += BOSS_SPEED;
      }
      //Boss nhay len (bay len)
      else if(input_type_.jump_ == 1)
      {
         //Neu Boss dung tren mat dat
         if(on_ground_ == true)
         {
            //Khong dung -= vi muon nhay nhanh
            y_val_ = -BOSS_HIGH_VAL;
         }

         //Set flag Boss hien tai dang lo lung
         on_ground_ = false;

         //Ngay luc nhay len, set truoc flag dap xuong mat dat
         //Neu khong, ngay sau khi dap xuong, Boss tiep tuc nhay len vi flag van bang 1
         input_type_.jump_ = 0;

      }
      //Ham kiem tra Boss va cham voi tilemap
      CheckToMap(map_data);
   }

   if(think_time_ > 0)
   {
      think_time_--;
      if(think_time_ == 0)
      {
         InitBoss();
      }
   }
}

void BossObject::InitBoss()
{
   //Set lai flag Boss lo lung khi hoi sinh
   on_ground_ = false;

   //Neu vi tri Boss theo phuong x vuot qua 4 o tile
   if(x_pos_ > 256)
   {
      x_pos_ -= 256; //4 o tile
   }
   else //Boss dang o vi tri xuat phat
   {
      x_pos_ = 0;
   }
   y_pos_ = 0;

   //Set lai van toc cua Boss
   x_val_ = 0;
   y_val_ = 0;

   //Set lai think_time_ = 0 (trang thai khong delay)
   think_time_ = 0;

   //Set lai trang thai di chuyen (Boss huong' sang trai)
   input_type_.left_ = 1;
}

void BossObject::CheckToMap(Map& map_data)
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
      think_time_ = 60; //theo delay time giua 2 mang la (60 frame)
   }
} //Copy tu ThreatObject.cpp

void BossObject::InitBullet(SDL_Renderer* des)
{
   BulletObject* p_bullet = new BulletObject();
   bool ret = p_bullet->LoadImg("boss_bullet.png", des, SDL_TRUE, DEMO);
   if(!ret) {printf ("Unable to load boss bullet!");}
   else
   {
      p_bullet->set_is_move(true);
      p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
      p_bullet->SetRect(rect_.x - 50, rect_.y + height_frame_ - 30);
      p_bullet->set_x_val(15);

      bullet_list_.push_back(p_bullet);
   }
}

void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
   if(frame_ == 18) //Tai frame 18th tro di la luc Boss ban' dan.
   {
      InitBullet(des);
   }

   //Check tung vien dan cua BOSS
   for(int i = 0 ; i < bullet_list_.size() ; ++i)
   {
      BulletObject* p_bullet = bullet_list_.at(i);
      if(p_bullet != NULL)
      {
         if(p_bullet->get_is_move())
         {
            p_bullet->HandleMove(x_limit, y_limit);
            p_bullet->Render(des);
         }
         else //dan khong di chuyen (qua gioi han hoac trung' Main)
         {
            //Giai phong vien dan
            p_bullet->Free();
            bullet_list_.erase(bullet_list_.begin() + i);

            /*
            //Su dung lai vien dan
            p_bullet->set_is_move(true);
            p_bullet->SetRect(this->rect_.x + 5, y_pos_ + 10); //rect_.x la vi tri cua threat
            */
         }
      }
   }
}



