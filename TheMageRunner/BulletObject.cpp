
#include "BulletObject.h"
#include "MainObject.h" //Phuc vu ham` HandleWhileMainCenter

BulletObject::BulletObject()
{
   x_pos_ = 0;
   y_pos_ = 0;

   x_val_ = 0;
   y_val_ = 0;
   is_move_ = false;
   bullet_type_ = SKILL_NONE;
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

void BulletObject::HandleWhileMainCenter(const int& main_x_pos, const int& main_status)
{
   int left_margin_x = SCREEN_WIDTH/2;
   int right_margin_x = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH/2;

   //Khoi tao gia' tri. x_pos ban dau
   static int post_main_x_pos = MAX_MAP_X*TILE_SIZE + EPSILON;
   //Neu x_pos cu~ == x_pos_ moi => map_data khong thay doi, ta bo qua ham` nay`
   if(post_main_x_pos == main_x_pos ) return;
   //Neu map_data khac', ta gan x_pos_ cu~ = x_pos moi'
   post_main_x_pos = main_x_pos;

   /**
      left_margin_x                           right_margin_x
   ***********************************************
   *  *                                       *  *
   *  *                                       *  *
   *  *                                       *  *
   *  *                                       *  *
   ***********************************************

   **/

   if(main_x_pos > left_margin_x && main_x_pos < right_margin_x)
   {
      //Neu vien dan ban' huong' ben phai'
      if(bullet_dir_ == DIR_RIGHT)
      {
         //Nhan vat di chuyen sang ben trai'
         if(main_status == MainObject::WALK_LEFT || main_status == MainObject::JUMP_LEFT)
         {
            //=> Vien dan bi lam cham lai, phai tang toc do
            rect_.x += PLAYER_VELOCITY;

         }
         //Nhan vat cung~ di chuyen sang ben phai?
         else if(main_status == MainObject::WALK_RIGHT || main_status == MainObject::JUMP_RIGHT)
         {
            //=> Vien dan duoc gia toc, phai giam toc do
            rect_.x -= PLAYER_VELOCITY;
         }
      }
      //Neu vien dan ban' huong' ben trai'
      else if(bullet_dir_ == DIR_LEFT)
      {
         //Nhan vat cung~ di chuyen sang ben trai'
         if(main_status == MainObject::WALK_LEFT || main_status == MainObject::JUMP_LEFT)
         {
            //=> Vien dan duoc gia toc, phai giam toc do
            rect_.x += PLAYER_VELOCITY;
         }
         //Nhan vat di chuyen sang ben phai?
         else if(main_status == MainObject::WALK_RIGHT || main_status == MainObject::JUMP_RIGHT)
         {
            //=> Vien dan bi lam cham lai, phai tang toc do
            rect_.x -= PLAYER_VELOCITY;
         }
      }
      //Con nhieu` huong' dan nua~, edit sau ...
   }
}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
   bool ret = false;

   /** MAIN BULLET **/
   if(bullet_type_ == BulletObject::MAIN_FIRE_BALL_LEFT)
   {
      ret = LoadImg(g_name_skill_main_fire_ball_left, des, SDL_FALSE, WHITE);
   }
   else if(bullet_type_ == BulletObject::MAIN_FIRE_BALL_RIGHT)
   {
      ret = LoadImg(g_name_skill_main_fire_ball_right, des, SDL_FALSE, WHITE);
   }
   else if(bullet_type_ == BulletObject::MAIN_ICE_SHARD_LEFT)
   {
      ret = LoadImg(g_name_skill_main_ice_shard_left, des, SDL_FALSE, WHITE);
   }
   else if(bullet_type_ == BulletObject::MAIN_ICE_SHARD_RIGHT)
   {
      ret = LoadImg(g_name_skill_main_ice_shard_right, des, SDL_FALSE, WHITE);
   }

   /**THREAT BULLET**/
   if(bullet_type_ == BulletObject::WISP_FIRE_BALL_LEFT)
   {
      ret = LoadImg(g_name_skill_wisp_fire_ball_left, des, SDL_FALSE, WHITE);
   }
   else if(bullet_type_ == BulletObject::WISP_FIRE_BALL_RIGHT)
   {
      ret = LoadImg(g_name_skill_wisp_fire_ball_right, des, SDL_FALSE, WHITE);
   }
   else if(bullet_type_ == BulletObject::WISP_ICE_SHARD_LEFT)
   {
      //
   }
   else if(bullet_type_ == BulletObject::WISP_ICE_SHARD_RIGHT)
   {
      //
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

   //Neu khong phai TH dac biet, di chuyen vien dan theo x_val_ va y_val_
   x_pos_ += x_val_;
   y_pos_ += y_val_;

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
