
#include "ExpObject.h"

ExpObject::ExpObject()
{
   exp_type_ = 0;
   frame_width_ = 0;
   frame_height_ = 0;
   frame_ = -1;
}

ExpObject::~ExpObject()
{

}

/**bool ExpObject::LoadImg(const std::string file_path, SDL_Renderer* des)
{
   bool ret = BaseObject::LoadImg(file_path, des);
   if(!ret) { printf("Unable to load exp object!"); }
   else
   {
      frame_width_ = rect_.w/EXP_NUM_FRAME;
      frame_height_ = rect_.h;
   }
   return ret;
} **/

bool ExpObject::LoadImgExp(SDL_Renderer* des)
{
   bool ret = false;

   if(exp_type_ == EXP_MAIN)
   {
      ret = LoadImg("exp_main.png", des);
      if(!ret) {ret = false;}
      frame_width_ = rect_.w/EXP_NUM_FRAME;
      frame_height_ = rect_.h;
   }
   else if(exp_type_ == EXP_THREAT)
   {
      ret = LoadImg("exp_threat.png", des);
      if(!ret) {ret = false;}
      frame_width_ = rect_.w/EXP_NUM_FRAME;
      frame_height_ = rect_.h;
   }
   return ret;
}

void ExpObject::set_clips()
{
   if(frame_width_ > 0 && frame_height_ > 0)
   {
      for(int i = 0 ; i < EXP_NUM_FRAME ; ++i)
      {
         frame_clip_[i].x = i*frame_width_;
         frame_clip_[i].y = 0;
         frame_clip_[i].w = frame_width_;
         frame_clip_[i].h = frame_height_;
      }
   }
}

void ExpObject::Show(SDL_Renderer* des)
{
   frame_++;
   if(frame_ == EXP_NUM_FRAME - 1)
   {
      this->set_is_exp(false);
   }

   SDL_Rect* current_clip = &frame_clip_[frame_];

   SDL_Rect renderQuad = {rect_.x, rect_.y, frame_width_, frame_height_};

   if(current_clip != NULL)
   {
      renderQuad.w = current_clip->w;
      renderQuad.h = current_clip->h;
   }

   SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}
