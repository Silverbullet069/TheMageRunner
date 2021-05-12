
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ExpObject.h"

#define MAX_FALL_SPEED 10
#define GRAVITY_VELOCITY 0.8
#define PLAYER_FRAME_NUM 8
#define PLAYER_VELOCITY 8
#define PLAYER_JUMP_VAL 20

class MainObject : public BaseObject
{
public:
   MainObject();
   ~MainObject();

   //Dinh nghia trang thai di chuyen
   enum WalkType
   {
      WALK_NONE = 0,
      WALK_RIGHT = 1,
      WALK_LEFT = 2,
   };

   bool LoadImg(const std::string file_path, SDL_Renderer* des); //Ham load anh nhan vat
   void Show(SDL_Renderer* des); // In ra tung frame, 1 frame he thuong = 1 frame anh?
   void HandleInputAction(SDL_Event events, SDL_Renderer* des); //Vien dan khoi tao trong nay
   void set_clips();
   SDL_Rect GetRectFrame();
   //Khong set_x_val va set_y_val vi toc do di chuyen la phu thuoc vao HandleInputAction
   //Khong set_x_pos va set_y_pos vi vi tri duoc quyet dinh vao CheckToMap

   void DoPlayer(Map& map_data); // Ham xu ly nhan vat voi tile map
   void InitPlayer(); //Ham xu ly hoi sinh nhan vat
   void CheckToMap(Map& map_data); //Ham kiem tra nhan vat va cham voi tile map
   //Ham set lai cac thong so mep cua ban do
   void SetMapXY(const int& map_x, const int& map_y) {map_x_ = map_x; map_y_ = map_y;}
   //Ham lam tile map chay theo nhan vat, tinh toan theo start_x_ va start_y_
   void CenterEntityOnMap(Map& map_data);
   //Ham load anh nhan vat tuong ung voi trang thai di chuyen cua nhan vat
   void UpdateImagePlayer(SDL_Renderer* des);

   //Ham khoi tao bang dan va lay bang dan cua nhan vat
   void set_bullet_list(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}
   std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
   void HandleBullet(SDL_Renderer* des); //Ham xu ly bang dan cua nhan vat
   void RemoveBullet(const int& idx);

   //Ham khoi tao vu no va lay vu no
   void set_exp_list(std::vector<ExpObject*> exp_list) {p_exp_list_ = exp_list; }
   std::vector<ExpObject*> get_exp_list() const {return p_exp_list_;}
   void InitExplosion(const int& objType, const int& obj_x_pos, const int& obj_y_pos, SDL_Renderer* des);
   void HandleExplosion(SDL_Renderer* des); //Ham xu ly chuoi~ vu no tao ra boi nhan vat
   void RemoveExplosion(const int& idx); //Ham xoa vu no

   //Ham khoi tao thoi gian delay giua 2 mang
   void set_come_back_time(const int& cb_time) {come_back_time_ = cb_time;}
   void IncreaseMoney(); //Ham xu ly bien' dong tien cua nhan vat
   int GetMoney() const {return money_count_;} //Ham lay tien cua nhan vat

private:

   //Vi tri hien thi cua nhan vat
   float x_pos_;
   float y_pos_;

   //Van toc di chuyen cua nhan vat
   float x_val_;
   float y_val_;

   //Vi tri mep cua ban do
   int map_x_;
   int map_y_;

   //Luu trang thai di chuyen cua nhan vat
   Input input_type_;

   int status_; //Luu trang thai truoc do va hien tai cua nhan vat

   bool on_ground_; //Flag kiem tra nhan vat dang dung tren mat dat khong

   int come_back_time_; //Thoi gian delay giua 2 mang

   int frame_; //Luu chi so cua frame

   //Mang toa do cac clip trong 1 sprite
   SDL_Rect frame_clip_[PLAYER_FRAME_NUM];

   //Kich thuoc 1 frame
   int width_frame_;
   int height_frame_;

   //Bang dan cua nhan vat
   std::vector<BulletObject*> p_bullet_list_;
   bool toggle_bullet_; //0 - sphere, 1 - laser

   //Vu no tao ra boi DAN CUA NHAN VAT
   std::vector<ExpObject*> p_exp_list_;

   int money_count_; //Bien quan ly tien cua nhan vat

};

#endif // MAIN_OBJECT_H_
