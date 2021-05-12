#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common_Function.h"

class BaseObject
{
public:
      //Constructor cua BaseObject
      BaseObject();

      //Destructor cua BaseObject
      ~BaseObject();

      //In ra man hinh p_object_
      void Show();

      //Kiem tra load anh thanh cong tu 1 dia chi cu the
      bool LoadImg(std::string file_path);

      //Khoi tao toa do x va y
      void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}

      //Lay toa do x va y da khoi tao
      SDL_Rect GetRect() const {return rect_;}

      //Lay object da khoi tao
      SDL_Texture* GetObject() const {return p_object_;}

protected:
      //Toa do, kich co cua p_object_
      SDL_Rect rect_;

      //Img luu duoi dang texture cua p_object
      SDL_Texture* p_object_;
};

#endif
