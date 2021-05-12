
#include "TextObject.h"

TextObject::TextObject()
{
   str_val_ = "";
   text_color_.r = 255;
   text_color_.g = 255;
   text_color_.b = 255; //white
   texture_ = NULL;
   width_ = 0;
   height_ = 0;
}

TextObject::~TextObject()
{
   Free();
}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* des)
{
   bool success = true;

   SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
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
         width_ = text_surface->w;
         height_ = text_surface->h;
      }
      SDL_FreeSurface(text_surface);
   }

   return success;
}

void TextObject::SetColor(const Uint8& red, const Uint8& green, const Uint8& blue)
{
   text_color_.r = red;
   text_color_.g = green;
   text_color_.b = blue;
}

void TextObject::SetColorType(const int& colorType)
{
   switch (colorType)
   {
   case RED_TEXT :
      {
         SDL_Color color = {255, 0, 0};
         text_color_ = color;
      }
      break;
   case WHITE_TEXT :
      {
         SDL_Color color = {255, 255, 255};
         text_color_ = color;
      }
      break;
   case BLACK_TEXT :
      {
         SDL_Color color = {0, 0, 0};
         text_color_ = color;
      }
      break;
   }
}

void TextObject::RenderText(SDL_Renderer* des,
                            const int& xp, const int& yp,
                            SDL_Rect* clip /*NULL*/,
                            double angle /*0.0*/,
                            SDL_Point* center /*NULL*/,
                            SDL_RendererFlip flip /*SDL_FLIP_NONE*/)
{
   SDL_Rect renderQuad = {xp, yp, width_, height_};
   if(clip != NULL)
   {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
   }
   SDL_RenderCopyEx(des, texture_, clip, &renderQuad, angle, center, flip);
}

void TextObject::Free()
{
   if(texture_ != NULL)
   {
      SDL_DestroyTexture(texture_);
      texture_ = NULL;
   }
}

