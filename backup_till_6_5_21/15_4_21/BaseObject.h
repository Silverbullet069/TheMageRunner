#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common_Function.h"

class BaseObject
{
public:
      BaseObject();
      ~BaseObject();
   //Khoi tao toa do x va y
      void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
   //Lay toa do x va y da khoi tao
      SDL_Rect GetRect() const {return rect_;}
   //Lay object da khoi tao
      SDL_Texture* GetObject() const {return p_object_;}
   //Kiem tra load anh thanh cong tu 1 dia chi cu the, truyen vao 1 renderer cu the
      bool LoadImg(const std::string file_path, SDL_Renderer* des);
   //In ra man hinh p_object_
      void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
   //Don dep bo nho, goi ham nay thuc chat la su dung destructor
      void Free();

protected:
      //Toa do, kich co cua p_object_
      SDL_Rect rect_;

      //Img luu duoi dang texture cua p_object
      SDL_Texture* p_object_;
};

#endif
