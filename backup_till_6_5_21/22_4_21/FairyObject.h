
#ifndef FAIRY_OBJECT_H_
#define FAIRY_OBJECT_H_

#include "CommonFunction.h"
#include "TextObject.h"
#include "ElementaryFunctions.h"

class FairyObject
{
public:
   FairyObject();
   ~FairyObject();

   enum MoveType
   {
      FLY_LEFT = 0,
      FLY_RIGHT = 1,
      FLY_FORWARD = 2,
      VANISH_FORWARD = 3,
      TOTAL_MOVE_TYPE = 4,

   };

   enum Trajectory
   {
      SIN = 10,
      COS = 11,
      STRAIGHT_DOWN = 12,
      TOTAL_TRAJECTORY = 13,

   };

   SDL_Texture* LoadTextureAndDimension(SDL_Renderer* des, const std::string& file_path, int& w, int& h);
   void LoadAllFairyAction(SDL_Renderer* des); //Use multiple LoadTextureAndDimension
   void SetClipsEachAction();
   void InitFairy();

   void ImpTypeMove(); // For-non animation
   void HandleInputAction(SDL_Event& events);
   void HandleMove();
   void Show(SDL_Renderer* des);

   bool get_is_move() const { return is_move_; }
   bool get_is_active() const { return is_active_; }
   //Khong can` setter va getter, vi` toan` bo chuyen dong. cua Fairy se duoc thiet ke san~
   //Khong co su tuong tac giua Fairy va` cac Object khac'

   void InitConvo(SDL_Renderer* des, SDL_Event& events);

private:
   /** USED **/
   SDL_Texture* p_txt_fairy_object_;
   int width_object_;
   int height_object_;
   SDL_Rect* p_frame_clip_object_;

   /** SWITCH **/
   SDL_Texture* p_txt_fairy_fly_left_;
   SDL_Texture* p_txt_fairy_fly_right_;
   int width_side_;
   int height_side_;
   SDL_Rect* p_frame_clip_side_;

   SDL_Texture* p_txt_fairy_fly_forward_;
   SDL_Texture* p_txt_fairy_vanish_forward_;
   int width_forward_;
   int height_forward_;
   SDL_Rect* p_frame_clip_forward_;

   /** COMMON **/

   // Fairy chi? di chuyen trong 1 KHUNG HINH vi` fairy chi? di chuyen
   // khi dang guide nv trong phan` Tutorial voi map = 1 KHUNG HINH
   //int x_pos_;
   //int y_pos_;
   //int map_x_;
   //int map_y_;

   SDL_Rect rect_;

   int x_val_;
   int y_val_;

   int status_;
   int trajectory_;

   int frame_;

   bool is_move_;
   bool is_active_;

   TextObject fairy_convo_;
};
#endif // FAIRY_OBJECT_H_
