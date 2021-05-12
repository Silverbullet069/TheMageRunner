
#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
   number_ = 0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& xPos)
{
   pos_list_.push_back(xPos);
}

void PlayerPower::Init(SDL_Renderer* des)
{
   bool ret = LoadImg("player_power.png", des);
   if(!ret) { printf("Unable to load player power!"); }
   else
   {
      number_ = 3;
      if(pos_list_.size() > 0)
      {
         pos_list_.clear();
      }
      //fix cung
      AddPos(20);
      AddPos(60);
      AddPos(100);
   }
}

void PlayerPower::Show(SDL_Renderer* des)
{
   for(int i = 0 ; i < pos_list_.size() ; ++i)
   {
      rect_.x = pos_list_.at(i);
      rect_.y = 0;
      Render(des);
   }
}

void PlayerPower::IncreaseNum()
{
   number_++;
   int last_pos = pos_list_.back();
   last_pos += 40;
   pos_list_.push_back(last_pos);
}

void PlayerPower::DecreaseNum()
{
   number_--;
   pos_list_.pop_back();
}

PlayerMoney::PlayerMoney()
{
   x_pos_ = 0;
   y_pos_ = 0;
}

PlayerMoney::~PlayerMoney()
{
   //
}

void PlayerMoney::Init(SDL_Renderer* des)
{
   bool ret = LoadImg("money.png", des);
   if(!ret) {printf("Unable to load player money!");}
   else
   {
      SetPos(SCREEN_WIDTH*0.5 - 300, 10);
   }
}

void PlayerMoney::Show(SDL_Renderer* des)
{
   rect_.x = x_pos_;
   rect_.y = y_pos_;
   Render(des);
}
