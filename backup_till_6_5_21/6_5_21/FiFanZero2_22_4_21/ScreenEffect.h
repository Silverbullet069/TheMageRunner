
#ifndef SCREEN_EFFECT_H_
#define SCREEN_EFFECT_H_

#include "CommonFunction.h"
//Object hinh hoc, khong phai hinh anh
//Khong can phai khai bao object Geometric khi su dung vi tat ca cac' ham` deu la static

class ScreenEffect
{
public:
   static void RenderRectangle(SDL_Renderer* des, const SDL_Rect& rect, const SDL_Color& color);

   static void RenderOutline(SDL_Renderer* des, const SDL_Rect& rect, const SDL_Color& color);

   static void FadeOutScreen(SDL_Renderer* des, const SDL_Rect& rect,
                             const SDL_Color& color, SDL_Event& events);

   static void FadeInScreen(SDL_Renderer* des, const SDL_Rect& rect,
                            const SDL_Color& color, SDL_Event& events);

   static void FadeOutScreenNoClick(SDL_Renderer* des, const SDL_Rect& rect,
                                    const SDL_Color& color);

   static void FadeInScreenNoClick(SDL_Renderer* des, const SDL_Rect& rect,
                                   const SDL_Color& color);

   static void HandleInputAction(SDL_Event& events, bool& switch_flag);

};

#endif // SCREEN_EFFECT_H_
