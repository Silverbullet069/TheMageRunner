#include "BaseObject.h"

BaseObject::BaseObject()
{
      //Khoi tao cac gia tri trong BaseObject
      rect_.x = 0;
      rect_.y = 0;
      p_object_ = NULL;
}

BaseObject::~BaseObject()
{
      //Xoa texture trong BaseObject
      if (p_object_ != NULL)
      {
            SDL_DestroyTexture(p_object_);
            p_object_ = NULL;
            rect_.x = 0;
            rect_.y = 0;
      }
}

bool BaseObject::LoadImg(const std::string file_path)
{
      //Khoi tao flag success
      bool success = true;

      //Load anh vao trong p_object_ tu ham LoadImage trong SDLCommonFunction
      p_object_ = SDLCommonFunction::LoadImage(file_path);
      if (p_object_ == NULL)
      {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError() );
            success = false;
      }
      return success;
}

void BaseObject::Show()
{
      if (p_object_ != NULL)
      {
            //Copy img p_object_ vao trong renderer
            SDL_RenderCopy(g_renderer, p_object_, NULL, &rect_);
      }
}
