
#include "TextObject.h"
#include <iostream>

TextObject::TextObject()
{
   str_text_type_ = "";
   str_text_total_ = "";
   text_color_ = WHITE;
   p_txt_text_type_ = NULL;
   text_type_pos_.x = 0;
   text_type_pos_.y = 0;
   text_type_pos_.w = 0;
   text_type_pos_.h = 0;
   text_total_width_ = 0;
   text_total_height_ = 0;
   is_skip_ = false;
   count_text_delay_ = 0;
   text_delay_ = FRAME_TEXT_DELAY;
   tp_ = 0;
}

TextObject::~TextObject()
{
   Free();
}

bool TextObject::CreateSurfaceTextTotal(TTF_Font* font)
{
   //Create TextTotal here
   SDL_Surface* p_text_total_surface = TTF_RenderText_Solid(font, str_text_total_.c_str(), text_color_);

   if(p_text_total_surface == NULL)
   {
      printf("Unable to load text total!");
   }
   else
   {
      //For TextTotal
      text_total_width_ = p_text_total_surface->w;
      text_total_height_ = p_text_total_surface->h;
   }
   SDL_FreeSurface(p_text_total_surface);

   return p_text_total_surface != NULL;
}

bool TextObject::LoadTextureTextType(TTF_Font* font, SDL_Renderer* des)
{
   //Create TextType here
   SDL_Surface* p_text_type_surface = TTF_RenderText_Solid(font, str_text_type_.c_str(), text_color_);

   if(p_text_type_surface == NULL)
   {
      std::cout<< "Unable to load text type from : " << str_text_type_ << std::endl;
   }
   else
   {
      //Create texture_ for TextType
      p_txt_text_type_ = SDL_CreateTextureFromSurface(des, p_text_type_surface);

      if(p_txt_text_type_ == NULL)
      {
         std::cout<< "Unable to load text type texture!" << str_text_type_ << std::endl;
      }
      else
      {
         //For TextType
         text_type_pos_.w = p_text_type_surface->w;
         text_type_pos_.h = p_text_type_surface->h;
      }
      SDL_FreeSurface(p_text_type_surface);
   }

   return p_txt_text_type_ != NULL;
}

void TextObject::RenderText(SDL_Renderer* des,
                            SDL_Rect* clip /*NULL*/,
                            double angle /*0.0*/,
                            SDL_Point* center /*NULL*/,
                            SDL_RendererFlip flip /*SDL_FLIP_NONE*/)
{
   if(clip != NULL)
   {
      text_type_pos_.w = clip->w;
      text_type_pos_.h = clip->h;
   }
   SDL_RenderCopyEx(des, p_txt_text_type_, clip, &text_type_pos_, angle, center, flip);
}

void TextObject::RenderClear()
{
   //
}

void TextObject::Free()
{
   if(p_txt_text_type_ != NULL)
   {
      SDL_DestroyTexture(p_txt_text_type_);
      p_txt_text_type_ = NULL;
      //Reset lai. trang. thai' de su dung. lai.
      str_text_type_ = "";
      is_skip_ = false;
   }
}

void TextObject::HandleInputActionByTime(SDL_Event& events)
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
         }
      }
   }
}

void TextObject::HandleInputActionByFrame(SDL_Event& events, bool& flag)
{
   while(SDL_PollEvent(&events))
   {
      if(events.type == SDL_QUIT )
      {
         return;
      }
      if(events.type == SDL_MOUSEBUTTONDOWN)
      {
         if(events.button.button == SDL_BUTTON_LEFT)
         {
            flag = true;
         }
      }
   }
}


void TextObject::RenderTypingAnimationByTime(SDL_Renderer* des, SDL_Event& events)
{
   for(int tp = 0 ; tp < str_text_total_.size(); ++tp)
   {
      this->HandleInputActionByTime(events);

      if(str_text_total_[tp] == ' ')
      {
         continue; //Bo qua dau cach'
      }
      str_text_type_ = str_text_total_.substr(0, tp+1);
      this->LoadTextureTextType(g_font_text, g_renderer);
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
   SDL_Delay(EACH_CONVO_DELAY_TIME);
}


void TextObject::RenderTypingAnimationByFrame(SDL_Renderer* des, int& convo_order, bool is_auto, bool& flag_done)
{
   if(count_text_delay_ > 0)
   {
      count_text_delay_--;
   }
   else //text_delay_ = 0;
   {
      if(str_text_total_[tp_] == ' ')
      {
         tp_++;
      }
      str_text_type_ = str_text_total_.substr(0, tp_+1);
      LoadTextureTextType(g_font_text, g_renderer);
      RenderText(g_renderer);
      tp_++;

      if(tp_ >= str_text_total_.size())
      {
         flag_done = true;
         convo_order++;
         tp_ = 0;
         str_text_type_ = "";
         //is_convo_run_ = false;
         while(is_auto == false)
         {
            HandleInputActionByFrame(g_event, is_auto);
         }
      }

      count_text_delay_ = text_delay_;
   }
}

