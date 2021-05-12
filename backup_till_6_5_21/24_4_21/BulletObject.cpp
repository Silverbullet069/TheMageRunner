
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

   if(bullet_type_ == SPHERE_BULLET)
   {
      ret = LoadImg("bullet_sphere.png", des);
   }
   else if(bullet_type_ == LASER_BULLET)
   {
      ret = LoadImg("bullet_laser.png", des);
   }
   else if(bullet_type_ == FIRE_BALL)
   {
      ret = LoadImg(g_name_skll_main_fire_ball, des);
   }
   else if(bullet_type_ == ICE_SHARD)
   {
      ret = LoadImg(g_name_skill_main_ice_shard, des);
   }
   return ret;
}

void BulletObject::CheckToMap(Map& map_data)
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
   int height_min = (rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE);

   //Tim` xem vien^ dan. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua vien^ dan. la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_ + x_val_) / TILE_SIZE;
   //De ma duong` bien cua nhan vat co the trung voi bien cua TILE_MAP
   //Ta tru di 1 luong EPSILON la sai so de check chuan xac hon
   x2 = (x_pos_ + x_val_ + width_frame_ - EPSILON) / TILE_SIZE;

   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong y
   y1 = (y_pos_) / TILE_SIZE; //Khong cong them y_val_
   y2 = (y_pos_ + height_min - EPSILON - epsilon_y) / TILE_SIZE; /** LUU Y : EPSILON_Y FIX TEXTURE NON 64x64 */

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

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            //Set gia tri cua no = 0 => Lan render tiep theo se ra o tile blank
            map_data.tile[y1][x2] = 0;
            map_data.tile[y2][x2] = 0;
            IncreaseMoney();
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

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            map_data.tile[y1][x1] = 0;
            map_data.tile[y2][x1] = 0;
            IncreaseMoney();
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

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            map_data.tile[y2][x1] = 0;
            map_data.tile[y2][x2] = 0;
            IncreaseMoney();
         }
         else
         {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
               y_pos_ = y2*TILE_SIZE;
               y_pos_ -= (height_frame_ + EPSILON);
               y_val_ = 0;
               on_ground_ = true;
               /**
               //Neu nhu luc bat dau khong bam chuot/ban phim, set trang thai cua nhan vat la RIGHT
                  if(status_ == WALK_NONE)
                  {
                  status_ = WALK_RIGHT;
                  }
               */
            }
         }
      }
      else if(y_val_ < 0) //Jump
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y1][x2];

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            map_data.tile[y1][x1] = 0;
            map_data.tile[y1][x2] = 0;
            IncreaseMoney();
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
