#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

const int EXPLOSION_WIDTH = 165;
const int EXPLOSION_HEIGHT = 165;
const int TOTAL_FRAMES = 4;

class ExplosionObject : public BaseObject
{
public:
   ExplosionObject();
   ~ExplosionObject();
   void set_clip();
   void set_frame(const int& fr) {frame_ = fr;}
   void ShowEx(SDL_Renderer* des);

private :
   int frame_;
   SDL_Rect clip_[TOTAL_FRAMES];
};
#endif // EXPLOSION_OBJECT_H_
