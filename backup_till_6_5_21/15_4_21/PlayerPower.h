#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "BaseObject.h"
#include <vector>

const int LIFE_WIDTH = 40;
const int LIFE_HEIGHT = 40;

class PlayerPower : public BaseObject
{
public:
   PlayerPower();
   ~PlayerPower();
   //Set so luong mang
   void SetNumber(const int& num) {number_ = num;}
   //Set vi tri theo phuong x cua tung mang
   void AddPos(const int& x_pos);
   //Add cac vi tri cua tung mang
   void Init();
   //Render cac mang song con lai
   void Show(SDL_Renderer* des);
   //Giam so luong mang
   void Decrease();

private:
   //So mang
   int number_;

   //Vi tri cua tung hinh dai dien cho mang
   std::vector<int> pos_list_;

};
#endif // PLAYER_POWER_H_
