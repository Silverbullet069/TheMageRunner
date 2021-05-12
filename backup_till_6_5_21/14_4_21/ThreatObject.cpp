#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
   //Set toa do ban dau tai bien man hinh ben phai
   rect_.x = SCREEN_WIDTH;
   rect_.y = SCREEN_HEIGHT*0.5;
   rect_.w = WIDTH_THREAT;
   rect_.h = HEIGHT_THREAT;

   //Van toc theo phuong x va y
   x_val_ = 0;
   y_val_ = 0;
}

ThreatObject::~ThreatObject()
{
   if(p_amo_list_.size() > 0)
   {
      for(int i = 0 ; i < p_amo_list_.size() ; ++i)
      {
         AmoObject* p_amo = p_amo_list_.at(i);
         if(p_amo != NULL)
         {
            delete p_amo;
            p_amo = NULL;
         }
      }
      p_amo_list_.clear();
   }
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
   if(p_amo != NULL)
   {
      bool ret = p_amo->LoadImg(g_name_bullet_threat);
      if(ret)
      {
         //Gan trang thai dan di chuyen la true
            p_amo->set_is_move(true);
         //Set kich co cua vien dan
            p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
         //Set loai dan
            p_amo->set_type(AmoObject::SPHERE);
         //Set vi tri vien dan duoc ban ra
            p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
         //Set van toc theo phuong x cua vien dan
            p_amo->set_x_val(VELOCITY_BULLET_THREAT);
         //Cho vien dan vao bang dan
            p_amo_list_.push_back(p_amo);
      }
   }
}

void ThreatObject::MakeAmo(const int& x_limit, const int& y_limit)
{
   for(int i = 0 ; i < p_amo_list_.size() ; ++i)
   {
      //Xet tung vien dan trong bang dan
      AmoObject* p_amo = p_amo_list_.at(i);
      if(p_amo != NULL)
      {
         //Vien dan dang di chuyen
         if(p_amo->get_is_move())
         {
            //Copy vien dan ra renderer
            p_amo->Show();
            //Thay doi toa do cua vien dan
            p_amo->HandleMoveRightToLeft();
         }
         //is_move_ false (vien dan da cham toi bien)
         else
         {
            //Tai su dung lai vien dan
            //Set trang thai di chuyen cua vien dan = true
            p_amo->set_is_move(true);
            //Set lai vi tri cua vien dan theo vi tri cua ThreatObject
            p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
         }
      }
   }
}

void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
      rect_.x -= x_val_; //-= la di chuyen tu phai sang trai , += trai sang phai
      if(rect_.x < 0)
      {
            //Sau khi di toi bien man hinh ben trai, no quay tro lai bien phai, thay vi XOA
            rect_.x = SCREEN_WIDTH;
            rect_.y = SDLCommonFunction::MakeRandValue();
      }
}

void ThreatObject::HandleInputAction(SDL_Event events)
{

}

void ThreatObject::Reset(const int& x_border)
{
   rect_.x = x_border;
   rect_.y = SDLCommonFunction::MakeRandValue();

   for(int i = 0 ; i < p_amo_list_.size(); ++i)
   {
      AmoObject* p_amo = p_amo_list_.at(i);
      if(p_amo != NULL)
      {
         ResetAmo(p_amo);
      }
   }
}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
   //Set vi tri vien dan duoc ban ra
   p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}
