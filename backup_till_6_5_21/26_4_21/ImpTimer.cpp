#include "ImpTimer.h"
#include "CommonFunction.h"

ImpTimer::ImpTimer()
{
   start_tick_ = 0;
   paused_tick_ = 0;

   is_paused_ = false;
   is_started_ = false;

}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
   //Set trang thai chay = true
      is_started_ = true;
   //Set trang thai tam dung = false
      is_paused_ = false;
   //Luu lai thoi gian chay
      start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop()
{
   //Set trang thai chay = false
      is_started_ = false;
   //Set trang thai tam dung = false
      is_paused_ = false;
   //Set lai cac bien thoi gian
      start_tick_ = 0;
      paused_tick_ = 0;
}

//Tam dung dong ho
void ImpTimer::paused()
{
   //Neu dong ho dang chay va khong bi tam dung
   if(is_started_ == true && is_paused_ == false)
   {
      //Set trang thai tam dung = true
         is_paused_ = true;
      //Thoi gian tam dung dong ho
      //Bang thoi diem chuong trinh dang chay
      //Tru di thoi diem dong ho bat dau chay
         paused_tick_ = SDL_GetTicks() - start_tick_;
      //Reset lai start time
         start_tick_ = 0;
   }
}

//Huy tam dung dong ho
void ImpTimer::unpaused()
{
   //Neu dong ho dang chay va bi tam dung
   if(is_started_ == true && is_paused_ == true)
   {
      //Set trang thai tam dung = false
         is_paused_ = false;
      //Thoi gian huy tam dung dong ho, coi nhu thoi gian chay dong ho
      //Bang thoi diem chuong trinh hien tai dang chay
      //Tru di thoi diem ke tu luc dong ho bat dau tam dung
         start_tick_ = SDL_GetTicks() - paused_tick_;
      //Reset lai pause time
         paused_tick_ = 0;
   }
}

int ImpTimer::get_ticks()
{
   //Neu dong ho dang chay
   if(is_started_ == true)
   {
      //Neu dong ho dang chay va bi tam dung
      if(is_paused_ == true)
      {
         //Lay gia tri thoi gian ke tu khi bi tam dung
         return paused_tick_;
      }
      else
      {
         //Lay gia tri thoi diem chuong trinh hien tai dang chay
         //Tru di thoi diem chay dong ho
         return SDL_GetTicks() - start_tick_;
      }
   }
   //Con khong, 0
   return 0;
}
