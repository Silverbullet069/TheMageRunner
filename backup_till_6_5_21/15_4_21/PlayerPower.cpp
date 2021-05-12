#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
   number_ = 0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& x_pos)
{
   pos_list_.push_back(x_pos);
}

void PlayerPower::Show(SDL_Renderer* des)
{
   if(number_ == pos_list_.size())
   {
      for(int i = 0 ; i < pos_list_.size() ; ++i)
      {
         rect_.x = pos_list_.at(i);
         Render(des);
      }
   }
}

void PlayerPower::Init()
{
   number_ = 3;
   if(pos_list_.size() > 0)
   {
      //Sau khi game over, ta phai xoa het pos_list_ di de the hien lai tu dau
      pos_list_.clear();
   }
   AddPos(20);
   AddPos(60);
   AddPos(100);
}

void PlayerPower::Decrease()
{
   number_--;
   pos_list_.pop_back();
}
