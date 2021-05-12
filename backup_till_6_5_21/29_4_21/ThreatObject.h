
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include <vector>
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_VELOCITY 0.8
#define THREAT_MAX_FALL_VELOCITY 10
#define THREAT_VELOCITY 3

class ThreatObject : public BaseObject
{
public:
   ThreatObject();
   ~ThreatObject();

   enum TypeMove
   {
      STATIC_THREAT = 0,
      MOVE_IN_SPACE = 1,
   };

   bool LoadImg(const std::string file_path, SDL_Renderer* des);
   void set_clips();
   SDL_Rect GetRectFrame();
   void Show(SDL_Renderer* des);
   //Khong co HandleInputAction vi ThreatObject do may tinh dieu khien

   void set_x_val(const float& xVal) {x_val_ = xVal;}
   void set_y_val(const float& yVal) {y_val_ = yVal;}

   int get_width_frame() const {return width_frame_;}
   int get_height_frame() const {return height_frame_;}

   void set_x_pos(const float& xPos) {x_pos_ = xPos;}
   void set_y_pos(const float& yPos) {y_pos_ = yPos;}
   float get_x_pos() const {return x_pos_;}
   float get_y_pos() const {return y_pos_;}

   void SetMapXY(const int& mapX, const int& mapY) {map_x_ = mapX; map_y_ = mapY;}
   void DoThreat(Map& map_data);
   void CheckToMap(Map& map_data);
   void InitThreat();

   void set_type_move(const int& typeMove) {type_move_ = typeMove;}
   void SetAnimationPos(const int& posA, const int& posB)
      {animation_a_ = posA; animation_b_ = posB;}
   void set_input_left(const int& inputLeft) {input_type_.left_ = inputLeft;}
   void ImpMoveType(SDL_Renderer* des); //Ham xu ly di chuyen trong pham vi a-b

   std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; }
   void set_bullet_list (const std::vector<BulletObject*> bulletList)
   { bullet_list_ = bulletList; }
   void InitBullet(BulletObject* p_bullet, SDL_Renderer* des);
   void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
   void RemoveBullet(const int& idx);


   //Viet them
   bool LoadThreatLeftImg(SDL_Renderer* des);
   bool LoadThreatRightImg(SDL_Renderer* des);
   bool LoadThreatStaticImg(SDL_Renderer* des);

private:

   //Viet them
   //Xu ly = SDLCommonFunction
   //txt_threat_ deu la trung gian cua p_object_
   SDL_Texture* txt_threat_left_;
   SDL_Texture* txt_threat_right_;
   SDL_Texture* txt_threat_static_;
   SDL_Rect rect_threat_left_;
   SDL_Rect rect_threat_right_;
   SDL_Rect rect_threat_static_;

   //Luu vi tri mep cua ban do
   int map_x_;
   int map_y_;

   //Vi tri xuat hien cua ke thu
   float x_pos_;
   float y_pos_;

   //Van toc di chuyen theo phuong x va y cua ke thu
   float x_val_;
   float y_val_;

   bool on_ground_; //Flag kiem tra ke thu dung tren mat dat

   int come_back_time_; //Thoi gian delay giua 2 mang

   //Mang toa do cac clip trong 1 sprite
   SDL_Rect frame_clip_[THREAT_FRAME_NUM];

   //Kich thuoc 1 frame
   int width_frame_;
   int height_frame_;

   int frame_; //Luu chi so cua frame

   int type_move_; //Luu trang thai truoc do va hien tai cua ke thu (= status_)

   //Luu gioi han vi tri ma ke thu di chuyen
   int animation_a_;
   int animation_b_;

   Input input_type_; //Luu trang thai di chuyen cua ke thu

   std::vector<BulletObject*> bullet_list_;
};


#endif // THREAT_OBJECT_H_
