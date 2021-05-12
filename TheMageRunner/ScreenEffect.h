
#ifndef SCREEN_EFFECT_H_
#define SCREEN_EFFECT_H_

#include "CommonFunction.h"
//Object hinh hoc, khong phai hinh anh
//Khong can phai khai bao object Geometric khi su dung vi tat ca cac' ham` deu la static

class ScreenEffect
{
public:
   static void HandleInputAction(SDL_Event& events, bool& switch_flag);

   static void RenderRectangle(SDL_Renderer* des, const SDL_Rect& rect, const SDL_Color& color);

   static void RenderOutline(SDL_Renderer* des, const SDL_Rect& rect, const SDL_Color& color);

   static void FadeOutScreenOnClick(SDL_Renderer* des, SDL_Event& events);

   static void FadeInScreenOnClick(SDL_Renderer* des, SDL_Event& events);

   static void FadeOutScreenNoClick(SDL_Renderer* des);

   static void FadeInScreenNoClick(SDL_Renderer* des, SDL_Texture* p_text);

   static void BlurScreenNoClick(SDL_Renderer* des);

};

#endif // SCREEN_EFFECT_H_
