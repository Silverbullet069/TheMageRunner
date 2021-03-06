#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseObject.h"
#include "SDL_ttf.h"
#include <string>

class TextObject : public BaseObject
{
public:
   enum TextColor
   {
      RED_TEXT = 0,
      WHITE_TEXT = 1,
      BLACK_TEXT = 2,
   };

   TextObject();
   ~TextObject();
   void SetText(const std::string& text) {str_val_ = text;}
   void SetColor(const int& type);
   //void HandleInputAction(SDL_Event events);
   void CreateGameText(TTF_Font* font, SDL_Renderer* des); //Da xu ly rect_.w va rect_.h

private:
   std::string str_val_;
   SDL_Color text_color_;
};

#endif // TEXT_OBJECT_H_
