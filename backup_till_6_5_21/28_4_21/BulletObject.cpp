
#include "BulletObject.h"

BulletObject::BulletObject()
{
   x_pos_ = 0;
   y_pos_ = 0;

   x_val_ = 0;
   y_val_ = 0;
   is_move_ = false;
   bullet_type_ = FIRE_BALL;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
   if(bullet_dir_ == DIR_RIGHT)
   {
      rect_.x += x_val_;
      if(rect_.x > x_border)
      {
         is_move_ = false;
      }
   }
   else if(bullet_dir_ == DIR_LEFT)
   {
      rect_.x -= x_val_;
      if(rect_.x < 0)
      {
         is_move_ = false;
      }
   }
   else if(bullet_dir_ == DIR_UP)
   {
      rect_.y -= y_val_;
      if(rect_.y < 0)
      {
         is_move_ = false;
      }
   }
   else if(bullet_dir_ == DIR_UP_LEFT)
   {
      rect_.x -= x_val_;
      if(rect_.x < 0){ is_move_ = false; }

      rect_.y -= y_val_;
      if(rect_.y < 0){ is_move_ = false; }
   }
   else if(bullet_dir_ == DIR_UP_RIGHT)
   {
      rect_.x += x_val_;
      if(rect_.x > x_border) { is_move_ = false; }

      rect_.y -= y_val_;
      if(rect_.y < 0) { is_move_ = false;}
   }
   else if(bullet_dir_ == DIR_DOWN_LEFT)
   {
      rect_.x -= x_val_;
      if(rect_.x < 0){ is_move_ = false; }

      rect_.y += y_val_;
      if(rect_.y > y_border) { is_move_ = false;}
   }
   else if(bullet_dir_ == DIR_DOWN_RIGHT)
   {
      rect_.x += x_val_;
      if(rect_.x > x_border) { is_move_ = false; }

      rect_.y += y_val_;
      if(rect_.y > y_border) { is_move_ = false;}
   }
}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
   bool ret = false;

   if(bullet_type_ == FIRE_BALL)
   {
      ret = LoadImg(g_name_skill_main_fire_ball, des);
   }
   else if(bullet_type_ == ICE_SHARD)
   {
      ret = LoadImg(g_name_skill_main_ice_shard, des);
   }
   else if(bullet_type_ == FIRE_BALL_WISP_LEFT)
   {
      ret = LoadImg(g_name_skill_wisp_fire_ball_left, des);
   }
   else if(bullet_type_ == FIRE_BALL_WISP_RIGHT)
   {
      ret = LoadImg(g_name_skill_wisp_fire_ball_right, des);
   }

   return ret;
}

void BulletObject::CheckToMap(Map& map_data)
{
   //x1x2y1y2 tinh theo o tiles, KHONG PHAI PIXEL
   //Gioi han kiem tra tu a => b theo phuong x
   int x1 = 0;
   int x2 = 0;

   //Gioi han kiem tra tu a => b theo phuong y
   int y1 = 0;
   int y2 = 0;

   //Kiem tra theo phuong ngang
   int height_min = (rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE);

   //Tim` xem nhan^ vat. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_ + x_val_) / TILE_SIZE;
   //De ma duong` bien cua nhan vat co the trung voi bien cua TILE_MAP
   //Ta tru di 1 luong EPSILON la sai so de check chuan xac hon
   x2 = (x_pos_ + x_val_ + rect_.w - EPSILON) / TILE_SIZE;

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
         int val1 = map_data.tile[y1][x2];
         int val2 = map_data.tile[y2][x2];

         if((val1 != BLANK_TILE && val1 != STATE_MONEY) ||(val2 != BLANK_TILE && val2 != STATE_MONEY)) //
         //Check o ben phai, va o ben duoi cua no
         {
            is_move_ = false;
         }
      }
      else if(x_val_ < 0) //Move left
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y2][x1];

         if((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) //
         //Check o ben trai, va o ben duoi cua no
         {
            //Chan vien dan lai.
            //x_pos_ = (x1 + EPSILON)*TILE_SIZE;
            //x_val_ = 0;

            is_move_ = false;
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


   /**

   //Check theo phuong thang dung
   int width_min = (rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE);

   //Tim` xem nhan^ vat. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_)/TILE_SIZE;
   x2 = (x_pos_ + width_min)/TILE_SIZE;

   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong y
   y1 = (y_pos_ + y_val_)/TILE_SIZE;
   y2 = (y_pos_ + y_val_ + rect_.h - EPSILON) / TILE_SIZE;

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
            y_pos_ -= (rect_.h + EPSILON);
            y_val_ = 0;
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

   */

   //Neu khong phai TH dac biet, di chuyen vien dan theo x_val_ va y_val_
   x_pos_ += x_val_;
   //y_pos_ += y_val_;

   //Vien dan di chuyen cham toi bien trai'
   if(x_pos_ < 0)
   {
      x_pos_ = 0;
   }
   else if(x_pos_ + rect_.w > map_data.max_x_) //Vien dan di chuyen cham toi bien phai?
   {
      x_pos_ = map_data.max_x_ - rect_.w - EPSILON;
   }
}
