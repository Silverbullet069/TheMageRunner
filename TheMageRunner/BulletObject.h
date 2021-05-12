
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"

class BulletObject : public BaseObject
{
public:
   BulletObject();
   ~BulletObject();

   enum BulletDir
   {
      DIR_RIGHT = 20,
      DIR_LEFT = 21,
      DIR_UP = 22,
      DIR_UP_LEFT = 23,
      DIR_UP_RIGHT = 24,
      DIR_DOWN_LEFT = 25,
      DIR_DOWN_RIGHT = 26,
   };

   enum BulletType
   {
      SKILL_NONE = 39,
      //Main
      MAIN_FIRE_BALL_LEFT = 40,
      MAIN_FIRE_BALL_RIGHT = 41,
      MAIN_ICE_SHARD_LEFT = 42,
      MAIN_ICE_SHARD_RIGHT = 43,

      //Threat
      WISP_FIRE_BALL_LEFT = 50,
      WISP_FIRE_BALL_RIGHT = 51,
      WISP_ICE_SHARD_LEFT = 52,
      WISP_ICE_SHARD_RIGHT = 53,

   };

   //Ham set vi tri cua vien dan tren tile map
   void set_x_pos(const int& xPos) { x_pos_ = xPos; }
   void set_y_pos(const int& yPos) { y_pos_ = yPos; }

   //Ham set van toc cua vien dan theo phuong x va y
   void set_x_val(const int& xVal) { x_val_ = xVal; }
   void set_y_val(const int& yVal) { y_val_ = yVal; }
   int get_x_val() const { return x_val_; }
   int get_y_val() const { return y_val_; }

   //Ham set trang thai di chuyen cua vien dan
   void set_is_move(const bool& isMove) {is_move_ = isMove;}
   bool get_is_move() const { return is_move_; }

   //Ham set va get huong di cua vien dan
   void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;}
   unsigned int get_bullet_dir() const { return bullet_dir_; }
   //Ham set va get loai dan
   void set_bullet_type(const unsigned int& bulletType) {bullet_type_ = bulletType;}
   unsigned int get_bullet_type() const { return bullet_type_; }

   void scale_width_height(const float& scaler) { rect_.w*= scaler; rect_.h*=scaler; }

   //Ham xu ly di chuyen cua vien dan, vien dan vuot qua' bien man hinh se bien mat
   void HandleMove(const int& x_border, const int& y_border);
   //Ham xu ly di chuyen cua vien dan trong TH nv di chuyen = CenterEntityOnMap
   void HandleWhileMainCenter(const int& main_x_pos, const int& main_status);
   //Load img cua tung vien dan theo BulletType
   bool LoadImgBullet(SDL_Renderer* des);
   //Ham kiem tra va cham giua vien dan va tile
   void CheckToMap(Map& map_data);

private:
   //Vi tri cua vien dan tren tile map
   //Su dung x_pos_ va y_pos_ cua Main
   int x_pos_;
   int y_pos_;

   //Van toc cua vien dan
   int x_val_;
   int y_val_;

   bool is_move_; //Flag di chuyen

   unsigned int bullet_dir_; //Huong' dan
   unsigned int bullet_type_; //Loai. dan

};
#endif // BULLET_OBJECT_H_
