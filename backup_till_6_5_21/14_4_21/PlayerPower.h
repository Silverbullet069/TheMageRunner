#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "BaseObject.h"
#include <vector>

#define LIFE_WIDTH 40
#define LIFE_HEIGHT 40

class PlayerPower : public BaseObject
{
public:
   PlayerPower();
   ~PlayerPower();
   void SetNumber(const int& num) {number_ = num;}
   void AddPos(const int& x_pos);
   //Show cac mang song con lai
   void Render();
   //Load anh va add cac vi tri cua tung mang
   void Init();
   //Giam so luong mang
   void Decrease();

private:
   //So mang
   int number_;

   //Vi tri cua tung hinh dai dien cho mang
   std::vector<int> pos_list_;

};
#endif // PLAYER_POWER_H_
