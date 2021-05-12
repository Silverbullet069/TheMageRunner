
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "BaseObject.h"
#include "BulletObject.h"

class ThreatObject : public BaseObject
{
public:
   ThreatObject();
   ~ThreatObject();

   enum TypeElement
   {
      FIRE = 100,
      ICE = 101,
      SHADOW = 102,
      EARTH = 103,
      WIND = 104,
      HOLY = 105,

   };

   //Thay the input
   enum TypeMove
   {
      STATIC_THREAT = 0,
      MOVE_LEFT = 1,
      MOVE_RIGHT = 2,
      THREAT_DIE = 3,
   };

   bool LoadImg(const std::string file_path, SDL_Renderer* des);
   void set_clips();
   //Fuse lenh SDLCommonFunction::SetObject, set_width_frame(), set_height_frame() lam` 1
   void FuseSet(SDL_Texture* txt, const int& w_fr, const int& h_fr);
   SDL_Rect GetRectFrame();
   void Show(SDL_Renderer* des);
   //Khong co HandleInputAction vi ThreatObject do may tinh dieu khien

   //Ham set van toc cua ke thu
   void set_x_val(const int& xVal) {x_val_ = xVal;}
   void set_y_val(const int& yVal) {y_val_ = yVal;}

   //Ham lay kich thuoc 1 frame, su dung set_width_frame neu dung SDLCommonFunction::SetObject
   void set_width_frame(const int& widthFrame) { width_frame_ = widthFrame; }
   void set_height_frame(const int& heightFrame) { height_frame_ = heightFrame; }
   int get_width_frame() const {return width_frame_;}
   int get_height_frame() const {return height_frame_;}

   //Ham set va get vi tri cua ke thu tren tile map
   void set_x_pos(const int& xPos) {x_pos_ = xPos;}
   void set_y_pos(const int& yPos) {y_pos_ = yPos;}
   int get_x_pos() const {return x_pos_;}
   int get_y_pos() const {return y_pos_;}

   void SetMapXY(const int& mapX, const int& mapY) {map_x_ = mapX; map_y_ = mapY;}
   void DoThreat(Map& map_data);
   void CheckToMap(Map& map_data);
   void InitThreat();

   void set_type_move(const int& typeMove) {type_move_ = typeMove;}
   int get_type_move() const { return type_move_;  }
   void SetAnimationPos(const int& posA, const int& posB) //pos
      {animation_a_ = posA; animation_b_ = posB;}
   //void set_input_left(const int& inputLeft) {input_type_.left_ = inputLeft;}
   //Ham load anh dua tren TypeMove cua ke thu, dong thoi xu ly vi tri cua vien dan
   void ImpMoveType(SDL_Renderer* des); //Ham xu ly di chuyen trong pham vi a-b

   //Ham xu ly dan cua ke thu
   std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; }
   void set_bullet_list (const std::vector<BulletObject*> bulletList)
   { bullet_list_ = bulletList; }
   //Ham truyen mot vien dan da khoi tao truoc va set dac diem cho no
   void InitBullet(BulletObject* p_bullet, SDL_Renderer* des);
   //Ham set lai cac thong so cua vien dan khi ke thu` doi huong' di chuyen
   void ResetBullet(SDL_Renderer* des);
   //Ham set pham vi hoat dong cua vien dan
   void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
   //Ham huy vien dan trong TH ban trung main
   void RemoveBullet(const int& idx);

   //Ham set va get nguyen to cua ke thu
   void set_type_element(const int& typeElement) {type_element_ = typeElement;}
   int get_type_element() const { return type_element_; }

   //Ham set va get 1 frame
   void set_frame(const int& fr) {frame_ = fr;}
   int get_frame() const {return frame_;}

   //Ham luu tru anh ke thu, chi load 1 lan
   bool LoadThreatLeftImg(SDL_Renderer* des);
   bool LoadThreatRightImg(SDL_Renderer* des);
   bool LoadThreatStaticImg(SDL_Renderer* des);
   bool LoadThreatDieImg(SDL_Renderer* des);

private:

   //Viet them
   //Xu ly = SDLCommonFunction
   //txt_threat_ deu la trung gian cua p_object_
   SDL_Texture* txt_threat_left_;
   SDL_Texture* txt_threat_right_;
   SDL_Texture* txt_threat_static_;
   SDL_Texture* txt_threat_die_;
   SDL_Rect rect_threat_left_;
   SDL_Rect rect_threat_right_;
   SDL_Rect rect_threat_static_;
   SDL_Rect rect_threat_die_;

   int width_frame_left_;
   int height_frame_left_;

   int width_frame_right_;
   int height_frame_right_;

   int width_frame_static_;
   int height_frame_static_;

   int width_frame_die_;
   int height_frame_die_;

   //Luu vi tri mep cua ban do
   int map_x_;
   int map_y_;

   //Vi tri xuat hien cua ke thu
   int x_pos_;
   int y_pos_;

   //Van toc di chuyen theo phuong x va y cua ke thu
   int x_val_;
   int y_val_;

   bool on_ground_; //Flag kiem tra ke thu dung tren mat dat

   int come_back_time_; //Thoi gian delay giua 2 mang

   //Mang toa do cac clip trong 1 sprite
   SDL_Rect frame_clip_[THREAT_FRAME_NUM];

   //Kich thuoc 1 frame
   int width_frame_;
   int height_frame_;

   int frame_; //Luu chi so cua frame

   int type_move_; //Luu trang thai truoc do va hien tai cua ke thu (= status_)

   int type_element_; //Luu nguyen to cua con quai vat

   //Luu gioi han vi tri ma ke thu di chuyen
   int animation_a_;
   int animation_b_;

   //Input input_type_; //Luu trang thai di chuyen cua ke thu

   std::vector<BulletObject*> bullet_list_;
};


#endif // THREAT_OBJECT_H_
