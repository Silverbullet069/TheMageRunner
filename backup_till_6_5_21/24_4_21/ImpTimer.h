
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

#include "CommonFunction.h"

class ImpTimer
{
public:
   ImpTimer();
   ~ImpTimer();

   //Cac trang thai cua dong ho, bat dau, dung, tam dung, huy tam dung
   void start();
   void stop();
   void paused();
   void unpaused();

   //Ham lay thoi gian
   int get_ticks();

   bool is_started() const {return is_started_;}
   bool is_paused() const {return is_paused_;}

private:
   int start_tick_; //Thoi gian khi dong ho bat dau chay
   int paused_tick_; //Thoi gian khi dong ho bat dau tam dung

   //Trang thai cua dong ho
   bool is_paused_;
   bool is_started_;
};

#endif // IMP_TIMER_H_
