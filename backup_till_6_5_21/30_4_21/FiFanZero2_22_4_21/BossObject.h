
#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_

#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define BOSS_SPEED 2
#define BOSS_HIGH_VAL 18

#define BOSS_FRAME_NUM 32

class BossObject : public BaseObject
{
public:
   BossObject();
   ~BossObject();

   void Show(SDL_Renderer* des);
   bool LoadImg(const std::string file_path, SDL_Renderer* des);
   void set_clips();

   void set_x_val(const float& xVal) {x_val_ = xVal;}
   void set_y_val(const float& yVal) {y_val_ = yVal;}

   void set_x_pos(const float& xPos) {x_pos_ = xPos;}
   void set_y_pos(const float& yPos) {y_pos_ = yPos;}
   float get_x_pos() const {return x_pos_;}
   float get_y_pos() const {return y_pos_;}

   int get_width_frame() const {return width_frame_;}
   int get_height_frame() const {return height_frame_;}

   void SetMapXY(const int& mapX, const int& mapY) {map_x_ = mapX; map_y_ = mapY;}
   void CheckToMap(Map& map_data);
   //void CenterEntityOnMap(Map& map_data);
   void DoBoss(Map& map_data);
   void InitBoss();

   std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; }
   void set_bullet_list (const std::vector<BulletObject*> bulletList)
   { bullet_list_ = bulletList; }
   void InitBullet(SDL_Renderer* des);
   void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);

private:
   //Vi tri xuat hien cua Boss tren ban do
   int x_pos_;
   int y_pos_;

   //Van toc di chuyen cua Boss theo phuong x va y
   int x_val_;
   int y_val_;

   //Vi tri mep ban do
   int map_x_;
   int map_y_;

   //Trang thai di chuyen cua Boss, do COMPUTER dieu khien
   Input input_type_;

   //Flag check Boss dung tren mat dat
   bool on_ground_;

   //Chi so cua frame
   int frame_;

   //Luu toa do cua cac clip trong 1 sprite Boss
   SDL_Rect frame_clip_[BOSS_FRAME_NUM];

   //Kich thuoc 1 frame
   int width_frame_;
   int height_frame_;

   //Hoat dong nhu come_back_time_
   int think_time_;

   //Bang dan cua Boss
   std::vector<BulletObject*> bullet_list_;
};
#endif // BOSS_OBJECT_H_
