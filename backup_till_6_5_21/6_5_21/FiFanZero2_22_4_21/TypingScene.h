
#ifndef TYPING_SCENE
#define TYPING_SCENE

#include "CommonFunction.h"
#include "TextObject.h"
#include "ScreenEffect.h"

#define TOTAL_INNER_MONO_SCENE_1 6
#define TOTAL_INNER_MONO_SCENE_2 8
#define TOTAL_INNER_MONO_SCENE_3 8

class TypingScene
{
public:
   TypingScene();
   ~TypingScene();
   void InitBackStory(SDL_Renderer* des, SDL_Event& events);

private:
   TextObject inter_mono_;
};
#endif // TYPING_SCENE
