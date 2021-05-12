
#include "FairyObject.h"

FairyObject::FairyObject()
{
   p_txt_fairy_object_ = NULL;
   p_txt_fairy_fly_left_ = NULL;
   p_txt_fairy_fly_right_ = NULL;
   p_txt_fairy_fly_forward_ = NULL;
   p_txt_fairy_vanish_forward_ = NULL;
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
   is_active_ = false;
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

   p_txt_fairy_fly_forward_ = LoadTextureAndDimension(des, g_name_fairy_fly_forward, width_forward_, height_forward_);

   //p_txt_fairy_vanish_forward_ = LoadTextureAndDimension(des, g_name_fairy_vanish_forward, width_forward_, height_forward_);
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

void FairyObject::Show(SDL_Renderer* des)
{
   frame_++;

   if(frame_ >= FAIRY_FRAME_NUM)
   {
      frame_ = 0;
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

   }
}

void FairyObject::InitFairy()
{
   x_val_ = FAIRY_VELOCITY_X_VAL;
   y_val_ = FAIRY_VELOCITY_Y_VAL;
   is_move_ = true;
   is_active_ = true;
   status_ = FLY_LEFT;
   trajectory_ = SIN;
   this->ImpTypeMove();
}

void FairyObject::HandleInputAction(SDL_Event& events)
{
   while(SDL_PollEvent(&events))
   {
      //Quit game
      if(events.type == SDL_QUIT )
      {
         return;
      }
      if(events.type == SDL_MOUSEBUTTONDOWN)
      {
         if(events.button.button == SDL_BUTTON_LEFT)
         {
            /**
            static bool skip = true;
            if(skip == true)
            {
               x_val_ *= 10;
               y_val_ *= 10;
               skip = false;
            }
            **/
         }
      }
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
         is_move_ = false;
      }
   }
}

void FairyObject::InitConvo(SDL_Renderer* des, SDL_Event& events)
{
   if(is_move_ == false)
   {
      fairy_convo_.SetColor(WHITE);
      fairy_convo_.SetTextTotal("Greetings, explorer.");
      fairy_convo_.SetPosXY(this->rect_.x - 500, this->rect_.y + 500);
      fairy_convo_.RenderTypingAnimation(des, events);
   }
}
