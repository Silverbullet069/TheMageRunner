#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

//Component
//Ve^ co? ban? thi` day^ la` Component quan? ly' ve^` Luc.

class Vector2D
{
    public:
        float X, Y; //Khai bao' 2 truong` co ban? la` toa. do^. X va` Y

    public:
        Vector2D(float x = 0, float y = 0): X(x), Y(y) {} //Constructor Vector2D

    public:
        //Ham` + toa. do^. cua? 2 vector
        inline Vector2D operator+(const Vector2D& v2) const { return Vector2D(X + v2.X, Y + v2.Y); }

        //Ham` - toa. do^. cua? 2 vector
        inline Vector2D operator-(const Vector2D& v2) const { return Vector2D(X - v2.X, Y - v2.Y); }

        //Ham` scale toa. do^. cua? 1 vector voi' 1 luong. cho truoc'
        inline Vector2D operator*(const float scalar) const { return Vector2D(X*scalar, Y*scalar); }

        //Ham` kiem? tra tinh' dung' dan'
        void Log(std::string mag = "")
        {
            std::cout<< mag << "(X Y) = (" << X << " " << Y << ")" << std::endl;
        }
};

#endif // VECTOR2D_H
