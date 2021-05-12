#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

#define EXPLOSION_WIDTH 165
#define EXPLOSION_HEIGHT 165

class ExplosionObject : public BaseObject
{
public:
   ExplosionObject();
   ~ExplosionObject();
   void set_clip();
   void set_frame(const int& fr) {frame_ = fr;}
   void ShowEx();

private :
   int frame_;
   SDL_Rect clip_[4];
};
#endif // EXPLOSION_OBJECT_H_
