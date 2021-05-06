#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"

class Transform
{
    public:
        float X, Y; //Khai bao' 2 truong` co ban? la` toa. do^. X va` Y

    public:
        Transform(float x = 0, float y = 0): X(x), Y(y) {} //Constructor Transform

        //Ham` kiem? tra tinh' dung' dan'
        void Log(std::string mag = "")
        {
            std::cout<< mag << "(X Y) = (" << X << " " << Y << ")" << std::endl;
        }

    public:
        inline void TranslateX(float x) { X += x; } //Dich. toa. do^. X 1 khoang? = x
        inline void TranslateY(float y) { Y += y; } //Dich. toa. do^. Y 1 khoang? = y
        inline void Translate(Vector2D v) { X += v.X; Y += v.Y;} //Dich toa. do^. X va` Y theo 1 vector (hay dich. vector)
};

#endif // TRANSFORM_H
