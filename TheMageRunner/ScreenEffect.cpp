
#include "ScreenEffect.h"

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

void ScreenEffect::FadeOutScreenOnClick(SDL_Renderer* des, SDL_Event& events)
{
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
   bool begin_fading = true;
   bool done_fading = false;
   bool trivial = true;
   while(!done_fading)
   {
      ScreenEffect::HandleInputAction(events, begin_fading);
      //truyen` begin_fading, khi click, begin_fading == true
      if(begin_fading == true)
      {
         for(Uint8 i = 0; i <= ALPHA_BLEND_RANGE ; ++i)
         {
            ScreenEffect::HandleInputAction(events, trivial);
            SDL_SetRenderDrawColor(des, 0, 0, 0, i); //black
            SDL_RenderFillRect(des, NULL);
            SDL_RenderPresent(des);
            SDL_Delay(FADING_DELAY_TIME);
         }
         done_fading = true;
      }
   }
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_NONE);
}

void ScreenEffect::FadeInScreenOnClick(SDL_Renderer* des, SDL_Event& events)
{
   //
}

void ScreenEffect::FadeOutScreenNoClick(SDL_Renderer* des)
{
   bool trivial = true;
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
   for(Uint8 i = 0; i <= ALPHA_BLEND_RANGE ; ++i)
   {
      ScreenEffect::HandleInputAction(g_event, trivial); //anti-lag
      SDL_SetRenderDrawColor(des, 0, 0, 0, i); //BLACK
      SDL_RenderFillRect(des, NULL);
      SDL_RenderPresent(des);
      SDL_Delay(FADING_DELAY_TIME);
   }
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_NONE);
}

void ScreenEffect::FadeInScreenNoClick(SDL_Renderer* des, SDL_Texture* p_text)
{
   bool flag = true;
   if(p_text != NULL)
   {
      SDL_SetTextureBlendMode(p_text, SDL_BLENDMODE_BLEND);
      for(Uint8 i = 0; i <= ALPHA_BLEND_RANGE ; ++i)
      {
         ScreenEffect::HandleInputAction(g_event, flag); //anti-lag
         SDL_SetTextureAlphaMod(p_text, i);
         SDL_RenderCopy(des, p_text, NULL, NULL); // all screen
         SDL_RenderPresent(des);
         SDL_Delay(FADING_DELAY_TIME);
      }
      SDL_DestroyTexture(p_text);
      p_text = NULL;
   }
}

void ScreenEffect::BlurScreenNoClick(SDL_Renderer* des)
{
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
   SDL_SetRenderDrawColor(des, 0, 0, 0, ALPHA_BLEND_RANGE); //BLACK
   SDL_RenderFillRect(des, NULL);
   SDL_RenderPresent(des);
   SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_NONE);
}

