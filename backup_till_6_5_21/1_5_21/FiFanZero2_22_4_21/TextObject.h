

#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunction.h"
//Khong include BaseObject vi ham TextObject khong xu ly hinh anh

class TextObject
{
public:
   TextObject();
   ~TextObject();

   enum TextColor
   {
      RED_TEXT = 0,
      WHITE_TEXT = 1,
      BLACK_TEXT = 2,
   };

   //bool LoadFromFile(const std::string file_path);
   bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* des);
   void Free();

   void SetColor(const Uint8& red, const Uint8& green, const Uint8& blue);
   void SetColorType(const int& colorType);

   void RenderText(SDL_Renderer* des,
                   const int& xp, const int& yp,
                   SDL_Rect* clip = NULL,
                   double angle = 0.0,
                   SDL_Point* center = NULL,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
   int GetWidth() const {return width_;}
   int GetHeight() const {return height_;}

   void SetText(const std::string& text) {str_val_ = text;}
   std::string GetText() const {return str_val_;}


private:
   std::string str_val_;
   SDL_Color text_color_;
   SDL_Texture* texture_;
   int width_;
   int height_;

};
#endif // TEXT_OBJECT_H_
