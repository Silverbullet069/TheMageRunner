
#ifndef FAIRY_OBJECT_H_
#define FAIRY_OBJECT_H_

#include "CommonFunction.h"
#include "TextObject.h"
#include "ScreenEffect.h"
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
      IDLE_FORWARD = 4,
      TOTAL_MOVE_TYPE = 5,

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
   void InitFairyIntro();
   void InitFairyTutorial();

   void ImpTypeMove(); // For-non animation
   void HandleInputAction(SDL_Event& events);
   void HandleMove();
   void HandleConvoIntro(SDL_Renderer* des);
   void HandleConvoTutorial(SDL_Renderer* des);
   void SetBreakBetweenConvo();
   void FreezeScreenToConvo(SDL_Renderer* des);
   void Show(SDL_Renderer* des);
   void RenderClear(SDL_Renderer* des);

   bool get_is_move() const { return is_move_; }
   bool get_is_active() const { return is_active_; }
   void set_convo_run(const bool& flag) { is_convo_run_ = flag; }
   bool get_convo_run() const { return is_convo_run_; }
   int get_convo_order() const { return convo_order_; }
   TextObject get_convo() const { return fairy_convo_; }
   //Khong can` setter va getter, vi` toan` bo chuyen dong. cua Fairy se duoc thiet ke san~
   //Khong co su tuong tac giua Fairy va` cac Object khac'

   //ONLY FOR TUTORIAL AND GUIDES, NOT FOR ANIMATION
   void SetRect(const int& xPos, const int& yPos) { rect_.x = xPos; rect_.y = yPos; }
   void set_status(const int& sts) { status_ = sts; }

   void set_is_in_tutorial(const bool& flag) { is_in_tutorial_ = flag; }
   void set_is_in_intro(const bool& flag) { is_in_intro_ = flag; }

   bool get_selected_yes() const {return selected_yes_; }

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
   SDL_Texture* p_txt_fairy_idle_forward_;
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

   bool is_active_;
   bool is_move_;
   bool is_skip_move_;
   bool is_convo_run_;
   bool is_set_convo_[FAIRY_CONVO_NUM];
   bool is_done_convo_[FAIRY_CONVO_NUM];

   int convo_order_;

   TextObject fairy_convo_;
   TextObject UI_tutorial_yes_;
   TextObject UI_tutorial_no_;
   //Toa do cua con tro chuot
   int x_mouse_;
   int y_mouse_;
   bool selected_yes_;
   bool selected_no_;
   bool is_set_ui_tutorial_;

   bool is_in_intro_;
   bool is_in_tutorial_;
};
#endif // FAIRY_OBJECT_H_
