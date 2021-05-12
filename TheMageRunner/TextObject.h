

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
   bool CreateSurfaceTextTotal(TTF_Font* font);
   bool LoadTextureTextType(TTF_Font* font, SDL_Renderer* des); //Su dung. doi voi TextObject ko co animation
   void Free();
   void SetPosXY(const int& xPos, const int& yPos) { text_type_pos_.x = xPos; text_type_pos_.y = yPos; }
   void RenderClear();
   void RenderText(SDL_Renderer* des,
                   SDL_Rect* clip = NULL,
                   double angle = 0.0,
                   SDL_Point* center = NULL,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
   void HandleInputActionByTime(SDL_Event& events);
   void RenderTypingAnimationByTime(SDL_Renderer* des, SDL_Event& events);

   void HandleInputActionByFrame(SDL_Event& events, bool& flag);
   void RenderTypingAnimationByFrame(SDL_Renderer* des, int& convo_order, bool is_auto, bool& flag_done);

   void SetColor(const SDL_Color& color) { text_color_ = color; }

   void SetTextType(const std::string& type_val) { str_text_type_ = type_val;}
   std::string GetTextType() const { return str_text_type_; }
   void SetTextTotal(const std::string& total_val) {str_text_total_ = total_val;}
   std::string GetTextTotal() const { return str_text_total_; }

   int get_total_width() const { return text_total_width_; }
   int get_total_height() const { return text_total_height_; }
   void set_text_delay(const int& textDelay) { text_delay_ = textDelay; }
   SDL_Rect GetRectType() const { return text_type_pos_; }

private:
   std::string str_text_type_;
   std::string str_text_total_;
   SDL_Color text_color_;
   SDL_Texture* p_txt_text_type_;
   SDL_Rect text_type_pos_;
   int text_total_width_;
   int text_total_height_;
   //bool is_active_;
   bool is_skip_;

   int tp_;
   int count_text_delay_;
   int text_delay_;
};
#endif // TEXT_OBJECT_H_
