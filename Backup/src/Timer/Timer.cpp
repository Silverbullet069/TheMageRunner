#include "Timer.h"
#include "SDL.h"

Timer* Timer::s_Instance = nullptr;

void Timer::Start()
{
   //Set trang thai chay = true
      m_IsStarted = true;
   //Set trang thai tam dung = false
      m_IsPaused = false;
   //Luu lai thoi gian chay
      m_StartTime = SDL_GetTicks();
}

void Timer::Paused()
{
   //Neu dong ho dang chay va khong bi tam dung
   if(m_IsStarted == true && m_IsPaused == false)
   {
      //Set trang thai tam dung = true
         m_IsPaused = true;
      //Thoi gian tam dung dong ho
      //Bang thoi diem chuong trinh dang chay
      //Tru di thoi diem dong ho bat dau chay
         m_IsPaused = SDL_GetTicks() - m_StartTime;
      //Reset lai start time
         m_StartTime = 0;
   }
}

void Timer::Unpaused()
{
    //Neu dong ho dang chay va bi tam dung
   if(m_IsStarted == true && m_IsPaused == true)
   {
      //Set trang thai tam dung = false
         m_IsPaused = false;
      //Thoi gian huy tam dung dong ho, coi nhu thoi gian chay dong ho
      //Bang thoi diem chuong trinh hien tai dang chay
      //Tru di thoi diem ke tu luc dong ho bat dau tam dung
         m_StartTime = SDL_GetTicks() - m_IsPaused;
      //Reset lai pause time
         m_IsPaused = 0;
   }
}

void Timer::Stop()
{
   //Set trang thai chay = false
      m_IsStarted = false;
   //Set trang thai tam dung = false
      m_IsPaused = false;
   //Set lai cac bien thoi gian
      m_StartTime = 0;
      m_IsPaused = 0;
}

void Timer::SetFPS(const int& fake_fps)
{
    //Neu dong ho dang chay
    if(m_IsStarted == true)
    {
        //Lay gia tri thoi diem chuong trinh hien tai dang chay
        //Tru di thoi diem chay dong ho
        int real_time_per_fr = SDL_GetTicks() - m_StartTime;
        static int fake_time_per_fr = 1000/fake_fps;
        if(real_time_per_fr < fake_time_per_fr)
        {
            SDL_Delay(fake_time_per_fr - real_time_per_fr);
        }

    }
}

int Timer::GetTicks()
{
    //Neu dong ho dang chay
    if(m_IsStarted == true)
    {
        //Neu dong ho dang chay va bi tam dung
        if(m_IsPaused == true)
        {
            //Lay gia tri thoi gian ke tu khi bi tam dung
            return m_IsPaused;
        }
        else
        {
            //Lay gia tri thoi diem chuong trinh hien tai dang chay
            //Tru di thoi diem chay dong ho
            return SDL_GetTicks() - m_StartTime;
        }
    }
    //Con khong, 0
    return 0;
}

