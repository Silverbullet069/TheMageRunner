
#include "ScreenEffect.h"

void ScreenEffect::RenderRectangle(SDL_Renderer* des, const SDL_Rect& rect, const SDL_Color& color)
{
   SDL_SetRenderDrawColor(des, color.r, color.g, color.b, 0xFF);
   SDL_RenderFillRect(des, &rect); //FILL
}

void ScreenEffect::RenderOutline(SDL_Renderer* des, const SDL_Rect& rect, const SDL_Color& color)
{
   SDL_SetRenderDrawColor(des, color.r, color.g, color.b, 0xFF);
   SDL_RenderDrawRect(des, &rect); //DRAW
}

void ScreenEffect::HandleInputAction(SDL_Event& events, bool& switch_flag)
{
   while(SDL_PollEvent(&events))
   {
      //Quit game
      if(events.type == SDL_QUIT )
      {
         return;
      }
      if(events.type == SDL_MOUSEBUTTONDOWN)
      {
         if(events.button.button == SDL_BUTTON_LEFT)
         {
            switch_flag = true;
         }
      }
   }
}

void ScreenEffect::FadeOutScreen(SDL_Renderer* des, const SDL_Rect& rect,
                             const SDL_Color& color, SDL_Event& events)
{
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
   bool begin_fading = false;
   bool done_fading = false;
   while(!done_fading)
   {
      ScreenEffect::HandleInputAction(events, begin_fading);
      if(begin_fading == true)
      {
         for(Uint8 i = 0; i <= ALPHA_BLEND_RANGE ; ++i)
         {
            ScreenEffect::HandleInputAction(events, begin_fading);
            //truyen` begin_fading vao` k de lam gi
            SDL_SetRenderDrawColor(des, color.r, color.g, color.b, i);
            SDL_RenderFillRect(des, &TOTAL_SCREEN);
            SDL_RenderPresent(des);
            SDL_Delay(FADING_DELAY_TIME);
         }
         done_fading = true;
      }
   }
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_NONE);
}

