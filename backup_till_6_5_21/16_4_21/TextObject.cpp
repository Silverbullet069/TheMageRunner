#include "TextObject.h"

TextObject::TextObject()
{
   str_val_ = "";
   text_color_.r = 255;
   text_color_.g = 255;
   text_color_.b = 255;
}

TextObject::~TextObject()
{

}

/**
void TextObject::HandleInputAction(SDL_Event events)
{
   if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
   {
      int pos_x, pos_y;
      SDL_GetMouseState(&pos_x, &pos_y);

      bool is_inside = true;

      if (pos_x < rect_.x)
      {
         is_inside = false;
      }
      else if (pos_x > rect_.x + rect_.w)
      {
         is_inside = false;
      }
      else if (pos_y > rect_.y)
      {
         is_inside = false;
      }
      else if (pos_y > rect_.y + rect_.h)
      {
         is_inside = false;
      }

      if(!is_inside)
      {
         TextObject::SetColor(BLACK_TEXT);
      }
      else //is_inside
      {
         TextObject::SetColor(RED_TEXT);
      }
   }
}
**/
void TextObject::SetColor(const int& type)
{
   if(type == RED_TEXT)
   {
      SDL_Color color = {255, 0 ,0};
      text_color_ = color;
   }
   else if(type == WHITE_TEXT)
   {
      SDL_Color color = {255, 255, 255};
      text_color_ = color;
   }
   else //BLACK_TEXT
   {
      SDL_Color color = {0, 0, 0};
      text_color_ = color;
   }
}

void TextObject::CreateGameText(TTF_Font* font, SDL_Renderer* des)
{
   SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
   if(text_surface == NULL )
	{
      printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
      p_object_ = SDL_CreateTextureFromSurface(g_renderer, text_surface);
		if( p_object_ == NULL )
		{
         printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
      {
         //Set text width va text height tu Surface
         rect_.w = text_surface->w;
         rect_.h = text_surface->h;
      }
		//Get rid of old surface
		SDL_FreeSurface( text_surface );
	}
	Render(des);
}
