#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BaseObject.h"

#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

class AmoObject : public BaseObject
{
public:
      //Khoi tao 2 loai dan (bao gom ca NONE)
      enum AmoType
      {
            NONE = 0,
            LASER = 1,
            SPHERE = 2
      };
      //Constructor cua AmoObject
      AmoObject();

      //Destructor cua AmoObject
      ~AmoObject();

      //Ham xu ly di chuyen duoc nhap tu ban phim va chuot
      void HandleInputAction(SDL_Event events);

      //Ham thay doi toa do vien dan ban ra tu trai sang phai
      void HandleMove(const int& x_border, const int& y_border);

      //Ham thay doi toa do vien dan ban ra tu phai sang trai
      void HandleMoveRightToLeft();

      //Ham set van toc theo phuong x va y
      void set_x_val(const int& val) {x_val_ = val;}
      void set_y_val(const int& val) {y_val_ = val;}

      //Ham get van toc theo phuong x va y
      int get_x_val() const {return x_val_ ;}
      int get_y_val() const {return y_val_ ;}

      //Ham get loai dan
      int get_type() const {return amo_type_;}

      //Ham set loai dan
      void set_type(const int& type) {amo_type_ = type;}

      //Ham kiem tra dan co di chuyen khong
      bool get_is_move() const {return is_move_;}

      //Ham set trang thai di chuyen cua vien dan
      void set_is_move(bool is_move) {is_move_ = is_move;}

      //Ham khoi tao kich co cua TUNG LOAI vien dan
      void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;}

private:
      //Van toc cua vien dan theo phuong x va y
      int x_val_;
      int y_val_;

      //Loai dan
      int amo_type_;

      //flag di chuyen vien dan
      bool is_move_;

};

#endif
