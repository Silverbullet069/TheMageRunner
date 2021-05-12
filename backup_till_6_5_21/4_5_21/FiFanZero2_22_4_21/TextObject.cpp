
#include "TextObject.h"

TextObject::TextObject()
{
   str_text_type_ = "";
   str_text_total_ = "";
   text_color_.r = 255;
   text_color_.g = 255;
   text_color_.b = 255; //white
   texture_ = NULL;
   text_pos_.x = 0;
   text_pos_.y = 0;
   text_pos_.w = 0;
   text_pos_.h = 0;
   is_skip_ = false;
   is_done_ = false;
   is_active_ = true;
}

TextObject::~TextObject()
{
   Free();
}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* des)
{
   bool success = true;

   SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_text_type_.c_str(), text_color_);
   if(text_surface == NULL)
   {
      printf("Unable to load text surface!");
      success = false;
   }
   else
   {
      texture_ = SDL_CreateTextureFromSurface(des, text_surface);
      if(texture_ == NULL)
      {
         printf("Unable to load text texture!");
         success = false;
      }
      else
      {
         text_pos_.w = text_surface->w;
         text_pos_.h = text_surface->h;
      }
      SDL_FreeSurface(text_surface);
   }

   return success;
}

void TextObject::RenderText(SDL_Renderer* des,
                            SDL_Rect* clip /*NULL*/,
                            double angle /*0.0*/,
                            SDL_Point* center /*NULL*/,
                            SDL_RendererFlip flip /*SDL_FLIP_NONE*/)
{
   if(clip != NULL)
   {
      text_pos_.w = clip->w;
      text_pos_.h = clip->h;
   }
   SDL_RenderCopyEx(des, texture_, clip, &text_pos_, angle, center, flip);
}

void TextObject::Free()
{
   if(texture_ != NULL)
   {
      SDL_DestroyTexture(texture_);
      texture_ = NULL;
      //Reset lai. trang. thai' de su dung. lai.
      str_text_type_ = "";
      is_skip_ = false;
      is_done_ = false;
      is_active_ = true;
   }
}

void TextObject::HandleInputAction(SDL_Event& events)
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

            if(is_skip_ == false)
            {
               is_skip_ = true;
            }

            if(is_done_ == true)
            {
               is_active_ = false;
            }
         }
      }
   }
}

void TextObject::RenderTypingAnimation(SDL_Renderer* des, SDL_Event& events)
{
   for(int tp = 0 ; tp < str_text_total_.size(); ++tp)
   {
      this->HandleInputAction(events);

      if(str_text_total_[tp] == ' ')
      {
         continue; //Bo qua dau cach'
      }
      str_text_type_ = str_text_total_.substr(0, tp+1);
      this->LoadFromRenderText(g_font_text, g_renderer);
      this->RenderText(g_renderer);
      SDL_RenderPresent(g_renderer);
      if(is_skip_ == false)
      {
         SDL_Delay(NORMAL_TYPING_DELAY_TIME);
      }
      else
      {
         SDL_Delay(SKIP_TYPING_DELAY_TIME);
      }
   }
   is_done_ = true;

   while(is_active_)
   {
      this->HandleInputAction(events);
   }
}

