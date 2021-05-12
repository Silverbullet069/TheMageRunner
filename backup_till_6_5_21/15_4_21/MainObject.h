#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

const int WIDTH_MAIN_OBJECT = 77;
const int HEIGHT_MAIN_OBJECT = 52;

class MainObject : public BaseObject
{
public:
   //Constructor cua MainObject
   MainObject();

   //Destructor cua MainObject
   ~MainObject();

   //Ham xu ly di chuyen duoc nhap tu ban phim va chuot
   void HandleInputAction(SDL_Event events, SDL_Renderer* des);

   //Ham in ra man hinh
   void HandleMove();

   //AmoObject la mot TRUONG cua MainObject => Nhan vat mang theo dan ben minh
   //AmoObject duoc xu ly ben trong MainObject.cpp
   void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
   std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}

   //Ham quan ly trang thai cua vien dan
   void MakeAmo(SDL_Renderer* des);

   //Ham xoa vien dan trung muc tieu
   void RemoveAmo(const int& idx);

private:
      //Van toc theo phuong x va y
      int x_val_;
      int y_val_;

      //List dan duoc
      std::vector<AmoObject*> p_amo_list_;
};


#endif //MAIN_OBJECT_H_
