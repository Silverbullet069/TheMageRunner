
#ifndef EXP_OBJECT_H_
#define EXP_OBJECT_H_

#include "BaseObject.h"

#define EXP_NUM_FRAME 8

class ExpObject : public BaseObject
{
public:
   enum ExpType
   {
      EXP_THREAT = 70,
      EXP_MAIN = 71,
   };

   ExpObject();
   ~ExpObject();

   bool LoadImgExp(SDL_Renderer* des);
   void set_clips();
   //void set_frame(const int& fr) {frame_ = fr;}

   void Show(SDL_Renderer* des);

   void set_exp_type(const unsigned int& expType) {exp_type_ = expType;}
   unsigned int get_exp_type() const {  return exp_type_;  }

   void set_is_exp(const bool& isExp) { is_exp_ = isExp; }
   bool get_is_exp() const {  return is_exp_;  }

   int get_frame_width() const { return frame_width_; }
   int get_frame_height() const {  return frame_height_;}

private:
   bool is_exp_;

   unsigned int exp_type_;

   int frame_width_;
   int frame_height_;

   unsigned int frame_;
   SDL_Rect frame_clip_[EXP_NUM_FRAME];
};

#endif // EXP_OBJECT_H_
