
#ifndef EXP_OBJECT_H_
#define EXP_OBJECT_H_

#include "BaseObject.h"

#define EXP_NUM_FRAME 8

class ExpObject : public BaseObject
{
public:
   ExpObject();
   ~ExpObject();

   void set_clips();
   void set_frame(const int& fr) {frame_ = fr;}
   virtual bool LoadImg(const std::string file_path, SDL_Renderer* des);
   void Show(SDL_Renderer* des);
   int get_frame_width() const { return frame_width_; }
   int get_frame_height() const {  return frame_height_;}

private:
   int frame_width_;
   int frame_height_;

   unsigned int frame_;
   SDL_Rect frame_clip_[EXP_NUM_FRAME];
};

#endif // EXP_OBJECT_H_
