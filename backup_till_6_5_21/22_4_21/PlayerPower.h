
#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "BaseObject.h"

class PlayerPower : public BaseObject
{
public:
   PlayerPower();
   ~PlayerPower();
   void SetNum(const int& num) {number_ = num;}
   void AddPos(const int& xPos);
   void Init(SDL_Renderer* des);
   void Show(SDL_Renderer* des);
   void IncreaseNum();
   void DecreaseNum();

private:
   int number_;
   std::vector<int> pos_list_;
};

class PlayerMoney : public BaseObject
{
public:
   PlayerMoney();
   ~PlayerMoney();

   void Init(SDL_Renderer* des);
   void Show(SDL_Renderer* des);
   void SetPos(const int& xPos, const int& yPos) {x_pos_ = xPos; y_pos_ = yPos;}

private:
   int x_pos_;
   int y_pos_;
};


#endif // PLAYER_POWER_H_
