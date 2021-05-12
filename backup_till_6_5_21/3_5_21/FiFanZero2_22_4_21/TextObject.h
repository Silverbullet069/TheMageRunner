

#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunction.h"
//Khong include BaseObject vi ham TextObject khong xu ly hinh anh

class TextObject
{
public:
   TextObject();
   ~TextObject();

   //bool LoadFromFile(const std::string file_path);
   //Tao surface tu string chu~, sau do tao. texture tu` surface
   bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* des);
   void Free();
   void SetPosXY(const int& xPos, const int& yPos) { text_pos_.x = xPos; text_pos_.y = yPos; }
   void RenderText(SDL_Renderer* des,
                   SDL_Rect* clip = NULL,
                   double angle = 0.0,
                   SDL_Point* center = NULL,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
   void HandleInputAction(SDL_Event& events);
   void RenderTypingAnimation(SDL_Renderer* des, SDL_Event& events);

   void SetColor(const SDL_Color& color) { text_color_ = color; }

   void SetTextType(const std::string& type_val) { str_text_type_ = type_val;}
   std::string GetTextType() const { return str_text_type_; }
   void SetTextTotal(const std::string& total_val) {str_text_total_ = total_val;}
   std::string GetTextTotal() const { return str_text_total_; }

private:
   std::string str_text_type_;
   std::string str_text_total_;
   SDL_Color text_color_;
   SDL_Texture* texture_;
   SDL_Rect text_pos_;
   //bool is_active_;
   bool is_skip_;
   bool is_done_;
   bool is_active_;

};
#endif // TEXT_OBJECT_H_
