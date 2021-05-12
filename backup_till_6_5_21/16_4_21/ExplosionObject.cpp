#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
   frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::set_clip()
{
   //CAUTION : rect.w = width cua ca sprite

   clip_[0].x = 0;
   clip_[0].y = 0;
   clip_[0].w = rect_.w/TOTAL_FRAMES;
   clip_[0].h = rect_.h;

   clip_[1].x = 1*rect_.w/TOTAL_FRAMES;
   clip_[1].y = 0;
   clip_[1].w = rect_.w/TOTAL_FRAMES;
   clip_[1].h = rect_.h;

   clip_[2].x = 2*rect_.w/TOTAL_FRAMES;
   clip_[2].y = 0;
   clip_[2].w = rect_.w/TOTAL_FRAMES;
   clip_[2].h = rect_.h;

   clip_[3].x = 3*rect_.w/TOTAL_FRAMES;
   clip_[3].y = 0;
   clip_[3].w = rect_.w/TOTAL_FRAMES;
   clip_[3].h = rect_.h;

}

void ExplosionObject::ShowEx(SDL_Renderer* des)
{
   //rect_.x va rect_.y thay doi truoc khi goi ShowEx nen phai set lai
   SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w/TOTAL_FRAMES, rect_.h};
   if(frame_ >= 4)
   {
      frame_ = 0;
   }
   SDL_RenderCopy(des, p_object_, &clip_[frame_], &renderQuad);
}
