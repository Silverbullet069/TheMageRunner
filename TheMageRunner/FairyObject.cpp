
#include "FairyObject.h"

FairyObject::FairyObject()
{
   p_txt_fairy_object_ = NULL;
   p_txt_fairy_fly_left_ = NULL;
   p_txt_fairy_fly_right_ = NULL;
   p_txt_fairy_fly_forward_ = NULL;
   p_txt_fairy_vanish_forward_ = NULL;
   p_txt_fairy_idle_forward_ = NULL;
   p_frame_clip_object_ = NULL;
   p_frame_clip_side_ = NULL;
   p_frame_clip_forward_ = NULL;
   width_object_ = 0;
   height_object_ = 0;
   width_side_ = 0;
   height_side_ = 0;
   width_forward_ = 0;
   height_forward_ = 0;

   //x_pos_ = 0;
   //y_pos_ = 0;
   //map_x_ = 0;
   //map_y_ = 0;
   rect_.x = 0;
   rect_.y = 0;
   rect_.w = 0;
   rect_.h = 0;
   x_val_ = 0;
   y_val_ = 0;
   status_ = TOTAL_MOVE_TYPE;
   trajectory_ = TOTAL_TRAJECTORY;
   frame_ = 0;
   is_move_ = false;
   is_skip_move_ = false;
   is_active_ = false;
   is_convo_run_ = false;
   convo_order_ = 0;

   x_mouse_ = 0;
   y_mouse_ = 0;
   selected_yes_ = false;
   selected_no_ = false;
   is_set_ui_tutorial_ = false;

   is_in_intro_ = false;
   is_in_tutorial_ = false;
}

FairyObject::~FairyObject()
{
   if(p_txt_fairy_object_ != NULL)
   {
      SDL_DestroyTexture(p_txt_fairy_object_);
      p_txt_fairy_object_ = NULL;
   }

   if(p_txt_fairy_fly_left_ != NULL)
   {
      SDL_DestroyTexture(p_txt_fairy_fly_left_);
      p_txt_fairy_fly_left_ = NULL;
   }

   if(p_txt_fairy_fly_right_ != NULL)
   {
      SDL_DestroyTexture(p_txt_fairy_fly_right_);
      p_txt_fairy_fly_right_ = NULL;
   }

   if(p_txt_fairy_fly_forward_ != NULL)
   {
      SDL_DestroyTexture(p_txt_fairy_fly_forward_);
      p_txt_fairy_fly_forward_ = NULL;
   }

   if(p_txt_fairy_vanish_forward_ != NULL)
   {
      SDL_DestroyTexture(p_txt_fairy_vanish_forward_);
      p_txt_fairy_vanish_forward_ = NULL;
   }

   if(p_txt_fairy_idle_forward_ != NULL)
   {
      SDL_DestroyTexture(p_txt_fairy_idle_forward_);
      p_txt_fairy_idle_forward_ = NULL;
   }

   if(p_frame_clip_object_ != NULL)
   {
      delete []p_frame_clip_object_;
      p_frame_clip_object_ = NULL;
   }

   if(p_frame_clip_side_ != NULL)
   {
      delete []p_frame_clip_side_;
      p_frame_clip_side_ = NULL;
   }

   if(p_frame_clip_forward_ != NULL)
   {
      delete []p_frame_clip_object_;
      p_frame_clip_object_ = NULL;
   }

}

