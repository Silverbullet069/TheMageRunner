#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33

class ThreatObject : public BaseObject
{
public:
      //Constructor cua ThreatObject
      ThreatObject();

      //Destructor cua ThreatObject
      ~ThreatObject();

      //Ham copy ra renderer
      void HandleMove(const int& x_border, const int& y_border);

      //Ham xu ly di chuyen tu dong
      void HandleInputAction(SDL_Event events);

      //Ham set van toc theo phuong x va y
      void set_x_val(const int& val) {x_val_ = val;}
      void set_y_val(const int& val) {y_val_ = val;}

      //Ham get van toc theo phuong x va y
      int get_x_val() const {return x_val_ ;}
      int get_y_val() const {return y_val_ ;}

      //Ham set bang dan
      void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}

      //Ham get bang dan
      std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}

      //Ham khoi tao vien dan
      void InitAmo(AmoObject* p_amo);

      //Ham quan ly trang thai cua vien dan
      void MakeAmo(const int& x_limit, const int& y_limit);

      //Reset lai vi tri cua threat khi bi ban no
      void Reset(const int& x_border);

      //Reset lai vien dan cua threat
      void ResetAmo(AmoObject* p_amo);

private :
      //Van toc theo phuong x va y
      int x_val_;
      int y_val_;

      //Bang dan
      std::vector<AmoObject*> p_amo_list_;

};
#endif // THREAT_OBJECT_H_
