#include "AmoObject.h"

AmoObject::AmoObject()
{
      //Khoi tao cac gia tri
      rect_.x = 0;
      rect_.y = 0;
      x_val_ = 0;
      y_val_ = 0;
      is_move_ = false;
      amo_type_ = NONE;

      //Khoi tao width va height cua vien dan tai ham SetWidthHeight
}

AmoObject::~AmoObject()
{

}

void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
      //Xet truong hop chi ban theo duong thang(theo chieu x), tu trai sang phai
      if (is_move_ == true)
      {
            rect_.x += x_val_;
            if (rect_.x > x_border)
            {
                  is_move_ = false;
            }
      }
}

void AmoObject::HandleMoveRightToLeft()
{
      //Xet truong hop chi ban theo duong thang(theo chieu x), tu phai sang trai
      rect_.x -= x_val_;
      if(rect_.x < 0)
      {
            is_move_ = false;
      }

}

void AmoObject::HandleInputAction(SDL_Event events)
{
      //Todo
}
