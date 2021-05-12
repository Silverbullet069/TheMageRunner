
#include "ElementaryFunctions.h"

float Graph::CalSin(const int& x_rad) //x here is rad
{
   float new_x_rad = x_rad;
   while(new_x_rad >= 0)
   {
      new_x_rad -= 2*PI/abs(SIN_FACTOR_A);
   }
   int n = 0;
   float sin_taylor_last_frac = 1;
   bool is_minus = false;
   float sin_taylor_ans = 0;
   float ans = 0;

   while(abs(sin_taylor_last_frac) > EPSILON_SIN)
   {
      if((n&1) == 0) //n%2==0
      {
         is_minus = false;
      }
      else
      {
         is_minus = true;
      }

      sin_taylor_last_frac = 1; //Reset
      for(int i = 1 ; i <= 2*n + 1 ; ++i)
      {
         sin_taylor_last_frac *= (SIN_FACTOR_A*new_x_rad + SIN_FACTOR_B) / i;
      }
      if(is_minus == true)
      {
         sin_taylor_last_frac *= (-1);
      }

      sin_taylor_ans += sin_taylor_last_frac;
      n++;
   }

   ans = SIN_FACTOR_K*sin_taylor_ans + SIN_FACTOR_C;
   return ans;
}

float Graph::CalCos(const int& x_rad) //x here is rad
{
   float new_x_rad = x_rad;
   while(new_x_rad >= 0)
   {
      new_x_rad -= 2*PI/abs(COS_FACTOR_A);
   }
   int n = 0;
   float cos_taylor_last_frac = 1;
   bool is_minus = false;
   float cos_taylor_ans = 0;
   float ans = 0;

   while(abs(cos_taylor_last_frac) > EPSILON_COS)
   {
      if((n&1) == 0) //n%2==0
      {
         is_minus = false;
      }
      else
      {
         is_minus = true;
      }

      cos_taylor_last_frac = 1; //Reset
      for(int i = 1 ; i <= 2*n; ++i)
      {
         cos_taylor_last_frac *= (COS_FACTOR_A*new_x_rad + COS_FACTOR_B) / i;
      }
      if(is_minus == true)
      {
         cos_taylor_last_frac *= (-1);
      }

      cos_taylor_ans += cos_taylor_last_frac;
      n++;
   }

   ans = COS_FACTOR_K*cos_taylor_ans + COS_FACTOR_C;
   return ans;
}