SDL_Texture* FairyObject::LoadTextureAndDimension(SDL_Renderer* des,
                                                  const std::string& file_path,
                                                  int& width, int& height)
{
   //Khoi tao texture rong~
   SDL_Texture* new_texture = NULL;

   //Load image vao surface tai 1 dia chi cu the
   SDL_Surface* loaded_surface = IMG_Load(file_path.c_str());

   //Neu surface load khong duoc
   if(loaded_surface == NULL)
   {
      printf( "Unable to load fairy surface %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError() );
   }
   else
   {
      new_texture = SDL_CreateTextureFromSurface(des, loaded_surface);

      if(new_texture == NULL)
      {
         printf( "Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError() );
      }
      else
      {
         //Set lai rect_
         width = loaded_surface->w/FAIRY_FRAME_NUM;
         height = loaded_surface->h;
      }
      //Huy surface cu
      SDL_FreeSurface(loaded_surface);
   }

   return new_texture;
}

void FairyObject::LoadAllFairyAction(SDL_Renderer* des)
{
   p_txt_fairy_fly_left_ = LoadTextureAndDimension(des, g_name_fairy_fly_left, width_side_, height_side_);

   p_txt_fairy_fly_right_ = LoadTextureAndDimension(des, g_name_fairy_fly_right, width_side_, height_side_);

   p_txt_fairy_idle_forward_ = LoadTextureAndDimension(des, g_name_fairy_idle_forward, width_forward_, height_forward_);
   //NOTE, this is wrong if you put width_forward_ and height_forward_ here cause our texture only got 1 frame
   //But it will be renew afterwards so don't mind.

   p_txt_fairy_fly_forward_ = LoadTextureAndDimension(des, g_name_fairy_fly_forward, width_forward_, height_forward_);

   p_txt_fairy_vanish_forward_ = LoadTextureAndDimension(des, g_name_fairy_vanish_forward, width_forward_, height_forward_);
}

void FairyObject::SetClipsEachAction()
{
   p_frame_clip_side_ = new SDL_Rect[FAIRY_FRAME_NUM];
   p_frame_clip_forward_ = new SDL_Rect[FAIRY_FRAME_NUM];
   for(int i = 0 ; i < FAIRY_FRAME_NUM ; ++i)
   {
      p_frame_clip_side_[i].x = i*width_side_;
      p_frame_clip_side_[i].y = 0;
      p_frame_clip_side_[i].w = width_side_;
      p_frame_clip_side_[i].h = height_side_;

      p_frame_clip_forward_[i].x = i*width_forward_;
      p_frame_clip_forward_[i].y = 0;
      p_frame_clip_forward_[i].w = width_forward_;
      p_frame_clip_forward_[i].h = height_forward_;
   }
}

void FairyObject::RenderClear(SDL_Renderer* des)
{
   ScreenEffect::RenderRectangle(des, rect_, BLACK);
}

void FairyObject::Show(SDL_Renderer* des)
{
   frame_++;

   if(frame_ >= FAIRY_FRAME_NUM)
   {
      frame_ = 0;
      if(status_ == VANISH_FORWARD)
      {
         is_active_ = false;
         return ;
      }
   }

   if(status_ == IDLE_FORWARD)
   {
      frame_ = 0; //Only one frame in IDLE_FORWARD texture
   }

   rect_.w = width_object_;
   rect_.h = height_object_;

   SDL_RenderCopy(des, p_txt_fairy_object_, (p_frame_clip_object_ + frame_), &rect_);
}

void FairyObject::ImpTypeMove()
{
   switch(status_)
   {
   case FLY_LEFT :
      {
         p_txt_fairy_object_ = p_txt_fairy_fly_left_;
         width_object_ = width_side_;
         height_object_ = height_side_;
         p_frame_clip_object_ = p_frame_clip_side_;
      }
      break;

   case FLY_RIGHT :
      {
         p_txt_fairy_object_ = p_txt_fairy_fly_right_;
         width_object_ = width_side_;
         height_object_ = height_side_;
         p_frame_clip_object_ = p_frame_clip_side_;
      }
      break;

   case FLY_FORWARD :
      {
         p_txt_fairy_object_ = p_txt_fairy_fly_forward_;
         width_object_ = width_forward_;
         height_object_ = height_forward_;
         p_frame_clip_object_ = p_frame_clip_forward_;
      }
      break;

   case VANISH_FORWARD :
      {
         p_txt_fairy_object_ = p_txt_fairy_vanish_forward_;
         width_object_ = width_forward_;
         height_object_ = height_forward_;
         p_frame_clip_object_ = p_frame_clip_forward_;
      }
      break;
   case IDLE_FORWARD :
      {
         p_txt_fairy_object_ = p_txt_fairy_idle_forward_;
         width_object_ = width_forward_;
         height_object_ = height_forward_;
         p_frame_clip_object_ = p_frame_clip_forward_;
      }
   }
}

void FairyObject::InitFairyIntro()
{
   x_val_ = FAIRY_VELOCITY_X_VAL;
   y_val_ = FAIRY_VELOCITY_Y_VAL;
   is_move_ = true;
   is_active_ = true;
   is_in_intro_ = true;
   status_ = FLY_LEFT;
   trajectory_ = SIN;
   this->ImpTypeMove();
}

void FairyObject::InitFairyTutorial()
{
   x_val_ = 0;
   y_val_ = 0;
   is_active_ = true;
   is_in_tutorial_ = true;
   status_ = IDLE_FORWARD;
   this->ImpTypeMove();
}

void FairyObject::HandleInputAction(SDL_Event& events)
{
   //Quit game
   switch(events.type)
   {
      case SDL_QUIT :
         return ;

      case SDL_MOUSEBUTTONDOWN :
         {
            if(events.button.button == SDL_BUTTON_LEFT)
            {
               if(is_skip_move_ == false && is_move_ == true && is_in_intro_ == true)
               {
                  x_val_ *= 3;
                  y_val_ *= 3;
                  is_skip_move_ = true;
               }

               if(is_convo_run_ == true && is_in_intro_ == true)
               {
                  x_mouse_ = events.motion.x;
                  y_mouse_ = events.motion.y;

                  if(SDLCommonFunction::CheckFocusWithRect(x_mouse_, y_mouse_, UI_tutorial_yes_.GetRectType()))
                  {
                     selected_yes_ = true;
                     status_ = VANISH_FORWARD;
                     this->ImpTypeMove();
                     frame_ = -1;

                  }
                  if(SDLCommonFunction::CheckFocusWithRect(x_mouse_, y_mouse_, UI_tutorial_no_.GetRectType()))
                  {
                     selected_no_ = true;
                     status_ = VANISH_FORWARD;
                     this->ImpTypeMove();
                     frame_ = -1;
                  }
               }

               if(is_convo_run_ == true && is_in_tutorial_ == true)
               {
                  is_convo_run_ == false;
               }
            }
         }
         break;

      case SDL_MOUSEMOTION :
         {
            if(is_convo_run_ == true)
            {
               x_mouse_ = events.motion.x;
               y_mouse_ = events.motion.y;

               if(SDLCommonFunction::CheckFocusWithRect(x_mouse_, y_mouse_, UI_tutorial_yes_.GetRectType()))
               {
                  UI_tutorial_yes_.SetColor(RED);
               }
               else
               {
                  UI_tutorial_yes_.SetColor(WHITE);
               }

               if(SDLCommonFunction::CheckFocusWithRect(x_mouse_, y_mouse_, UI_tutorial_no_.GetRectType()))
               {
                  UI_tutorial_no_.SetColor(RED);
               }
               else
               {
                  UI_tutorial_no_.SetColor(WHITE);
               }
            }
         }
         break;

   }
}

void FairyObject::HandleMove()
{
   if(trajectory_ == SIN)
   {
      static int x_sin = SCREEN_WIDTH; //Vi tri ban dau` la sat' le` ben phai?
      if(-width_object_ <= x_sin && x_sin <= SCREEN_WIDTH)
      {
         //-width la` de fairy tao hieu ung di chuyen qua' le` ben trai'
         rect_.x = x_sin;
         rect_.y = (int)Graph::CalSin(x_sin);
         x_sin -= x_val_;
      }
      else
      {
         trajectory_ = COS;
         status_ = FLY_RIGHT;
         this->ImpTypeMove();
      }
   }

   if(trajectory_ == COS)
   {
      static int x_cos = -width_object_;
      if(-width_object_ <= x_cos && x_cos <= SCREEN_WIDTH)
      {
         //Tuong tu
         rect_.x = x_cos;
         rect_.y = (int)Graph::CalCos(x_cos);
         x_cos += x_val_;
      }
      else
      {
         trajectory_ = STRAIGHT_DOWN;
         status_ = FLY_FORWARD;
         this->ImpTypeMove();
      }
   }

   if(trajectory_ == STRAIGHT_DOWN)
   {
      static int x_strg_down = (SCREEN_WIDTH - width_object_)/2; // Chinh' giua~ theo phuong x
      static int y_strg_down = -height_object_; //qua' le` ben tren^
      if(-height_object_ <= y_strg_down && y_strg_down <= (SCREEN_HEIGHT - width_object_)/2) //Chinh' giua~ theo phuong y
      {
         rect_.x = x_strg_down;
         rect_.y = y_strg_down;
         y_strg_down += y_val_;
      }
      else
      {
         if(is_move_ == true)
         {
            is_move_ = false;
            is_convo_run_ = true;
            convo_order_ = 0;
         }
      }
   }
}

void FairyObject::SetBreakBetweenConvo()
{
   //if(is_done_convo_[1] == true && is_set_convo_[2] == false)
   //{
   //   is_convo_run_ = false;
   //}
   if(is_done_convo_[2] == true && is_set_convo_[3] == false)
   {
      is_convo_run_ = false;
   }
   else if(is_done_convo_[3] == true && is_set_convo_[4] == false)
   {
      is_convo_run_ = false;
   }
   else if(is_done_convo_[5] == true && is_set_convo_[6] == false)
   {
      is_convo_run_ = false;
   }
}


void FairyObject::FreezeScreenToConvo(SDL_Renderer* des)
{
   ScreenEffect::BlurScreenNoClick(des);
   this->SetRect(6*TILE_SIZE, 6*TILE_SIZE);
   this->Show(des);
   is_convo_run_ = true;
}

void FairyObject::HandleConvoIntro(SDL_Renderer* des)
{
   if(is_convo_run_ == true)
   {
      switch(convo_order_)
      {
      case 0:
      {
         if(is_set_convo_[0] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("Greetings, traveler.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY((SCREEN_WIDTH - fairy_convo_.get_total_width())/2 , this->rect_.y + 2*TEXT_SPACING);
            is_set_convo_[0] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, true, is_done_convo_[0]);
      }
         break;

      case 1:
      {
         if(is_set_convo_[1] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("My name is Lylia. I will guide you though your adventrue.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY((SCREEN_WIDTH - fairy_convo_.get_total_width())/2, this->rect_.y + 3*TEXT_SPACING);
            is_set_convo_[1] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, true, is_done_convo_[1]);
      }
         break;

      case 2:
      {
         if(is_set_convo_[2] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("Let's go through the basics. Do you want to enter tutorials ?");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            is_set_convo_[2] = true;
         }
         fairy_convo_.SetPosXY((SCREEN_WIDTH - fairy_convo_.get_total_width())/2, this->rect_.y + 4*TEXT_SPACING);
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, true, is_done_convo_[2]);
      }
         break;

      default :
      {
         if(is_set_ui_tutorial_ == false)
         {
            UI_tutorial_yes_.SetColor(WHITE);
            UI_tutorial_yes_.SetTextType("YES");
            UI_tutorial_yes_.SetPosXY(this->rect_.x - 200, this->rect_.y + 5*TEXT_SPACING);
            UI_tutorial_no_.SetColor(WHITE);
            UI_tutorial_no_.SetTextType("NO");
            UI_tutorial_no_.SetPosXY(this->rect_.x + 400, this->rect_.y + 5*TEXT_SPACING);
            is_set_ui_tutorial_ = true;
         }

         UI_tutorial_yes_.LoadTextureTextType(g_font_text, des);
         UI_tutorial_yes_.RenderText(des);

         UI_tutorial_no_.LoadTextureTextType(g_font_text, des);
         UI_tutorial_no_.RenderText(des);
      }
         break;
      }
   }
}

void FairyObject::HandleConvoTutorial(SDL_Renderer* des)
{
   if(is_convo_run_ == true)
   {
      switch(convo_order_)
      {
      case 0:
      {
         if(is_set_convo_[0] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("This is you, a mage suffers from amnesia.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY(this->rect_.x + width_object_, this->rect_.y);
            is_set_convo_[0] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, false, is_done_convo_[0]);
      }
         break;

      case 1:
      {
         if(is_set_convo_[1] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("OK, first let's try to move.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY(this->rect_.x + width_object_, this->rect_.y + TEXT_SPACING);
            is_set_convo_[1] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, false, is_done_convo_[1]);
      }
         break;

      case 2:
      {
         if(is_set_convo_[2] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("Press A to walk left.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY(this->rect_.x + width_object_, this->rect_.y + TEXT_SPACING*2);
            is_set_convo_[2] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, false, is_done_convo_[2]);
      }
         break;

      case 3:
      {
         if(is_set_convo_[3] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("Good, now press D to walk right.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY(this->rect_.x + width_object_, this->rect_.y);
            is_set_convo_[3] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, false, is_done_convo_[3]);
      }
         break;

      case 4:
      {
         if(is_set_convo_[4] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("Perfect, on to the next.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY(this->rect_.x + width_object_, this->rect_.y);
            is_set_convo_[4] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, false, is_done_convo_[4]);
      }
         break;

      case 5 :
      {
         if(is_set_convo_[5] == false)
         {
            fairy_convo_.SetColor(WHITE);
            fairy_convo_.SetTextTotal("Move to middle to exit tutorial.");
            fairy_convo_.CreateSurfaceTextTotal(g_font_text);
            fairy_convo_.SetPosXY(this->rect_.x + width_object_, this->rect_.y + TEXT_SPACING);
            is_set_convo_[5] = true;
         }
         fairy_convo_.RenderTypingAnimationByFrame(des, convo_order_, false, is_done_convo_[5]);
      }

      default :
         break;
      }
   }
}
