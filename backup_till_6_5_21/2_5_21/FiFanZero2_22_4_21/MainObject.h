
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "ExpObject.h"

class MainObject : public BaseObject
{
public:
   MainObject();
   ~MainObject();
   enum Dir
   {
      LEFT = 30,
      RIGHT = 31,

   };


   //Dinh nghia status_
   enum Status
   {
      IDLE_LEFT = 0,
      IDLE_RIGHT = 1,
      WALK_LEFT = 2,
      WALK_RIGHT = 3,
      JUMP_LEFT = 4,
      JUMP_RIGHT = 5,
      TAKE_HIT_LEFT = 6,
      TAKE_HIT_RIGHT = 7,
      RESPAWN = 8,
      KO_LEFT = 9,
      KO_RIGHT = 10,

   };
   void set_status(const int& st) { status_ = st; }
   int get_status() const { return status_ ; }

   //khong can direction, direction do BulletObject quan ly
   enum SkillType
   {
      FIRE_BALL = 20,
      ICE_SHARD = 21,

   };
   void set_skill_type(const int& skillType) {skill_type_ = skillType; }
   int get_skill_type() const { return skill_type_; }

   void set_toggle_bullet(const int& toggleBullet) { toggle_bullet_ = toggleBullet; }
   int get_toggle_bullet() const { return toggle_bullet_; }

   bool LoadImg(const std::string file_path, SDL_Renderer* des); //Ham load anh nhan vat
   void Show(SDL_Renderer* des); // In ra tung frame, 1 frame he thuong = 1 frame anh?, ham` nay` tinh' rect_.x va rect_.y
   //Ham` xu ly trang. thai' di chuyen cua nhan vat, dong` thoi` khoi tao skill
   void HandleInputAction(const SDL_Event& events, SDL_Renderer* des);
   void set_clips();
   SDL_Rect GetRectFrame();

   //Khong set_x_val va set_y_val vi toc do di chuyen la phu thuoc vao HandleInputAction
   //Khong set_x_pos va set_y_pos vi vi tri duoc quyet dinh vao CheckToMap
   int get_x_pos() const {  return x_pos_;  }
   //int get_y_pos() const {  return y_pos_;  }

   void DoPlayer(Map& map_data); // Ham xu ly nhan vat voi tile map
   void InitPlayer(); //Ham xu ly hoi sinh nhan vat
   //Check va cham nv voi tile map, epsilon_x va y tinh sai so
   void CheckToMap(Map& map_data);
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

   //Ham luu tru anh nhan vat, chi goi 1 LAN
   void LoadAllPlayerAction(SDL_Renderer* des);

   //Khoi tao va lay kich thuoc 1 frame
   void set_width_frame(const int& w_frame) { width_frame_ = w_frame; }
   int get_width_frame() const { return width_frame_; }
   void set_height_frame(const int& h_frame) { height_frame_ = h_frame; }
   int get_height_frame() const { return height_frame_; }

   void set_frame(const int& fr) { frame_ = fr; }
   int get_frame() const { return frame_; }

   void set_come_back_time(const int& cb_t) { come_back_time_ = cb_t; } //Set time delay
   void set_invul_time(const int& inv_t) { invul_time_ = inv_t; } // Set time bat' tu
   int get_invul_time() const { return invul_time_; }
   void set_ko_time(const int& ko_t) { ko_time_ = ko_t; }
   void IncreaseMoney() {  money_count_++; }//Ham xu ly bien' dong tien cua nhan vat
   int GetMoney() const {return money_count_;} //Ham lay tien cua nhan vat

private:
   /**Ly do tai sao phai co bien rect_player la vi txt duoc load = SDLCommonFunction::LoadTexture ko khien rect_ thay doi
   Con binh thuong su dung BaseObject::LoadImg se khien rect_ trong BaseObject thay doi **/

   SDL_Texture* txt_player_idle_left_;
   SDL_Texture* txt_player_idle_right_;
   SDL_Texture* txt_player_walk_left_;
   SDL_Texture* txt_player_walk_right_;
   SDL_Texture* txt_player_jump_left_;
   SDL_Texture* txt_player_jump_right_;
   SDL_Texture* txt_player_take_hit_left_;
   SDL_Texture* txt_player_take_hit_right_;
   SDL_Texture* txt_player_ko_left_;
   SDL_Texture* txt_player_ko_right_;

   //Vi tri hien thi cua nhan vat
   int x_pos_;
   int y_pos_;

   //Van toc di chuyen cua nhan vat
   int x_val_;
   int y_val_;

   //Vi tri mep cua ban do
   int map_x_;
   int map_y_;

   //Luu trang thai di chuyen cua nhan vat
   Input input_type_;

   int status_; //Luu trang thai truoc do va hien tai cua nhan vat

   bool on_ground_; //Flag kiem tra nhan vat dang dung tren mat dat khong
   bool is_ice_shard_learned_; //Flag kiem tra nhan vat da hoc duoc skill ICE_SHARD chua

   int come_back_time_; //Thoi gian delay giua 2 mang sau khi nv roi xuong vuc
   int invul_time_; //Thoi gian nv bat' tu' sau khi mat' 1 mang.
   int ko_time_; //Thoi gian nv die cho den luc thoat chuong trinh

   int frame_; //Luu chi so cua frame

   //Mang toa do cac clip trong 1 sprite
   SDL_Rect frame_clip_[PLAYER_FRAME_NUM];

   //Kich thuoc 1 frame, cac ham` trong MainObject chi lam viec voi 2 bien nay
   int width_frame_;
   int height_frame_;

   //Bang dan cua nhan vat
   std::vector<BulletObject*> p_bullet_list_;
   unsigned int toggle_bullet_;
   unsigned int skill_type_;

   //Vu no tao ra boi DAN CUA NHAN VAT
   std::vector<ExpObject*> p_exp_list_;

   int money_count_; //Bien quan ly tien cua nhan vat

};

#endif // MAIN_OBJECT_H_
