#include "MainObject.h"

MainObject::MainObject()
{
   //Khoi tao cac gia tri toa do va van toc
   rect_.x = 0;
   rect_.y = 0;
   rect_.w = WIDTH_MAIN_OBJECT;
   rect_.h = HEIGHT_MAIN_OBJECT;
   x_val_ = 0;
   y_val_ = 0;
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events)
{
   //Giu phim
   if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
   {
      switch (events.key.keysym.sym)
      {
         case SDLK_w: y_val_ -= VELOCITY_MAIN; break;
         case SDLK_s: y_val_ += VELOCITY_MAIN; break;
         case SDLK_a: x_val_ -= VELOCITY_MAIN; break;
         case SDLK_d: x_val_ += VELOCITY_MAIN; break;
      }
   }
   //Nha phim
   else if (events.type == SDL_KEYUP && events.key.repeat == 0)
   {
      switch(events.key.keysym.sym )
      {
         case SDLK_w: y_val_ += VELOCITY_MAIN; break;
         case SDLK_s: y_val_ -= VELOCITY_MAIN; break;
         case SDLK_a: x_val_ += VELOCITY_MAIN; break;
         case SDLK_d: x_val_ -= VELOCITY_MAIN; break;
      }
   }
   //Chuot bam xuong
   else if (events.type == SDL_MOUSEBUTTONDOWN)
   {
      //Cap phat bo nho cho vien dan moi
      AmoObject* p_amo = new AmoObject();

      //Chuot trai
      if (events.button.button == SDL_BUTTON_LEFT)
      {
         //InitAmo
         //Set kich co cua dan Laser
         p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);

         //Load and cua dan Laser
         p_amo->LoadImg(g_name_bullet_main_laser);

         //Set loai cua dan - Laser
         p_amo->set_type(AmoObject::LASER);

         //Tao audio cua dan Laser
         Mix_PlayChannel(-1, g_sound_bullet_laser, 0);
      }
      //Chuot phai
      else if (events.button.button == SDL_BUTTON_RIGHT)
      {
         //InitAmo
         //Set kich co cua dan Tron
         p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);

         //Load anh cua dan Tron
         p_amo->LoadImg(g_name_bullet_main_sphere);

         //Set loai cua dan - Sphere
         p_amo->set_type(AmoObject::SPHERE);

         //Tao audio cua dan Sphere
         Mix_PlayChannel(-1, g_sound_bullet_sphere, 0);
      }

      //Set vi tri cua vien dan theo vi tri cua nhan vat
         p_amo->SetRect(this->rect_.x + this->rect_.w - 30, this->rect_.y + this->rect_.h*0.75 );
      //Set trang thai di chuyen la true
         p_amo->set_is_move(true);
      //Set van toc theo phuong x cua vien dan
         p_amo->set_x_val(VELOCITY_BULLET_MAIN);
      //Luu vien dan vao trong p_amo_list, co the duoc lay bang GetAmoList() - duoc dung trong ham main
         p_amo_list_.push_back(p_amo);

   }
   else if (events.type == SDL_MOUSEBUTTONUP)
   {
      ;//
   }
   else
   {
      ;//
   }
}

void MainObject::MakeAmo()
{
   for (int i = 0; i < p_amo_list_.size(); ++i)
   {
      AmoObject* p_amo = p_amo_list_.at(i);
      if (p_amo != NULL)
      {
         if (p_amo->get_is_move())
         {
            //Border o day la khung man hinh, phan biet voi threats
            p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

            //Hien thi vien dan len man hinh
            p_amo->Show();
         }
      }
      else //Move false (hoac la chua bam chuot, hoac la vien dan di qua gioi han khung man hinh)
      {
         if (p_amo != NULL)
         {
            //Xoa vien dan khoi p_amo_list, p_amo_list_ mat 1 phan tu
            p_amo_list_.erase(p_amo_list_.begin() + i);

            //Huy vien dan
            delete p_amo;
            p_amo = NULL;
         }
      }
   }
}

void MainObject::HandleMove()
{
   //Di chuyen nhan vat trai/ phai
   rect_.x += x_val_; //mPosX += mVelX

   //Neu nhan vat di chuyen sat bien trai/phai
   if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
   {
      rect_.x -= x_val_;
   }

   //Di chuyen nhan vat len/xuong
   rect_.y += y_val_; //mPosY += mVelY

   //Neu nhan vat di chuyen sat bien tren/duoi
   if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - UNDER_LIMIT)
   //- UNDER_LIMIT de khong cham vao mat dat
   {
      rect_.y -= y_val_;
   }
}

void MainObject::RemoveAmo(const int& idx)
{
   //Khi bam chuot p_amo_list_ cap nhat lien tuc
   //for(int i = 0 ; i < p_amo_list_.size() ; ++i)
   //{

      if(idx < p_amo_list_.size())
      {
         AmoObject* p_amo = p_amo_list_.at(idx);
         p_amo_list_.erase(p_amo_list_.begin() + idx);
         if(p_amo != NULL)
         {
            delete p_amo;
            p_amo = NULL;
         }
      }

   //}
}

/**
Ham MakeAmo o trong main loop

                  for (int i = 0; i < plane_object.GetAmoList().size(); ++i)
                  {
                        //amo_list la trung gian de tac dong vao p_amo_list_
                        std::vector<AmoObject*> amo_list = plane_object.GetAmoList();
                        AmoObject* p_amo = amo_list.at(i);

                        if (p_amo != NULL)
                        {
                              if (p_amo->get_is_move())
                              {
                                    //Border o day la khung man hinh, phan biet voi threats
                                    p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

                                    //Hien thi vien dan len man hinh
                                    p_amo->Show();
                              }
                        }
                        else //Move false (hoac la chua bam chuot, hoac la vien dan di qua gioi han khung man hinh)
                        {
                              if (p_amo != NULL)
                              {
                                    //Xoa vien dan khoi amo_list, amo_list mat 1 phan tu
                                    amo_list.erase(amo_list.begin() + i);

                                    //Set lai amo_list, vi amo_list da mat 1 phan tu
                                    plane_object.SetAmoList(amo_list);

                                    //Huy vien dan
                                    delete p_amo;
                                    p_amo = NULL;
                              }
                        }
                  }
**/
