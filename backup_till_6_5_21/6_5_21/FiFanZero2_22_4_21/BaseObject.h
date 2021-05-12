
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
public:
      BaseObject();
      ~BaseObject();
   //Khoi tao toa do x va y
      void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
   //Check load img tu 1 dia chi cu the, truyen vao 1 renderer, su dung virtual
      virtual bool LoadImg(const std::string& file_path, SDL_Renderer* des,
                           const int& color_flag, const SDL_Color& color);
   //In ra man hinh p_object_
      void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
   //Don dep bo nho, goi ham nay thuc chat la su dung destructor
      void Free();

   //Lay toa do x va y da khoi tao
      SDL_Rect GetRect() const {return rect_;}
   //Set object, texture lay ngoai class BaseObject
      void SetObject(SDL_Texture* texture) { p_object_ = texture; }
   /** Luu y, ham tren RAT DE THAT THOAT BO NHO, nhung trong game nay, ham nay chi dung de
   chuyen doi luan phien giua cac texture, tat game cac texture nay se bi huy di,
   vay nen khong gay ra that thoat **/
   //Lay object da khoi tao
      SDL_Texture* GetObject() const {return p_object_;}

protected:
      //Toa do, kich co cua p_object_
      SDL_Rect rect_;

      //Img luu duoi dang texture cua p_object
      SDL_Texture* p_object_;
};

#endif
