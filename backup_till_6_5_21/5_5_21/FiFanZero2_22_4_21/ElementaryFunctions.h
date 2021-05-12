
#ifndef ELEMENTARY_FUNCTIONS_H_
#define ELEMENTARY_FUNCTIONS_H_

#include "CommonFunction.h"

struct Factor
{
   Factor(float k, float a, float b, float c)
   {
      k_ = k;
      a_ = a;
      b_ = b;
      c_ = c;
   }
   float k_;
   float a_;
   float b_;
   float c_;
   // Trigonometric Functino : y = k.sin(a.x + b) + c
};

class Graph
{
public:
   //For now, dont use Factor in here
   static float CalSin(const int& x_rad);
   static float CalCos(const int& x_rad);
};
#endif // ELEMENTARY_FUNCTIONS_H_
