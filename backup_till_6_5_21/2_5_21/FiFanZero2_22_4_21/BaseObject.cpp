#include "BaseObject.h"

BaseObject::BaseObject()
{
   //Khoi tao cac gia tri trong BaseObject
   rect_.x = 0;
   rect_.y = 0;
   rect_.w = 0;
   rect_.h = 0;
   p_object_ = NULL;
}

BaseObject::~BaseObject()
{
   Free();
}

bool BaseObject::LoadImg(const std::string& file_path, SDL_Renderer* des,
                         const int& color_flag, const SDL_Color& color)
{
   //Giai phong bo nho neu truoc do ton tai p_object_
      Free();
   //Khoi tao texture rong~
      SDL_Texture* new_texture = NULL;

   //Khoi tao surface de load anh
      SDL_Surface* loaded_surface = IMG_Load(file_path.c_str());

   //Neu surface load khong thanh
      if (loaded_surface == NULL)
      {
            printf( "Unable to load image %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError() );
      }
      else
      {
         SDL_SetColorKey(loaded_surface, color_flag, SDL_MapRGB(loaded_surface->format, color.r, color.g, color.b));
         new_texture = SDL_CreateTextureFromSurface(des, loaded_surface);
         if(new_texture == NULL)
         {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError() );
         }
         else
         {
            rect_.w = loaded_surface->w;
            rect_.h = loaded_surface->h;
         }
         SDL_FreeSurface(loaded_surface);
      }

      p_object_ = new_texture;

   return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*NULL*/)
{
   //RenderQuad mac dinh = rect_, chinh lai rect_.x va rect_.y dung ham SetRect()
   SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};
   if (p_object_ != NULL)
   {
      //Copy img p_object_ vao trong renderer
         SDL_RenderCopy(des, p_object_, clip, &renderQuad);
   }
}

void BaseObject::Free()
{
   //Xoa texture trong BaseObject
      if (p_object_ != NULL)
      {
         SDL_DestroyTexture(p_object_);
         p_object_ = NULL;
         rect_.w = 0;
         rect_.h = 0;
      }
}
